#ifndef COM_SOWROV_OTOCODER_TESTDATA_H_
#define COM_SOWROV_OTOCODER_TESTDATA_H_
#include <vector>
#include "VariableValue.h"
/**
 * A TestData object will hold a singe test case I/O data
 */
class TestData {
private:
    std::vector<VariableValue> input;
    VariableValue output;
    bool outputUnknown;

public:
    TestData(void);
    ~TestData(void);
    void setOutputValue(VariableValue r);
    void setOutputUnknown();
    bool isOutputUnknown();
    void addInput(VariableValue in);

    VariableValue* getInputAt(int i);
    VariableValue* getOutput();
    void clear();
};

#endif
