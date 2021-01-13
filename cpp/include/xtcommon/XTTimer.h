#pragma once 
#ifndef XT_TIMER_H
#define XT_TIMER_H


/**
* \file XTTimer.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for timer.
*
* \description
*	Designed for timer.
*/

#include <cstdint>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <sstream>

#include <memory>

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/unordered_set.hpp>
#include <boost/signals2.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>			 
#include <boost/bind.hpp>			 
#include <boost/any.hpp>	 

#include <ctime>
#include <chrono>

#include "XTConfig.h"
#include "safe_ptr.h"

#include "log4z.h"
#include "Util.h"
#include "TimeUtil.h"

namespace XT
{

	class XTTimer;
	class XTTimerMgr;

class XT_COMMON_API XTTimer
{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	XTTimer();

	/**
	* @brief constructor
	*/
	XTTimer(int i);

	/**
	* @brief constructor
	*/
	XTTimer(int i, int nowtype);

	/**
	* @brief default copy constructor
	*/
	XTTimer(const XTTimer& from);// = default;

	/**
	* @brief default copy assignment
	*/
	XTTimer& operator=(const XTTimer& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~XTTimer();

	///@}
 
	/**
	* @brief get now type
	*
	* @return nowtype, default is 0, if it is 1, use outside timestamp(such as market timestamp)
	*/
	int getNowType();

	/**
	* @brief set now type
	*/
	void setNowType(int i);

	/**
	* @brief set now timestamp
	*
	* @param ts
	*/
	void setNowTs(int64_t ts);

	/**
	* @brief get timer interval
	*
	* @return interval milli seconds
	*/
	int getInterval();

	/**
	* @brief get count
	*
	* @return count
	*/
	int getCount();

	/**
	* @brief get intdate
	*
	* @return intdate
	*/
	int getIntDate();

	/**
	* @brief get inttime
	*
	* @return inttime
	*/
	int getIntTime();

	/**
	* @brief get day inttime
	*
	* @return day inttime
	*/
	int getDayIntTime();

	/**
	* @brief get current timestamp
	*
	* @return current timestamp
	*/
	int64_t getNowTs();

	/**
	* @brief get timer timestamp
	*
	* @return timer timestamp
	*/
	int64_t getTimerTs();


//	void start();

	/**
	* @brief stop timer
	*/
	void stop();

	/**
	* @brief connect timer
	*
	* @param subscriber
	* 
	* @return connection
	*/
	boost::signals2::connection connectSignalTimer(const boost::signals2::signal<void(int)>::slot_type& subscriber);

	/**
	* @brief signal
	*/
	std::shared_ptr< boost::signals2::signal<void(int)> > & signal();

protected:
	/**
	* @brief on timer event
	*/
	void onTimer();

protected:
	int m_nowType;

	int m_interval;///< interval in milliseconds
	bool m_isRunning; ///< is running flag
	int m_count; ///< count

	int64_t m_intervalTs;
	int64_t m_nowTs; //< current timestamp
	int64_t m_timerTs; ///< second_timestamp
	int64_t m_nextTimerTs; ///< next second_timestamp
	int64_t m_nextTimerTsMin; ///< next seocnd_timestamp min
	int64_t m_nextTimerTsMax; ///< next second_timestamp max

	int m_intdate;
	int m_inttime;
	int m_dayinttime;

	boost::thread* m_timer_thread; ///< timer thread

	std::shared_ptr< boost::signals2::signal<void(int)> > m_signal; //boost::signals2::signal<void()> m_signalTimer;///< timer signal

}; //class XT_COMMON_API XTTimer
   //////typedef for XTTimer
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<XTTimer> XTTimerPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<XTTimer> XTTimerPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<XTTimer> XTTimerPtr;

#else

typedef ::boost::shared_ptr<XTTimer> XTTimerPtr;
#endif


typedef ::sf::safe_ptr<XTTimer> XTTimerSafePtr;

typedef sf::contfree_safe_ptr<XTTimer> XTTimerContFreePtr;
//////end typedef for XTTimer
 

class XT_COMMON_API XTTimerMgr{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	XTTimerMgr() {}

	/**
	* @brief copy constructor
	*/
	XTTimerMgr(const XTTimerMgr& from) {} //= delete;

	/**
	* @brief copy assignment
	*/
	XTTimerMgr& operator=(const XTTimerMgr& from) { return *this; } //= delete;

	/**
	* @brief destructor
	*/
	virtual ~XTTimerMgr() {}

	///@}

public:
	/**
	* @brief get singleton instance
	*
	* @return singleton instance
	*/
	static XTTimer* getOneSecondTimer();

	/**
	* @brief get local singleton instance
	*
	* @return local timer instance
	*/
	static XTTimer* getLocalTimer();

	/**
	* @brief get mkt singleton instance
	*
	* @return mkt timer instance
	*/
	static XTTimer* getMktTimer();


};//class XT_COMMON_API XTTimerMgr


}//namespace

#endif
