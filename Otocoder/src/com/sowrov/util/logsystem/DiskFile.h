#ifndef COM_SOWROV_UTIL_LOGSYSTEM_DISKFILE_H_
#define COM_SOWROV_UTIL_LOGSYSTEM_DISKFILE_H_
#include "OutputDevice.h"
#include "Calendar.h"
#include <fstream>
#include <string>

namespace com {
namespace sowrov {
namespace util {
namespace logsystem {

/**
 * <p><code>DiskFile</code> is an implementaion of <code>OutputDevice</code>
 * to output the log data to the disk file with a given name.
 * default log file name is: ChronicleLog.txt
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
 * @author  Sowrov
 * @date    03-28-2010
 * @version 1.0.0
 */
class DiskFile : public OutputDevice {
private:
	//maintain is fresh device flag
	bool freshFile;
	std::ofstream output;
	std::string filePathName;
public:
	DiskFile();
	DiskFile (std::string);
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
