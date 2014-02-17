#ifndef COM_SOWROV_OTOCODER_GLOBALS_H_
#define COM_SOWROV_OTOCODER_GLOBALS_H_
#include <string>
static std::string BASE_URL = "http://community.topcoder.com/tc";
//&class=
static std::string SEARCH_URL = "http://community.topcoder.com/tc?module=ProblemArchive";
//&pm=??&rd=??
static std::string PROBLEM_DETAIL_URL = "http://community.topcoder.com/tc?module=ProblemDetail";
//&pm=??
static std::string PROBLEM_STATEMENT_URL = "http://community.topcoder.com/stat?c=problem_statement";
//&cr=??&rd=??&pm=??
static std::string PROBLEM_SOLUTION_URL = "http://community.topcoder.com/stat?c=problem_solution";

class Globals {
public:
    

    Globals() {
    }

    static std::string getBaseUrl(){
        return BASE_URL;
    }

    static std::string getSearchUrl(char* query) {
        return SEARCH_URL+"&class="+query;
    }

    static std::string getSearchUrl(const std::string& query) {
        return SEARCH_URL+"&sd=asc&class="+query;
    }

    static std::string getProblemStatementUrl(const std::string& problemId){
        return PROBLEM_STATEMENT_URL+"&pm="+problemId;
    }

    static std::string getSolutionPageUrl(const std::string& problemId, const std::string& roundId, const std::string& codeId) {
        return PROBLEM_SOLUTION_URL+"&cr="+codeId+"&rd="+roundId+"&pm="+problemId;
    }

    static std::string getDetailPageUrl(const std::string& problemId, const std::string& roundId) {
        return PROBLEM_DETAIL_URL +"&rd="+roundId+"&pm="+problemId;
    }
};
#endif