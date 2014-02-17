#ifndef COM_SOWROV_OTOCODER_METHOD_H_
#define COM_SOWROV_OTOCODER_METHOD_H_
#include <vector>
#include <string>
#include "Variable.h"
/**
 * Method class will hold the method information of the given problem
 */
class Method {
private:
    std::vector<Variable> parameter;
    std::string name;
    Variable ret;
public:
    Method(void);
    Method(const std::string& name);
    ~Method(void);
    void setName(const std::string& name);
    void addParameterVariable(Variable var);
    std::string getName();
    Variable* getReturnVariable();
    void setReturnVariable(Variable var);
    int getNumberOfParameters();
    Variable* getParameterAt(int i);
};

#endif