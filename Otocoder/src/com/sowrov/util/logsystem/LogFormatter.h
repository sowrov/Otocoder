#ifndef COM_SOWROV_UTIL_LOGSYSTEM_LOGFORMATTER_H_
#define COM_SOWROV_UTIL_LOGSYSTEM_LOGFORMATTER_H_

#include <string>

namespace com {
namespace sowrov {
namespace util {
namespace logsystem {

class LogFormatter{
public:

	/**
	 * Any fresh device will write any message return by this method before
	 * writing any log message. HTML or XML type log formatter should use this
	 * method for proper intro text, like for HTML it may return something like
	 * this:
	 * "<html><head><title>This is Log Title</title></heaD><body>"
	 *
	 * @return initial string for any fresh device
	 */
	virtual std::string getIntroFormat()		= 0;

	/**
	 * Logger will write any text return by this method if the current device
	 * was used for logging any message.
	 *
	 * @return final string to the device
	 */
	virtual std::string getFinalFormat()		= 0;


	/**
	 * construct a formated string for FATAL errors with the input parameters
	 *
	 * @param std::string The Message
	 * @param int line No
	 * @param std::string function name 
	 * @param std::string file name
	 * @return string
	 */
	virtual std::string getFatalFormat(std::string , int, std::string, std::string )	= 0;
	
	/**
	 * construct a formated string for CRITICAL errors with the input parameters
	 *
	 * @param std::string The Message
	 * @param int line No
	 * @param std::string function name 
	 * @param std::string file name
	 * @return string
	 */
	virtual std::string getCriticalFormat(std::string str, int lineNo, std::string functionName, std::string fileName )	= 0;
	
	/**
	 *
	 * @param str 
	 * @param lineNo 
	 * @param functionName 
	 * @param fileName 
	 * @return 
	 */
	virtual std::string getWarningFormat(std::string str, int lineNo, std::string functionName, std::string fileName )	= 0;
	
	/**
	 *
	 * @param str 
	 * @param lineNo 
	 * @param functionName 
	 * @param fileName 
	 * @return 
	 */
	virtual std::string getInfoFormat(std::string str, int lineNo, std::string functionName, std::string fileName )		= 0;
	
	/**
	 *
	 * @param str 
	 * @param lineNo 
	 * @param functionName 
	 * @param fileName 
	 * @return 
	 */
	virtual std::string getDebugFormat(std::string str, int lineNo, std::string functionName, std::string fileName )	= 0;
};

}
}
}
}
#endif
