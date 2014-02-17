#include "Console.h"

namespace com {
namespace sowrov {
namespace util {
namespace logsystem {
	
	void Console::init() {
		this->freshConsole = true;
	}

	bool Console::isFreshDevice() {
		return this->freshConsole;
	}

	void Console::write(std::string str) {
		std::cout << str;
		this->flush();
		this->freshConsole = false;
	}

	void Console::flush () {
		std::cout.flush();
	}

	void Console::close() {}
}
}
}
}
