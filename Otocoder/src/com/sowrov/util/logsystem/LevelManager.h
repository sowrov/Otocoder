#ifndef COM_SOWROV_UTIL_LOGSYSTEM_LEVELMANAGER_H_
#define COM_SOWROV_UTIL_LOGSYSTEM_LEVELMANAGER_H_

#include <string>

namespace com {
namespace sowrov {
namespace util {
namespace logsystem {

enum LogLevel { 
	/**
	 * value zero (0)
	 * No Message will be logged
	 */
	NOLOG,
	/**
	 * 1
	 * Error that cause the application to exit
	 */
	FATAL,
	/**
	 * 2
	 * Error but not that vital to stop the application
	 */
	CRITICAL,
	/**
	 * 3
	 * Not so vital error, but better to inform the user.
	 */
	WARNING,
	/**
	 * 4
	 * Any information that could help the user
	 */
	INFO,
	/**
	 * 5
	 * All debug message
	 */
	DEBUG
};

/**
 * <p>This is the log level manager which deal with log level for the logger</p>
 * 
 * <p>Instance of <code>LevelManager</code> is immutable and threadsafe</p>
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
class LevelManager {
private:
	//current level holder
	int currentLevel;
public:

	/**
	 * Default constructor of level manager, initialize the level up to DEBUG
	 */
	LevelManager ();


	/**
	 * Constructor of level manager, initialize the level up to given value
	 * @param level 
	 */
	LevelManager (int level);

	/**
	 * set level for the current logger
	 * @param level 
	 */
	void setLevel (int level);


	/**
	 * return current log level
	 *
	 * @return current log level
	 */
	int getLevel ();

	/**
	 * Is the given level is enabled by the current level
	 *
	 * @param level given level
	 * @return true/false base one enabled or disabled
	 */
	bool isEnableLevel (int level);
	
	/**
	 * convert a level to sting name.
	 *
	 * @param level given level to convert
	 * @return "Unknown" if the level is grater than 5
	 */
	static std::string getLevelName (int level);
};
}
}
}
}

#endif //COM_SOWROV_UTIL_LOGSYSTEM_LEVELMANAGER_H_
