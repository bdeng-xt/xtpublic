#pragma once
#ifndef XT_FILLSTAT_H
#define XT_FILLSTAT_H
/**
* \file FillStat.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for fills statstics.
*
* \description
*	Designed for get statistics of order fills.
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

	class FillStat;
	//////typedef for FillStat
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<FillStat> FillStatPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<FillStat> FillStatPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<FillStat> FillStatPtr;

#else

	typedef ::boost::shared_ptr<FillStat> FillStatPtr;
#endif


	typedef ::sf::safe_ptr<FillStat> FillStatSafePtr;

	typedef ::sf::contfree_safe_ptr<FillStat> FillStatContFreePtr;
	//////end typedef for FillStat

	class XT_COMMON_API FillStat
	{

	public:
		/**
		* @name Constructor and Initialization
		*/
		///@{

		/**
		* @brief constructor
		*/
		FillStat();

		/**
		* @brief default copy constructor
		*/
		FillStat(const FillStat& from);// = default;

		/**
		* @brief default copy assignment
		*/
		FillStat& operator=(const FillStat& from);// = default;

		/**
		* @brief destructor
		*/
		virtual ~FillStat();

		///@}

		/**
		* @name update
		*/
		///@{

		/**
		* @brief add px and volume
		*
		* @param px as price
		* @param volume as filled volume
		*/
		void addPxVolume(int bsint, double price, int64_t volume);

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
		const XT::FillStatDataPtr& getFillStatData();



		/**
		* @brief get unrealized px pnl
		*
		* @return unrealized px pnl
		*/
		double getUPxPnL(double exitpx);

		/**
		* @brief get last pnl exit px
		*
		* @return last pnl exit px
		*/
		double getPnLExitPx();

		///**
		//* @brief set last pnl exit px
		//*
		//* @param last pnl exit px
		//*/
		//void setPnLExitPx(double px);

		
		///@}


		/**
		* @brief copy from other
		*/
		void copyFrom(const FillStatPtr & other);

	protected:
		XT::FillStatDataPtr m_fillStatData;

		double m_lastPnLExitPx;
 

	};//class




}//namespace

#endif