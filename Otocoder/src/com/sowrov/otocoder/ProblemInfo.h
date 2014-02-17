#ifndef COM_SOWROV_OTOCODER_PROBLEMINFO_H_
#define COM_SOWROV_OTOCODER_PROBLEMINFO_H_
#include <string>

class ProblemInfo {
    std::string className;
    std::string contestName;
    std::string category;
    std::string writerName;
    std::string problemId;
    std::string roundId;
    std::string level;
    std::string bestTime;
    std::string averageTime;

public:
    ProblemInfo(void);
    ~ProblemInfo(void);
    void setClassName(const std::string& name);
    void setWriterName(const std::string& writerName);
    void setProblemId(const std::string& id);
    void setRoundId(const std::string& id);
    void setContestName(const std::string& str);
    void setCategory(const std::string& str);
    void setLevel(const std::string& str);
    void setBestTime(const std::string& strTime);
    void setAverageTime(const std::string& strTime);

    std::string getAverageTime();
    std::string getBestTime();
    std::string getClassName();
    std::string getWriterName();
    std::string getProblemId();
    std::string getRoundId();
    std::string getContestName();
    std::string getCategory();
    std::string getLevel();
};

#endif