#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

#include <com/sowrov/util/logsystem/ChronicleLogger.h>
#include <com/sowrov/util/StringTokenizer.h>
#include <com/sowrov/otocoder/http/PageDownloader.h>
#include <com/sowrov/otocoder/parser/TcHtmlParser.h>
#include <com/sowrov/otocoder/Problem.h>
#include <com/sowrov/util/MiscellaneousMethods.h>
#include <com/sowrov/otocoder/codegen/CppCode.h>
#include "globals.h"
#include "argvparser.h"
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#include <direct.h>
#else
#include <unistd.h>
#endif

using namespace CommandLineProcessing;
//login to server
//download the search page
//parse the page to get className, problemId, roundId
//download problem description
//parse problem description and prepare Method
//download problem detail page
//get codeId
//download full test page
//parse and gen full test cases
//generate initial code and input-output file
std::string USER, PASS;

std::string getAPage(PageDownloader &pageDownloader, std::string url, bool mustHave=true) {
    std::string pageText = "";
    int totalTry=0;
    while (totalTry++<3) {
        _CLogDebug("Try "<<totalTry<<": Get url -> "+url);
        pageText = pageDownloader.getPage(url);
        if (pageText.compare("")!=0) {//not zero, means pageText has content
            _CLogDebug("Got response text of length: "<<pageText.length());
            break;
        }
    }
    if (totalTry<0) {
        if (mustHave) {
            _CLogFatal("Could not download "+url+", a must have page, exiting");
            exit(-1);
        } else {
            _CLogCritical("Could not download "+url);
            return "";
        }
    }
    if (pageText.find("Sorry, there was an error in your request.")!=std::string::npos) {
        _CLogCritical("Wrong url requested! url: "+url);
        if (mustHave) {
            _CLogFatal("Could not download must have page, exiting");
            exit(-1);
        } else {
            return "";
        }
    }
    return pageText;
}

std::string load_file ( const std::string& path ) {
    std::ostringstream contents;
    std::ifstream file(path.c_str());
    if ( !file.is_open() ) {
        // process error.
    }
    contents << file.rdbuf();
    return (contents.str());
}

int collectProblemData(PageDownloader& pageDownloader, TcHtmlParser& htmlParser, Problem& problem, std::string className) {
    std::string pageText;
    //1. Init
    if (!pageDownloader.init(NULL) ) {
        exit(-1);
    }
    //2. login
    int totalTry=3;
    while(totalTry-- && !pageDownloader.tcServerLogin(USER,PASS)) {
        _CLogDebug("Failed attempt to login: "+totalTry);
    }

    if (totalTry<0) {
        _CLogFatal("Failed to login to the server");
        exit(-1);
    }
    _CLogInfo("Successfully logged in to the server.");
    
    //3. search the class using query word: http://community.topcoder.com/tc?module=ProblemArchive&class=Time
    //   collect problemId and roundId
    pageText = getAPage(pageDownloader, Globals::getSearchUrl(className));
    std::vector<ProblemInfo> problemList = htmlParser.parseProblemInfoSearch(pageText, className);

    if (problemList.empty()) {
        _CLogFatal("Parser was unable to parse the search page or search result was empty. Please try again.");
        exit(-1);
    }
    int problemIndex = 0;
    if (problemList.size()>1) {
        std::cout<<"Search returned multiple problems:"<<std::endl;
        for (int i=0; i<problemList.size(); i++) {
            std::cout<<i<<". "<<problemList.at(i).getClassName()<<" "<<problemList.at(i).getContestName()<<std::endl;
        }
        std::cout<<"Please select the right one:"<<std::endl;
        while(true) {
            std::cin>>problemIndex;
            if (problemIndex>-1 && problemIndex<problemList.size()) {
                break;
            } else {
                std::cout<<"Please enter a proper index number:"<<std::endl;
            }
        }
    }
    problem.setProblemInfo(problemList.at(problemIndex));
    if (problem.getProblemId().empty() || problem.getRoundId().empty()) {
        _CLogFatal("Parser was unable to parse the search page. Please try again.");
        exit(-1);
    }
    _CLogInfo("Found the problem: "+problem.getClassName());

    //4. get problem statement 
    pageText = getAPage(pageDownloader, Globals::getProblemStatementUrl(problem.getProblemId()));
    if (!htmlParser.parseProblemDescription(pageText, problem)) {
        _CLogFatal("Parser was unable to download/parse problem description. Please try again.");
        exit(-1);
    }
    
    //rd=15501&pm=12588
    //problem.setProblemId(std::string("12588"));
    //problem.setRoundId(std::string("15501"));
    //5. get the problem detail page to get fastest solver (coder) Id
    pageText = getAPage(pageDownloader, Globals::getDetailPageUrl(problem.getProblemId(), problem.getRoundId()));
    if (!htmlParser.parseProblemDetails(pageText, problem) || problem.getCoderId().empty()) {
        _CLogWarning("No way to get full test cases from web!");
    } else {
        //6. get full test cases
        pageText = getAPage(pageDownloader, Globals::getSolutionPageUrl(problem.getProblemId(), problem.getRoundId(), problem.getCoderId()));
        if (!htmlParser.parseProblemTestset(pageText, problem)) {
            _CLogWarning("Failed to get Full test set!");
        } else {
            _CLogInfo("Successfully downloaded full test set.");
        }
    }
}

bool isFileExist(std::string name) {
    std::ifstream ifs(name.c_str());
    return ifs.good();
}

// Get current date/time, format is YYYY-MM-DD HH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

    return buf;
}

void setStdinEcho(bool enable = true) {
#ifdef WIN32 
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode; GetConsoleMode(hStdin, &mode); 
    if( !enable ) mode &= ~ENABLE_ECHO_INPUT;
    else mode |= ENABLE_ECHO_INPUT; SetConsoleMode(hStdin, mode ); 
#else 
    struct termios tty; 
    tcgetattr(STDIN_FILENO, &tty); 
    if( !enable ) tty.c_lflag &= ~ECHO; 
    else tty.c_lflag |= ECHO; 
    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif 
}

int main(int argc, char* argv[]) {
    std::string str = "";
    PageDownloader pageDownloader;
    Problem problem;
    TcHtmlParser htmlParser;
    std::string pageText;
    _CLsetLevel(4);
    ArgvParser cmd;
    int overWriteDuplicate=-1;
    // init
    cmd.setIntroductoryDescription("Otocoder - Search, Download, Parse, Generate Initial Code and full test set.");

    cmd.setHelpOption("h", "help", "Print this help page");

    cmd.defineOption("verbose", "Be verbose", ArgvParser::NoOptionAttribute);
    cmd.defineOptionAlternative("verbose","v");

    cmd.defineOption("overwrite", "Overwrite on duplicate (default is 'Ask what to do')? [y/n]", ArgvParser::OptionRequiresValue);
    cmd.defineOptionAlternative("overwrite","w");

    cmd.defineOption("dir", "Directory in which problem data will be generated.", ArgvParser::OptionRequiresValue);
    cmd.defineOptionAlternative("dir","d");

    cmd.defineOption("user", "User name", ArgvParser::OptionRequiresValue);
    cmd.defineOptionAlternative("user","u");
    cmd.defineOption("password", "User Password", ArgvParser::OptionRequiresValue);
    cmd.defineOptionAlternative("password","p");
    
    // finally parse and handle return codes (display help etc...)
    int result = cmd.parse(argc, argv);

    if (result != ArgvParser::NoParserError) {
        std::cout << cmd.parseErrorDescription(result);
        exit(1);
    }
    
    // now query the parsing results
    if (cmd.foundOption("v")) {
        _CLsetLevel(5);
    }

    //user name
    if (cmd.foundOption("u")) {
        USER = cmd.optionValue("u");
    }

    //password
    if (cmd.foundOption("p")) {
        PASS = cmd.optionValue("p");
    }

    if (cmd.foundOption("w")) {
        char ch = cmd.optionValue("w")[0];
        overWriteDuplicate = (ch=='y'||ch=='Y')?1:0;
    }

    std::string dir="./";

    if (cmd.foundOption("d")) {
        dir = cmd.optionValue("d");
    }

    _CLogDebug("Otocoder has started");

    str = "";
    str += dir;
    int systemResponse = chdir(str.c_str());

    if (cmd.arguments()>0) {
        str = cmd.argument(0);
    } else {
        _CLogCritical("You must provide a ProblemName as argument");
        return -1;
    }

    while (USER.empty()) {
        std::cout<<"TC user name: ";
        std::cin>>USER;
        PASS="";
    }

    while (PASS.empty()) {
        std::cout<<"Password: ";
        setStdinEcho(false);
        std::cin>>PASS;
        setStdinEcho();
    }

    collectProblemData(pageDownloader, htmlParser, problem, str);

    str = "mkdir ";
    str += problem.getClassName();
    systemResponse = system(str.c_str());

    std::string path = problem.getClassName()+"/"+problem.getClassName();//path
    bool createCpp = overWriteDuplicate==0?false:true;
    if (isFileExist(path+".cpp") && overWriteDuplicate==-1) {
        std::cout<<"A code file already exist, do you want to overwrite? [y/n] ";
        char ch;
        std::cin>>ch;
        if (!(ch=='y' || ch=='Y')) {
            createCpp = false;
        }
    }
    std::ofstream ofs;
    //write problem statement file
    ofs.open((path+".txt").c_str());
    ofs<<problem.getProblemStatement()<<std::endl;
    ofs<<"Problem Authod: "<<problem.getWriterName()<<std::endl;
    ofs<<"Contest name: "<<problem.getContestName()<<std::endl;
    ofs.close();

    //write full test set
    ofs.open((path+".io").c_str());
    problem.writeFullTest(ofs);
    ofs.close();

    // generate code
    if (createCpp) {
        CppCode cppCode;
        std::string theCode = cppCode.generateCode(problem);
        std::ofstream codeFs;
        codeFs.open((path+".cpp").c_str());
        codeFs<<theCode;
        codeFs.close();
    } else {
        _CLogDebug("Will not create a "+path+".cpp file");
    }

    if (createCpp || !isFileExist(path+".st")) {
        //generate state file
        ofs.open((path+".st").c_str());
        ofs<<problem.getClassName()<<std::endl;
        ofs<<problem.getProblemCategory()<<std::endl;
        ofs<<problem.getProblemInfo()->getLevel()<<std::endl;
        ofs<<problem.getProblemInfo()->getBestTime()<<std::endl;
        ofs<<problem.getProblemInfo()->getAverageTime()<<std::endl;
        ofs<<currentDateTime()<<std::endl; //start time
        ofs.close();
    }

    return 0;
}

int main1(int argc, char* argv[]) {
    std::ofstream ofs("EllysNewNickname/EllysNewNickname.st", std::ios_base::app);
    ofs<<time(0)<<std::endl;
    ofs.close();
    return 0;
}
