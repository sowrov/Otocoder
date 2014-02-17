#include "ProblemInfo.h"


ProblemInfo::ProblemInfo(void) {
    this->level="";
}


ProblemInfo::~ProblemInfo(void) {
}

void ProblemInfo::setClassName(const std::string& name) {
    this->className = name;
}

void ProblemInfo::setWriterName(const std::string& writerName) {
    this->writerName = writerName;
}

void ProblemInfo::setProblemId(const std::string& id) {
    this->problemId = id;
}

void ProblemInfo::setRoundId(const std::string& id) {
    this->roundId  = id;
}

void ProblemInfo::setContestName(const std::string& str) {
    this->contestName = str;
}

void ProblemInfo::setCategory(const std::string& str) {
    this->category = str;
}

void ProblemInfo::setLevel(const std::string& str) {
    if (str.empty()) {
        this->level = "";
        return;
    }
    if (this->level.empty()) {
        this->level = str;
    } else {
        this->level += " & "+str;
    }
}

void ProblemInfo::setAverageTime(const std::string& strTime) {
    this->averageTime = strTime;
}

std::string ProblemInfo::getAverageTime() {
    return this->averageTime;
}

void ProblemInfo::setBestTime(const std::string& strTime) {
    this->bestTime = strTime;
}

std::string ProblemInfo::getBestTime() {
    return this->bestTime;
}

std::string ProblemInfo::getClassName() {
    return this->className;
}

std::string ProblemInfo::getWriterName() {
    return this->writerName;
}

std::string ProblemInfo::getProblemId() {
    return this->problemId;
}

std::string ProblemInfo::getRoundId() {
    return this->roundId;
}

std::string ProblemInfo::getContestName() {
    return this->contestName;
}

std::string ProblemInfo::getCategory() {
    return this->category;
}

std::string ProblemInfo::getLevel() {
    return this->level;
}