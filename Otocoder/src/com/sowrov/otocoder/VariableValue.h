#ifndef COM_SOWROV_OTOCODER_VARIABLEVALUE_H_
#define COM_SOWROV_OTOCODER_VARIABLEVALUE_H_
#include <vector>
#include <string>
#include <com/sowrov/util/logsystem/ChronicleLogger.h>
/**
 * VariableValue object will be the storage of a variable, which can be an array or single variable.
 */
class VariableValue {
private:
    std::vector<std::string> data;
public:
    VariableValue(void);
    ~VariableValue(void);
    void addData(const std::string& d);
    std::vector<std::string> getData();
    int getDataCount();
    std::string getDataAt(int);
    std::string toString(bool arr, const std::string& longlongPrefix);
    void clear();
};

#endif
