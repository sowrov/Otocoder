#include "Variable.h"


Variable::Variable(void) {
    this->arrayFlag = false;
    this->dataType = "";
    this->name = "";
}

Variable::~Variable(void){
}

Variable::Variable(const std::string& dataType, const std::string& name, bool arrayFlag) {
    this->dataType = com::sowrov::util::StringUtil::toUpperCase(dataType);
    this->name = name;
    this->arrayFlag = arrayFlag;
}

void Variable::setDataType(const std::string& dataType) {
    this->dataType = com::sowrov::util::StringUtil::toUpperCase(dataType);
}

void Variable::setName(const std::string& name) {
    this->name = name;
}

void Variable::setArray(bool arrayFlag) {
    this->arrayFlag = arrayFlag;
}

std::string Variable::getDataType() {
    return this->dataType;
}

std::string Variable::getName() {
    return this->name;
}

bool Variable::isArray() {
    return this->arrayFlag;
}
