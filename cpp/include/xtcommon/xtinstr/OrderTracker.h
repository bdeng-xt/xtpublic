#pragma once
#ifndef XT_ORDERTRACKER_H
#define XT_ORDERTRACKER_H
/**
* \file FillTracer.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for track orders.
*
* \description
*	Designed for tracking orders.
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

namespace XT
{

 class XT_COMMON_API OrderTracker
{
public:
	/**
	* @name Constructor and Initialization
	*/
	///@{

	/**
	* @brief constructor
	*/
	OrderTracker();

	/**
	* @brief default copy constructor
	*/
	OrderTracker(const OrderTracker& from);// = default;

	/**
	* @brief default copy assignment
	*/
	OrderTracker& operator=(const OrderTracker& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~OrderTracker();

	///@}

	/**
	* @name Update
	*/
	///@{

	/**
	* @brief set scaleDoubleToInt64
	*
	* @param v as scale
	*/
	void setScaleDoubleToInt64(int64_t v);

	/**
	* @brief update orderinfo
	*/
	void updateOrderInfo(const OrderInfoPtr& orderinfo);

	///@}

	/**
	* @name Accessors
	*/
	///@{

	/**
	* @brief workingOrdersMap
	* 
	* @return workingOrdersMap
	*/
	const std::map<int, OrderInfoPtr >& workingOrdersMap();

	/**
	* @brief workingQuotesMap
	*
	* @return workingQuotesMap
	*/
	const std::map<int, QuoteInfoPtr >& workingQuotesMap();

	///**
	//* @brief orderStatData
	//*
	//* @return orderStatData
	//*/
	//boost::shared_ptr<OrderStatData>& orderStatData();

	///**
	//* @brief int64PxToSzMaps
	//*
	//* @return int64PxToSzMaps
	//*/
	//boost::array< std::map<int64_t, int32_t>, 2>  int64PxToSzMaps(); ///< key:intPx,value:sz, only keep intPx when open_size for the intPx is not zero
	//
	//																 /**
	//* @brief openOrdersMaps
	//*
	//* @return openOrdersMaps
	//*/
	//boost::array< std::map<int64_t, std::map<int32_t, int32_t> >, 2>  openOrdersMaps(); ///< key:intPx,key:seqnum,value:sz, keep all intPx, only keep seqnum when orders are open

	/**
	* @brief bsOrdersSz array
	*
	* @return bsOrdersSz array
	*/
	const boost::array<OrdersSzPairPtr, 2>& bsOrdersSz();

	/**
	* @brief bsOrdersSz array
	*
	* @return bsOrdersSz array
	*/
	const boost::array<OrdersSzPairPtr, 2>& bsOrdersSzOpenTdy();	
	/**
	* @brief bsOrdersSzCloseTdy array
	*
	* @return bsOrdersSzCloseTdy array
	*/
	const boost::array<OrdersSzPairPtr, 2>& bsOrdersSzCloseTdy();
	/**
	* @brief bsOrdersSzOpenYtd array
	*
	* @return bsOrdersSzOpenYtd array
	*/
	const boost::array<OrdersSzPairPtr, 2>& bsOrdersSzOpenYtd();//not necessary,to remove later
	/**
	* @brief bsOrdersSzCloseYtd array
	*
	* @return bsOrdersSzCloseYtd array
	*/	
	const boost::array<OrdersSzPairPtr, 2>& bsOrdersSzCloseYtd();


	/**
	* @brief get changed size
	*
	* @return chgSz
	*/
	int64_t getChgSz();

	/**
	* @brief get changed number of orders
	*
	* @return chgOrders
	*/
	int getChgOrders();

	///@}


protected:

	std::map<int, OrderInfoPtr > m_workingOrdersMap;
	std::map<int, QuoteInfoPtr > m_workingQuotesMap;

	boost::array<OrdersSzPairPtr, 2> m_bsOrdersSz;

	boost::array<OrdersSzPairPtr, 2> m_bsOrdersSzOpenTdy;
	boost::array<OrdersSzPairPtr, 2> m_bsOrdersSzCloseTdy;

	boost::array<OrdersSzPairPtr, 2> m_bsOrdersSzOpenYtd;//not necessary,to remove later
	boost::array<OrdersSzPairPtr, 2> m_bsOrdersSzCloseYtd;


	//boost::shared_ptr<OrderStatData> m_orderStatData;

	//boost::array< std::map<int64_t, int32_t>, 2>  m_int64PxToSzMaps; ///< key:intPx,value:sz, only keep intPx when open_size for the intPx is not zero
	//boost::array< std::map<int64_t, std::map<int32_t, int32_t> >, 2>  m_openOrdersMaps; ///< key:intPx,key:seqnum,value:sz, keep all intPx, only keep seqnum when orders are open

	std::map<int, int64_t> m_orderIdToOpenSzMap;

	int64_t m_chgSz;
	int m_chgOrders;

	int64_t m_scaleDoubleToInt64;
	double m_scaleInt64ToDouble;

};//class


  //////typedef for OrderTracker
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<OrderTracker> OrderTrackerPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<OrderTracker> OrderTrackerPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<OrderTracker> OrderTrackerPtr;

#else

typedef ::boost::shared_ptr<OrderTracker> OrderTrackerPtr;
#endif


typedef ::sf::safe_ptr<OrderTracker> OrderTrackerSafePtr;

typedef sf::contfree_safe_ptr<OrderTracker> OrderTrackerContFreePtr;
//////end typedef for OrderTracker


}//namespace

#endif