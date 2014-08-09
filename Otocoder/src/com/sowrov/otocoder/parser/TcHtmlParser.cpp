#include "TcHtmlParser.h"


TcHtmlParser::TcHtmlParser(void) {
}


TcHtmlParser::~TcHtmlParser(void) {
}

void TcHtmlParser::trim(std::string& str){
    int s,e,len;
    len=str.length();
    s=0;e=len-1;
    while (s<len && (com::sowrov::util::StringUtil::isSpace(str[s]) || str[s]>255)) {
        s++;
    }
    while (e>-1 && (com::sowrov::util::StringUtil::isSpace(str[e]) || str[e]>255)) {
        e--;
    }
    if (s>e) {
        str = "";
    }
    else if (!(s==0 && e==len-1)){
        str = str.substr(s,e-s+1);
    }
}

std::string TcHtmlParser::extractId(std::string& str, std::string query) {
    size_t p1 = str.find(query);
    if (p1!=std::string::npos) {
        p1 += query.size();
        size_t p2 = str.find("&", p1);
        return str.substr(p1, p2-p1).c_str();
    }
    return "";
}

std::string TcHtmlParser::getLineAfter(const std::string& text, const std::string& query, size_t& lastPos) {
	size_t pos1;
	std::string str = "";
	bool gotEnd = false;
	while (true) {
		pos1 = text.find(query, lastPos) + query.length();
		if (pos1 == std::string::npos) {
			_CLogCritical("Could not find '" + query + "' word!");
			return "";
		}
		lastPos = text.find('\n', pos1 + 1);
		if (lastPos == std::string::npos) {
			lastPos = text.length() - 1;
			gotEnd = true;
		}
		str = text.substr(pos1, lastPos - pos1 + 1);
		this->trim(str);
		if (!str.empty() || gotEnd) {
			break;
		}
	}
	return str;
}

bool TcHtmlParser::parseVariable(std::string& str, Variable& var) {
    var.setArray(false);
    int len = str.length();
    if (str[len-1]==']') {
        var.setArray(true);
        str[len-2] = ' '; str[len-1] = ' ';
    } else if (str[len-1]=='>') {
        var.setArray(true);
        str[len-1]=' ';
        int i=0;
        while(str[i]!='<'){str[i++]=' ';}
        str[i]=' ';
    }
    this->trim(str);
    if (str.empty()) {
        _CLogCritical("Could not parse variable info");
        return false;
    }
    var.setDataType(str);
    return true;
}

bool TcHtmlParser::parseMethodDefinition(const std::string& problemStatement, size_t& lastPos, Problem& problem) {
    Method method;
    Variable variable;
    com::sowrov::util::StringTokenizer *strTok;
    //--
    std::string str;
    std::string tmpStr = this->getLineAfter(problemStatement, "Class:", lastPos);
    problem.setClassName(tmpStr);

    tmpStr = this->getLineAfter(problemStatement, "Method:", lastPos);
    method.setName(tmpStr);
    //---
    tmpStr = this->getLineAfter(problemStatement, "Parameters:", lastPos);
    strTok = new com::sowrov::util::StringTokenizer(tmpStr, ",");
    while (strTok->hasMoreTokens()) {
        str = strTok->nextToken();
        if (this->parseVariable(str, variable)) {
            method.addParameterVariable(variable);
        }
    }
    //----
    tmpStr = this->getLineAfter(problemStatement, "Returns:", lastPos);
    this->parseVariable(tmpStr, variable);
    variable.setName("expected_"); //Name for the return variable
    method.setReturnVariable(variable);
    //-----
    tmpStr = this->getLineAfter(problemStatement, "signature:", lastPos);
    strTok = new com::sowrov::util::StringTokenizer(tmpStr, ",)");
    int i=0;
    while (strTok->hasMoreTokens()) {
        str = strTok->nextToken();
        str = str.substr(str.find_last_of(' ')+1);
        method.getParameterAt(i)->setName(str);
        i++;
    }
    if (method.getNumberOfParameters()==0 || method.getNumberOfParameters()!=i) {
        _CLogCritical("Something went wrong on method description parsing.");
        return false;
    }
    problem.setMethod(method);
    return true;
}

bool TcHtmlParser::readSingleVariableValue(const std::string& problemStatement, Variable* variable, size_t& lastPos, VariableValue& varVal, bool keepStrQuote=true) {
    varVal.clear();
    std::string tmpStr, str;
    size_t pos, pos2;
    if (variable->isArray()) {
        pos = problemStatement.find('{', lastPos);
        pos2 = problemStatement.find('}', pos+1);
        if (pos==std::string::npos || pos2==std::string::npos) {
            return false;
        }
        tmpStr = problemStatement.substr(pos+1, pos2-pos-1); //do not copy '{' and '}'
        lastPos = pos2+1; //move the pointer next to '}'
        if (variable->getDataType()=="STRING") {
            pos2 = -1;
            while (true) {
                //in case of string there will be always two quotation '"' marks
                pos = tmpStr.find('"', pos2+1);
                if (pos==std::string::npos) {
                    //this is not error because we assume array size is as long as we find a quotation mark
                    break;
                }
                pos2 = tmpStr.find('"', pos+1);
                if (pos2==std::string::npos) {
                    _CLogWarning("Input string read error "+tmpStr);
                    break;
                }
                if (keepStrQuote) {
                    str = tmpStr.substr(pos, pos2-pos+1);
                } else {
                    str = tmpStr.substr(pos+1, pos2-pos-1);
                }
                
                varVal.addData(str);
            }
        } else {
            com::sowrov::util::StringTokenizer strTok(tmpStr, ", \n\t\r");
            while(strTok.hasMoreTokens()) {
                varVal.addData(strTok.nextToken());
            }
        }
    } else {
        str = this->getLineAfter(problemStatement, "", lastPos);
        if (!keepStrQuote && variable->getDataType()=="STRING") {
            pos = str.find('"', 0);
            pos2 = str.find('"', pos+1);
            str = str.substr(pos+1, pos2-pos-1);
        }
        varVal.addData(str);
    }
    return true;
}

bool TcHtmlParser::parseSampleTestcases(const std::string& problemStatement, size_t& lastPos, Problem &problem) {
    VariableValue varVal;
    Method* method;
    TestData testCase;
    std::stringstream ssi;
    int testNo = 0, varCount;
    std::string tmpStr, str;
    lastPos = problemStatement.find("Examples", lastPos);
    method = problem.getMethod();
    varCount = method->getNumberOfParameters();
    while(lastPos!=std::string::npos) {
        ssi.clear();
        testCase.clear();
        ssi <<testNo;
        ssi >> tmpStr;
        tmpStr = '\n'+tmpStr;
        tmpStr += ")"; //0)
        lastPos = problemStatement.find(tmpStr, lastPos);
        if (lastPos!=std::string::npos) {
            lastPos += tmpStr.length();
            for (int i=0; i<varCount; i++) {
                if (this->readSingleVariableValue(problemStatement, method->getParameterAt(i), lastPos, varVal)) {
                    testCase.addInput(varVal);
                } else {
                    _CLogCritical("Could not read parameter: "+i);
                }
            }
            tmpStr = "Returns:";
            lastPos = problemStatement.find(tmpStr, lastPos);
            if (lastPos==std::string::npos) {
                _CLogCritical("Could not find return value for case: "+testNo);
                break;
            }
            lastPos += tmpStr.length();
            if (this->readSingleVariableValue(problemStatement, method->getReturnVariable(), lastPos, varVal)) {
                testCase.setOutputValue(varVal);
            } else {
                _CLogCritical("Could not read return value for case: "+testNo);
            }
            problem.addSampleTestCase(testCase);
        }
        testNo++;
    }
    return true;
}

std::string TcHtmlParser::extractProblemStatement(std::string& problemPage) {
    bool beginOfNode = true;
    bool noMoreChild = false;
    bool problemStatementBegan = false;
    bool problemStatementBegan2 = false;
    bool printedALine = false;
    std::string text, problemStatement="";
    htmlDocPtr doc = htmlReadMemory(problemPage.c_str(), problemPage.size(), "", "utf8", HTML_PARSE_RECOVER|HTML_PARSE_NOERROR);

    xmlXPathContext *xpathCtx = xmlXPathNewContext( doc );
    xmlChar* xpathExpr = BAD_CAST "//td[@class='problemText']";
    xmlXPathObject * xpathObj = xmlXPathEval( xpathExpr, xpathCtx );
    xmlNode *currentNode=NULL;
    int depth;
    if (xpathObj->nodesetval->nodeNr>0) { //number of nodes greater than 0
        currentNode=xpathObj->nodesetval->nodeTab[0];
        currentNode=currentNode->children; //table of the problem statement.
        if (currentNode!=NULL && strcmp((char*)currentNode->name, "table")!=0) {
            currentNode = currentNode->next;
        }
        depth=1;
        while (currentNode && depth) {
            // output node if it is an element
            if (beginOfNode && currentNode->type == XML_TEXT_NODE) {
                text = (char *)currentNode->content;
                this->trim(text);
                if (problemStatementBegan) {
                    if(!text.empty()) {
                        printedALine = true;
                        problemStatement += text;
                        //printf("%s", text.c_str());
                    }
                } else if (!problemStatementBegan) {
                    //trim(text);
                    if (text.find("Problem Statement") != std::string::npos) {
                        problemStatementBegan = true;
                        printedALine = true;
                        problemStatement = text; //beginning problem statement
                    }
                }
            } else if (problemStatementBegan && !beginOfNode && currentNode->type == XML_ELEMENT_NODE) {
                char fc = currentNode->name[0];
                char sc = currentNode->name[1];

                if (printedALine && ((fc=='h') || (fc=='p') || (fc=='t' && (sc =='r' || sc == 'a')) || (fc=='d'))) {
                    printedALine = false;
                    problemStatement += "\n\n";
                    //printf("\n\n");
                } else if (fc=='t' && sc=='d' && printedALine) {
                    problemStatement += "  ";
                    //printf("  ");
                }
            }

            if (!noMoreChild && currentNode->children) {
                currentNode = currentNode->children;
                beginOfNode = true;
                depth++;
            }
            else if (currentNode->next) {
                currentNode = currentNode->next;
                beginOfNode = true;
                noMoreChild = false;
            }
            else {
                currentNode = currentNode->parent;
                beginOfNode = false; // avoid going to siblings or children
                noMoreChild = true;
                depth--;
            }
        }
    } else {
        _CLogCritical("Problem statement not found");
        return "";
    }

    
    return problemStatement;
}

std::vector<ProblemInfo> TcHtmlParser::parseProblemInfoSearch(std::string& searchPage, std::string classname) {
    htmlDocPtr doc;
    doc = htmlReadMemory(searchPage.c_str(), searchPage.size(), "", "utf8", HTML_PARSE_RECOVER|HTML_PARSE_NOERROR);
    //doc = htmlParseDoc((xmlChar*)searchPage.c_str(), "utf8");
    classname = com::sowrov::util::StringUtil::toLowerCase(classname);
    xmlXPathContext *xpathCtx = xmlXPathNewContext( doc ); 
    std::string tmpStr;

    xmlChar* xpathExpr = BAD_CAST "//a[starts-with(@href,'/stat?c=problem_statement')]";
    xmlXPathObject * xpathObj = xmlXPathEval( xpathExpr, xpathCtx );
    xmlNode *node=NULL;
    int i, parseError=0;
    std::vector<ProblemInfo> problemList;
    ProblemInfo singleProblem;
    if (xpathObj->nodesetval->nodeNr>0) { //number of nodes greater than 0
        for (int p=0; p<xpathObj->nodesetval->nodeNr; p++) {
            node = xpathObj->nodesetval->nodeTab[p];
            node = node->parent;
            singleProblem.setLevel("");
            i=0;
            parseError = 1;
            while(node != NULL && i<10) {
                parseError = 0;
                if (i==0||i==1||i==3) {
                    if (node->children != NULL && strcmp((char*)node->children->name,  "a") == 0) {
                        tmpStr = (char*)node->children->children->content; //a->text->content
                    } else if (node->children->next != NULL && strcmp((char*)node->children->next->name, "a")==0) {
                        tmpStr = (char*)node->children->next->children->content;
                    } else {
                        parseError=1;
                        tmpStr ="";
                    }
                    
                    this->trim(tmpStr);
                    if (i==0) {
                        if (parseError) {
                            _CLogWarning("Class name not found on search result");
                            break;
                        }
                        singleProblem.setClassName(tmpStr);
                    } else if (i==1) {
                        if (parseError) {
                            _CLogDebug("Contest name not found on search result");
                        }
                        singleProblem.setContestName(tmpStr);
                    } else if (i==3) {
                        if (parseError) {
                            _CLogDebug("Problem writer name not found on search result");
                        }
                        singleProblem.setWriterName(tmpStr);
                    }
                } else if (i==4) { //category
                    if (node->children != NULL) {
                        tmpStr = (char*)node->children->content;
                    } else {
                        _CLogDebug("Problem category not found on search result");
                        tmpStr="";
                    }
                    this->trim(tmpStr);
                    singleProblem.setCategory(tmpStr);
                } else if (i==5 || i==7) { //level
                    if (node->children != NULL) {
                        tmpStr = (char*)node->children->content;
                    } else {
                        //_CLogDebug("Problem category not found on search result");
                        tmpStr="";
                    }
                    this->trim(tmpStr);
                    if (!tmpStr.empty()) {
                        if (i==5) {
                            tmpStr = "D1L"+tmpStr;
                        } else {
                            tmpStr = "D2L"+tmpStr;
                        }
                        singleProblem.setLevel(tmpStr);
                    }
                }
                else if (i==9) {
                    if (node->children != NULL && strcmp((char*)node->children->name, "a")==0) {
                        //td->a->properties->text->content
                        tmpStr = (char*)node->children->properties->children->content; //get the detail url
                    } else if (node->children->next != NULL && strcmp((char*)node->children->next->name, "a")==0) {
                        //td->text->a->properties->text->content
                        tmpStr = (char*)node->children->next->properties->children->content; //get the detail url
                    } else {
                        _CLogWarning("Got error on parsing problem and contest ids in search result");
                        parseError=1;
                        break;
                    }
                    singleProblem.setRoundId(extractId(tmpStr, "rd="));
                    singleProblem.setProblemId(extractId(tmpStr, "pm="));
                }
                i++;
                node = node->next;
                if (strcmp((char*)node->name, "td") !=0) { //maybe we hit text node
                    node = node->next;
                }
            }
            if (!parseError) {
                tmpStr = com::sowrov::util::StringUtil::toLowerCase(singleProblem.getClassName());
                if (tmpStr==classname) { //exact match
                    _CLogDebug("Found exact match of the Problem");
                    problemList.clear();
                    problemList.push_back(singleProblem);
                    break;
                }
                _CLogDebug("Found Problem: "+singleProblem.getClassName());
                problemList.push_back(singleProblem);
            }
        }
    } else {
        _CLogCritical("Search query did not return any result");
    }
    return problemList;
}

bool TcHtmlParser::parseProblemDescription(std::string& problemPage, Problem& problem) {
    problem.setProblemStatement(this->extractProblemStatement(problemPage));
    size_t currentPos=0; //initial read pointer
    if (!this->parseMethodDefinition(problem.getProblemStatement(), currentPos, problem)) {
        _CLogCritical("Could not parse method definition properly");
        return false;
    }
    if (!this->parseSampleTestcases(problem.getProblemStatement(), currentPos, problem)) {
        _CLogCritical("Could not parse sample test cases properly");
        return false;
    }
    return true;
}

bool TcHtmlParser::parseProblemTestset(std::string& solutionPage, Problem& p) {
    htmlDocPtr doc = htmlReadMemory(solutionPage.c_str(), solutionPage.size(), "", "utf8", HTML_PARSE_RECOVER|HTML_PARSE_NOERROR);

    xmlXPathContext *xpathCtx = xmlXPathNewContext( doc );
    xmlChar* xpathExpr = BAD_CAST "//tr[@valign='top']";
    xmlXPathObject * xpathObj = xmlXPathEval( xpathExpr, xpathCtx );
    xmlNode *currentNode=NULL;

    Method* method = p.getMethod();
    VariableValue varVal;
    Variable* var;
    TestData testData;
    std::string inputStr, outputStr, tmpStr;
    bool parseError=false;
    for (int i=0; i<xpathObj->nodesetval->nodeNr; i++) {
        currentNode = xpathObj->nodesetval->nodeTab[i];
                        //tr ->     td->   td
        currentNode = currentNode->children->next;
        if (currentNode!=NULL && strcmp((char*)currentNode->name, "td")!=0) {
            //tr ->     td->   text -> td
            currentNode = currentNode->next;
        }
        if (currentNode!=NULL  && strcmp((char*)currentNode->name, "td")==0) {
            inputStr = (char*)currentNode->children->content;
        } else {
            parseError = true;
        }
        
                           //td -> text-> td -> text -> td 
        //go to 2nd td from currentNode
        int k=0;
        while(k++<2) {
            currentNode = currentNode->next;
            if (currentNode!=NULL && strcmp((char*)currentNode->name, "text")==0) {
                currentNode = currentNode->next;
            }
        }

        if (currentNode!=NULL  && strcmp((char*)currentNode->name, "td")==0) {
            outputStr = (char*) currentNode->children->content;
        } else {
            parseError = true;
        }
        
        if(!parseError) {
            //lets parse the input case
            testData.clear();
            size_t lastPos = 0, pos, pos2; //lastPos of inputStr
            for (int j=0; j<method->getNumberOfParameters(); j++) {
                varVal.clear();
                var = method->getParameterAt(j);
                if (var->isArray()) {
                    pos = inputStr.find("{", lastPos);
                    pos2 = inputStr.find("}", pos+1);
                    if (pos2 == std::string::npos) {
                        _CLogWarning("Full testcase parser didn't find the end of an array {}");
                        pos2 = inputStr.length()-1;
                    }
                    lastPos = inputStr.find(",", pos2);
                } else {
                    pos = lastPos;
                    pos2 = inputStr.find(",", pos+1);
                    lastPos = pos2;
                    if (pos2 == std::string::npos) {
                        pos2 = inputStr.length()-1;
                    } else {
                        pos2--; //we do not need the comma
                    }
                }
                tmpStr = inputStr.substr(pos, pos2-pos+1);
                pos = 0; //after creating tmpStr, pos is always 0
                this->readSingleVariableValue(tmpStr, var, pos, varVal, false);
                if (lastPos != std::string::npos) {
                    lastPos++;
                }
                testData.addInput(varVal);
            }
            //read the output
            lastPos=0;
            varVal.clear();
            this->readSingleVariableValue(outputStr, method->getReturnVariable(), lastPos, varVal, false);
            testData.setOutputValue(varVal);
            p.addTestCase(testData);
        }
    }
    return true;
}

std::string TcHtmlParser::findBestTime(xmlNode* aTag) {
    xmlNode * node=aTag;
    if (node) node = node->parent; //td
    if (node) node = node->parent; //tr
    if (node) node = node->prev; //tr 1 up
    if (node) node = node->prev; //tr 2 up
    if (node) node = node->children; //td Best Time
    if (node) {
        //td -> text -> td
        while(node->next->next != NULL) {
            node = node->next->next;
        }
        std::string bestTime = (char*)node->children->content;
        this->trim(bestTime);
        return bestTime;
    }
    return "";
}

std::string TcHtmlParser::findAverageTime(xmlNode* aTag) {
    xmlNode * node=aTag;
    if (node) node = node->parent; //td
    if (node) node = node->parent; //tr
    if (node) node = node->next; //tr 1 down
    if (node) node = node->children; //td Average Correct Time
    if (node) {
        //td -> text -> td
        while(node->next->next != NULL) {
            node = node->next->next;
        }
        std::string averageTime = (char*)node->children->content;
        this->trim(averageTime);
        return averageTime;
    }
    return "";
}

//ToDo: test this method with problem: TopView 
bool TcHtmlParser::parseProblemDetails(std::string& problemDetailPage, Problem& problem) {
    htmlDocPtr doc;
    doc = htmlReadMemory(problemDetailPage.c_str(), problemDetailPage.size(), "", "utf8", HTML_PARSE_RECOVER|HTML_PARSE_NOERROR);
    
    xmlXPathContext *xpathCtx = xmlXPathNewContext( doc ); 
    std::string coderId;

    xmlChar* xpathExpr = BAD_CAST "//a[starts-with(@href,'\/stat?c=problem_solution')]";
    xmlXPathObject * xpathObj = xmlXPathEval( xpathExpr, xpathCtx );
    xmlNode *node=NULL;

    if (xpathObj->nodesetval->nodeNr>0) {
        for (int i=0; i<xpathObj->nodesetval->nodeNr; i++) {
            node = xpathObj->nodesetval->nodeTab[i];
            //a->properties->text->content
            coderId = (char*)node->properties->children->content;
            coderId = extractId(coderId, "cr=");
            if (!coderId.empty()) {
                problem.setCoderId(coderId);
                problem.getProblemInfo()->setBestTime(this->findBestTime(node));
                problem.getProblemInfo()->setAverageTime(this->findAverageTime(node));
                break;
            }
            coderId="";
        }
        
        if (coderId.empty()) {
            _CLogCritical("Could not find any solution!");
            return false;
        }
        
    } else {
        _CLogCritical("Could not parse problem detail page");
        return false;
    }
    return true;
}
