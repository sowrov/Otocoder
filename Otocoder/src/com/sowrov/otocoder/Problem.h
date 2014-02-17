#ifndef COM_SOWROV_OTOCODER_PROBLEM_H_
#define COM_SOWROV_OTOCODER_PROBLEM_H_
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "TestData.h"
#include "Method.h"
#include "ProblemInfo.h"

#include <com/sowrov/util/StringUtil.h>
#include <com/sowrov/util/logsystem/ChronicleLogger.h>

class Problem {
private:
    std::string problemStatement;
    ProblemInfo problemInfo;
    std::string coderId;
    Method method;
    std::vector<TestData> sampleTestCases;
    std::vector<TestData> fullTestCases;

    void writeSingleVariableData (std::ofstream& ofs, Variable* var, VariableValue* varData);
public:
    Problem(void);
    Problem(std::string& problemStatement);
    ~Problem(void);

    void setProblemInfo(ProblemInfo& problemInfo);
    void setProblemStatement(const std::string& str);
    void setClassName(std::string& name);
    void setWriterName(std::string& writerName);
    void setProblemId(std::string& id);
    void setRoundId(std::string& id);
    void setCoderId(std::string& id);
    void setMethod(Method m);
    void setContestName(const std::string& str);
    void setProblemCategory(const std::string& str);
    
    /**
     * Add a test case as sample test case
     */
    void addSampleTestCase(TestData& td);
    /**
     * Add input a Test case
     */
    void addTestCase(TestData& td);

    ProblemInfo* getProblemInfo();
    std::string getProblemStatement();
    std::string getClassName();
    std::string getWriterName();
    std::string getProblemId();
    std::string getRoundId();
    std::string getCoderId();
    std::string getContestName();
    std::string getProblemCategory();
    Method* getMethod();

    int getSampleTestSize();
    int getFullTestSize();
    TestData* getSampleTestCaseAt(unsigned int i);
    TestData* getFullTestCaseAt(unsigned int i);

    
    void writeFullTest(std::ofstream& ofs);
};

#endif