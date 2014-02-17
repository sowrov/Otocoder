#ifndef COM_SOWROV_UTIL_LOGSYSTEM_CONSOLE_H_
#define COM_SOWROV_UTIL_LOGSYSTEM_CONSOLE_H_
#include "OutputDevice.h"
#include <iostream>

namespace com {
namespace sowrov {
namespace util {
namespace logsystem {

/**
 * <p><code>Console</code> is an implementaion of <code>OutputDevice</code>
 * to output the log data to the system console
 * </p>
 * 
 * <p>Instance of <code>ThisClass</code> is immutable and threadsafe</p>
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
class Console : public OutputDevice {
private:
	bool freshConsole;
public:
	/**
	 * Any Initialization steps for the device
	 */
	void init();

	/**
	 * If the device was never used after construction, it should reply false,
	 * else true
	 *
	 * @return 
	 */
	bool isFreshDevice ();

	/**
	 * Write an string to the device
	 * @param std::string 
	 */
	void write(std::string);

	/**
	 * Flash any buffer text to the device
	 */
	void flush();

	/**
	 * Close the Device
	 */
	void close();
};

}
}
}
}
#endif