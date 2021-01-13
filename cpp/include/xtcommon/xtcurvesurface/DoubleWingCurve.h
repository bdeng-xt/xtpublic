#pragma once
#ifndef XT_DOUBLEWINGCURVE_H
#define XT_DOUBLEWINGCURVE_H
/**
* \file DoubleWingCurve.h
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
#include "MathUtil.h"
//#include "ql/quantlib.hpp"

#include "safe_ptr.h"
namespace XT {



class XT_COMMON_API DoubleWingFunction : public DoubleFunction 
{
public:

	/** 
	* @name Constructor and Destructor
	*/
	///@{
	/**
	* @brief constructor
	*/
	DoubleWingFunction();

	/**
	* @brief default copy constructor
	*/
	DoubleWingFunction(const DoubleWingFunction& from)  ;

	/**
	* @brief default copy assignment
	*/
	DoubleWingFunction& operator=(const DoubleWingFunction& from) ;

	/**
	* @brief destructor
	*/
	virtual ~DoubleWingFunction() {}

	///@}

	/** @name Calculation
	*
	*/
	///@{
	/**
	* @brief implement value()
	*
	* @param x as input double vector
	*
	* @return value corresponding to input vector x
	*/
	virtual double getValue(const std::vector<double> & x, int cpttype );

	/**
	* @brief implement values()
	*
	* @param x as input double vector
	* @param y as output gradient double vector
	*/
	virtual void calcGradient(const std::vector<double> & x, std::vector<double> & y, int cpttype);

	///@}

	/** 
	* @name Copy
	*/
	///@{
	/**
	* @brief deep clone
	*
	* @return cloned double function pointer
	*/
    virtual DoubleFunctionPtr deepClone();
	///@}

	/** @name Factory
	*
	*/
	///@{
	/**
	* @brief factorory function
	*
	* @return double function pointer
	*/
	static DoubleFunctionPtr create() ;
	///@}
protected:
	/**
	* @brief initialization
	*/
	void init();
};
//////typedef for DoubleWingFunction

#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<DoubleWingFunction> DoubleWingFunctionPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<DoubleWingFunction> DoubleWingFunctionPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<DoubleWingFunction> DoubleWingFunctionPtr;

#else

typedef ::boost::shared_ptr<DoubleWingFunction> DoubleWingFunctionPtr;
#endif


typedef ::sf::safe_ptr<DoubleWingFunction> DoubleWingFunctionSafePtr;

typedef sf::contfree_safe_ptr<DoubleWingFunction> DoubleWingFunctionContFreePtr;
//////end typedef for DoubleFunction

class XT_COMMON_API DoubleWingCurve : public Curve
{
public:

	/** @name Constructor and Destructor
	*
	*/
	///@{
	/**
	* @brief constructor
	*/
	DoubleWingCurve() ;

	/**
	* @brief default copy constructor
	*/
	DoubleWingCurve(const DoubleWingCurve& from) ;

	/**
	* @brief default copy assignment
	*/
	DoubleWingCurve& operator=(const DoubleWingCurve& from)  ;

	/**
	* @brief destructor
	*/
	virtual ~DoubleWingCurve() {}
	///@}


protected:
	/**
	* @brief initialization
	*/
	void init();

public:

	/** @name Calculation
	*
	*/
	///@{
	/**
	* @brief fit curve
	*/
	virtual void fit( );

	/**
	* @brief update weights
	*/
	virtual void updateWeights();

	/**
	* @brief diff value between pointmap and model
	*
	* @param paramtypeint
	*
	* @return diff value
	*/
	virtual double diffValueForPointMap(int paramtypeint);

	/**
	* @brief diff value between pointlist and model
	*
	* @param paramtypeint
	*
	* @return diff value
	*/
	virtual double diffValueForPointList(int paramtypeint);

	/**
	* @brief diff value between pointmap list and model
	*
	* @param paramtypeint
	*
	* @return diff value
	*/
	virtual double diffValueForPointMapList(int paramtypeint);

	///@}

	/** @name Factory
	*
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
	void fitSlopePcCcForDataMapList();


}; //end class
   //////typedef for DoubleWingCurve
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<DoubleWingCurve> DoubleWingCurvePtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<DoubleWingCurve> DoubleWingCurvePtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<DoubleWingCurve> DoubleWingCurvePtr;

#else

typedef ::boost::shared_ptr<DoubleWingCurve> DoubleWingCurvePtr;
#endif


typedef ::sf::safe_ptr<DoubleWingCurve> DoubleWingCurveSafePtr;

typedef sf::contfree_safe_ptr<DoubleWingCurve> DoubleWingCurveContFreePtr;
//////end typedef for DoubleWingCurve

 

} //end namespace XT

#endif
