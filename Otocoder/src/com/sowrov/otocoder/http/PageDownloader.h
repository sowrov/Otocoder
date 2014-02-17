#ifndef COM_SOWROV_OTOCODER_HTTP_PAGEDOWNLOADER_H_
#define COM_SOWROV_OTOCODER_HTTP_PAGEDOWNLOADER_H_
#include <stdio.h>
#include <string>
#include <stdexcept>
#include <curl/curl.h>
#include <curl/easy.h>
#include <com/sowrov/util/logsystem/ChronicleLogger.h>
#include <com/sowrov/util/StringUtil.h>
#include <com/sowrov/otocoder/globals.h>

class PageDownloader {
private:
    CURL *connection;
    //  libcurl variables for error strings and returned data
    char errorBuffer[CURL_ERROR_SIZE];
    std::string buffer;
    std::string baseUrl; //'http://community.topcoder.com/tc'

    /** Libcurl write callback function */
    static int writer(char *data, size_t size, size_t nmemb, std::string *writerData);
    
public:
    PageDownloader(void);
    ~PageDownloader(void);

    /**Initialize with the base url*/
    bool init(char *url);

    /**
     * Login to topcoder server
     */
    bool tcServerLogin(std::string userName, std::string passWord);
    /**
     * download and return the page of the given page path, 
     * if pagePath do not start with http:// or www. then this method
     * will assume the given path as relative and merge it with the base
     * path before making any http request.
     */
    std::string getPage(std::string pagePath); //relative path
};

#endif
