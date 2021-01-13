#pragma once
#ifndef XT_ROLLINGMIN_H
#define XT_ROLLINGMIN_H
/**
* \file RollingMin.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for rolling window.
*
* \description
*	Designed for calculating min value a rolling window.
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

class XT_COMMON_API RollingMin {
public:
	/** 
	* @name Constructor  
	*/
	///@{

	/**
	* @brief constructor
	*/
	RollingMin();

	/**
	* @brief constructor
	*
	* @param span in seconds
	*/
	RollingMin(int32_t span);

	/**
	* @brief default copy constructor
	*/
	RollingMin(const RollingMin& from) = default;

	/**
	* @brief default copy assignment
	*/
	RollingMin& operator=(const RollingMin& from) = default;

	/**
	* @brief destructor
	*/
	virtual ~RollingMin() {};

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
	* @name Getters
	*/
	///@{
	/**
	* @brief get min value
	*
	* @return min value
	*/
	int64_t minValue();
	///@}
private:
	int64_t m_spanDT; ///< span date time in microseconds
	int64_t m_minValue; ///< max value

//	std::deque<std::pair<int64_t, int64_t> > minWindow;

	std::deque<int64_t> m_tsWindow; ///< timestamp window
	std::deque<int64_t> m_vWindow; ///< value window

};//class XT_COMMON_API RollingMin

  //////typedef for RollingMin
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<RollingMin> RollingMinPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<RollingMin> RollingMinPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<RollingMin> RollingMinPtr;

#else

typedef ::boost::shared_ptr<RollingMin> RollingMinPtr;
#endif


typedef ::sf::safe_ptr<RollingMin> RollingMinSafePtr;

typedef sf::contfree_safe_ptr<RollingMin> RollingMinContFreePtr;
//////end typedef for RollingMin
}//namespace XT

#endif
