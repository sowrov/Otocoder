#include "VariableValue.h"

VariableValue::VariableValue(void) {
    this->data.clear();
}

VariableValue::~VariableValue(void) {
    this->data.clear();
}

void VariableValue::addData(const std::string& d) {
    this->data.push_back(d);
}

std::vector<std::string> VariableValue::getData() {
    return this->data;
}

int VariableValue::getDataCount() {
    return this->data.size();
}

std::string VariableValue::getDataAt(int i) {
    if (i>=this->data.size()) {
        _CLogCritical("Variable data index out of bound");
        return "";
    }
    return this->data[i];
}

std::string VariableValue::toString(bool arr, const std::string& longlongSuffix) {
    std::string str= "";
    if (arr) {
        str += "{";
        for (int i=0; i<this->data.size(); i++) {
            if (i) {
                str += ", ";
            }
            str += this->data[i]+longlongSuffix;
        }
        str += "}";
    } else if (this->data.size()>0){
        str = this->data[0]+longlongSuffix;
    }
    return str;
}

void VariableValue::clear() {
    return this->data.clear();
}