#include "File.h"

namespace com {
namespace sowrov {
namespace io {
File::File(){
	this->completePath="";
	this->path="";
}

File::File(std::string pathName) {
	this->path = pathName;
	this->fileInputStream.open(this->path.c_str());
	this->completePath = "";
}

File::~File() {
	this->fileInputStream.close();
}

bool File::exists(){
	if (!this->fileInputStream) {
		return false;
	} else {
		return true;
	}
}
}
}
}