#ifndef COM_SOWROV_UTIL_LOGSYSTEM_PLAINTEXT_H_
#define COM_SOWROV_UTIL_LOGSYSTEM_PLAINTEXT_H_
#include "LogFormatter.h"
#include "LevelManager.h"
#include "Calendar.h"

namespace com {
namespace sowrov {
namespace util {
namespace logsystem {

/**
 * <p>Implementaion of <code>LogFormatter</code> interface for plain text format</p>
 * 
 * <p>Instance of <code>PlainText</code> is immutable and threadsafe</p>
 *
 * <p><b>Requirements:</b>
 * <ul>
 *   <li>Standard ANSI C++, 32-bit compiler</li>
 * </ul>
 * </p>
 *
 * <p>Copyright &copy; 1997, Company, Inc. All rights reserved.</p>
 * 
 * @author  isearch1
 * @date    03-29-2010
 * @version 1.0.0
 */
class PlainText : public LogFormatter {
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
	std::string getIntroFormat();

	/**
	 * Logger will write any text return by this method if the current device
	 * was used for logging any message.
	 *
	 * @return final string to the device
	 */
	std::string getFinalFormat();


	/**
	 * construct a formated string for FATAL errors with the input parameters
	 *
	 * @param std::string The Message
	 * @param int line No
	 * @param std::string function name 
	 * @param std::string file name
	 * @return string
	 */
	std::string getFatalFormat(std::string , int, std::string, std::string );
	
	/**
	 * construct a formated string for CRITICAL errors with the input parameters
	 *
	 * @param std::string The Message
	 * @param int line No
	 * @param std::string function name 
	 * @param std::string file name
	 * @return string
	 */
	std::string getCriticalFormat(std::string str, int lineNo, std::string functionName, std::string fileName );
	
	/**
	 *
	 * @param str 
	 * @param lineNo 
	 * @param functionName 
	 * @param fileName 
	 * @return 
	 */
	std::string getWarningFormat(std::string str, int lineNo, std::string functionName, std::string fileName );
	
	/**
	 *
	 * @param str 
	 * @param lineNo 
	 * @param functionName 
	 * @param fileName 
	 * @return 
	 */
	std::string getInfoFormat(std::string str, int lineNo, std::string functionName, std::string fileName );
	
	/**
	 *
	 * @param str 
	 * @param lineNo 
	 * @param functionName 
	 * @param fileName 
	 * @return 
	 */
	std::string getDebugFormat(std::string str, int lineNo, std::string functionName, std::string fileName );
};

}
}
}
}
#endif
