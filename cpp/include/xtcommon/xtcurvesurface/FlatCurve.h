#pragma once
#ifndef XT_FLATCURVE_H
#define XT_FLATCURVE_H
/**
* \file FlatCurve.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for the flat curve
*
* \description
*	Designed for calculating flat curve.
*/
#include "XTConfig.h"
#include "DoubleFunction.h"
#include "Curve.h"
//#include "ql/quantlib.hpp"
namespace XT {

class XT_COMMON_API FlatFunction: public DoubleFunction {
public:

	/** 
	* @name Constructor and Destructor
	*/
	///@{
	/**
	* @brief constructor
	*/
	FlatFunction();

	/**
	* @brief default copy constructor
	*/
	FlatFunction(const FlatFunction& from)  ;

	/**
	* @brief default copy assignment
	*/
	FlatFunction& operator=(const FlatFunction& from)  ;

	/**
	* @brief constructor with parameter
	*
	* @param v as flat value
	*/
	FlatFunction(double v) ;

	/**
	* @brief destructor
	*/
	virtual ~FlatFunction() {}

	///@}


	/** @name Calculation
	*
	*/
	///@{
	/**
	* @brief implement value()
	*/
	double getValue(const std::vector<double> & x, int cpttype );

	/**
	* @brief implement gradient()
	*/
	void calcGradient(const std::vector<double> & x, std::vector<double> & y, int cpttype) ;

	///@}


	/** @name Copy
	*
	*/
	///@{
	/**
	* @brief deep clone
	*/
    virtual DoubleFunctionPtr deepClone();
	///@}


	/** @name Factory
	*
	*/
	///@{
	/**
	* @brief factory function
	*/
	static DoubleFunctionPtr create();
	///@}
}; //end class FlatFunction

   //////typedef for FlatFunction
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<FlatFunction> FlatFunctionPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<FlatFunction> FlatFunctionPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<FlatFunction> FlatFunctionPtr;

#else

typedef ::boost::shared_ptr<FlatFunction> FlatFunctionPtr;
#endif


typedef ::sf::safe_ptr<FlatFunction> FlatFunctionSafePtr;

typedef sf::contfree_safe_ptr<FlatFunction> FlatFunctionContFreePtr;
//////end typedef for FlatFunction

class XT_COMMON_API FlatCurve : public Curve {
public:

	/** @name Constructor and Destructor
	*
	*/
	///@{
	/**
	* @brief constructor with parameter
	*
	* @param v as flat value
	*/
	FlatCurve(double v);

	/**
	* @brief default copy constructor
	*/
	FlatCurve(const FlatCurve& from)  ;

	/**
	* @brief default copy assignment
	*/
	FlatCurve& operator=(const FlatCurve& from)  ;

	/**
	* @brief constructor 
	*/
	FlatCurve() ;

	/**
	* @brief destructor
	*/
	virtual ~FlatCurve() {}

	///@}


	/** 
	* @name Calculation
	*/
	///@{

	/**
	* @brief re-implement getYByCtrlPoints()
	*
	* @param x as input 
	*
	* @return control point value at x
	*/
	double getYByCtrlPoints(double x);

	/**
	* @brief re-implement getYByFunc()
	*
	* @param x as input 
	*
	* @return curve value at x point
	*/
	double getYByFunc(double x);

	/**
	* @brief fit constant flat curve
	*/
	virtual void fit();

	///@}


	/** 
	* @name Factory
	*/
	///@{
	/**
	* @brief factory function
	*
	* @param v as flat value
	* 
	* @return curve pointer
	*/
	static CurvePtr create(double v) ;
	///@}
protected:


}; //end class FlatCurve
   //////typedef for FlatCurve
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<FlatCurve> FlatCurvePtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<FlatCurve> FlatCurvePtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<FlatCurve> FlatCurvePtr;

#else

typedef ::boost::shared_ptr<FlatCurve> FlatCurvePtr;
#endif


typedef ::sf::safe_ptr<FlatCurve> FlatCurveSafePtr;

typedef sf::contfree_safe_ptr<FlatCurve> FlatCurveContFreePtr;
//////end typedef for FlatCurve
}//end namespace XT
#endif
