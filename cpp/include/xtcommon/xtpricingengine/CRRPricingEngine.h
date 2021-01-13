#pragma once
#ifndef XT_CRRPRICINGENGINE_H
#define XT_CRRPRICINGENGINE_H
/**
* \file CRRPricingEngine.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for CRR Binomial pricing engine.
*
* \description
*	Designed for use for CRR binomial method.
*/

#include <boost/smart_ptr.hpp>
#include "safe_ptr.h"
#include "XTConfig.h"
#include "PricingEngine.h"
#include "EnumHelper.h"
#include "PxUtil.h"

namespace XT {

class XT_COMMON_API CRRPricingEngine : public PricingEngine {

public:
	/** 
	* @name Constructor and Destructor
	*/
	///@{
	/**
	* @brief constructor
	*/
	CRRPricingEngine();

	/**
	* @brief default copy constructor
	*/
	CRRPricingEngine(const CRRPricingEngine& from) = default;

	/**
	* @brief default copy assignment
	*/
	CRRPricingEngine& operator=(const CRRPricingEngine& from) = default;

	/**
	* @brief destructor
	*/
	virtual ~CRRPricingEngine() {}
	///@}

	/** 
	* @name Calc
	*/
	///@{
	/**
	* @brief re-implement calc()
	*/
	virtual void calc();
	///@}

	/**
	*  @name Factory
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


   //////typedef for CRRPricingEngine
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<CRRPricingEngine> CRRPricingEnginePtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<CRRPricingEngine> CRRPricingEnginePtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<CRRPricingEngine> CRRPricingEnginePtr;

#else

typedef ::boost::shared_ptr<CRRPricingEngine> CRRPricingEnginePtr;
#endif


typedef ::sf::safe_ptr<CRRPricingEngine> CRRPricingEngineSafePtr;

typedef sf::contfree_safe_ptr<CRRPricingEngine> CRRPricingEngineContFreePtr;
//////end typedef for CRRPricingEngine



} //end namespace XT


#endif