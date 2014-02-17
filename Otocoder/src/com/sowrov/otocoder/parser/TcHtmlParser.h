#ifndef COM_SOWROV_OTOCODER_PARSER_TCHTMLPARSER_H_
#define COM_SOWROV_OTOCODER_PARSER_TCHTMLPARSER_H_

#include <string>
#include <vector>
#include <cstring>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>

#include <com/sowrov/otocoder/ProblemInfo.h>
#include <com/sowrov/otocoder/Problem.h>
#include <com/sowrov/util/StringTokenizer.h>
#include <com/sowrov/util/logsystem/ChronicleLogger.h>

class TcHtmlParser {
private:
    void trim(std::string& str);
    std::string extractId(std::string& str, std::string query);
    std::string findBestTime(xmlNode* aTag);
    std::string findAverageTime(xmlNode* aTag);
    std::string extractProblemStatement(std::string& problemPage);
    /**
     * find the query word from the lastPos of text and
     * return a substring up to newline, update the lastPos
     */
    std::string getLineAfter(const std::string& text, const std::string& query, size_t& lastPos);

    /**
     * get full method definition from the text
     *
     * @param problemStatement string of problem statement
     * @param lastPos position of problemStatement from where this method should read the string
     * @param problem Problem object to be updated
     */
    bool parseMethodDefinition(const std::string& problemStatement, size_t& lastPos, Problem &problem);

    bool parseVariable(std::string& str, Variable& var);
    /**
     * @param sstream string stream of problem statement
     * @param problem Problem object to be updated
     */
    bool parseSampleTestcases(const std::string& problemStatement, size_t& lastPos, Problem &problem);
    bool readSingleVariableValue(const std::string& problemStatement, Variable* variable, size_t& lastPos, VariableValue& varVal, bool keepStrQuote);
public:
    TcHtmlParser(void);
    ~TcHtmlParser(void);
    /**
     * parse tc problem search page (HTML content) and populate Problem object
     * @param searchPage html content of the search page which content the problem info
     * @param problem Problem object
     */
    std::vector<ProblemInfo> parseProblemInfoSearch(std::string& searchPage, std::string classname);
    bool parseProblemDescription(std::string& problemPage, Problem& problem);
    bool parseProblemTestset(std::string& solutionPage, Problem& problem);
    bool parseProblemDetails(std::string& problemDetailPage, Problem& problem);
};

#endif