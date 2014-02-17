#ifndef COM_SOWROV_IO_FILE_H_
#define COM_SOWROV_IO_FILE_H_

#include <string>
#include <fstream>

namespace com {
namespace sowrov {
namespace io {
class File {
private:
    std::string path;
    std::string completePath;
    std::fstream fileInputStream;
public:
    /**
     * Constructs a file object
     */
    File();

    /**
     * Constructs a file object from a given file path
     */
    File(std::string pathName);

    ~File();

    /**
     * Tests whether the file or directory denoted by this abstract pathname exists.
     * @returns true if and only if the file or directory denoted by this abstract pathname exists; false otherwise 
     */
    bool exists();

};
}
}
}
#endif
