#include "Method.h"

Method::Method(void) {
    this->name="";
    this->parameter.clear();
}

Method::~Method(void) {
    this->parameter.clear();
}

Method::Method(const std::string& name) {
    this->name = name;
    this->parameter.clear();
}

void Method::setName(const std::string& name) {
    this->name = name;
}

void Method::setReturnVariable(Variable var) {
    this->ret = var;
}

void Method::addParameterVariable(Variable var) {
    this->parameter.push_back(var);
}

std::string Method::getName() {
    return this->name;
}

Variable* Method::getReturnVariable() {
    return &this->ret;
}

int Method::getNumberOfParameters() {
    return this->parameter.size();
}

Variable* Method::getParameterAt(int i) {
    return &this->parameter.at(i);
}

