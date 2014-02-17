#ifndef COM_SOWROV_OTOCODER_VARIABLE_H_
#define COM_SOWROV_OTOCODER_VARIABLE_H_
#include <string>
#include <com/sowrov/util/StringUtil.h>

class Variable {
private:
    /** Data type of the variable*/
    std::string dataType;
    //variable name
    std::string name;
    //set as true if the variable is an array
    bool arrayFlag;
public:
    Variable(void);
    Variable(const std::string& dataType, const std::string& name, bool arrayFlag);
    ~Variable(void);
    void setDataType(const std::string& dataType);
    void setName(const std::string& name);
    void setArray(bool arrayFlag);
    std::string getDataType();
    std::string getName();
    bool isArray();
};

#endif
