#include "LevelManager.h"

namespace com {
namespace sowrov {
namespace util {
namespace logsystem {
	LevelManager::LevelManager() {
		this->currentLevel = DEBUG;
	}

	LevelManager::LevelManager(int level) {
		this->currentLevel = level;
	}

	void LevelManager::setLevel(int level) {
		this->currentLevel = level;
	}

	int LevelManager::getLevel() {
		return this->currentLevel;
	}

	bool LevelManager::isEnableLevel(int level) {
		if (level <= this->currentLevel) {
			return true;
		}
		else {
			return false;
		}
	}

	std::string LevelManager::getLevelName (int level) {
		if (level == 0) {
			return "NoLog";
		}
		else if (level == 1) {
			return "Fatal";
		}
		else if (level == 2) {
			return "Critical";
		}
		else if (level == 3) {
			return "Warning";
		}
		else if (level == 4) {
			return "Info";
		}
		else if (level == 5) {
			return "Debug";
		}
		else {
			return "Unknown";
		}
	}

}
}
}
}
