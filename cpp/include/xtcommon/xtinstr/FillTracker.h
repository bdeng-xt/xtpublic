#pragma once
#ifndef XT_FILLTRACKER_H
#define XT_FILLTRACKER_H
/**
* \file FillTracer.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for track fills.
*
* \description
*	Designed for tracking order fills.
*/
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <set>
#include <map>
#include <list>

#include <boost/array.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/smart_ptr.hpp>

#include "safe_ptr.h"

#include "XTConfig.h"
#include "LogUtil.h"

#include "Util.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "FillStat.h"

namespace XT
{

class XT_COMMON_API FillTracker
{

public:
	/**
	* @name Constructor and Initialization
	*/
	///@{

	/**
	* @brief constructor
	*/
	FillTracker();

	/**
	* @brief default copy constructor
	*/
	FillTracker(const FillTracker& from);// = default;

	/**
	* @brief default copy assignment
	*/
	FillTracker& operator=(const FillTracker& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~FillTracker();

	///@}

	/**
	* @name update
	*/
	///@{

	/**
	* @brief add FillInfo
	*
	* @param fillinfo as FillInfo
	*/
	void addFillInfo(const FillInfoPtr& fillinfo);

	/**
	* @brief add FillInfo for prev trading days
	*
	* @param fillinfo as FillInfo
	*/
	void addPrevFillInfo(const FillInfoPtr& fillinfo);

	/**
	* @brief add FillInfo for current trading day 
	*
	* @param fillinfo as FillInfo
	*/
	void addCurrFillInfo(const FillInfoPtr& fillinfo);




	///@}

	/**
	* @name accessors
	*/
	///@{

	/**
	* @brief last FillInfo
	*
	* @return last FillInfo
	*/
	const FillInfoPtr& lastFillInfo();


	/**
	* @brief Fill Statistics information
	*
	* @return FillStat
	*/
	const FillStatPtr& fillStat();

	/**
	* @brief  Fill Statistics information for prev trading days position
	*
	* @return FillStatPrev
	*/
	const FillStatPtr& fillStatPrev();

	/**
	* @brief  Fill Statistics information for the current trading day
	*
	* @return FillStatCurr
	*/
	const FillStatPtr& fillStatCurr();

	///**
	//* @brief previous Fill Statistics information
	//*
	//* @return previous FillStat
	//*/
	//const FillStatPtr& fillStatPrev();

	///**
	//* @brief previous Fill Statistics information for yesterday position
	//*
	//* @return previous FillStatYtd
	//*/
	//const FillStatPtr& fillStatYtdPrev();

////
	/**
	* @brief Fill Statistics information for open today
	*
	* @return FillStat open today
	*/
	const FillStatPtr& fillStatOpenTdy();

	/**
	* @brief Fill Statistics information for close today
	*
	* @return FillStat close today
	*/
	const FillStatPtr& fillStatCloseTdy();

	/**
	* @brief Fill Statistics information open yesterday
	*
	* @return FillStat open yesterday
	*/
	const FillStatPtr& fillStatOpenYtd();

	/**
	* @brief Fill Statistics information close yesterday
	*
	* @return FillStat close yesterday
	*/
	const FillStatPtr& fillStatCloseYtd();


	////

	/**
	* @brief get last fill orderid
	*
	* @return orderid of last fill
	*/
	int getLastFillOrderId();

	/**
	* @brief get last fill px
	*
	* @return px of last fill
	*/
	double getLastFillPx();


	/**
	* @brief get last fill sz
	*
	* @return size of last fill
	*/
	int64_t getLastFillSz();

	/**
	* @brief get last fill timestamp
	*
	* @return timestamp of last fill
	*/
	int64_t getLastFillTs();

	/**
	* @brief get buy px*volume
	*
	* @return total sum of buy px*volume
	*/
	double getBuyPxVolume();

	/**
	* @brief get sell px*volume
	*
	* @return total sum of sell px*volume
	*/
	double getSellPxVolume();

	/**
	* @brief get buy volume
	*
	* @return total sum of buy volume
	*/
	int64_t getBuyVolume();


	/**
	* @brief get sell volume
	*
	* @return total sum of sell volume
	*/
	int64_t getSellVolume();


	/**
	* @brief get volume
	*
	* @return total sum of volume
	*/
	int64_t getTotVolume();

////
	/**
	* @brief get realized px pnl
	*
	* @return realized px pnl
	*/
	double getRPxPnL();

	/**
	* @brief get unrealized px pnl
	*
	* @return unrealized px pnl
	*/
	double getUPxPnL(double exitpx);

	/**
	* @brief get realized px pnl for prev trading days position
	*
	* @return realized px pnl for prev trading days postion
	*/
	double getRPxPnLPrev();

	/**
	* @brief get unrealized px pnl for prev trading days position
	*
	* @return unrealized px pnl for prev trading days position
	*/
	double getUPxPnLPrev(double exitpx);

	/**
	* @brief get realized px pnl for current trading day position
	*
	* @return realized px pnl for current trading day postion
	*/
	double getRPxPnLCurr();

	/**
	* @brief get unrealized px pnl for current trading days position
	*
	* @return unrealized px pnl for current trading days position
	*/
	double getUPxPnLCurr(double exitpx);

////

	/**
	* @brief get last unrealized px pnl
	*
	* @return last unrealized px pnl
	*/
	double getLastUPxPnL(double exitpx);

	/**
	* @brief get last position cost
	*
	* @return last position cost
	*/
	double getPosCost();

	/**
	* @brief get last position cost
	*
	* @return last position cost
	*/
	double getLastPosCost();

	/**
	* @brief get last position min cost
	*
	* @return last position min cost
	*/
	double getLastPosCostMin();

	/**
	* @brief get last position max cost
	*
	* @return last position max cost
	*/
	double getLastPosCostMax();

	/**
	* @brief get net position
	*
	* @return net position
	*/
	int64_t getNetPos();


	/**
	* @brief get previous net position
	*
	* @return previous net position
	*/
	int64_t getNetPosPrev();

	/**
	* @brief get new  position
	*
	* @return new net position
	*/
	int64_t getNetPosNew();

	///@}

protected:
	sf::contfree_safe_ptr<std::list<FillInfoPtr > > m_buyFillInfoList;
	sf::contfree_safe_ptr<std::list<FillInfoPtr > > m_sellFillInfoList;

	FillInfoPtr m_lastFillInfo;

	FillStatPtr m_fillStat;
	FillStatPtr m_fillStatPrev;
	FillStatPtr m_fillStatCurr;


	FillStatPtr m_fillStatOpenTdy;
	FillStatPtr m_fillStatCloseTdy;
	boost::array<FillStatPtr, 2> m_tdyFillStats;

	FillStatPtr m_fillStatOpenYtd;
	FillStatPtr m_fillStatCloseYtd;
	boost::array<FillStatPtr, 2> m_ytdFillStats;


	double m_lastPosCost;
	double m_lastPosCostMin;
	double m_lastPosCostMax;



};//class


  //////typedef for FillTracker
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<FillTracker> FillTrackerPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<FillTracker> FillTrackerPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<FillTracker> FillTrackerPtr;

#else

typedef ::boost::shared_ptr<FillTracker> FillTrackerPtr;
#endif


typedef ::sf::safe_ptr<FillTracker> FillTrackerSafePtr;

typedef sf::contfree_safe_ptr<FillTracker> FillTrackerContFreePtr;
//////end typedef for FillTracker

}//namespace

#endif