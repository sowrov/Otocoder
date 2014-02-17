#include "Problem.h"

Problem::Problem(void) {
    this->problemStatement = "";
    this->coderId = "";
    this->sampleTestCases.clear();
    this->fullTestCases.clear();
}

Problem::~Problem(void) {
    this->sampleTestCases.clear();
    this->fullTestCases.clear();
}

Problem::Problem(std::string& problemStatement) {
    this->problemStatement = problemStatement;
    this->coderId = "";
    this->sampleTestCases.clear();
    this->fullTestCases.clear();
}

void Problem::setProblemStatement(const std::string& str) {
    this->problemStatement = str;
}

void Problem::setClassName(std::string& name) {
    this->problemInfo.setClassName(name);
}

void Problem::setWriterName(std::string& writerName) {
    this->problemInfo.setWriterName(writerName);
}

void Problem::setProblemId(std::string& id) {
    this->problemInfo.setProblemId(id);
}

void Problem::setRoundId(std::string& id) {
    this->problemInfo.setRoundId(id);
}

void Problem::setCoderId(std::string& id) {
    this->coderId = id;
}

void Problem::setMethod(Method m) {
    this->method = m;
}

void Problem::addSampleTestCase(TestData& td) {
    this->sampleTestCases.push_back(td);
}

void Problem::addTestCase(TestData& td) {
    this->fullTestCases.push_back(td);
}

ProblemInfo* Problem::getProblemInfo() {
    return &this->problemInfo;
}

Method* Problem::getMethod() {
    return &this->method;
}

std::string Problem::getProblemStatement() {
    return this->problemStatement;
}

std::string Problem::getClassName() {
    return this->problemInfo.getClassName();
}

std::string Problem::getWriterName() {
    return this->problemInfo.getWriterName();
}

std::string Problem::getProblemId() {
    return this->problemInfo.getProblemId();
}

std::string Problem::getRoundId() {
    return this->problemInfo.getRoundId();
}

std::string Problem::getCoderId() {
    return this->coderId;
}

int Problem::getSampleTestSize() {
    return this->sampleTestCases.size();
}

int Problem::getFullTestSize() {
    return this->fullTestCases.size();
}

TestData* Problem::getSampleTestCaseAt(unsigned int i) {
    if (i>=this->sampleTestCases.size()) {
        _CLogWarning("Index out of bound");
        return NULL;
    }
    return &this->sampleTestCases[i];
}

TestData* Problem::getFullTestCaseAt(unsigned int i) {
    if (i>=this->fullTestCases.size()) {
        _CLogWarning("Index out of bound");
        return NULL;
    }

    return &this->fullTestCases[i];
}

void Problem::setContestName(const std::string& str) {
    this->problemInfo.setContestName(str);
}

void Problem::setProblemCategory(const std::string& str) {
    this->problemInfo.setCategory(str);
}

std::string Problem::getContestName() {
    return this->problemInfo.getContestName();
}

std::string Problem::getProblemCategory() {
    return this->problemInfo.getCategory();
}

void Problem::setProblemInfo(ProblemInfo& problemInfo) {
    /*
    this->problemInfo.setClassName(problemInfo.getClassName());
    this->problemInfo.setContestName(problemInfo.getContestName());
    this->problemInfo.setCategory(problemInfo.getCategory());
    this->problemInfo.setProblemId(problemInfo.getProblemId());
    this->problemInfo.setRoundId(problemInfo.getRoundId());
    this->problemInfo.setWriterName(problemInfo.getWriterName());
    */
    this->problemInfo = problemInfo;
}

void Problem::writeSingleVariableData (std::ofstream& ofs, Variable* var, VariableValue* varData) {
    if (var->isArray()) {
        ofs<<varData->getDataCount()<<std::endl;
        for (int k=0; k<varData->getDataCount(); k++) {
            ofs<<varData->getDataAt(k)<<std::endl;
        }
    } else {
        ofs<<varData->getDataAt(0)<<std::endl;
    }
}

void Problem::writeFullTest(std::ofstream& ofs) {
    TestData* td;

    //number of test cases
    ofs<<this->fullTestCases.size()<<std::endl;
    for (int i=0; i<this->fullTestCases.size(); i++) {
        //write test case no. Every test case starts with a blank line
        ofs<<std::endl<<i<<")"<<std::endl;
        td = this->getFullTestCaseAt(i);
        for (int j=0; j<this->getMethod()->getNumberOfParameters(); j++) {
            //write one parameter value at a time
            this->writeSingleVariableData(ofs, this->getMethod()->getParameterAt(j), td->getInputAt(j));
        }
        //write the return (Expected) value
        this->writeSingleVariableData(ofs, this->getMethod()->getReturnVariable(), td->getOutput());
    }
}
