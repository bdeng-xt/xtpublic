#pragma once
#ifndef XT_SWANCURVE_H
#define XT_SWANCURVE_H
/**
* \file SwanCurve.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for the double wing curve
*
* \description
*	Designed for calculating double wing curve.
*/
#include "XTConfig.h"
#include "DoubleFunction.h"
#include "Curve.h"
#include "PxUtil.h"
#include "safe_ptr.h"

namespace XT {

class XT_COMMON_API SwanFunction : public DoubleFunction {
public:

	/** 
	* @name Constructor and Destructor
	*/
	///@{
	/**
	* constructor
	*/
	SwanFunction();

	/**
	* @brief default copy constructor
	*/
	SwanFunction(const SwanFunction& from);// = default;

	/**
	* @brief default copy assignment
	*/
	SwanFunction& operator=(const SwanFunction& from);// = default;

	/**
	* destructor
	*/
	virtual ~SwanFunction() {}

	///@}

	/** 
	* @name Calculation
	*/
	///@{
	/**
	* implement value()
	*/
	virtual double getValue(const std::vector<double> & x, int cpttype );

	/**
	* implement values()
	*/
	virtual void calcGradient(const std::vector<double> & x, std::vector<double> & y, int cpttype);

	///@}

	/** 
	* @name Copy
	*/
	///@{
	/**
	* deep clone
	*/
    virtual DoubleFunctionPtr deepClone();
	///@}

	/** 
	* @name Factory
	*/
	///@{
	/**
	* factorory function
	*/
	static DoubleFunctionPtr create() ;
	///@}
protected:
	/**
	* initialization
	*/
	void init();
};

//////typedef for SwanFunction
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<SwanFunction> SwanFunctionPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<SwanFunction> SwanFunctionPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<SwanFunction> SwanFunctionPtr;

#else

typedef ::boost::shared_ptr<SwanFunction> SwanFunctionPtr;
#endif


typedef ::sf::safe_ptr<SwanFunction> SwanFunctionSafePtr;

typedef sf::contfree_safe_ptr<SwanFunction> SwanFunctionContFreePtr;
//////end typedef for SwanFunction


class XT_COMMON_API SwanCurve : public Curve
{
public:

	/**
	* @name Constructor and Destructor
	*/
	///@{
	/**
	* @brief constructor
	*/
	SwanCurve() ;

	/**
	* @brief default copy constructor
	*/
	SwanCurve(const SwanCurve& from);// = default;

	/**
	* @brief default copy assignment
	*/
	SwanCurve& operator=(const SwanCurve& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~SwanCurve() {}
	///@}

	/** 
	* @name Calculation
	*/
	///@{
	/**
	* @brief fit curve
	*/
	virtual void fit();

	/**
	* @brief update weights
	*
	*/
	virtual void updateWeights();

	///@}

	/** 
	* @name Factory
	*/
	///@{
	/**
	* @brief factory function
	*
	* @return curve pointer
	*/
	static CurvePtr create() ;
	///@}
protected:
	std::vector<double> fitVcSlopePcCcByLoess();
	void fitVcSlopePcCc();


}; //end class

   //////typedef for SwanCurve
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<SwanCurve> SwanCurvePtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<SwanCurve> SwanCurvePtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<SwanCurve> SwanCurvePtr;

#else

typedef ::boost::shared_ptr<SwanCurve> SwanCurvePtr;
#endif


typedef ::sf::safe_ptr<SwanCurve> SwanCurveSafePtr;

typedef sf::contfree_safe_ptr<SwanCurve> SwanCurveContFreePtr;
//////end typedef for SwanCurve

/////////////////////////////////////


} //end namespace XT

#endif
