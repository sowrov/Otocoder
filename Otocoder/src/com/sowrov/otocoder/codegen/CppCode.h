#ifndef COM_SOWROV_OTOCODER_CODEGEN_CPPCODE_H_
#define COM_SOWROV_OTOCODER_CODEGEN_CPPCODE_H_
#include <string>
#include <vector>
#include <algorithm>
#include <com/sowrov/otocoder/Problem.h>
#include <com/sowrov/otocoder/codegen/CodeInterface.h>

class CppCode : public CodeInterface {
private:
    bool isDouble;
    std::string tabStr;
    std::string cppHeaderfiles();
    /**
     * Generate the method part of tc code
     */
    std::string generateDatatype(Variable* var);
    std::string methodCode(Method* method);
    //main method
    std::string generateDefaultMain();

    //generate method which will decide how to run the test
    std::string generateRunTest();
    //generate method of case verification
    std::string generateVerifyCase(Problem& problem);
    //generate method for all sample test cases
    std::string generateRunTestCase(Problem& problem);
    //generate code which will convert an array to a vector
    std::string vectorize(Variable* var, VariableValue* varVal);
    //generate code for individual test cases
    std::string generateTestCase(int caseNo, const std::string& className, Method* var, TestData* value);
    //generate a string of variable to value map, e.g: int var[]= {1, 3};
    std::string generateParameter(Variable* var, VariableValue* varVal);
    //generate a code which will output a complete vector
    std::string generateFormatResult(Variable* returnType);

    std::string generateOutputComparison(Variable *ret);

    std::string generateSingleCaseReader(Variable* var, const std::string&);
    std::string generateFullTestReader(Problem& problem);
    
public:
    CppCode(void);
    ~CppCode(void);

    std::string getFileExtension();

    /**
     * Generate the actual code (in className file) from problem object
     */
    std::string generateCode(Problem& problem);

    /**
     * Convert data type like: STRING, LONG, DOUBLE, INT, BOOL/BOOLEAN, CHAR to actual 
     * datatype of the language
     */
    std::string convertDataType(const std::string& s);
    
};

#endif