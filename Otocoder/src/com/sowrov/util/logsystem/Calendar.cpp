#include "Calendar.h"

namespace com {
namespace sowrov {
namespace util {
namespace logsystem {
	//construction of singleton static timer
	Calendar Calendar::calendar;

	Calendar::Calendar() {
		this->gmtFlag = false;
		this->updateCalender ();
		this->monthName[0] = "January";
		this->monthName[1] = "February";
		this->monthName[2] = "March";
		this->monthName[3] = "April";
		this->monthName[4] = "May";
		this->monthName[5] = "June";
		this->monthName[6] = "July";
		this->monthName[7] = "August";
		this->monthName[8] = "September";
		this->monthName[9] = "October";
		this->monthName[10] = "November";
		this->monthName[11] = "December";

		this->weekDayName [0] = "Sunday";
		this->weekDayName [1] = "Monday";
		this->weekDayName [2] = "Tuesday";
		this->weekDayName [3] = "Wednesday";
		this->weekDayName [4] = "Thursday";
		this->weekDayName [5] = "Friday";
		this->weekDayName [6] = "Saturday";
	}

	Calendar::~Calendar(){}

	/**
	 * get the singleton timer
	 *
	 * @return the timer
	 */
	Calendar& Calendar::getCalendar() {
		return Calendar::calendar;
	}

	/**
	 * set whether the time should be in GMT
	 *
	 * @param bool true to set GMT
	 */
	void Calendar::setGMTFlag(bool flag) {
		this->gmtFlag = flag;
	}
	
	/**
	 * update the calender to current system calender
	 */
	void Calendar::updateCalender () {
		struct tm *timeInfo;
        time_t rawtime;
        time ( &rawtime );
        
		if (this->gmtFlag) {
			timeInfo = std::gmtime (&rawtime);
		} else {
			timeInfo = std::localtime ( &rawtime );
		}
		this->hour = timeInfo->tm_hour;
		this->minute = timeInfo->tm_min;
		this->second = timeInfo->tm_sec;
		this->dayNo = timeInfo->tm_mday;
		this->weekDayNo = timeInfo->tm_wday;
		this->monthNo = timeInfo->tm_mon;
		this->yearNo = timeInfo->tm_year;
	}

	/**
	 * update calender with a Time Structure pointer
	 * GMT flag will not be effective in this case
	 *
	 * @param tm* time structure
	 */
	void Calendar::updateCalender (struct tm* timeInfo) {
		if (timeInfo == NULL) {
			return;
		}
		this->hour = timeInfo->tm_hour;
		this->minute = timeInfo->tm_min;
		this->second = timeInfo->tm_sec;
		this->dayNo = timeInfo->tm_mday;
		this->weekDayNo = timeInfo->tm_wday;
		this->monthNo = timeInfo->tm_mon;
		this->yearNo = timeInfo->tm_year;
	}


	/**
	 * user define the calendar
	 *
	 * @param hour  hour>=0 && hour<=23
	 * @param minute minute>=0 && minute<=59
	 * @param second second>=0 && second<=59
	 * @param dayNo dayNo>=1 && dayNo<=31
	 * @param monthNo monthNo>=0 && monthNo<=11
	 * @param year year>=1900
	 */
	void Calendar::updateCalender (int hour, int minute, int second, int dayNo, int monthNo, int year ) {
		if (hour>=0 && hour<=23 && minute>=0 && minute<=59
			&& second>=0 && second<=59 && dayNo>=1 && dayNo<=31
			&& monthNo>=0 && monthNo<=11 && year>=1900) {
			this->hour = hour;
			this->minute = minute;
			this->second = second;
			this->dayNo = dayNo;
			this->monthNo = monthNo;
			this->yearNo = yearNo-1900;
			this->weekDayNo = this->calculateWeekDayNo ();
		}
	}

	/**
	 * get last updated hour
	 *
	 * @return day hour 0-23
	 */
	int Calendar::getHour() {
		return this->hour;
	}

	/**
	 * get last updated minute
	 *
	 * @return minute 0-59
	 */
	int Calendar::getMinute() {
		return this->minute;
	}

	/**
	 * get last updated second
	 * @return second 0-59
	 */
	int Calendar::getSecond() {
		return this->second;
	}

	/**
	 * get last updated month day
	 *
	 * @return 
	 */
	int Calendar::getDay() {
		return this->dayNo;
	}

	/**
	 * get last updated week day
	 *
	 * @return 
	 */
	std::string Calendar::getWeekDay() {
		if (this->weekDayNo<0 && this->weekDayNo > 6) {
			return "";
		}
		return this->weekDayName[this->weekDayNo];
	}

	/**
	 * calculate week day No. (0-6) from last updated date
	 * Sunday is day 0
	 * @return 
	 */
	int Calendar::calculateWeekDayNo () {
		return this->calculateWeekDayNo (this->dayNo, this->monthNo, this->yearNo+1900);
	}
	/**
	 * calculate week day No. (0-6) from a given date
	 * Sunday is day 0
	 * @return 
	 */
	int Calendar::calculateWeekDayNo (int day, int month, int year) {
		if ( day<1 || day>31 || month<1 || month>12 ) {
			return -1;
		}

		if (month == 1 || month == 2) {
			month = 12 + month;
			year--;
		}

		int val = ((month+1)*3)/5;
		val = day+(month*2)+val+year+(year/4)-(year/100)+(year/400)+1;
		val %=7;
		return val;
	}
	

	/**
	 * get last updated month
	 *
	 * @return month 1-12
	 */
	int Calendar::getMonth() {
		return this->monthNo + 1;
	}

	/**
	 * get name of the last updated month
	 *
	 * @return 
	 */
	std::string Calendar::getMonthName() {
		return this->monthName[this->monthNo];
	}

	/**
	 * get last updated year
	 *
	 * @return YYYY
	 */
	int Calendar::getYear() {
		return this->yearNo + 1900;
	}

	/**
	 * get formated date
	 * --Day--
	 * d - Day of the month, 2 digits with leading zeros (01-31)
	 * j - Day of the month without leading zeros (1-31)
	 * D - A textual representation of a day, three letters (Sun - Mon)
	 * l (lowercase L) - A full textual representation of the day of the week  (Sunday - Saturday)
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
	std::string Calendar::getFormattedDate(std::string format) {
		std::string formattedDate = "";
		char tmp[10];
		for (unsigned int i=0; i<format.length (); i++) {
			if (format[i]=='d') {
				sprintf(tmp,"%02d", this->dayNo);
				formattedDate += tmp;
			}
			else if (format[i]=='j') {
				sprintf(tmp,  "%d", this->dayNo);
				formattedDate += tmp;
			}
			else if (format[i]=='D') {
				formattedDate += this->weekDayName[this->weekDayNo].substr (0,3);
			}
			else if (format[i]=='l') {
				formattedDate += this->weekDayName[this->weekDayNo];
			}
			else if (format[i]=='w') {
				sprintf(tmp,  "%d", this->weekDayNo);
				formattedDate += tmp;
			}
			else if (format[i]=='F') {
				formattedDate += this->monthName[this->monthNo];
			}
			else if (format[i]=='m') {
				sprintf(tmp,  "%02d", this->monthNo);
				formattedDate += tmp;
			}
			else if (format[i]=='n') {
				sprintf(tmp,  "%d", this->monthNo);
				formattedDate += tmp;
			}
			else if (format[i]=='M') {
				formattedDate += this->monthName[this->monthNo].substr (0,3);
			}
			else if (format[i]=='Y') {
				int num = this->yearNo + 1900;
				sprintf(tmp,  "%d", num);
				formattedDate += tmp;
			}
			else if (format[i]=='y') {
				int num = (this->yearNo + 1900) % 100;
				sprintf(tmp,  "%02d", num);
				formattedDate += tmp;
			}
			else if (format[i]=='a') {
				if (this->hour<12) {
					formattedDate += "am";
				}
				else {
					formattedDate += "pm";
				}
			}
			else if (format[i]=='A') {
				if (this->hour<12) {
					formattedDate += "AM";
				}
				else {
					formattedDate += "PM";
				}
			}
			else if (format[i]=='g') {
				int num = this->hour;
				if (num>12) {
					num %= 12; //pm
				}
				if (num == 0) {
					num = 12; //am
				}
				sprintf(tmp,  "%d", num);
				formattedDate += tmp;
			}
			else if (format[i]=='G') {
				sprintf(tmp,  "%d", this->hour);
				formattedDate += tmp;
			}
			else if (format[i]=='h') {
				int num = this->hour;
				if (num>12) {
					num %= 12; //pm
				}
				if (num == 0) {
					num = 12; //am
				}
				sprintf(tmp,  "%02d", num);
				formattedDate += tmp;
			}
			else if (format[i]=='H') {
				sprintf(tmp,  "%02d", this->hour);
				formattedDate += tmp;
			}
			else if (format[i]=='i') {
				sprintf(tmp,  "%02d", this->minute);
				formattedDate += tmp;
			}
			else if (format[i]=='s') {
				sprintf(tmp,  "%02d", this->second);
				formattedDate += tmp;
			}
			else {
				formattedDate += format[i];
			}
		}
		return formattedDate;
	}
}
}
}
}
