#pragma once
#ifndef XT_TIME_UTIL_H
#define XT_TIME_UTIL_H

/**
* \file TimeUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide time utility functions.
*
* \description
*	This component provides utility functions for time.
*/

#include <cstdint>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <algorithm>

#include <ctime>
#include <chrono>

#define BOOST_DATE_TIME_SOURCE
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time_adjustor.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include "XTConfig.h"


namespace XT
{

class XT_COMMON_API TimeUtil {
public:
	TimeUtil() {} // = delete;
	TimeUtil(const TimeUtil&) {} // = delete;
//	TimeUtil(TimeUtil&&) {} // = delete;
	~TimeUtil() {} // = delete;

	TimeUtil& operator=(const TimeUtil&) { return *this; } // = delete;
//	TimeUtil& operator=(TimeUtil&&) { return *this; } // = delete;
//////
public:
	static int64_t getHalfSecond();

	static int64_t getOneSecond();

	static int64_t getTwoSeconds();

	static int64_t getFiveSeconds();

	static int64_t getTenSeconds();

	static int64_t getFifteenSeconds();

	static int64_t getOneMinute();

	static int64_t getOneHour();

	static int64_t getOneDay();


	static int64_t getThousand();
	static double getMilli();

	static int64_t getMillion();
	static double getMicro();

	static int64_t getBillion();
	static double getNano();

protected:
	static const int64_t s_HalfSecond; ///< 0.5 seconds
	static const int64_t s_OneSecond; ///< one second

	static const int64_t s_TwoSeconds; ///< two seconds
	static const int64_t s_FiveSeconds; ///< five seconds
	static const int64_t s_TenSeconds; ///< ten seconds
	static const int64_t s_FifteenSeconds; ///< fifteen seconds
	
	static const int64_t s_OneMinute; ///< one minute
	static const int64_t s_OneHour; ///< one hour
	static const int64_t s_OneDay; ///< one day

	static const int64_t s_Thousand;///< one thousand
	static const double s_Milli;///< 1/thousand
	
	static const int64_t s_Million; ///< one million
	static const double s_Micro; ///< micro, 10^-6, 1/million

	static const int64_t s_Billion; ///< one billion 10^9
	static const double s_Nano; ///< 10^-9 1/billion

	static const std::chrono::system_clock::time_point s_EPOCH;///< epoch time point

	static const int64_t s_TimeZone_Shift;


public:
	/**
	* @brief get nowtype
	*
	* @return nowtype
	*/
	static int getNowType();

	/**
	* @brief set nowtype
	*
	* @param i
	*/
	static void setNowType(int i);

	/**
	* @brief set nowts
	*
	* @param ts
	*/
	static void setNowTs(int64_t ts);
	
protected:
	static int m_nowType;
	static int64_t m_nowTs;

public:

	/**
	* convert to localtime tm
	*/
	static bool toLocaltime(const time_t *t, tm * tt);

	/**
	* convert to gmtime tm
	*/
	static bool toGmtime(const time_t *t, tm * tt);

protected:

	/**
	* calculate timezone offset
	*/
	static int64_t calcTimeZoneShift();

	/**
	* get current time point
	*/
	static std::chrono::system_clock::time_point getNowTp();



	///**
	//* get chrono timepoint
	//* @param year year such as 2015
	//* @param month month such as 01
	//* @param day day such as 01
	//* @param hour hour such as 01
	//* @param minute minute such as 0
	//* @param second second such as 0
	//*/
	//static std::chrono::system_clock::time_point getTimePoint(int year, int month, int day, int hour, int minute, int second);

	///**
	//* get date time str in format like 2015-01-01 01:00:00.000000
	//* @param tp timepoint
	//*/
	//static std::string getTimePointStr(std::chrono::system_clock::time_point & tp);

	///**
	//* get time point for an int date(like 20150101)
	//* @param intdate integer date like 20150101
	//*/
	//static std::chrono::system_clock::time_point getTimePointForIntdate(int intdate);

	///**
	//* get time point for a time stamp
	//* @param ts int64 timestamp
	//*/
	//static std::chrono::system_clock::time_point getTimePointForTs(int64_t ts);

public:
	/**
	* get timezone shift
	*/
	static int64_t getTimeZoneShift();

	/**
	* get current date time string in format like 2015-01-01 01:00:00.000000
	*/
	static std::string getNowStr();

	/**
	* get local current date time string in format like 2015-01-01 01:00:00.000000
	*/
	static std::string getLocalNowStr();

	/**
	* get current date time string in json format like "edt":"2015-01-01 01:00:00.000000"
	*/
	static std::string getNowJsonStr();

	/**
	* get current time string in format like 01:00:00.000000
	*/
	static std::string getNowTimeStr();

	/**
	* get local current time string in format like 01:00:00.000000
	*/
	static std::string getLocalNowTimeStr();

	/**
	* get current time integer in HHMMSS
	*/
	static int getNowHHMMSSInt();
	/**
	* get local current time integer in HHMMSS
	*/
	static int getLocalNowHHMMSSInt();
	/**
	* get current inttime
	*/
	static int getNowIntTime();

	/**
	* get local current inttime
	*/
	static int getLocalNowIntTime();

	/**
	* get current week inttime
	*/
	static int getNowWeekIntTime();

	/**
	* get local current week inttime
	*/
	static int getLocalNowWeekIntTime();

	/**
	* get current day inttime, starts with 0 if is after 18:00, 1 before 18:00
	*/
	static int getNowDayIntTime();

	/**
	* get local current day inttime, starts with 0 if is after 18:00, 1 before 18:00
	*/
	static int getLocalNowDayIntTime();

	/**
	* get current integer hour
	*/
	static int getNowHour();

	/**
	* get current integer minute
	*/
	static int getNowMinute();

	/**
	* get current integer second
	*/
	static int getNowSecond();


	/**
	* get current time stamp
	*/
	static int64_t getNowTs();

	/**
	* get local current time stamp
	*/
	static int64_t getLocalNowTs();

	/**
	* get current time ints
	*/
	static bool getNowTimeValInts(int& secs, int& usecs);

	/**
	* get local current time ints
	*/
	static bool getLocalNowTimeValInts(int& secs, int& usecs);

	/**
	* get current unix time stamp in double
	*/
	static double getNowUts();

	/**
	* get local current unix time stamp in double
	*/
	static double getLocalNowUts();

	/**
	* get current int date, like 20150101
	*/
	static int getNowIntDate();

	/**
	* get day of week for intdate
	*/
	static int getDayOfWeekForIntDate(int i);

	/**
	* get day of year for intdate
	*/
	static int getDayOfYearForIntDate(int i);

	/**
	* get day of week for timestamp
	*/
	static int getDayOfWeekForTs(int64_t ts);

	/**
	* get prev intdate 
	*/
	static int getPrevIntDate(int i);

	/**
	* get prev work intdate
	*/
	static int getPrevWorkIntDate(int i);

	/**
	* get next intdate
	*/
	static int getNextIntDate(int i);

	/**
	* get prev work intdate
	*/
	static int getNextWorkIntDate(int i);

	/**
	* add days to intdate
	*/
	static int addDaysToIntDate(int intdate, int days);

	/**
	* get local current int date, like 20150101
	*/
	static int getLocalNowIntDate();


 

	/**
	* get int64 timestamp
	* @param sec seconds
	* @param usec microseconds
	*/
	static int64_t getTs(int sec, int usec);

	/**
	* get double timestamp
	* @param sec seconds
	* @param usec microseconds
	*/
	static double getUts(int sec, int usec);

	/**
	* get date time string for timestamp
	* @param ts int64_t timestamp
	*/
	static std::string getStrForTs(int64_t ts);
	
	/**
	* get date time string for timestamp
	* @param ts int64_t timestamp
	*/
	static std::string getStr19ForTs(int64_t ts);

	/**
	* get date time json string for timestamp
	* @param ts int64_t timestamp
	*/
	static std::string getJsonStrForTs(int64_t ts);

	/**
	* get date string(like 20150101) for timestamp
	* @param ts int64_t timestamp
	*/
	static std::string getDateStrForTs(int64_t ts);

	/**
	* get time string(like 01:01:00) for timestamp
	* @param ts int64_t timestamp
	*/
	static std::string getTimeStrForTs(int64_t ts);


	/**
	* get int date(like 20150101) for timestamp
	* @param int64_t timestamp
	*/
	static int getIntDateForTs(int64_t ts);

	/**
	* @brief get int time for timestamp
	*
	* @param timestamp
	*
	* @return inttime
	*/
	static int getIntTimeForTs(int64_t ts);

	/**
	* @brief get weekday int time for timestamp
	*
	* @param timestamp
	*
	* @return weekinttime
	*/
	static int getWeekIntTimeForTs(int64_t ts);

	/**
	* @brief get day int time for timestamp
	*
	* @param timestamp
	*
	* @return dayinttime
	*/
	static int getDayIntTimeForTs(int64_t ts);

	/**
	* @brief get day inttime
	*
	* @param timestr
	*/
	static int getDayIntTimeForTimeStr(const std::string& timestr);

	/**
	* @brief get inttime
	*
	* @param timestr
	*/
	static int getIntTimeForTimeStr(const std::string& timestr);

	/**
	* get timestamp for integer year,month,day,hour,minute,second, and microseconds
	* @param year integer year like 2015
	* @param month integer month like 01
	* @param day integer day like 01
	* @param hour integer hour like 01
	* @param minute integer minute like 01
	* @param second integer second like 0
	* @param micro integer micro seconds
	*/
	static int64_t getTsForYMDHMSU(int year, int month, int day, int hour, int minute, int second, int micro);

	/**
	* get time stamp for intdate, timestr and milliseconds
	* @param intdate for example, 20150101
	* @param timestr
	* @param milliseconds
	*/
	static int64_t getTsForDayTimeMilliseconds(int intdate, const std::string& timestr, int milliseconds);

	/**
	* get days between two dates
	* @param intdate1 date from
	* @param intdate2 date to
	*/
	static int getDaysBetween(int intdate1, int intdate2);

	///**
	//* get trade days between two dates
	//* @param intdate1 date from
	//* @param intdate2 date to
	//*/
	//static int getTradeDaysBetween(int intdate1, int intdate2);

	/**
	* get date str(like 20150101) for intdate
	* @param intdate integer date like 20150101
	*/
	static std::string getDateStrForIntdate(int intdate);

	/**
	* get timestamp for date time string with length 26
	* @param dtstr date time string
	*/
	static int64_t getTsForDTStr(const std::string& dtstr);

	/**
	* get timestamp for intdate and time string such as 09:00:00.000000
	* @param intdate
	* @param timestr
	*/
	static int64_t getTsForIntDateAndTimeStr(int intdate, const std::string& timestr);

	/**
	* get timestamp for intdate
	* @param intdate
	*/
	static int64_t getTsForIntDate(int intdate);

 

	/**
	* get seconds part for timestamp
	* @param ts timestamp
	*/
	static int getSecForTs(int64_t ts);

	/**
	* get seconds part for double timestamp
	* @param ts double timestamp
	*/
	static int getSecForUts(double uts);

	/**
	* get microseconds part for timestamp
	* @param ts timestamp
	*/
	static int getUsecForTs(int64_t ts);

	/**
	* get microseconds part for double timestamp
	* @param uts double timestamp
	*/
	static int getUsecForUts(double uts);

	/**
	* get matlab time value for timestamp
	* @param dtTicks timestamp
	*/
	static double getMatlabDatenumForTicks(int64_t dtTicks);

	/**
	* get timestamp for matlab time
	* @param dn matlab time
	*/
	static int64_t getTicksForMatlabDatenum(double dn);

	/**
	* get double timestamp for dot net timestamp
	* @param dtTicks int64_t timestamp
	*/
	static double getUtsForTicks(int64_t dtTicks);

	/**
	* get dot net timestamp for double timestamp
	* @param uts double timestamp
	*/
	static int64_t getTicksForUts(double uts);

	/**
	* get timestamp for dot net timestamp
	* @param dtTicks dot net timestamp
	*/
	static int64_t getTsForTicks(int64_t dtTicks);

	/**
	* get dotnet timestamp for int64_t timestamp
	* @param int64_t timestamp
	*/
	static int64_t getTicksForTs(int64_t ts);

	/**
	* get months between two dates
	* @param intdate1 date from
	* @param intdate2 date to
	*/
	static int getMonthsBetween(int intdate1, int intdate2);

public:
	/**
	* @brief get timestamp from logline
	*
	* @param line
	*
	* @return timestamp
	*/
	static int64_t getTsForLogLine(const std::string& line);

///////////////////////////////////////////////////////
protected:
	/**
	* @brief get microseconds between two ptime
	*
	* @param pt0 as the start ptime
	* @param pt1 as ent end ptime
	*
	* @return time duration in microseconds
	*/
	static int64_t getMicrosecondsBetweenPts(const boost::posix_time::ptime& pt0, const boost::posix_time::ptime& pt1);

	/**
	* @brief get timestamp for ptime
	*
	* @param pt as ptime
	*
	* @return timestamp
	*/
	static int64_t getTsForPt(const boost::posix_time::ptime& pt);

	/**
	* @brief get string for ptime
	*
	* @param pt as ptime
	*
	* @return string in format YYYY-MM-DD HH:mm:ss
	*/
	static std::string getStr19ForPt(const boost::posix_time::ptime& pt);
	/**
	* @brief get string for ptime
	*
	* @param pt as ptime
	*
	* @return string in format YYYY-MM-DD HH:mm:ss.xxxxxx
	*/
	static std::string getStr26ForPt(const boost::posix_time::ptime& pt);

	/**
	* @brief get week int time for ptime
	*
	* @param pt as ptime
	*
	* @return week int time
	*/
	static int getWeekIntTimeForPt(const boost::posix_time::ptime& pt);

	/**
	* @brief get int time for ptime
	*
	* @param pt as ptime
	*
	* @return day int time
	*/
	static int getDayIntTimeForPt(const boost::posix_time::ptime& pt);

	/**
	* @brief get int time for ptime
	*
	* @param pt as ptime
	*
	* @return int time
	*/
	static int getIntTimeForPt(const boost::posix_time::ptime& pt);



	/**
	* @brief get utc time for timestamp
	*
	* @param ts as timestamp
	*
	* @return ptime
	*/
	static boost::posix_time::ptime getUtcTimeForTs(int64_t ts);
	/**
	* @brief get utc time for double timestamp
	*
	* @param uts as double timestamp
	*
	* @return ptime
	*/
	static boost::posix_time::ptime getUtcTimeForUts(double uts);

	/**
	* @brief get local time for timestamp
	*
	* @param ts as timestamp
	*
	* @return ptime
	*/
	static boost::posix_time::ptime getLocalTimeForTs(int64_t ts);
	/**
	* @brief get local time for double timestamp
	*
	* @param uts as double timestamp
	*
	* @return ptime
	*/
	static boost::posix_time::ptime getLocalTimeForUts(double uts);

	/**
	* @brief get chrono timepoint
	*
	* @param year year such as 2015
	* @param month month such as 01
	* @param day day such as 01
	* @param hour hour such as 01
	* @param minute minute such as 0
	* @param second second such as 0
	*
	* @return chrono time_point
	*/
	static std::chrono::system_clock::time_point getTimePoint(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second);

	/**
	* @brief get date time str in format like 2015-01-01 01:00:00.000000
	*
	* @param tp timepoint
	*
	* @return time string
	*/
	static std::string getTimePointStr(std::chrono::system_clock::time_point & tp);

	/**
	* @brief get time point for an int date(like 20150101)
	*
	* @param intdate integer date like 20150101
	*
	* @return chrono time_point
	*/
	static std::chrono::system_clock::time_point getTimePointForIntDate(int32_t intdate);

	/**
	* @brief get time point for a time stamp
	*
	* @param ts int64 timestamp
	*
	* @return chrono time_point
	*/
	static std::chrono::system_clock::time_point getTimePointForTs(int64_t ts);

};//class TimeUtil

}//namespace XT


#endif