#pragma once
#ifndef XT_ROLLINGMAX_H
#define XT_ROLLINGMAX_H
/**
* \file RollingMax.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for rolling window.
*
* \description
*	Designed for calculate max value of a rolling window.
*/

#include <cstdint>
#include <deque>
#include <boost/smart_ptr.hpp>
#include "safe_ptr.h"

#include "XTConfig.h"
#include "XTData.pb.h"
#include "EnumHelper.h"

#include "Util.h"
#include "LogUtil.h"

namespace XT {

class XT_COMMON_API RollingMax {
public:
	/** @name Constructor 
	* 
	*/
	///@{

	/**
	* @brief constructor
	*/
	RollingMax();

	/**
	* @brief constructor
	*
	* @param span in seconds
	*/
	RollingMax(int32_t span);

	/**
	* @brief default copy constructor
	*/
	RollingMax(const RollingMax& from) = default;

	/**
	* @brief default copy assignment
	*/
	RollingMax& operator=(const RollingMax& from) = default;

	/**
	* @brief destructor
	*/
	virtual ~RollingMax() {};

	///@}

	/** 
	* @name Updating Functions
	*/
	///@{
	/**
	* @brief add value
	*
	* @param ts as timestamp or tick
	* @param va as double value
	*/
	void add(int64_t ts, int64_t v);

	/**
	* @brief update timestamp 
	*
	* @param ts as timestamp
	*/
	void updateTs(int64_t ts);
	///@}

	/**
	*  @name Getters
	*/
	///@{
	/**
	* @brief get max value
	*
	* @return max value
	*/
	int64_t maxValue();
	///@}
private:
	int64_t m_spanDT; ///< span date time in microseconds
	int64_t m_maxValue; ///< max value

//	std::deque<std::pair<int64_t, int64_t> > maxWindow;

	std::deque<int64_t> m_tsWindow; ///< timestamp window
	std::deque<int64_t> m_vWindow; ///< value window

};//class XT_COMMON_API RollingMax

  //////typedef for RollingMax
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<RollingMax> RollingMaxPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<RollingMax> RollingMaxPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<RollingMax> RollingMaxPtr;

#else

typedef ::boost::shared_ptr<RollingMax> RollingMaxPtr;
#endif


typedef ::sf::safe_ptr<RollingMax> RollingMaxSafePtr;

typedef sf::contfree_safe_ptr<RollingMax> RollingMaxContFreePtr;
//////end typedef for RollingMax

}//namespace XT

#endif
