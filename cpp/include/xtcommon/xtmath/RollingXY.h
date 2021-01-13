#pragma once
#ifndef XT_ROLLINGXY_H
#define XT_ROLLINGXY_H
/**
* \file RollingXY.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for x,y rolling window.
*
* \description
*	Designed for storing x,y values information of a rolling window.
*/

#include <boost/smart_ptr.hpp>
#include "safe_ptr.h"

#include "XTConfig.h"
#include "Rolling.h"
#include "Util.h"

namespace XT {

class XT_COMMON_API RollingXY {
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	RollingXY() :
		m_rx(RollingPtr(new Rolling(60, RollingType::Time, DateTimeType::UTS)))
		, m_ry(RollingPtr(new Rolling(60, RollingType::Time, DateTimeType::UTS)))
		, m_rxy(RollingPtr(new Rolling(60, RollingType::Time, DateTimeType::UTS)))
	{}
        
	/**
	* @brief constructor
	*
	* @param span in seconds
	* @param rtype as rolling type
	* @param dttype as date time type
	*/
     RollingXY(int32_t span  , RollingType::enumtype rtype  , DateTimeType::enumtype dttype );

	 /**
	 * @brief default copy constructor
	 */
	 RollingXY(const RollingXY& from) = default;

	 /**
	 * @brief default copy assignment
	 */
	 RollingXY& operator=(const RollingXY& from) = default;

		/**
		* @brief destructor
		*/
		virtual ~RollingXY();

	///@}
     
		/**
		* @brief add x,y values
		*
		* @param dt as timestamp or tick
		* @param x as first value
		* @param y as second value
		*/
        void add(int64_t dt, double x, double y);
         

        /**
        * @brief rolling x
		*
		* @return rolling x pointer
        */
        RollingPtr& rx();

        /**
        * @brief rolling y
		*
		* @return rolling y pointer
        */
        RollingPtr& ry(); 

        /**
        * @brief rollying xy
		*
		* @return rolling xy pointer
        */
        RollingPtr& rxy();


        //#region fields
protected:

        RollingPtr m_rx;///< rolling x window
        RollingPtr m_ry; ///< rolling y window
        RollingPtr m_rxy; ///< rolling x*y window

        //#endregion fields


protected:
//		int32_t isYGreaterThanZero;

}; //end class RolllingXY

   //////typedef for RollingXY
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<RollingXY> RollingXYPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<RollingXY> RollingXYPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<RollingXY> RollingXYPtr;

#else

typedef ::boost::shared_ptr<RollingXY> RollingXYPtr;
#endif


typedef ::sf::safe_ptr<RollingXY> RollingXYSafePtr;

typedef sf::contfree_safe_ptr<RollingXY> RollingXYContFreePtr;
//////end typedef for RollingXY
} //end namespace XT

#endif
