#include "DiskFile.h"

namespace com {
namespace sowrov {
namespace util {
namespace logsystem {
	DiskFile::DiskFile() {
		this->filePathName = "ChronicleLog.txt";
	}

	DiskFile::DiskFile (std::string filePathName) {
		this->filePathName = filePathName;
	}

	void DiskFile::init() {
		this->output.open (this->filePathName.c_str ());
		this->freshFile = true;
	}

	bool DiskFile::isFreshDevice() {
		return this->freshFile;
	}

	void DiskFile::write(std::string str) {
		this->freshFile = false;
		this->output<<str;
		this->flush ();
	}
	void DiskFile::flush() {
		this->output.flush ();
	}
	void DiskFile::close() {
		this->output.close ();
	}
}
}
}
}

