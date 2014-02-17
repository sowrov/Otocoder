#include "CppCode.h"


CppCode::CppCode(void) {
    this->isDouble = false;
    this->tabStr = "    ";
}


CppCode::~CppCode(void) {
}

std::string CppCode::getFileExtension() {
    return ".cpp";
}

std::string CppCode::cppHeaderfiles(){
    std::string headers[] = {
        "#include \"vector\"",
        "#include \"list\"",
        "#include \"map\"",
        "#include \"set\"",
        "#include \"string\"",
        "#include \"deque\"",
        "#include \"queue\"",
        "#include \"stack\"",
        "#include \"bitset\"",
        "#include \"algorithm\"",
        "#include \"functional\"",
        "#include \"utility\"",
        "#include \"iomanip\"",
        "#include \"cctype\"",
        "#include \"numeric\"",
        "#include \"iostream\"",
        "#include \"cstdio\"",
        "#include \"cmath\"",
        "#include \"cstdlib\"",
        "#include \"cstring\"",
        "#include \"sstream\"",
        "#include \"fstream\"",
        "#include \"cassert\"",
        "#include \"ctime\"",
    };
    int size=24;

    srand(time(0));
    
    std::random_shuffle(headers, headers+size);
    std::string str="";
    for (int i=0; i<size; i++) {
        str+=headers[i]+"\n";
    }
    str += "\nusing namespace std;\n";
    return str;
}

std::string CppCode::methodCode(Method* method) {
    std::string mCode=tabStr, tmpStr;
    Variable *var = method->getReturnVariable();
    if (var->getDataType()=="DOUBLE") {
        this->isDouble = true;
    }

    mCode += this->generateDatatype(var)+" ";

    mCode += method->getName()+"(";
    for (int i=0; i<method->getNumberOfParameters(); i++) {
        var = method->getParameterAt(i);
        if (var->getDataType()=="DOUBLE") {
            this->isDouble = true;
        }
        if (i>0) {
            mCode += ", ";
        }

        mCode += this->generateDatatype(var)+" "; //int a, vector<string> b etc.
        mCode += var->getName();
    }
    mCode += ") {\n        ";
    mCode += this->generateDatatype(method->getReturnVariable())+" out;\n\n";
    mCode += "        return out;\n    }\n";
    return mCode;
}

std::string CppCode::generateDefaultMain() {
    std::string str;
    str = "int main(int argc, char *argv[]) {\n" +
            tabStr+"if (argc == 1) {\n" +
            tabStr+tabStr+"otocoder::run_test();\n" +
            tabStr+"} else {\n" +
            tabStr+tabStr+"for (int i=1; i<argc; ++i)\n" +
            tabStr+tabStr+tabStr+"otocoder::run_test(atoi(argv[i]));\n" +
            tabStr+"}\n" +
            "}\n";
    return str;
}

std::string CppCode::generateRunTest() {
    std::string str;
    str = 
    tabStr+"int run_test_case(int );\n" +
    tabStr+"bool run_full_test();\n" +
    tabStr+"// casenum<-1 to run full test set, casenum=-1 (default) to run all sample test cases,\n    // casenum>-1 value to run specific sample case\n"+
    tabStr+"void run_test(int casenum = -1, bool quiet = false) {\n" +
    tabStr+tabStr+"if (casenum < -1) {\n" +
    tabStr+tabStr+tabStr+"if (!run_full_test()) {\n" +
    tabStr+tabStr+tabStr+tabStr+"cerr << \"Illegal inputs in full test cases!\" << endl;\n" +
    tabStr+tabStr+tabStr+"}\n" +
    tabStr+tabStr+tabStr+"return;\n" +
    tabStr+tabStr+"}\n" +
    tabStr+tabStr+"if (casenum > -1) {\n" +
    tabStr+tabStr+tabStr+"if (run_test_case(casenum) == -1 && !quiet) {\n" +
    tabStr+tabStr+tabStr+tabStr+"cerr << \"Illegal input! Test case \" << casenum << \" does not exist.\" << endl;\n" +
    tabStr+tabStr+tabStr+"}\n" +
    tabStr+tabStr+tabStr+"return;\n" +
    tabStr+tabStr+"}\n" +
    "\n" +
    tabStr+tabStr+"int correct = 0, total = 0;\n" +
    tabStr+tabStr+"for (int i=0;; ++i) {\n" +
    tabStr+tabStr+tabStr+"int x = run_test_case(i);\n" +
    tabStr+tabStr+tabStr+"if (x == -1) {\n" +
    tabStr+tabStr+tabStr+tabStr+"if (i >= 100) break;\n" +
    tabStr+tabStr+tabStr+tabStr+"continue;\n" +
    tabStr+tabStr+tabStr+"}\n" +
    tabStr+tabStr+tabStr+"correct += x;\n" +
    tabStr+tabStr+tabStr+"++total;\n" +
    tabStr+tabStr+"}\n" +
    "\n" +
    tabStr+tabStr+"if (total == 0) {\n" +
    tabStr+tabStr+tabStr+"cerr << \"No test cases run.\" << endl;\n" +
    tabStr+tabStr+"} else if (correct < total) {\n" +
    tabStr+tabStr+tabStr+"cerr << \"Some cases FAILED (passed \" << correct << \" of \" << total << \").\" << endl;\n" +
    tabStr+tabStr+"} else {\n" +
    tabStr+tabStr+tabStr+"cerr << \"All \" << total << \" tests passed!\" << endl;\n" +
    tabStr+tabStr+"}\n" +
    tabStr+"}\n\n";
    
    return str;
}

std::string CppCode::generateFormatResult(Variable* returnType) {
    std::string str="";
    if (returnType->isArray()) {
        str = "    template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << \"{\"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << \",\"; os << \" \" << *vi; } os << \" }\"; return os; }\n";

        if (returnType->getDataType() == "STRING") {
            str+="    template<> ostream& operator<<(ostream &os, const vector<string> &v) { os << \"{\"; for (vector<string>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << \",\"; os << \" \\\"\" << *vi << \"\\\"\"; } os << \" }\"; return os; }\n";
        }
        str += "\n\n";
    }
    return str;
}

std::string CppCode::generateDatatype(Variable* var) {
    std::string dataType = this->convertDataType(var->getDataType());
    if (var->isArray()) {
        dataType = "vector<"+dataType+">";
    }
    return dataType;
}

std::string CppCode::generateParameter(Variable* var, VariableValue* varVal) {
    std::string code;
    std::string longlongPrefix;
    code = this->convertDataType(var->getDataType()) 
                        + " "+ var->getName() + (var->isArray()?"[]":"") + " = "; //int[] varname = 
    if (var->getDataType() == "LONG") {
        longlongPrefix = "LL";
    } else {
        longlongPrefix = "";
    }
    code += varVal->toString(var->isArray(), longlongPrefix) +";\n"; // {a, b};
    return code;
}

std::string CppCode::vectorize(Variable* var, VariableValue* varVal) {
    if (!var->isArray()) {
        return var->getName();
    } else {
        if (varVal->getDataCount()==0) {
            // Visual C++ empty array hack
            return this->generateDatatype(var) + "()";
        }

        return this->generateDatatype(var) + "(" + var->getName() + ", " + var->getName() +
                " + (sizeof " + var->getName() + " / sizeof " + var->getName() + "[0]))";
    }
}

std::string CppCode::generateVerifyCase(Problem& problem) {
    Variable* reType = problem.getMethod()->getReturnVariable();
    std::string typeName = this->generateDatatype(reType);
    std::string mCode;
    mCode = "    int verify_case(int casenum, const " + typeName + " &expected, const " + typeName + " &received, clock_t elapsed) { \n" +
            "        cerr << \"Example \" << casenum << \"... \"; \n" +
            "\n" +
            "        string verdict;\n" +
            "        vector<string> info;\n" +
            "        char buf[100];\n" +
            "\n" +
            "        if (elapsed > CLOCKS_PER_SEC / 200) {\n" +
            "            sprintf(buf, \"time %.2fs\", elapsed * (1.0/CLOCKS_PER_SEC));\n" +
            "            info.push_back(buf);\n" +
            "        }\n" +
            "\n";

    // Print "PASSED" or "FAILED" based on the result
    if (reType->getDataType()=="DOUBLE") {
        mCode +=
            std::string(
            "        if (compareDouble(expected, received)) {\n") +
            "            verdict = \"PASSED\";\n" +
            "            double rerr = moj_relative_error(expected, received); \n" +
            "            if (rerr > 0) {\n" +
            "                sprintf(buf, \"relative error %.3e\", rerr);\n" +
            "                info.push_back(buf);\n" +
            "            }\n";
    } else {
        mCode +=
            std::string("        if (expected == received) {\n") +
            "            verdict = \"PASSED\";\n";
    }
    mCode += 
            std::string("        } else {\n") +
            "            verdict = \"FAILED\";\n" +
            "        }\n" +
            "\n" +
            "        cerr << verdict;\n" +
            "        if (!info.empty()) {\n" +
            "            cerr << \" (\";\n" +
            "            for (int i=0; i<(int)info.size(); ++i) {\n" +
            "                if (i > 0) cerr << \", \";\n" +
            "                cerr << info[i];\n" +
            "            }\n" +
            "            cerr << \")\";\n" +
            "        }\n" +
            "        cerr << endl;\n" +
            "\n" +
            "        if (verdict == \"FAILED\") {\n";

    if (reType->getDataType()=="STRING" &&	!reType->isArray()) {
        mCode += 
            std::string("            cerr << \"    Expected: \\\"\" << expected << \"\\\"\" << endl;\n") +
            "            cerr << \"    Received: \\\"\" << received << \"\\\"\" << endl;\n";
    } else {
        mCode += 
            std::string("            cerr << \"    Expected: \" << expected << endl; \n") +
            "            cerr << \"    Received: \" << received << endl; \n";
    }
        mCode +=
            std::string("        }\n") +
            "\n" +
            "        return verdict == \"PASSED\";\n" +
            "    }\n" +
            "\n";
    return mCode;
}


std::string CppCode::generateOutputComparison(Variable *ret) {
    std::string str="";
    if (ret->getDataType()=="DOUBLE") {
        str = "#ifndef isinf\n";
        str += "#define isinf(x) (!_finite(x))\n";
        str += "#define isnan(x) _isnan(x)\n";
        str += "#endif\n";

        str += tabStr+"static const double epsilon = 1e-9; static bool compareDouble(double expected, double result) { return (fabs(expected - result) <= epsilon * fmax(1.0, fmax(fabs(expected), fabs(result)))); }\n";
        str += tabStr+"double moj_relative_error(double expected, double result) { if (isnan(expected) || isinf(expected) || isnan(result) || isinf(result) || expected == 0) return 0; return fabs(result-expected) / fabs(expected); }\n";
        if (ret->isArray()) {
            str+=tabStr+"static bool compareDouble(const vector<double> &a, const vector<double> &b) { if (a.size() != b.size()) return false; for (size_t i=0; i<a.size(); ++i) if (!compareDouble(a[i], b[i])) return false; return true; }\n";
            str+=tabStr+"double moj_relative_error(const vector<double> &expected, const vector<double> &result) { double ret = 0.0; for (size_t i=0; i<expected.size(); ++i) { ret = max(ret, moj_relative_error(expected[i], result[i])); } return ret; }\n";
        }
        str+="\n";
    }
    return str;
}

std::string CppCode::generateTestCase(int caseNo,const  std::string& className, Method* method, TestData* testData) {
    std::string code = "";
    
    for (int i=0; i<method->getNumberOfParameters(); i++) {
        code += "            " + this->generateParameter(method->getParameterAt(i), testData->getInputAt(i));
    }

    code += "            "+ this->generateParameter(method->getReturnVariable(), testData->getOutput());
    code += "\n";
    code += "            clock_t start_           = clock();\n";
    code += "            "+this->generateDatatype(method->getReturnVariable())+" received_ = " +
            className+"()."+method->getName()+"(";

    for (int i=0; i<method->getNumberOfParameters(); i++) {
        if (i) {
            code += ", ";
        }
        code += this->vectorize(method->getParameterAt(i), testData->getInputAt(i));
    }
    code += ");\n";
    code += "            return verify_case(casenum, " + 
            this->vectorize(method->getReturnVariable(), testData->getOutput()) + ", received_, clock()-start_);\n";
    return code;
}

std::string CppCode::generateRunTestCase(Problem& problem) {
    std::string mCode;
    mCode = "    int run_test_case(int casenum) {\n";
    mCode += "        switch (casenum) {\n";
    char arr[200];
    // Generate the individual test cases
    int totalCases = problem.getSampleTestSize();
    for (int i = 0; i < totalCases; ++i) {
        sprintf(arr, "        case %d: {\n", i);
        mCode += arr;
        mCode += this->generateTestCase(i, problem.getClassName(), problem.getMethod(), problem.getSampleTestCaseAt(i));
        mCode += "        }\n";
    }

    // next
    mCode +=std::string("        default:\n") +
            "            return -1;\n" +
            "        }\n" +
            "    }\n\n";
    return mCode;
}

std::string CppCode::generateSingleCaseReader(Variable* var, const std::string& preTabs) {
    std::string code="";
    if (var->isArray()) {
        code += preTabs+tabStr+var->getName()+".clear();\n";
        code += preTabs+tabStr+"std::cin>>N; std::cin.ignore(10, '\\n');\n" +
                preTabs+tabStr+"for(int j=0; j<N; j++) {\n";
        if (var->getDataType()=="STRING") {
            code += preTabs+tabStr+tabStr+"std::getline(std::cin,"+var->getName()+"_sin );\n";
        } else {
            code += preTabs+tabStr+tabStr+"std::cin>>"+var->getName()+"_sin; std::cin.ignore(10, '\\n');\n";
        }
        code += preTabs+tabStr+tabStr+var->getName()+".push_back("+var->getName()+"_sin);\n";
        code += preTabs+tabStr+"}\n";
    } else {
        if (var->getDataType()=="STRING") {
            code += preTabs+tabStr+"std::getline(std::cin,"+var->getName()+");\n";
        } else {
            code += preTabs+tabStr+"std::cin>>"+var->getName()+"; std::cin.ignore(10, '\\n');\n";
        }
    }

    return code;
}

std::string CppCode::generateFullTestReader(Problem& problem) {
    Method* method = problem.getMethod();
    Variable* var;
    std::string code =  
        tabStr + "const std::string currentDateTime() {\n"+
        tabStr + tabStr + "time_t     now = time(0);\n"+
        tabStr + tabStr + "struct tm  tstruct;\n"+
        tabStr + tabStr + "char       buf[80];\n" +
        tabStr + tabStr + "tstruct = *localtime(&now);\n"+
        tabStr + tabStr + "strftime(buf, sizeof(buf), \"%Y-%m-%d %X\", &tstruct);\n"+
        tabStr + tabStr + "return buf;\n"+
        tabStr+"}\n\n"+
        tabStr+"//This method will only accept input files that are formatted in proper way.\n"+
        tabStr+"//Command line example: "+problem.getClassName()+".exe -2 <"+problem.getClassName()+".io\n"+
        tabStr+"bool run_full_test() {\n" +
        tabStr+tabStr+"int testCase, N, caseNo, correct=0;\n";
    //declare all variables
    for (int i=0; i<method->getNumberOfParameters(); i++) {
        var = method->getParameterAt(i);
        code+= tabStr+tabStr+this->generateDatatype(var)+" "+var->getName()+";\n";//vector<int> var;
        //if we have an array then we will create another variable to read single item of that array, redundant but easy to code :|
        if (var->isArray()) {
            code += tabStr+tabStr+this->convertDataType(var->getDataType())+" "+var->getName()+"_sin;\n"; //with _in suffix
        }
    }
    var = method->getReturnVariable();
    code+= tabStr+tabStr+this->generateDatatype(var)+" "+var->getName()+";\n";//vector<int> var;
    if (var->isArray()) {
        code += tabStr+tabStr+this->convertDataType(var->getDataType())+" "+var->getName()+"_sin;\n"; //with _in suffix
    }
    code += "\n";
    code+= tabStr+tabStr+"std::cin>>testCase; std::cin.ignore(10, '\\n');\n" +
        tabStr+tabStr+"for (int i=0; i<testCase; i++) {\n" +
        tabStr+tabStr+tabStr+"std::cin>>caseNo; std::cin.ignore(10, '\\n');\n";
    //code to read all parameters
    for (int i=0; i<method->getNumberOfParameters(); i++) {
        code += this->generateSingleCaseReader(method->getParameterAt(i), tabStr+tabStr);
    }
    //code to read expected result
    code += this->generateSingleCaseReader(method->getReturnVariable(), tabStr+tabStr);

    //code to run class.Method(parameters...)
    code += tabStr+tabStr+tabStr+"clock_t start_           = clock();\n";
    code += tabStr+tabStr+tabStr+this->generateDatatype(method->getReturnVariable())+" received_ = " +
        problem.getClassName()+"()."+method->getName()+"(";

    for (int i=0; i<method->getNumberOfParameters(); i++) {
        if (i) {
            code += ", ";
        }
        code += method->getParameterAt(i)->getName();
    }
    code += ");\n";
    code += tabStr+tabStr+tabStr+"correct += verify_case(caseNo, " + method->getReturnVariable()->getName()  + ", received_, clock()-start_);\n";

    code+=tabStr+tabStr+"}//end of testCase for loop\n\n";
    code += tabStr+tabStr +"if (testCase == 0) {\n" +
            tabStr+tabStr+tabStr+"cerr << \"No test cases run.\" << endl;\n" +
            tabStr+tabStr+"} else if (correct < testCase) {\n"+
            tabStr+tabStr+tabStr+"cerr << \"Some cases FAILED (passed \" << correct << \" of \" << testCase << \").\" << endl;\n"+
            tabStr+tabStr+"} else {\n"+
            tabStr+tabStr+tabStr+"cerr << \"All \" << testCase << \" tests passed!\" << endl;\n"+
            tabStr+tabStr+tabStr+"std::ofstream ofs(\""+problem.getClassName()+".st\", std::ios_base::app);\n"+
            tabStr+tabStr+tabStr+"ofs<<currentDateTime()<<std::endl;\n"+
            tabStr+tabStr+tabStr+"ofs.close();\n"+
            tabStr+tabStr+"}\n"+
            tabStr+tabStr+"return true;\n"+
          tabStr+"}\n\n";
    return code;
}
/**
 * Generate the actual code from problem object
 */
std::string CppCode::generateCode(Problem& problem) {
    //All header file list
    std::string theCode = this->cppHeaderfiles();
    theCode += std::string("\n#define Zclr(arr) memset(arr, 0, sizeof(arr))\n") +
                "#define Nclr(arr) memset(arr, -1, sizeof(arr))\n" +
                "#define M31 1<<30\n" +
                "#define Pi (2.0*acos(0.0))\n" +
                "#define Eps (1e-9)\n"+
                "#define Rep(_var, _N) for (int _var=0; _var<_N; _var++ )\n"+
                "#define For(_var, _S,  _N) for (int _var=_S; _var<=_N; _var++ )\n\n";

    theCode += "class "+problem.getClassName()+" {\n" +
               "public:\n"+this->methodCode(problem.getMethod()) +
               "};\n\n"; //end of class code

    theCode += "// <editor-fold defaultstate=\"collapsed\" desc=\"Generated Code\">\n";
    theCode += "namespace otocoder {\n" +
               this->generateOutputComparison(problem.getMethod()->getReturnVariable())+
               this->generateRunTest() +
               this->generateFormatResult(problem.getMethod()->getReturnVariable()) +
               this->generateVerifyCase(problem) +
               this->generateRunTestCase(problem) +
               this->generateFullTestReader(problem)+
               "}\n\n";
    theCode += this->generateDefaultMain();
    theCode += "// </editor-fold>\n";

    return theCode;
}

/**
 * Convert data type like: STRING, LONG, DOUBLE, INT, BOOL/BOOLEAN, CHAR to actual 
 * datatype of the language
 */
std::string CppCode::convertDataType(const std::string& s) {
    if(s=="LONG") {
        return "long long";
    } else if(s=="STRING") {
        return "string";
    } else if(s=="INT") {
        return "int";
    } else if(s=="DOUBLE") {
        return "double";
    } else if(s=="BOOL" || s=="BOOLEAN") {
        return "bool";
    } else if(s=="CHAR") {
        return "char";
    }
    return "Error";
}
