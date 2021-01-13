#pragma once
#ifndef XT_BSMPRICINGENGINE_H
#define XT_BSMPRICINGENGINE_H
/**
* \file BSMPricingEngine.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for BSM european pricing engine.
*
* \description
*	Designed for use for calculating BSM method.
*/

#include <boost/smart_ptr.hpp>
#include "safe_ptr.h"

#include "XTConfig.h"
#include "PricingEngine.h"
#include "EnumHelper.h"
#include "PxUtil.h"
namespace XT {

class XT_COMMON_API BSMPricingEngine : public PricingEngine {

public:
	/** 
	* @name Constructor and Destructor
	*/
	///@{
	/**
	* @brief constructor
	*/
	BSMPricingEngine();

	/**
	* @brief default copy constructor
	*/
	BSMPricingEngine(const BSMPricingEngine& from) = default;

	/**
	* @brief default copy assignment
	*/
	BSMPricingEngine& operator=(const BSMPricingEngine& from) = default;

	/**
	* @brief destructor
	*/
	virtual ~BSMPricingEngine() {}
	///@}


	/** 
	* @name Calc
	*/
	///@{
	/**
	* @brief perform calculation
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
};

//////typedef for BSMPricingEngine
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<BSMPricingEngine> BSMPricingEnginePtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<BSMPricingEngine> BSMPricingEnginePtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<BSMPricingEngine> BSMPricingEnginePtr;

#else

typedef ::boost::shared_ptr<BSMPricingEngine> BSMPricingEnginePtr;
#endif


typedef ::sf::safe_ptr<BSMPricingEngine> BSMPricingEngineSafePtr;

typedef sf::contfree_safe_ptr<BSMPricingEngine> BSMPricingEngineContFreePtr;
//////end typedef for BSMPricingEngine


}//end namespace XT


#endif