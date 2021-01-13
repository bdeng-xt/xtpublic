#pragma once
#ifndef XT_BAWAMERICANPRICINGENGINE_H
#define XT_BAWAMERICANPRICINGENGINE_H

/**
* \file BAWAmericanPricingEngine.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for BAW american pricing engine.
*
* \description
*	Designed for use for calculating BAW method.
*/

#include <boost/smart_ptr.hpp>
#include "safe_ptr.h"

#include "XTConfig.h"
#include "XTData.pb.h"
#include "EnumHelper.h"
#include "PricingEngine.h"
#include "PxUtil.h"

namespace XT {
	class BAWAmericanPricingEngine;
	//////typedef for BAWAmericanPricingEngine
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<BAWAmericanPricingEngine> BAWAmericanPricingEnginePtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<BAWAmericanPricingEngine> BAWAmericanPricingEnginePtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<BAWAmericanPricingEngine> BAWAmericanPricingEnginePtr;

#else

	typedef ::boost::shared_ptr<BAWAmericanPricingEngine> BAWAmericanPricingEnginePtr;
#endif


	typedef ::sf::safe_ptr<BAWAmericanPricingEngine> BAWAmericanPricingEngineSafePtr;

	typedef sf::contfree_safe_ptr<BAWAmericanPricingEngine> BAWAmericanPricingEngineContFreePtr;
	//////end typedef for BAWAmericanPricingEngine

class XT_COMMON_API BAWAmericanPricingEngine : public PricingEngine {
public:

	/** 
	* @name Constructor and Destructor
	*/
	///@{
	/**
	* @brief constructor
	*/
	BAWAmericanPricingEngine();

	/**
	* @brief default copy constructor
	*/
	BAWAmericanPricingEngine(const BAWAmericanPricingEngine& from) = default;

	/**
	* @brief default copy assignment
	*/
	BAWAmericanPricingEngine& operator=(const BAWAmericanPricingEngine& from) = default;

	/**
	* @brief destructor
	*/
	virtual ~BAWAmericanPricingEngine() {}

	///@}

	/** 
	* @name Calc
	*/
	///@{
	/**
	* @brief implement calc()
	*/
	virtual void calc();

	///@}

	/** 
	* @name Factory
	*/
	///@{
	/**
	* @brief factory function
	*
	* @return created PricingEngine pointer
	*/
	static PricingEnginePtr create() ;
	///@}

}; //end class


} //end namespace XT

#endif
