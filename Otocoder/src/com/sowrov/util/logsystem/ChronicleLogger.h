#ifndef COM_SOWROV_UTIL_LOGSYSTEM_CHRONICLELOGGER_H_
#define COM_SOWROV_UTIL_LOGSYSTEM_CHRONICLELOGGER_H_
//#include "Device.h"
#include "Console.h"
#include "DiskFile.h"
#include "PlainText.h"
#include "Html.h"
#include "LevelManager.h"
#include "../thread/ThreadLocker.h"

#include <sstream>

#ifndef _CLThreadLock
#define _CLThreadLock() //No Log lock
#define _CLThreadUnLock() //So No Log unlock
#endif

//Set the Logger Output device to the given Diskfile with html formating
#define _CLDiskFileHtml(fileName) \
	com::sowrov::util::logsystem::ChronicleLogger::getLogger ().setDevice ( \
	new com::sowrov::util::logsystem::DiskFile(fileName));\
	com::sowrov::util::logsystem::ChronicleLogger::getLogger().setLogFormatter( \
	new com::sowrov::util::logsystem::Html())

//Set the Logger Output device to the given Diskfile with plain text formating
#define _CLDiskFilePlain(fileName) \
	com::sowrov::util::logsystem::ChronicleLogger::getLogger ().setDevice ( \
	new com::sowrov::util::logsystem::DiskFile(fileName));\
	com::sowrov::util::logsystem::ChronicleLogger::getLogger().setLogFormatter( \
	new com::sowrov::util::logsystem::PlainText())

//Set Log level
#define _CLsetLevel(level) \
	com::sowrov::util::logsystem::ChronicleLogger::getLogger().setLevel(level)

//Fatal: A very critical error which cause the application to terminate.
#define _CLogFatal(logData)														\
	do {																		\
	namespace ChronicleLoggerName = com::sowrov::util::logsystem;				\
	if(ChronicleLoggerName::ChronicleLogger::getLogger().isEnableLevel(			\
											ChronicleLoggerName::FATAL)) {		\
		std::ostringstream __cLogost__;											\
		__cLogost__<<logData;													\
		com::sowrov::util::logsystem::ChronicleLogger::getLogger().logFatal(	\
		__cLogost__.str(), __LINE__, __FUNCTION__, __FILE__);					\
		}																		\
	}while(0)

//Critical: Application fall in to a serious error but it can still go forward
#define _CLogCritical(logData)													\
	do {																		\
	namespace ChronicleLoggerName = com::sowrov::util::logsystem;				\
	if(ChronicleLoggerName::ChronicleLogger::getLogger().isEnableLevel(			\
											ChronicleLoggerName::CRITICAL)) {	\
		std::ostringstream __cLogost__;											\
		__cLogost__<<logData;													\
		com::sowrov::util::logsystem::ChronicleLogger::getLogger().logCritical(\
		__cLogost__.str(), __LINE__, __FUNCTION__, __FILE__);					\
		}																		\
	}while(0)

//Warning: Warning message for the user
#define _CLogWarning(logData)													\
	do {																		\
	namespace ChronicleLoggerName = com::sowrov::util::logsystem;				\
	if(ChronicleLoggerName::ChronicleLogger::getLogger().isEnableLevel(			\
											ChronicleLoggerName::WARNING)) {	\
		std::ostringstream __cLogost__;											\
		__cLogost__<<logData;													\
		com::sowrov::util::logsystem::ChronicleLogger::getLogger().logWarning(	\
		__cLogost__.str(), __LINE__, __FUNCTION__, __FILE__);					\
		}																		\
	}while(0)

//Info: Any information message.
#define _CLogInfo(logData)														\
	do {																		\
	namespace ChronicleLoggerName = com::sowrov::util::logsystem;				\
	if(ChronicleLoggerName::ChronicleLogger::getLogger().isEnableLevel(			\
											ChronicleLoggerName::INFO)) {		\
		std::ostringstream __cLogost__;											\
		__cLogost__<<logData;													\
		com::sowrov::util::logsystem::ChronicleLogger::getLogger().logInfo(	\
		__cLogost__.str(), __LINE__, __FUNCTION__, __FILE__);					\
		}																		\
	}while(0)

//Debug: Log any kind of message that will help to debug the app
#define _CLogDebug(logData)														\
	do {																		\
	namespace ChronicleLoggerName = com::sowrov::util::logsystem;				\
	if(ChronicleLoggerName::ChronicleLogger::getLogger().isEnableLevel(			\
											ChronicleLoggerName::DEBUG)) {		\
		std::ostringstream __cLogost__;											\
		__cLogost__<<logData;													\
		com::sowrov::util::logsystem::ChronicleLogger::getLogger().logDebug(	\
		__cLogost__.str(), __LINE__, __FUNCTION__, __FILE__);					\
		}																		\
	}while(0)


namespace com {
namespace sowrov {
namespace util {
namespace logsystem {


/**
 * <p>ChronicleLogger can be use to log anything to a given <code>OutputDevice</code>
 * by default two implementaion of <code>OutputDevice</code> is given.
 * one is <b>Console</b> i.e: <b>stdout</b> and another one is a <code>DiskFile</code>
 * </p>
 * 
 * <p> By default there are 6 log levels:
 * Level 0 - if log level is set to zero, nothing will be logged<br/>
 * Level 1 - Fatal Error, when the appliction must be stopped due to very serious error<br/>
 * Level 2 - Critical Error, but the application may continue working<br/>
 * Level 3 - Warning message
 * Level 4 - Any informational message<br/>
 * Level 5 - Debug message for the developer
 * </p>
 *
 * <p>Instance of <code>ChronicleLogger</code> is immutable and threadsafe</p>
 *
 * <p><b>Requirements:</b>
 * <ul>
 *   <li>Standard ANSI C++, 32-bit compiler</li>
 * </ul>
 * </p>
 *
 * <p>Copyright &copy; 1997, Company, Inc. All rights reserved.</p>
 * 
 * @author  Sowrov
 * @date    03-23-2010
 * @version 1.0.0
 */
class ChronicleLogger {
private:
	//this the singleton logger
	static ChronicleLogger logger;

	//device pointer
	OutputDevice *device;

	//log formatter
	LogFormatter *format;

	//log level manager
	LevelManager levelManager;
	
	//private default constructor
	ChronicleLogger();

	//private destructor
	~ChronicleLogger();

	ChronicleLogger(const ChronicleLogger&);

	ChronicleLogger & operator=(const ChronicleLogger &);

public:
	
	/**
	 * get the singleton logger object
	 * @return 
	 */
	static ChronicleLogger& getLogger();
	
	/**
	 * Set a device to the current logger
	 * @param *device 
	 */
	void setDevice (OutputDevice *device);

	/**
	 * set a formatter for the logger
	 *
	 * @param *format 
	 */
	void setLogFormatter (LogFormatter *format);


	/**
	 * set Log level
	 * @param level 
	 */
	void setLevel( int level);
	
	/**
	 * Is the given level is enabled by the current level
	 *
	 * @param level given level
	 * @return true/false base one enabled or disabled
	 */
	bool isEnableLevel(int level);
	
	/**
	 * Log a message
	 *
	 * @param message the string message
	 * @param logLevel level of this message
	 * @param lineNo current line no
	 * @param functionName function name
	 * @param fileName file name
	 */
	void log (std::string message, int logLevel, int lineNo, std::string functionName, std::string fileName);

	/**
	 * Fatal: A very critical error which cause the application to terminate.
	 *
	 * @param message the string message	 
	 * @param lineNo current line no
	 * @param functionName function name
	 * @param fileName file name
	 */
	void logFatal (std::string message, int lineNo, std::string functionName, std::string fileName);

	/**
	 * Critical: Application fall in to a serious error but it can still go forward
	 *
	 * @param message the string message
	 * @param lineNo current line no
	 * @param functionName function name
	 * @param fileName file name
	 */
	void logCritical (std::string message, int lineNo, std::string functionName, std::string fileName);

	/**
	 * Warning: Warning message for the user
	 *
	 * @param message the string message
	 * @param lineNo current line no
	 * @param functionName function name
	 * @param fileName file name
	 */
	void logWarning (std::string message, int lineNo, std::string functionName, std::string fileName);

	/**
	 * Info: Any information message.
	 *
	 * @param message the string message
	 * @param lineNo current line no
	 * @param functionName function name
	 * @param fileName file name
	 */
	void logInfo (std::string message, int lineNo, std::string functionName, std::string fileName);

	/**
	 * Log any kind of message that will help to debug the app
	 *
	 * @param message the string message
	 * @param lineNo current line no
	 * @param functionName function name
	 * @param fileName file name
	 */
	void logDebug (std::string message, int lineNo, std::string functionName, std::string fileName);

};

}
}
}
}
#endif
