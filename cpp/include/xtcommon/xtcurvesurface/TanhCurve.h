#pragma once
#ifndef XT_TANHCURVE_H
#define XT_TANHCURVE_H
/**
* \file TanhCurve.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for the tanh curve
*
* \description
*	Designed for calculating tanh curve.
*/
#include "XTConfig.h"
#include "DoubleFunction.h"
#include "Curve.h"
#include "Point.h"
#include "PxUtil.h"
 
#include "safe_ptr.h"

namespace XT {

	class TanhFunction;
	//////typedef for TanhFunction
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<TanhFunction> TanhFunctionPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<TanhFunction> TanhFunctionPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<TanhFunction> TanhFunctionPtr;

#else

	typedef ::boost::shared_ptr<TanhFunction> TanhFunctionPtr;
#endif


	typedef ::sf::safe_ptr<TanhFunction> TanhFunctionSafePtr;

	typedef sf::contfree_safe_ptr<TanhFunction> TanhFunctionContFreePtr;
	//////end typedef for TanhFunction

	class TanhCurve;
	//////typedef for TanhCurve
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<TanhCurve> TanhCurvePtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<TanhCurve> TanhCurvePtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<TanhCurve> TanhCurvePtr;

#else

	typedef ::boost::shared_ptr<TanhCurve> TanhCurvePtr;
#endif


	typedef ::sf::safe_ptr<TanhCurve> TanhCurveSafePtr;

	typedef sf::contfree_safe_ptr<TanhCurve> TanhCurveContFreePtr;
	//////end typedef for TanhCurve





class XT_COMMON_API TanhFunction : public DoubleFunction {
public:

	/** 
	* @name Constructor and Destructor
	*/
	///@{
	/**
	* @brief constructor
	*/
	TanhFunction();

	/**
	* @brief default copy constructor
	*/
	TanhFunction(const TanhFunction& from);// = default;

	/**
	* @brief default copy assignment
	*/
	TanhFunction& operator=(const TanhFunction& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~TanhFunction() {}
	///@}


	/** 
	* @name Calculation
	*/
	///@{
	/**
	* @brief implement value()
	*/
	virtual double getValue(const std::vector<double> & x, int cpttype );

	/**
	* @brief implement gradient()
	*/
	virtual void calcGradient(const std::vector<double> & x, std::vector<double> & y, int cpttype);

	///@}

	/**
	*  @name Copy
	*/
	///@{
	/**
	* @brief deep clone
	*/
	virtual DoubleFunctionPtr deepClone();
	///@}

	/** 
	* @name Factory
	*/
	///@{
	/**
	* @brief factory function
	*/
    static DoubleFunctionPtr create() ;
	///@}
protected:
	/**
	* @brief initialization
	*/
	void init();
}; //end class TanhFunction




class XT_COMMON_API TanhCurve : public Curve
{
public:

	/** 
	* @name Constructor and Destructor
	*/
	///@{
	/**
	* @brief constructor
	*/
	TanhCurve() ;

	/**
	* @brief default copy constructor
	*/
	TanhCurve(const TanhCurve& from);// = default;

	/**
	* @brief default copy assignment
	*/
	TanhCurve& operator=(const TanhCurve& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~TanhCurve() {}

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
	*/
	virtual void updateWeights();

	///@}

	/** 
	* @name Factory
	*/
	///@{
	/**
	* @brief factory function
	*/
	static CurvePtr create() ;
	///@}
protected:

}; //end class TanhCurve







} //end namespace XT
#endif
