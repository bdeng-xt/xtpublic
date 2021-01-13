#pragma once
#ifndef XT_LINECURVE_H
#define XT_LINECURVE_H
/**
* \file LineCurve.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for the line curve
*
* \description
*	Designed for calculating line curve.
*/
#include "XTConfig.h"
#include "DoubleFunction.h"
#include "Curve.h"

namespace XT {

class XT_COMMON_API LineFunction : public DoubleFunction {
public:
	/**
	*  @name Constructor and Destructor
	*/
	///@{
	/**
	* @brief constructor
	*/
	LineFunction() ;

	/**
	* @brief default copy constructor
	*/
	LineFunction(const LineFunction& from)  ;

	/**
	* @brief default copy assignment
	*/
	LineFunction& operator=(const LineFunction& from) ;

	/**
	* @brief destructor
	*/
	virtual ~LineFunction() {}

	///@}


	/** 
	* @name Calculation
	*/
	///@{

	/**
	* @brief implement value()
	*
	* @param x as input double vector
	*
	* @return curve cost calue for parameters x
	*/
	virtual double getValue(const std::vector<double> & x, int cpttype );

	/**
	* @brief implement gradient()
	*
	* @param x as input double vector
	* @param y as output gradient double vector
	*/
	virtual void calcGradient(const std::vector<double> & x, std::vector<double> & y, int cpytype);

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

	/** 
	* @name Factory
	*/
	///@{
	/**
	* @brief create
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
}; //end class LineFunction

   //////typedef for LineFunction
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<LineFunction> LineFunctionPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<LineFunction> LineFunctionPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<LineFunction> LineFunctionPtr;

#else

typedef ::boost::shared_ptr<LineFunction> LineFunctionPtr;
#endif


typedef ::sf::safe_ptr<LineFunction> LineFunctionSafePtr;

typedef sf::contfree_safe_ptr<LineFunction> LineFunctionContFreePtr;
//////end typedef for LineFunction


class XT_COMMON_API LineCurve : public Curve {
public:

	/**
	*  @name Constructor and Destructor
	*/
	///@{
	/**
	* @brief constructor
	*/
	LineCurve() ;

	/**
	* @brief default copy constructor
	*/
	LineCurve(const LineCurve& from) ;

	/**
	* @brief default copy assignment
	*/
	LineCurve& operator=(const LineCurve& from)  ;

	/**
	* @brief destructor
	*/
	virtual ~LineCurve() {}
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
}; //end class LineCurve


   //////typedef for LineCurve
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<LineCurve> LineCurvePtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<LineCurve> LineCurvePtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<LineCurve> LineCurvePtr;

#else

typedef ::boost::shared_ptr<LineCurve> LineCurvePtr;
#endif


typedef ::sf::safe_ptr<LineCurve> LineCurveSafePtr;

typedef sf::contfree_safe_ptr<LineCurve> LineCurveContFreePtr;
//////end typedef for LineCurve
} //end namespace XT

#endif
