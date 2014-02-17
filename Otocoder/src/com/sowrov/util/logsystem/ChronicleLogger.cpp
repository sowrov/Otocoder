#include "ChronicleLogger.h"

namespace com {
namespace sowrov {
namespace util {
namespace logsystem {
	
	ChronicleLogger ChronicleLogger::logger;

	ChronicleLogger::ChronicleLogger() {
		this->device = NULL;
		this->format = NULL;
		this->setDevice(new Console());
		this->setLogFormatter(new PlainText());
	}

	ChronicleLogger::~ChronicleLogger() {
		if (this->device != NULL) {
			//if the old device is not fresh then write the final format
			if (this->format != NULL && !this->device->isFreshDevice()) {
				this->device->write(this->format->getFinalFormat());
			}
			this->device->flush();
			this->device->close();
			delete this->device;
		}
		
		if (this->format != NULL) {
			delete this->format;
		}
	}
	
	ChronicleLogger& ChronicleLogger::getLogger () {
		return ChronicleLogger::logger;
	}

	void ChronicleLogger::setDevice(OutputDevice *device) {
		if (this->device != NULL) {
			//if the old device is not fresh then write the final format
			if (this->format != NULL && !this->device->isFreshDevice()) {
				this->device->write(this->format->getFinalFormat());
			}
			this->device->flush();
			this->device->close();
			delete this->device;
		}
		this->device = device;
		this->device->init();
	}

	void ChronicleLogger::setLogFormatter(LogFormatter *format) {
		if (this->format != NULL) {
			delete this->format;
		}
		this->format = format;
	}

	void ChronicleLogger::setLevel (int level) {
		this->levelManager.setLevel(level);
	}

	bool ChronicleLogger::isEnableLevel(int level) {
		return this->levelManager.isEnableLevel (level);
	}

	void ChronicleLogger::log(std::string message, int logLevel, int lineNo, std::string functionName, std::string fileName) {
		_CLThreadLock();
		if (this->device == NULL) {
			this->setDevice (new Console());
		}

		if (this->device->isFreshDevice ()) {
			this->device->write (this->format->getIntroFormat ());
		}

		if (logLevel == 1) {
			this->device->write (this->format->getFatalFormat (message, lineNo, functionName, fileName));
		}
		else if (logLevel == 2) {
			this->device->write (this->format->getCriticalFormat (message, lineNo, functionName, fileName));
		}
		else if (logLevel == 3) {
			this->device->write (this->format->getWarningFormat (message, lineNo, functionName, fileName));
		}
		else if (logLevel == 4) {
			this->device->write (this->format->getInfoFormat (message, lineNo, functionName, fileName));
		}
		else if (logLevel == 5) {
			this->device->write (this->format->getDebugFormat (message, lineNo, functionName, fileName));
		}
		_CLThreadUnLock();
	}
	
	void ChronicleLogger::logFatal (std::string message, int lineNo, std::string functionName, std::string fileName) {
		this->log (message, 1, lineNo, functionName, fileName);
	}

	void ChronicleLogger::logCritical (std::string message, int lineNo, std::string functionName, std::string fileName) {
		this->log (message, 2, lineNo, functionName, fileName);
	}

	void ChronicleLogger::logWarning (std::string message, int lineNo, std::string functionName, std::string fileName) {
		this->log (message, 3, lineNo, functionName, fileName);
	}

	void ChronicleLogger::logInfo (std::string message, int lineNo, std::string functionName, std::string fileName) {
		this->log (message, 4, lineNo, functionName, fileName);
	}

	void ChronicleLogger::logDebug (std::string message, int lineNo, std::string functionName, std::string fileName) {
		this->log (message, 5, lineNo, functionName, fileName);
	}
}
}
}
}
