#ifndef COM_SOWROV_UTIL_LOGSYSTEM_DATETIME_H_
#define COM_SOWROV_UTIL_LOGSYSTEM_DATETIME_H_

#include <string>
#include <ctime>
#include <stdio.h>

namespace com {
namespace sowrov {
namespace util {
namespace logsystem {

/**
 * <p>This is singleton calander for managing date and time issue</p>
 * 
 * <p>Instance of <code>Calander</code> is immutable and threadsafe</p>
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
class Calendar {
private:
	static Calendar calendar;

	std::string monthName [12]; //= {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	std::string weekDayName [7];// = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

	bool gmtFlag;
	
	int hour;
	int minute;
	int second;
	int dayNo;
	int monthNo;
	int yearNo;
	int weekDayNo;

	Calendar();

	~Calendar();

	Calendar(const Calendar&);

	Calendar& operator=(const Calendar&);

public:
	
	/**
	 * get the singleton calendar
	 *
	 * @return the calendar object
	 */
	static Calendar& getCalendar();

	/**
	 * set whether the time should be in GMT
	 *
	 * @param bool true to set GMT
	 */
	void setGMTFlag(bool);


	/**
	 * update the calender to current system calender
	 */
	void updateCalender ();

	/**
	 * update calender with a Time Structure pointer
	 * GMT flag will not be effective in this case
	 *
	 * @param tm* time structure
	 */
	void updateCalender (struct tm*);

	/**
	 * user define the calendar
	 *
	 * @param hour 
	 * @param minute 
	 * @param second 
	 * @param dayNo 
	 * @param monthNo 
	 * @param year 
	 */
	void updateCalender (int hour, int minute, int second, int dayNo, int monthNo, int year );

	/**
	 * get last updated hour
	 *
	 * @return day hour 0-23
	 */
	int getHour();

	/**
	 * get last updated minute
	 *
	 * @return minute 0-59
	 */
	int getMinute();

	/**
	 * get last updated second
	 * @return second 0-59
	 */
	int getSecond();

	/**
	 * get last updated month day
	 *
	 * @return 
	 */
	int getDay();

	/**
	 * get last updated week day
	 *
	 * @return 
	 */
	std::string getWeekDay();

	/**
	 * calculate week day No. (0-6) from last updated date
	 *
	 * @return 
	 */
	int calculateWeekDayNo ();

	/**
	 * calculate week day No. (0-6) from a given date
	 *
	 * @return 
	 */
	int calculateWeekDayNo (int day, int month, int year);

	/**
	 * get last updated month
	 *
	 * @return month 1-12
	 */
	int getMonth();

	/**
	 * get name of the last updated month
	 *
	 * @return 
	 */
	std::string getMonthName();

	/**
	 * get last updated year
	 *
	 * @return YYYY
	 */
	int getYear();

	/**
	 * get formated date
	 * --Day--
	 * d - Day of the month, 2 digits with leading zeros (01-31)
	 * j - Day of the month without leading zeros (1-31)
	 * D - A textual representation of a day, three letters (Sun - Mon)
	 * l - A full textual representation of the day of the week  (Sunday - Saturday)
	 * w -	Numeric representation of the day of the week  	0 (for Sunday) through 6 (for Saturday)
	 * --Month--
	 * F -	A full textual representation of a month (January through December)
	 * m -	Numeric representation of a month, with leading zeros (01 through 12)
	 * n - Numeric representation of a month, without leading zeros (1 through 12)
	 * M - A short textual representation of a month, three letters (Jan through Dec)
	 * --Year--
	 * Y - A full numeric representation of a year, 4 digits  	Examples: 1999 or 2003
	 * y - A two digit representation of a year 	Examples: 99 or 03
	 * --Time--
     * a - Lowercase Ante meridiem and Post meridiem  	am or pm
	 * A - Uppercase Ante meridiem and Post meridiem 	AM or PM
	 * g - 12-hour format of an hour without leading zeros 	1 through 12
	 * G - 24-hour format of an hour without leading zeros 	0 through 23
	 * h - 12-hour format of an hour with leading zeros 	01 through 12
	 * H - 24-hour format of an hour with leading zeros 	00 through 23
	 * i - Minutes with leading zeros 	00 to 59
	 * s - Seconds, with leading zeros 	00 through 59
	 * @param std::string date format
	 * @return formated date
	 */
	std::string getFormattedDate(std::string);
};
}
}
}
}

#endif
