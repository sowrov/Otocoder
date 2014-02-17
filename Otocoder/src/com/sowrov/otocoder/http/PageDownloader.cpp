#include "PageDownloader.h"

PageDownloader::PageDownloader(void) {
    connection = NULL;
}

PageDownloader::~PageDownloader(void) {
}

int PageDownloader::writer(char *data, size_t size, size_t nmemb,
    std::string *writerData) {
    if (writerData == NULL) {
        return 0;
    }

    writerData->append(data, size*nmemb);

    return size * nmemb;
}

bool PageDownloader::init(char *url) {
    int code;

    this->connection = curl_easy_init();
    if (url==NULL || url[0]==0) {
        this->baseUrl = Globals::getBaseUrl();
    } else {
        this->baseUrl = url; //http://community.topcoder.com/tc
    }

    if (this->connection == NULL) {
        _CLogCritical("Failed to create CURL connection");
        return false;
    }

    code = curl_easy_setopt(this->connection, CURLOPT_ERRORBUFFER, errorBuffer);
    //code |= curl_easy_setopt(this->connection, CURLOPT_URL, url);
    code |= curl_easy_setopt(this->connection, CURLOPT_FOLLOWLOCATION, 1L);
    code |= curl_easy_setopt(this->connection, CURLOPT_WRITEFUNCTION, writer);
    code |= curl_easy_setopt(this->connection, CURLOPT_WRITEDATA, &buffer);
    code |= curl_easy_setopt(this->connection, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:16.0) Gecko/20100101 Firefox/16.0");
    code |= curl_easy_setopt(this->connection, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
    code |= curl_easy_setopt(this->connection, CURLOPT_COOKIEJAR, "cookie.txt");
    //code |= curl_easy_setopt(this->connection, CURLOPT_VERBOSE, 1L); //Show log
    code |= curl_easy_setopt(this->connection, CURLOPT_AUTOREFERER, 1 );
    code |= curl_easy_setopt(this->connection, CURLOPT_POST, 1);
    if (code != CURLE_OK) {
        _CLogCritical(std::string("Failed to set option: ")+errorBuffer);
        return false;
    }
    _CLogDebug("Network setup complete");
    return true;
}

bool PageDownloader::tcServerLogin(std::string userName, std::string passWord) {
    int code;
    if (this->connection==NULL) {
        _CLogCritical("Connection was not initialized");
        return false;
    }
    this->buffer = "";
    std::string postData=std::string("username=")+userName+"&password="+passWord+"&rem=on&nextpage=";
    postData += baseUrl;//"http://www.topcoder.com/tc"; //stat?c=problem_statement&pm=7973
    //?&module=Login
    code = curl_easy_setopt(this->connection, CURLOPT_POSTFIELDS, postData.c_str());
    code |= curl_easy_setopt(this->connection, CURLOPT_POSTFIELDSIZE, postData.length());
    code |= curl_easy_setopt(this->connection, CURLOPT_URL, (baseUrl+"?&module=Login").c_str());
    if (code != CURLE_OK) {
        _CLogCritical(std::string("Failed to set option: ")+errorBuffer);
        return false;
    }
    try{
        _CLogDebug("Trying to login");
        code = curl_easy_perform(this->connection);
    } catch (std::logic_error &e){
        _CLogCritical(std::string("Failed to perform post request : ")+errorBuffer);
        return false; // skip this URL and go futher
    }

    if (code != CURLE_OK) {
        _CLogCritical(std::string("Failed to perform post request : ")+errorBuffer);
        return false;
    }

    if (this->buffer.find("Username or password incorrect")!=std::string::npos) {
        _CLogWarning("Given Username or password is incorrect");
        return false;
    }

    return true;
}


std::string PageDownloader::getPage(std::string url) {
    if (this->connection==NULL) {
        _CLogCritical("Connection was not initialized");
        return "";
    }
    
    std::string substr = com::sowrov::util::StringUtil::toLowerCase(url.substr(0, 7));

    //If url do not start with http or www then base url is added here
    if (!(substr.find("http://")==0 || substr.find("www.")==0)) {
        url = baseUrl+url;
    }
    this->buffer = "";
    _CLogDebug(url+" <- Trying this url");

    int code = curl_easy_setopt(this->connection, CURLOPT_URL, url.c_str());
    code = curl_easy_perform(this->connection);
    if (code != CURLE_OK) {
        _CLogCritical(std::string("Failed to perform get the page : ")+errorBuffer);
        return "";
    }
    return this->buffer;
}
