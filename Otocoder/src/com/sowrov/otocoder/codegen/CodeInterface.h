#ifndef COM_SOWROV_OTOCODER_CODEGEN_CODEINTERFACE_H_
#define COM_SOWROV_OTOCODER_CODEGEN_CODEINTERFACE_H_
#include <string>
#include <com/sowrov/otocoder/Problem.h>
#include <com/sowrov/otocoder/TestData.h>

/**
 * An interface class for codes
 */
class CodeInterface {
public:
    /**
     * Return file type extension of the code
     */
    virtual std::string getFileExtension() = 0;

    /**
     * Generate the actual code (in className file) from problem object
     */
    virtual std::string generateCode(Problem& problem) = 0;

    /**
     * Convert data type like: STRING, LONG, DOUBLE, INT, BOOL/BOOLEAN, CHAR to actual 
     * datatype of the language
     */
    virtual std::string convertDataType(const std::string& s) = 0;
};

#endif