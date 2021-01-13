#pragma once
#ifndef XT_UTIL_H
#define XT_UTIL_H

/**
* \file Util.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide utility functions.
*
* \description
*	This component provides common used functions, such as time, math, and etc.
*/

#include <cstdint>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <clocale>
#include <limits>

#include <thread>

#include <ctime>
#include <chrono>

#include <boost/unordered_map.hpp>
#include <boost/smart_ptr.hpp>

#include "LogUtil.h"

#include "XTConfig.h"
#include "FIXEnum.pb.h"
#include "FIXData.pb.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
//#include "XTData.h"

#include "EnumUtil.h"


#define BOOST_DATE_TIME_SOURCE
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time_adjustor.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>


#define BOOST_SYSTEM_NO_LIB
#define BOOST_FILESYSTEM_NO_LIB
#include <boost/filesystem.hpp>

//#include <boost/regex.hpp>
 

//#define BOOST_LOCALE_SOURCE
//#include <boost/locale.hpp>


#if defined(_WIN32) || defined(_WIN64) || defined(WIN32)
/////#include <WinSock2.h>
#include <Windows.h>
#else
#include <unistd.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include<pthread.h>
//#include <sys/time.h>
//#include <sys/stat.h>
//#include <dirent.h>
//#include <fcntl.h>
//#include <semaphore.h>
#include <iconv.h>

#endif

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32)
#include <wtypes.h>
#else
#endif


namespace XT {

class XT_COMMON_API Util {
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	Util() {}

	/**
	* @brief copy constructor
	*/
	Util(const Util& from) {} // = delete;

	/**
	* @brief copy assignment
	*/
	Util& operator=(const Util& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~Util() {}

	///@}

protected:

	/**
	* @name Empty or NULL Variables
	*/
	///@{

	static const std::string s_EmptyString; ///< empty string

	static std::vector<int> s_EmptyIntVector; ///< empty int vector
	static std::vector<double> s_EmptyDoubleVector; ///< empty double vector
	static std::vector<int64_t> s_EmptyInt64Vector; ///< empty int64_t vector
	static std::vector<std::string> s_EmptyStringVector; ///< empty string vector

	///@}

public:
	/**
	* @name Empty or Null Accessors
	*/
	///@{
	/**
	* @brief get empty string
	*/
	static const std::string& getEmptyString(); ///< empty string

	/**
	* @breif get empty int vector
	*
	* @return empty int vector
	*/
	static const std::vector<int>& getEmptyIntVector();

	/**
	* @breif get empty double vector
	*
	* @return empty double vector
	*/
	static const std::vector<double>& getEmptyDoubleVector();

	/**
	* @breif get empty int64_t vector
	*
	* @return empty int64_t vector
	*/
	static const std::vector<int64_t>& getEmptyInt64Vector();

	/**
	* @breif get empty string vector
	*
	* @return empty string vector
	*/
	static const std::vector<std::string>& getEmptyStringVector();

	///@}
protected :

	/** 
	* @name Static Variables
	*/
	///@{
	static const boost::posix_time::ptime EPOCH_UTC; ///< epoch utc
	static const boost::posix_time::ptime EPOCH_UTC_LOCAL; ///< epoch utc local

	static const int64_t s_Million; ///< one million
	static const int64_t s_Billion; ///< one billion
  	static const int64_t s_TenMillion; ///< ten million
	static const double s_Micro; ///< micro, 10^-6, 1/million

  	static const int64_t s_OneUTSSecond; ///< one unix second
  	static const int64_t s_OneUTSMinute; ///< one unix minute
  	static const int64_t s_OneUTSHour; ///< one unix hour
  	static const int64_t s_OneUTSDay; ///< one unix day
  	static const int64_t s_OneNETSecond; ///< one dot net second
  	static const int64_t s_OneNETMinute; ///< one dot net minute
  	static const int64_t s_OneNETHour; ///< one dot net hour
  	static const int64_t s_OneNETDay; ///< one dot net day

  	static const int64_t s_OneSecond; ///< one second
  	static const int64_t s_OneMinute; ///< one minute
  	static const int64_t s_OneHour; ///< one hour
	static const int64_t s_OneDay; ///< one day
	static const int64_t s_TwoSeconds; ///< two seconds
	static const int64_t s_FiveSeconds; ///< five seconds
	static const int64_t s_TenSeconds; ///< ten seconds
	static const int64_t s_FifteenSeconds; ///< fifteen seconds
	static const int64_t s_HalfSecond; ///< 0.5 seconds

	static const int64_t s_Int64DateTimeSecondMultiplier;
	static const int64_t s_Int64DateTimeMinuteMultiplier;
	static const int64_t s_Int64DateTimeHourMultiplier;
	static const int64_t s_Int64DateTimeDayMultiplier;
	static const int64_t s_Int64DateTimeMonthMultiplier;
	static const int64_t s_Int64DateTimeYearMultiplier;




	static const double s_NaN; ///< not a number double
	static const double s_NaN_Thresh; ///< thresh for testing if a double is NaN

	static const double s_Epsilon; ///< double epsilon
	static const double s_EpsilonMinus; ///< negative epsilon
	static const double s_Px_Min; ///< minimum price
	static const double s_Px_Max; ///< maximum price
	static const double s_Px_NaN; ///< invalid price
	static const double s_Px_Epsilon; ///< price epsilon
	static const double s_ImpVol_Min; ///< minimum implied vol
	static const double s_ImpVol_Max; ///< maximum implied vol

	///////////////////////////////////

	static int64_t s_ChinaStockMorningStart; ///<9:30 shift
	static int64_t s_ChinaStockMorningEnd; ///<11:30 shift
	static int64_t s_ChinaStockAfternoonStart; ///< 13:00 shift
	static int64_t s_ChinaStockAfternoonEnd; ///< 15:00 shift

	static int64_t s_LocalToUtcTsOffset; ///< diff between Utc and local
	static int64_t s_BeijingToUtcTsOffset; ///< diff between Beijing and local
	static int64_t s_ChicagoToUtcTsOffset; ///< diff between Chicago and local
	static int64_t s_NewyorkToUtcTsOffset; ///< diff between Newyork and local
	static int s_DaylightSavingFlag; ///< day light saving flag, if >0, it is day light saving


	///@}

public:

	/** 
	* @name Static Variables Accessors
	*/
	///@{
//	static const boost::posix_time::ptime EPOCH_UTC;
//	static const boost::posix_time::ptime EPOCH_UTC_LOCAL;

	/**
	* @brief get const one million
	*
	* @return const one million
	*/
	static int64_t getMillion();  

	/**
	* @brief get const  ten million
	*
	* @return const ten million
	*/
	static int64_t getTenMillion();  

	/**
	* @brief get const micro, 10^-6, 1/million
	*
	* @retrun const micro, 10^-6, 1/million
	*/
	static double getMicro();  

	/**
	* @brief get const one unix second
	*
	* @return const one unix second
	*/
	static int64_t getOneUTSSecond(); 

	/**
	* @brief get const one unix minute
	*
	* @return const one unix minute
	*/
	static int64_t getOneUTSMinute();  

	/**
	* @brief get const one unix hour
	*
	* @return const one unix hour
	*/
	static int64_t getOneUTSHour();  

	/**
	* @brief get const one unix day
	*
	* @return const one unix day
	*/
	static int64_t getOneUTSDay();  

	/**
	* @brief get const one dot net second
	*
	* @return one dot net second
	*/
	static int64_t getOneNETSecond();  

	/**
	* @brief get const one dot net minute
	*
	* @return const one dot net minute
	*/
	static int64_t getOneNETMinute(); 

	/**
	* @brief get const one dot net hour
	*
	* @return const one dot net hour
	*/
	static int64_t getOneNETHour();  

	/**
	* @brief get const one dot net day
	*
	* @return const one dot net day
	*/
	static int64_t getOneNETDay();  

	/**
	* @brief get const one second
	*
	* @return const one second
	*/
	static int64_t getOneSecond();  

	/**
	* @brief get const one minute
	*
	* @return const one minute
	*/
	static int64_t getOneMinute();  

	/**
	* @brief get const one hour
	*
	* @return const one hour
	*/
	static int64_t getOneHour(); 

	/**
	* @brief get const one day
	*
	* @return const one day
	*/
	static int64_t getOneDay();  

	/**
	* @brief get const two seconds
	*
	* @return const two seconds
	*/
	static int64_t getTwoSeconds();  

	/**
	* @brief get const five seconds
	*
	* @return const five seconds
	*/
	static int64_t getFiveSeconds();  

	/**
	* @brief get const ten seconds
	*
	* @return const ten seconds
	*/
	static int64_t getTenSeconds(); 

	/**
	* @brief get const fifteen seconds
	*
	* @return const fifteen seconds
	*/
	static int64_t getFifteenSeconds();  

	/**
	* @brief get const half seconds
	*
	* @return const half seconds
	*/
	static int64_t getHalfSecond();  


	/**
	* @brief get const NaN(not a number)
	*
	* @return const NaN
	*/
	static double getNaN();  

	/**
	* @brief get const NaN(not a number) Thresh
	*
	* @return const NaN Thresh
	*/
	static double getNaNThresh(); 

	/**
	* @brief get const epsilon
	*
	* @return const epsilon
	*/
	static double getEpsilon();  

	/**
	* @brief get const negative epsilon
	*
	* @return const negative epsilon
	*/
	static double getEpsilonMinus();  

	/**
	* @brief get const min price
	*
	* @return const min price
	*/
	static double getPxMin();  

	/**
	* @brief get const max price
	*
	* @return const max price
	*/
	static double getPxMax();  

	/**
	* @brief get const epsilon price
	*
	* @return const epsilon price
	*/
	static double getPxEpsilon(); 

	/**
	* @brief get invalid price
	*
	* @return const invalid price
	*/
	static double getPxNaN();

	/**
	* @brief test if it is NaN price
	*
	* @return if it is NaN price
	*/
	static bool isPxNaN(double d);

	/**
	* @brief get const min implied vol
	*
	* @return const min implied vol
	*/
	static double getImpVolMin();  

	/**
	* @brief get const max implied vol
	*
	* @return const max implied vol
	*/
	static double getImpVolMax(); ///< maximum implied vol

	/**
	* @brief get number of decimal places
	*
	* @return number of decimal places for a double
	*/
	static int getNumDecimalPlaces(double v);

	/**
	* @brief get scale for a double to change to integer
	*
	* @return scale
	*/
	static double getScale(double v);

////////////////////////////
	/**
	* @brief get china stock morning start (9:30 shift)
	*
	* @return china stock morning start (9:30 shift)
	*/
	static int64_t getChinaStockMorningStart(); 
	/**
	* @brief set china stock morning start (9:30 shift)
	*
	* @param v as china stock morning start  
	*/
	static void setChinaStockMorningStart(int64_t v);

	/**
	* @brief get china stock morning end (11:30 shift)
	*
	* @return china stock morning end (11:30 shift)
	*/
	static int64_t getChinaStockMorningEnd();  
	/**
	* @brief set china stock morning end (11:30 shift)
	*
	* @param v as china stock morning end  
	*/
	static void setChinaStockMorningEnd(int64_t v);
	
	/**
	* @brief get china stock afternoon start (13:30 shift)
	*
	* @return china stock afternoon start  
	*/
	static int64_t getChinaStockAfternoonStart(); 
	/**
	* @brief set china stock afternoon start (13:30 shift)
	*
	* @param v as china stock afternoon start
	*/
	static void setChinaStockAfternoonStart(int64_t v);
	
	/**
	* @brief get china stock afternoon end (15:00 shift)
	*
	* @return china stock afternoon end
	*/
	static int64_t getChinaStockAfternoonEnd();  

	/**
	* @brief set china stock afternoon end (15:00 shift)
	*
	* @param v as china stock afternoon end
	*/
	static void setChinaStockAfternoonEnd(int64_t v);

	/**
	* @brief get local to utc offset
	*
	* @return local to utc offset
	*/
	static int64_t getLocalToUtcTsOffset();   
	/**
	* @brief set local to utc offset
	*
	* @param v as local to utc offset
	*/
	static void setLocalToUtcTsOffset(int64_t v);
	
	/**
	* @brief get beijing to utc offset
	*
	* @return beijing to utc offset
	*/
	static int64_t getBeijingToUtcTsOffset();  

	/**
	* @brief set beijing to utc offset
	*
	* @param v as beijing to utc offset
	*/
	static void setBeijingToUtcTsOffset(int64_t v);
	
	/**
	* @brief get chicago to utc offset
	*
	* @return chicago to utc offset
	*/
	static int64_t getChicagoToUtcTsOffset();  
	/**
	* @brief set chicago to utc offset
	*
	* @param v as chicago to utc offset
	*/
	static void setChicagoToUtcTsOffset(int64_t v);
	
	/**
	* @brief get new york to utc offset
	*
	* @return new york to utc offset
	*/
	static int64_t getNewyorkToUtcTsOffset();  
	/**
	* @brief set new york to utc offset
	*
	* @param v as new york to utc offset
	*/
	static void setNewyorkToUtcTsOffset(int64_t v);
	
	/**
	* @brief get day night saving flag, if >0, it is day light saving
	*
	* @return day night saving flag
	*/
	static int getDaylightSavingFlag();  

	/**
	* @brief set day night saving flag, if >0, it is day light saving
	*
	* @param v as day night saving flag
	*/
	static void setDaylightSavingFlag(int v);



	///@}


public:
 
	/** 
	* @name Sequence and Order Ids
	*/
	///@{
	/**
	* @brief get next sequence id
	*/
	static int32_t getNextCountSeqId();

	/**
	* @brief get maxSeqIdPerSecond
	*/
	static int32_t getMaxSeqIdPerSecond();

	/**
	* @brief set maxSeqIdPerSecond
	*/
	static void setMaxSeqIdPerSecond(int32_t v);


	///**
	//* update intTime
	//**/
	//static void updateIntTime();

	/**
	* @brief update week inttime
	*/
	static void updateWeekIntTime();

	/**
	* @brief get next Sequence Id
	*/
	static int32_t getNextSeqId();


	/**
	* @brief get next quote id
	*/
	static int32_t getNextQid();

	/**
	* @brief get next order id
	*/
	static int32_t getNextOid(BuySellType::enumtype bs);

	/**
	* @brief get next buy order id
	*/
	static int32_t getNextBuyOid();

	/**
	* @brief get next sell order id
	*/
	static int32_t getNextSellOid();

	/**
	* @brief get order id from quote id
	* @param bs Buy or Sell
	* @param qid quote id
	*/
	static int getOidFromQid(BuySellType::enumtype bs,int qid) ;

	/**
	* @brief get quote id from order id
	* @param oid order id
	*/
	static int getQidFromOid(int oid) ;

	/**
	* @brief get coupled order id for an order id
	* @param oid order id
	*/
	static int getCoupledOid(int oid) ;
	///@}


	/** 
	* @name Double Price and Vol
	*/
	///@{

	/**
	* @brief test if a string is numeric
	*/
	static bool isNumeric(const std::string& s);

	/**
	* @brief test if a double is Not a number
	* @param d double
	*/
	static bool isNaNDouble(double d) ;
	/**
	* @brief test if a double is valid
	*/
	static bool isValidDouble(double d) ;

	/**
	* @brief test if a price is valid
	*/
	static bool isValidPx(double d) ;
	/**
	* @brief test if a vol is valid
	*/
	static bool isValidVol(double d) ;

	/**
	* @brief test if a vega value is valid
	*/
	static bool isValidVega(double d);

	///@}

	/** 
	* @name DateTime
	*/
	///@{
	/**
	* @brief sleep for milliseconds
	*/
	static void sleep(unsigned int ms);


	/**
	* @brief get tick count in milli seconds
	*/
	static int64_t getTickCount();

	/**
	* @brief get week int time for timestamp
	*/
	static int getWeekIntTimeForTs(int64_t ts);


 
	///**
	//* get current time point
	//*/
	//static std::chrono::system_clock::time_point getNowTp() ;

	/**
	* @brief get current date time string in format like 2015-01-01 01:00:00.000000
	*/
	static std::string getNowStr() ;

	/**
	* @brief get current date time string in json format like "edt":"2015-01-01 01:00:00.000000"
	*/
	static std::string getNowJsonStr();

	/**
	* @brief get current time string in format like 01:00:00.000000
	*/
	static std::string getNowTimeStr() ;

	/**
	* @brief get current year
	*/
	static int getNowYear();

	/**
	* @brief get current month
	*/
	static int getNowMonth();

	/**
	* @brief get current day
	*/
	static int getNowDay();

	/**
	* @brief get current time integer in HHMMSS
	*/
	static int32_t getNowHHMMSSInt();

	/**
	* @brief get current integer hour
	*/
	static int getNowHour() ;

	/**
	* @brief get current integer minute
	*/
	static int getNowMinute() ;

	/**
	* @brief get current integer second
	*/
	static int getNowSecond() ;

	/**
	* @brief get current int64datetime
	*/
	static int64_t getNowInt64DateTime();

	/**
	* @brief get diff in microseconds for two int64datetime
	*/
	static int64_t getInt64DateTimeDiff(int64_t dt0, int64_t dt1);


	/**
	* @brief get current time stamp
	*/
	static int64_t getNowTs()  ;

	/**
	* @brief get current week int time
	*/
	static int32_t getNowWeekIntTime();

	/**
	* @brief get current utc time stamp
	*/
	static int64_t getNowUtcTs();

	/**
	* @brief get current time stamp with hours shfit to Utc
	*/
	static int64_t getNowTsWithUtcHoursShift(int hours);

	/**
	* @brief get current beijing time stamp
	*/
	static int64_t getBeijingNowTs();

	 /**
	 * @brief get current beijing intdate
	 */
	static int getBeijingNowIntDate();

	/**
	* @brief get current beijing now date time str
	*/
	static std::string getBeijingNowStr();

	/**
	* @brief get current beijing time str in format HH:MM::SS
	*/
	static std::string getBeijingNowHHMMSSStr();

	/**
	* @brief get current Chicago time stamp
	*/
	static int64_t getChicagoNowTs();

	/**
	* @brief get current chicago intdate
	*/
	static int getChicagoNowIntDate();

	/**
	* @brief get current chicago now date time string
	*/
	static std::string getChicagoNowStr();

	/**
	* @brief get current chicago time str in format HH:MM::SS
	*/
	static std::string getChicagoNowHHMMSSStr();

	/**
	* @brief get current newyork time stamp
	*/
	static int64_t getNewyorkNowTs();

	/**
	* @brief get current newyork intdate
	*/
	static int getNewyorkNowIntDate();

	/**
	* @brief get current new york date time string
	*/
	static std::string getNewyorkNowStr();

	/**
	* @brief get current new york time str in format HH:MM::SS
	*/
	static std::string getNewyorkNowHHMMSSStr();
	
	/**
	* @brief get current unix time stamp in double
	*/
	static double getNowUts() ;

	/**
	* @brief get current int date, like 20150101
	*/
	static int32_t getNowIntDate() ;

	/**
	* @brief get shifted intdate with shift days
	*
	* @param intdate as int date
	* @param days
	*
	* @return int date
	*/
	static int getShiftedIntDate(int intdate, int days);

	/**
	* @brief is valid intdate or not
	*
	* @param i as intdate
	*
	* @return if intdate i is valid or not
	*/
	static bool isValidIntDate(int i);

	/**
	* @brief get reference Ts for intdate
	*
	* @param intdate as int date
	*
	* @return timestamp reference
	*/
	static int64_t getTsRef(int intdate);

	/**
	* @brief set reference Ts for intdate
	*
	* @param intdate as int date
	*/
	static void setTsRef(int intdate);

	/**
	* @brief get int64 timestamp
	*
	* @param sec seconds
	* @param usec microseconds
	*
	* @return timestamp
	*/
  static int64_t getTs(int32_t sec, int32_t usec) ;

  /**
  * @brief get double timestamp
  *
  * @param sec seconds
  * @param usec microseconds
  *
  * @return double timestamp
  */
  static double getUts(int32_t sec, int32_t usec) ;


	/**
	* @brief get date time string for timestamp
	*
	* @param ts int64_t timestamp
	*
	* @return string in YYYY-MM-DD HH:mm:ss.xxxxxx
	*/
	static std::string getStrForTs(int64_t ts) ;

	/**
	* @brief get timestamp for date time str
	*
	* @param s datetime string
	*
	* @return timestamp
	*/
	static int64_t getTsForStr(const std::string& s);

	/**
	* @brief get date time string yyyy-MM-dd HH:mm:ss for timestamp
	*
	* @param ts int64_t timestamp
	*
	* @return string in YYYY-MM-DD HH:mm:ss
	*/
	static std::string getStr19ForTs(int64_t ts) ;

	/**
	* @brief get time string in HH::mm:ss format
	*
	* @param ts as timestamp
	*
	* @return time string
	*/
	static std::string getHHMMSSStrForTs(int64_t ts);

	/**
	* @brief get timestamp for datetime str
	*
	* @param s datetime string
	*
	* @return timestamp
	*/
	static int64_t getTsForStr19(const std::string& s);

	/**
	* @brief get timestamp for date and time str
	*
	* @param date str
	* @param time str
	*
	* @return timestamp
	*/
	static int64_t getTsForDateAndTimeStr(const std::string& sDate, const std::string& sTime);

	/**
	* @brief get timestamp for intdate and time str
	*
	* @param intdate
	* @param time str
	*
	* @return timestamp
	*/
	static int64_t getTsForIntDateAndTimeStr(int intdate, const std::string& sTime);

	/**
	* @brief get timestamp for intdate and inttime
	*
	* @param intdate as int date
	* @param inttime
	* 
	* @return timestamp
	*/
	static int64_t getTsForIntDateAndIntTime(int intdate, int inttime);



	/**
	* @brief get date string(like 20150101) for timestamp
	*
	* @param ts int64_t timestamp
	*
	* @return date string
	*/
	static std::string getDateStrForTs(int64_t ts) ;

	/**
	* @brief get time string(like 01:01:00) for timestamp
	*
	* @param ts int64_t timestamp
	* 
	* @return time string
	*/
	static std::string getTimeStrForTs(int64_t ts);

	/**
	* @brief get int date(like 20150101) for timestamp
	*
	* @param int64_t timestamp
	*
	* @return int date
	*/
	static int getIntDateForTs(int64_t ts) ;

	/**
	* @brief get int time(like 100101 for 10:01:01) for timestamp
	*
	* @param int64_t timestamp
	*
	* @return int time
	*/
	static int getIntTimeForTs(int64_t ts);

	/**
	* @brief get int64 datetime(like 20180318100101000000) for timestamp
	*
	* @param ts as timestamp
	*
	* @return int64_t date
	*/
	static int64_t getInt64DateTimeForTs(int64_t ts);

	/**
	* @brief get int date(like 20180101) for int64 datetime
	*
	* @param ts as timestamp
	*
	* @return int date
	*/
	static int getIntDateForInt64DateTime(int64_t dt);

	/**
	* @brief get int time(like 100101 for 10:01:01) for int64 datetime
	*
	* @param ts as timestamp
	*
	* @return int time
	*/
	static int getIntTimeForInt64DateTime(int64_t dt);

	/**
	* @brief get day of week for timestamp
	*
	* @param ts as timestamp
	*
	* @return day of week
	*/
	static int getDayOfWeekForTs(int64_t ts);

	/**
	* @brief get timestamp for intdate
	*
	* @param intdate as int date
	*
	* @return timestamp
	*/
	static int64_t getTsForIntDate(int intdate);

	/**
	* @brief get day of week for intdate
	*
	* @param intdate as intdate
	*
	* @return day of week, 0 for sunday, 1 for monday
	*/
	static int getDayOfWeekForIntDate(int intdate);



	/**
	* @brief get timestamp for integer year,month,day,hour,minute,second, and microseconds
	*
	* @param year integer year like 2015
	* @param month integer month like 01
	* @param day integer day like 01
	* @param hour integer hour like 01
	* @param minute integer minute like 01
	* @param second integer second like 0
	* @param micro integer micro seconds
	*
	* @return timestamp
	*/
	static int64_t getTsForYMDHMSU(int year, int month, int day, int hour, int minute, int second, int micro) ;

	/**
	* @brief get time stamp for intdate, timestr and milliseconds
	*
	* @param intdate for example, 20150101
	* @param timestr
	* @param milliseconds
	*
	* @return timestamp
	*/
	static int64_t getTsForDayTimeMilliseconds(int intdate, const std::string& timestr, int milliseconds) ;

	/**
	* @brief get timestamp for intdate and timestr
	*
	* @param int date for example, 20150101
	* @param timestr 08:58:40.853
	* 
	* @return timestamp
	*/
	static int64_t getTsForIntDateTimestr(int intdate, const std::string& timestr);

	/**
	* @brief get int hour for timerstr
	*
	* @param timestr 08:58:40.853
	*
	* @return int hour
	*/
	static int32_t getHourForTimestr(const std::string& timestr);

	/**
	* @brief get days between two dates
	*
	* @param intdate1 date from
	* @param intdate2 date to
	*
	* @return number of days
	*/
	static int32_t getDaysBetween(int32_t intdate1, int32_t intdate2) ;

	/**
	* @brief get date str(like 20150101) for intdate
	*
	* @param intdate integer date like 20150101
	*
	* @return date string
	*/
	static std::string getDateStrForIntDate(int intdate) ;

	/**
	* @brief get timestamp for date time string with length 26
	*
	* @param dtstr date time string
	*
	* @return timestamp
	*/
	static int64_t getTsForDTStr(const std::string& dtstr) ;

	/**
	* @brief get local time string
	* 
	* @param ts as timestamp
	* 
	* @return string
	*/
  static std::string getLocalTimeStrForTs(int64_t ts) ;
  /**
  * @brief get local time string
  *
  * @param ts as double timestamp
  *
  * @return string
  */
  static std::string getLocalTimeStrForUts(double uts) ;



	/**
	* @brief get seconds part for timestamp
	*
	* @param ts timestamp
	*
	* @return seconds
	*/
  static int32_t getSecForTs(int64_t ts) ;

  /**
  * @brief get seconds part for double timestamp
  *
  * @param ts double timestamp
  *
  * @return seconds
  */
  static int32_t getSecForUts(double uts) ;

  /**
  * @brief get microseconds part for timestamp
  *
  * @param ts timestamp
  *
  * @return microseconds
  */
  static int32_t getUsecForTs(int64_t ts) ;

  /**
  * @brief get microseconds part for double timestamp
  *
  * @param uts double timestamp
  *
  * @return microseconds
  */
  static int32_t getUsecForUts(double uts) ;

   /**
   * @brief get matlab time value for timestamp
   *
   * @param dtTicks timestamp
   *
   * @return matlab time
   */
  static double getMatlabDatenumForTicks(int64_t dtTicks) ;

  /**
  * @brief get timestamp for matlab time
  *
  * @param dn matlab time
  *
  * @return ticks
  */
  static int64_t getTicksForMatlabDatenum(double dn) ;

  /**
  * @brief get double timestamp for dot net timestamp
  *
  * @param dtTicks int64_t timestamp
  *
  * @return double timestamp
  */
  static double getUtsForTicks(int64_t dtTicks) ;

  /**
  * @brief get dot net timestamp for double timestamp
  *
  * @param uts double timestamp
  *
  * @return ticks
  */
  static int64_t getTicksForUts(double uts) ;

  /**
  * @brief get timestamp for dot net timestamp
  *
  * @param dtTicks dot net timestamp
  *
  * @return timestamp
  */
  static int64_t getTsForTicks(int64_t dtTicks) ;

  /**
  * @brief get dotnet timestamp for int64_t timestamp
  *
  * @param int64_t timestamp
  *
  * @return ticks
  */
  static int64_t getTicksForTs(int64_t ts) ;

  /**
  * @brief get months between two dates
  *
  * @param intdate1 date from
  * @param intdate2 date to
  *
  * @return number of months
  */
  static int32_t getMonthsBetween(int32_t intdate1, int32_t intdate2) ;
	///@}

  /** 
  * @name IP Address Functions
  */
  ///@{

  /**
  * @brief convert ip address to int64_t
  *
  * @param ip string
  *
  * @return int64_t ip
  */
  static int64_t getInt64IPForIPAddress(const std::string& ip);

  /**
  * @brief convert int64_t to ip address
  *
  * @param int64_t value
  *
  * @return ip address
  */
  static std::string getIpAddressForInt64IP(int64_t v);

  /**
  * @brief get prefix for int64_t ip address
  *
  * @param int64_t value
  *
  * @return prefix for int64_t ip
  */
  static int64_t getPrefixForInt64IP(int64_t v);


  /**
  * @brief add prefix for int64_t ip address
  *
  * @param int64_t value
  * @param addv as address
  *
  * @return int64_t ip
  */
  static int64_t addPrefixForInt64IP(int64_t ipv, int64_t addv);


  ///@}

	/** 
	* @name String Functions
	*/
	///@{

	/**
	* @brief test if a str has prefix
	*
	* @param prefix
	* @param str
	*
	* @return if str starts with prefix
	*/
  static bool startsWithCStr(const char* prefix, const char* str);

  /**
  * @brief test if a str has prefix
  *
  * @param prefix
  * @param str
  *
  * @return if str starts with prefix
  */
  static bool startsWith(const std::string& prefix, const std::string& str);

  /**
  * @brief test if a string has valid prefix
  *
  * @param s as string
  * @param valid prefix set, if empty, then prefix is always valid
  *
  * @return if a string has valid prefix or not
  */
  static bool hasValidPrefix(const std::string& s, const std::set<std::string>& validset);

  /**
  * @brief convert const char pointer to string
  *
  * @param const char* cstr
  *
  * @return string
  */
  static std::string constchar2str(const char* c);


  /**
  * @brief convert int to string
  *
  * @param i integer
  *
  * @return string
  */
  static std::string int2str(int i) ;

  /**
  * @brief convert unsigned int to string
  *
  * @param unsigned int i
  *
  * @return string
  */
  static std::string uint2str(unsigned int i);

  /**
  * @brief convert long to string
  *
  * @param l long
  *
  * @return string
  */
  static std::string long2str(long l) ;

  /**
  * @brief convert longlong to string
  *
  * @param ll long long
  *
  * @return string
  */
  static std::string longlong2str(long long ll);

  /**
  * @brief convert size_t to string
  *
  * @param st size_t
  *
  * @return string
  */
  static std::string size_t2str(size_t st);

  /**
  * @brief convert int64_t to string
  *
  * @param i int64_t
  *
  * @return string
  */
  static std::string int642str(int64_t i) ;

  /**
  * @brief convert double to string
  *
  * @param d double
  *
  * @return string
  */
  static std::string double2str(double d) ;

  /**
  * @brief convert thread id to string
  *
  * @param tid thread id
  *
  * @return string
  */
  static std::string threadid2str(std::thread::id & tid) ;

  /**
  * @brief convert bool to string
  *
  * @param b bool
  *
  * @return string
  */
  static std::string bool2str(bool b) ;
 
 

  ///@}

	/** 
	* @name sql helper functions
	*/
	///@{

  /**
  * @brief get select sql for instruments between time range
  *
  * @param intdate as int date
  * @param securitytypestr as security type string
  * @param spanYear as span year length
  *
  * @return sql query string
  */
  static std::string getSelectSqlForInstruments(int intdate, const std::string& securitytypestr, int spanYear);

  /**
  * @brief get select sql for future between time range
  *
  * @param intdate as int date
  * @param spanYear as span year length
  *
  * @return sql query string
  */
  static std::string getSelectSqlForFuture(int intdate, int spanYear);

  /**
  * @brief get select sql for option between time range
  */
  static std::string getSelectSqlForOption(int intdate, int spanYear);

  /**
  * @brief get select sql for stock between time range
  *
  * @param intdate as int date
  * @param spanYear as span year length
  *
  * @return sql query string
  */
  static std::string getSelectSqlForStock(int currIntdate, int spanYear);

  /**
  * @brief get select sql for ETF between time range
  *
  * @param intdate as int date
  * @param spanYear as span year length
  *
  * @return sql query string
  */
  static std::string getSelectSqlForETF(int intdate, int spanYear);

  /**
  * @brief get select sql for index between time range
  *
  * @param intdate as int date
  * @param spanYear as span year length
  *
  * @return sql query string
  */
  static std::string getSelectSqlForIndex(int intdate, int spanYear);

	///@}


	/** 
	* @name Options
	*/
	///@{
	
	/**
	* @brief get underlying product for product
	*
	* @param productID as product id
	*
	* @return underlying product
	*/
	static std::string getUnderlyingProduct(std::string productID);

	/**
	* @brief set underlying product for product
	*
	* @param productID as product id
	* @param underlyingProduct as underlying product
	*
	*/
	static void setUnderlyingProduct(std::string productID,std::string underlyingProduct);

	/**
	* get exercise style for underlying product
	* @param undlyproduct underlying product
	*/
//	static ExerciseStyle::type getExerciseStyle(std::string undlyproduct);

	/**
	* @brief get default curve name for underlying product
	*
	* @param undproduct as underlying product id
	*
	* @return curve name
	*/
	static std::string getDefaultCurveName(std::string undlyproduct);

	/**
	* @brief get market maker spread for cotton
	*
	* @param bidPx bid price
	* @param monthsequence the sequence of month
	*
	* @return spread
	*/
	static double getMMSpread_CF(double bidPx, int monthsequence);

	/**
	* @brief get market maker spread for sugar
	*
	* @param bidPx bid price
	* @param monthsequence the sequence of month
	* 
	* @return spread
	*/
	static double getMMSpread_SR(double bidPx, int monthsequence);

	/**
	* @brief get market maker spread for IF
	*
	* @param bidPx bid price
	* @param monthsequence the sequence of month
	*
	* @return spread
	*/
	static double getMMSpread_IF(double bidPx, int monthseq);

	/**
	* @brief get market maker spread for m
	*
	* @param bidPx bid price
	* @param monthseq the sequence of month
	*
	* @return spread
	*/
	static double getMMSpread_m(double bidPx, int monthseq);

	///@}


	///** 
	//* @name File
	//*/
	/////@{
	///**
	//* @brief test if a file exists
	//*
	//* @param file name of file
	//*
	//* @return if file exists or not
	//*/
	//static bool existsFile(const std::string& filename);


	///**
	//* @brief back up a file
	//*
	//* @param file name of file
	//*
	//* @return status
	//*/
	//static int bkupFile(const std::string& filename);

	///**
	//* @brief back up a file
	//*
	//* @param file name of file
	//* @param bkup file name
	//*
	//* @return status
	//*/
	//static int bkupFileTo(const std::string& filename,const std::string& bkupfile);


	///**
	//* @brief find files by prefix name
	//*
	//* @param tgtPath as path
	//* @param nameprefix as prefix
	//*
	//* @return vector of file names
	//*/
	//static std::vector<std::string> getFilesWithNameStartsWith(const std::string& tgtPath, const std::string& nameprefix);

	///**
	//* @brief find files with substring in the name
	//*
	//* @param tgtPath as path
	//* @param subname
	//*
	//* @return vector of file names
	//*/
	//static std::vector<std::string> getFilesWithNameContains(const std::string& tgtPath, const std::string& subname);

	/////@}

 	/** 
	* @name Math
	*/
	///@{
	/**
	* @brief get min of two int32 integers
	*
	* @param x
	* @param y
	*
	* @return min of x and y
	*/
  static int32_t min_int32(int32_t x, int32_t y) ;
  /**
  * @brief get max of two int32 integers
  *
  * @param x
  * @param y
  *
  * @return max of x and y
  */
  static int32_t max_int(int32_t x, int32_t y);

  /**
  * @brief get min of two int64 integers
  *
  * @param x
  * @param y
  * 
  * @return min of x and y
  */
  static int64_t min_int64(int64_t x, int64_t y) ;
  /**
  * @brief get max of two int64 integers
  * 
  * @param x 
  * @param y
  * 
  * @return max of x and y
  */
  static int64_t max_int64(int64_t x, int64_t y) ;

  /**
  * @brief get sign of int32 integer
  *
  * @param x as int  value
  *
  * @return sign
  */
  static int32_t sign_int32(int32_t x) ;
  /**
  * @brief get sign of int64 integer
  *
  * @param x as int64_t value
  *
  * @return sign
  */
  static int64_t sign_int64(int64_t x) ;

  /**
  * @brief get abs of int32 integer
  *
  * @param x as int value
  *
  * @return absolute value
  */
  static int32_t abs_int32(int32_t x);
  /**
  * @brief get abs of int64 integer
  *
  * @param x as int64_t value
  *
  * @return absolute value
  */
  static int64_t abs_int64(int64_t x) ;

  /**
  * @brief round a double to 2 decimals
  *
  * @param x as double
  *
  * @return rounded value
  */
  static double round2(double x) ;
  /**
  * @brief round a double to 4 decimals
  *
  * @param x as double
  *
  * @return rounded value
  */
  static double round4(double x);
  /**
  * @brief round a double to 6 decimals
  *
  * @param x as double 
  *
  * @return rounded value
  */
  static double round6(double x) ;

  /**
  * @brief round a double to tick price
  *
  * @param px as double price
  * @param tickpx as tick price
  *
  * @return rounded price
  */
  static double roundPx(double px, double tickPx) ;
  /**
  * @brief round up a double to tick price
  *
  * @param px as double price
  * @param tickpx as tick price
  *
  * @return rounded price
  */
  static double roundUpPx(double px, double tickPx) ;
  /**
  * @brief round down a double to tick price
  * 
  * @param px as double price
  * @param tickpx as tick price
  *
  * @return rounded price
  */
  static double roundDnPx(double px, double tickPx) ;

  /**
  * @brief get median from a double array
  * 
  * @param dv as double vector
  *
  * @return median value
  */
  static double getMedian(const std::vector<double>& dv);
  /**
  * @brief get mode from a double array
  *
  * @param dv as double vector
  *
  * @return mode value
  */
  static double getMode(const std::vector<double>& dv);
  /**
  * @brief get mean from a double array
  *
  * @param dv s double vector
  *
  * @return mean value
  */
  static double getMean(const std::vector<double>& dv);
 
	///@}



	/** 
	* @name Character Coding
	*/
	///@{
  /**
  * @brief convert gb2312 string to utf-8 string
  *
  * @param s as string encoded in GBK2312
  *
  * @return utf8 string
  */
  static std::string gb2312ToUtf8(const std::string& s);


	/**
	* @brief convert gbk string to utf-8 string
	*
	* @param s as string encoded in GBK
	*
	* @return utf8 string
	*/
	static std::string gbkToUtf8(const std::string& s);


	/**
	* @brief convert gbk char* from gbk to utf8 char*
	*
	* @param utfStr as out put utf8 string
	* @param maxUftStrLen as maximum length
	* @param srcStr as input string
	*/
	static int gbk2Utf8(char *utfStr, size_t maxUtfStrlen, const char *srcStr);

	/**
	* @brief get utf8 string from gbk string
	*
	* @param s as string encoded in GBK
	*
	* @return utf8 string
	*/
	static std::string getUtf8StrForGbkStr(const std::string& s);


	///@}

protected:
//	static int32_t m_currIntTime;
	static int32_t m_currWeekIntTime; ///< current week int time
	static int32_t m_currSeqId; ///< current sequence id

	static int32_t m_countSeqId; ///< count sequence id
	static int32_t m_maxSeqIdPerSecond; ///< maximum sequence id per second
	static int64_t m_tsShift; ///< timestamp shift
	static int64_t m_tsRef; ///< timestamp reference
    static int64_t m_tsSeqId; ///< timestamp sequence id

	static boost::unordered_map<std::string,std::string> m_productIDToUnderlyingProductMap; ///< map for product id to underlying product

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


 
}; //end class Util


}//end namespace XT


#endif
