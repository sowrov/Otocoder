#ifndef COM_SOWROV_UTIL_LOGSYSTEM_OUTPUTDEVICE_H_
#define COM_SOWROV_UTIL_LOGSYSTEM_OUTPUTDEVICE_H_

#include <string>

namespace com {
namespace sowrov {
namespace util {
namespace logsystem {

/**
 * <p>OutputDevice Interface, All log output device class must implement this 
 * interface</p>
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
class OutputDevice{
public:

	/**
	 * Any Initialization steps for the device
	 */
	virtual void init() = 0;

	/**
	 * If the device was never used after construction, it should reply false,
	 * else true
	 *
	 * @return 
	 */
	virtual bool isFreshDevice () = 0;

	/**
	 * Write an string to the device
	 * @param std::string 
	 */
	virtual void write(std::string) = 0;

	/**
	 * Flash any buffer text to the device
	 */
	virtual void flush() = 0;

	/**
	 * Close the Device
	 */
	virtual void close() = 0;
};

}
}
}
}
#endif