#include "PlainText.h"


namespace com {
namespace sowrov {
namespace util {
namespace logsystem {

	std::string PlainText::getIntroFormat() {
		std::string format = "Last Compile Time: ";
		format += __DATE__;
		format += " ";
		format += __TIME__;
		Calendar::getCalendar ().updateCalender ();
		format += "\nLogging Started on this OutDevice at: ";
		format += Calendar::getCalendar ().getFormattedDate ("d F Y H:i:s")+"\n\n";
		return format;
	}

	std::string PlainText::getFinalFormat() {
		return "--------------------------------Logging Complete-------------------------------\n";
	}

	std::string PlainText::getFatalFormat(std::string message, int lineNo, std::string functionName, std::string fileName) {
		Calendar::getCalendar ().updateCalender ();
		std::string format =  "------- ";
		format += LevelManager::getLevelName (FATAL) +" Error -------\n";
		char tmp[10];
		sprintf (tmp, "%d", lineNo);
		format += "File:";
		format += fileName+"\n";
		format += "Line No:";
		format += tmp;
		format += " function:";
		format += functionName+"(...)\n";
		format += "Time: ";
		format += Calendar::getCalendar ().getFormattedDate ("d F Y H:i:s")+"\n\n";

		format += "Cause: ";
		format += message+"\n";
		format += "---------------------------\n\n";
		return format;
	}

	std::string PlainText::getCriticalFormat(std::string message, int lineNo, std::string functionName, std::string fileName) {
		Calendar::getCalendar ().updateCalender ();
		std::string format =  "------- ";
		format += LevelManager::getLevelName (CRITICAL) +" Error -------\n";
		char tmp[10];
		sprintf (tmp, "%d", lineNo);
		format += "File:";
		format += fileName+"\n";
		format += "Line No:";
		format += tmp;
		format += " function:";
		format += functionName+"(...)\n";
		format += "Time: ";
		format += Calendar::getCalendar ().getFormattedDate ("d F Y H:i:s")+"\n\n";

		format += "Cause: ";
		format += message+"\n";
		format += "---------------------------\n\n";
		return format;
	}

	std::string PlainText::getWarningFormat(std::string message, int lineNo, std::string functionName, std::string fileName) {
		char tmp[10];
		sprintf (tmp, "%d--", lineNo);

		std::string format = LevelManager::getLevelName (WARNING)+": ";
		format += fileName+ ":";
		format += tmp;
		format += functionName+"(...)\n>> ";
		format += message+"\n\n";
		return format;
	}

	std::string PlainText::getInfoFormat(std::string message, int lineNo, std::string functionName, std::string fileName) {
		std::string format = LevelManager::getLevelName (INFO)+": ";
		char tmp[10];
		sprintf (tmp, "%d--", lineNo);

		format += fileName+ ":";
		format += tmp;
		format += functionName+"(...)\n>> ";
		format += message+"\n\n";
		return format;
	}

	std::string PlainText::getDebugFormat(std::string message, int lineNo, std::string functionName, std::string fileName) {
		std::string format = LevelManager::getLevelName (DEBUG)+": ";
		char tmp[10];
		sprintf (tmp, "%d--", lineNo);

		format += fileName+ ":";
		format += tmp;
		format += functionName+"(...)\n>> ";
		format += message+"\n\n";
		return format;
	}

}
}
}
}
