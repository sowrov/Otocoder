#include "TestData.h"


TestData::TestData(void) {
    this->outputUnknown=true;
}


TestData::~TestData(void) {
    this->input.clear();
}

void TestData::setOutputValue(VariableValue r) {
    this->output = r;
    this->outputUnknown = false;
}

void TestData::setOutputUnknown() {
    this->outputUnknown = true;
}

bool TestData::isOutputUnknown() {
    return this->outputUnknown;
}

void TestData::addInput(VariableValue in) {
    this->input.push_back(in);
}

VariableValue* TestData::getInputAt(int i) {
    if (i<this->input.size()) {
        return &this->input[i];
    }
    return NULL;
}

VariableValue* TestData::getOutput() {
    return &this->output;
}

void TestData::clear() {
    this->input.clear();
    this->output.clear();
}
//