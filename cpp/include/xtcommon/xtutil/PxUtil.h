#pragma once
#ifndef XT_PXUTIL_H
#define XT_PXUTIL_H

/**
* \file PxUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide pricing functions.
*
* \description
*	This component provides pricing functions for options.
*/

#include <cmath>
#include <algorithm>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#include "XTConfig.h"
#include "FIXEnum.pb.h"
#include "FIXData.pb.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"

#include "EnumUtil.h"
#include "EnumHelper.h"
#include "LogUtil.h"

namespace XT {
class XT_COMMON_API PxUtil{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	PxUtil() {}

	/**
	* @brief copy constructor
	*/
	PxUtil(const PxUtil& from) {} // = delete;

	/**
	* @brief copy assignment
	*/
	PxUtil& operator=(const PxUtil& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~PxUtil() {}

	///@}

protected:
	/** 
	* @name Constants
	*/
	///@{
	static const double s_NegativeInf; ///< negative infinity
	static const double s_PositiveInf; ///< positive infinity
	static const double s_Pi; ///< pi constant
	static const double s_1OverSqrt2Pi; ///< 1.0/sqrt(2.0*pi)

	static const double s_DaysOneYear; ///< days in one year, 365
	static const double s_TradingDaysOneYear; ///< trading days in one year, 252
	static const double s_DayInYear; ///< day in year unit
	static const double s_TradingDayInYear; ///< trading day in year unit

	static int s_ImpVolMaxIteration; ///< max iterations for implied vol calculation
	static double s_ImpVolMin; ///< min implied vol
	static double s_ImpVolMax; ///< max implied vol
	static double s_ImpVolEpsilon; ///< epsilon for implied vol calculation
	static double s_ImpVolPxEpsilon; ///< price epsilon for implied vol calculation
	static double s_ImpVolBisectionThresh; ///< thresh for bisection implied vol calculation
	static double s_ImpVolDiff; ///< difference between current iteration and previous iteration
	static int s_ImpVolIterCount; ///< iteration count for implied vol calculation

	static double s_BAW_Kc;///< calculated critical Kc for BAW calculation
	static double s_BAW_Kp; ///< calculated critical Kp for BAW calculation
	static double s_BAW_E; ///< epsilon for BAW calculation
	static int s_BAW_MaxCount; ///< max iterations for BAW calculation
	static int s_BAW_Count; ///< iterations for BAW calculation
	static double s_BAW_EEP; ///< early exercise premium for BAW calculation

	static double s_Min_PxEpsilon; ///< minimum price epsilon
	static double s_Default_PxEpsilon; ///< default price epsilon
	static int s_Default_Max_ImpVolIterations; ///< default max iterations for implied vol calculation
	static int s_Default_NTimeSteps;///< default number of time steps
	static int s_Default_MPxSteps; ///< default number of price steps


	///@}


public:
	/**
	* @brief get infinity negative
	*
	* @return infinity negative
	*/
	static double getNegativeInf(); ///< negative infinity

	/**
	* @brief get infinity positive
	*
	* @return infinity positive
	*/
	static double getPositiveInf(); ///< positive infinity

	/**
	* @brief get pi
	*
	* @return pi
	*/
	static double getPi(); ///< pi constant

	/**
	* @brief get 1/sqrt(2*pi)
	* 
	* @return 1/sqrt(2*pi)
	*/
	static double get1OverSqrt2Pi(); ///< 1.0/sqrt(2.0*pi)

	/**
	* @brief get days in one year, 365
	*
	* @return days in one year, 365
	*/
	static double getDaysOneYear();

	/**
	* @brief get trading days in one year, 252
	*
	* @return trading days in one year, 252
	*/
	static double getTradingDaysOneYear(); 

	/**
	* @brief get day in year unit
	*
	* @return day in year unit
	*/
	static double getDayInYear();  

	/**
	* @brief get trading day in year unit
	*
	* @return trading day in year unit
	*/
	static double getTradingDayInYear();  

	/**
	* @brief get max iterations for implied vol calculation
	*
	* @return max iterations for implied vol calculation
	*/
	static int getImpVolMaxIteration(); 

	/**
	* @brief get min implied vol
	*
	* @return min implied vol
	*/
	static double getImpVolMin(); 

	/**
	* @brief get max implied vol
	*
	* @return max implied vol
	*/
	static double getImpVolMax();  

	/**
	* @brief get epsilon for implied vol calculation
	*
	* @return epsilon for implied vol calculation
	*/
	static double getImpVolEpsilon(); 

	/**
	* @brief get price epsilon for implied vol calculation
	*
	* @return price epsilon for implied vol calculation
	*/
	static double getImpVolPxEpsilon();  

	/**
	* @brief get thresh for bisection implied vol calculation
	*
	* @return thresh for bisection implied vol calculation
	*/
	static double getImpVolBisectionThresh();  

	/**
	* @brief get difference between current iteration and previous iteration
	*
	* @return difference between current iteration and previous iteration
	*/
	static double getImpVolDiff(); 

	/**
	* @brief get iteration count for implied vol calculation
	*
	* @return iteration count for implied vol calculation
	*/
	static int getImpVolIterCount();  

	/**
	* @brief get calculated critical Kc for BAW calculation
	*
	* @return calculated critical Kc for BAW calculation
	*/
	static double getBAWKc(); 

	/**
	* @brief get calculated critical Kp for BAW calculation
	*
	* @return calculated critical Kp for BAW calculation
	*/
	static double getBAWKp();  

	/**
	* @brief get  epsilon for BAW calculation
	*
	* @return  epsilon for BAW calculation
	*/
	static double getBAWE();  

	/**
	* @brief get max iterations for BAW calculation
	*
	* @return max iterations for BAW calculation
	*/
	static int getBAWMaxCount();  

	/**
	* @brief get iterations for BAW calculation
	*
	* @return iterations for BAW calculation
	*/
	static int getBAWCount();  

	/**
	* @brief get early exercise premium for BAW calculation
	*
	* @return early exercise premium for BAW calculation
	*/
	static double getBAWEEP(); 

	/**
	* @brief get minimum price epsilon
	*
	* @return minimum price epsilon
	*/
	static double getMinPxEpsilon();  

  /**
  * @brief get default price epsilon
  *
  * @return default price epsilon
  */
  static double getDefaultPxEpsilon(); 

	/**
	* @brief get default default max iterations for implied vol calculation
	*
	* @return default max iterations for implied vol calculation
	*/
   static int getDefaultMaxImpVolIterations();  

 
  /**
  * @brief get default number of time steps
  *
  * @return  default number of time steps
  */
  static int getDefaultNTimeSteps(); 

  /**
  * @brief get default price steps
  *
  * @return default price steps
  */
  static int getDefaultMPxSteps(); ///< default number of price steps

	///**
	//* get const s_DayInYear which is 1.0/365.0
	//*/
	//static double getDayInYear();

	///**
	//* get s_TradingDayInYear which is 1.0/252.0
	//*/
	//static double getTradingDayInYear();

	/**
	*  @name get types by name
	*/
	///@{
	/**
	* @brief get OptionCalcType by name
	* 
	* @param name
	* 
	* @return OptionCalcType
	*/
	static OptionCalcType::enumtype getOptionCalcTypeByName(const std::string& name);

	/**
	* @brief get CallPutType by name
	*
	* @param name
	*
	* @return CallPutType
	*/
	static CallPutType::enumtype getCallPutTypeByName(const std::string& name);

	/**
	* @brief get OptionExerciseStyle by name
	*
	* @param name
	*
	* @return OptionExerciseStyle
	*/
	static OptionExerciseStyle::enumtype getOptionExerciseStyleByName(const std::string& name);

	/**
	* @brief get OptionPxMethod
	*
	* @param name
	*
	* @return OptionPxMethod
	*/
	static OptionPxMethod::enumtype getOptionPxMethodByName(const std::string& name);

	///@}

	/** 
	* @name Double Price and Vol
	*/
	///@{
	/**
	* @brief test if a vol is valid
	* 
	* @param vol as volatility
	* 
	* @return if vol is valid or not
	*/
    static bool isValidVol(double vol) ;

	/**
	* @brief min of two doubles
	*
	* @param x
	* @param y
	* 
	* @return min of x and y
	*/
	static double min_double(double x, double y) ;

	/**
	* @brief max of two doubles
	*
	* @param x
	* @param y
	*
	* @return max of x and y
	*/
	static double max_double(double x, double y) ;

	///@}


	/** 
	* @name Distributions
	*/
	///@{
 
	/**
	* @brief The normal distribution function
	* 
	* @param x
	* 
	* @return calculated value
	*/
    static double dnorm(double x);

	/**
	* @briefCummulative double precision algorithm based on Hart 1968, Based on implementation by Graeme West
	*
	* @param x
	*
	* @return calculated value
	*/
	static double pnorm(double x);

	/**
	* @brief The  bivariate normal distribution function
	*
	* @param x
	* @param y
	* @param rho
	*
	* @return calculated value
	*/
    static double dnorm2d(double x, double y, double rho);

	/**
	* @brief Cumulative density function for bivariate normal distribution, Drezner-Wesolowsky 1990 simple algorithm
	*
	* @param x
	* @param y
	* @param rho
	*
	* @return calculated value
	*/ 
	static double pnorm2d(double x, double y, double rho);

	/**
	* @brief Lower tail quantile for standard normal distribution function.
	*
	* @param p
	*
	* @return calculated value
	*/
	static double qnorm(double p);

	///@}


	/** 
	* @name Calc Functions
	*/
	///@{

	/**
	* @brief calculate option price and greeks
	*
	* @param calcType Price,ImpVol,Delta,Gamma,Vega,Theta,Rho
	* @param method BSM, BAW, or CRR
	* @param exerciseStyle American or European
	* @param cp Call, Put, or Straddle
	* @param S underlying price
	* @param X strike price
	* @param T time(in year) to expire
	* @param r risk free interest rate
	* @param b carry cost
	* @param v volatility or option price for implied vol calculation
	* @param nTimeSteps number of time steps for tree calculation
	* @param mPxSteps number of price steps for fdm
	* @param pxEpsilon price change for greeks calculation
	* 
	* @return calculated value
	*/
	static double calcOption(OptionCalcType::enumtype calcType,OptionPxMethod::enumtype method,OptionExerciseStyle::enumtype exerciseStyle, CallPutType::enumtype cp, double S, double X, double T, double r, double b, double v, int nTimeSteps, int mPxSteps, double pxEpsilon );

	static double calcOptionByTypeInt(int calcTypeInt, int methodInt, int exerciseStyleInt, int cpInt, double S, double X, double T, double r, double b, double v, int nTimeSteps, int mPxSteps, double pxEpsilon);

	static double calcOptionByTypeStr(const std::string& calcTypeStr, const std::string& methodStr, const std::string&  exerciseStyleStr, const std::string& cpStr, double S, double X, double T, double r, double b, double v, int nTimeSteps, int mPxSteps, double pxEpsilon);

	/**
	* @brief calculate implied vol with a seed implied vol
	*
	* @param method BSM, BAW, or CRR
	* @param exerciseStyle American or European
	* @param cp Call, Put, or Straddle
	* @param S underlying price
	* @param X strike price
	* @param T time(in year) to expire
	* @param r risk free interest rate
	* @param b carry cost
	* @param v volatility or option price for implied vol calculation
	* @param nTimeSteps number of time steps for tree calculation
	* @param mPxSteps number of price steps for fdm
	* @param vol0 start implied volatility
	* @param pxEpsilon, usually use half px tick, default is 0.005
	* @param ivMaxIterations max iterations for loops
	*
	* @return calcualted value
	*/
	static double calcImpVol(OptionPxMethod::enumtype method, OptionExerciseStyle::enumtype exerciseStyle, CallPutType::enumtype cp, double S, double X, double T, double r, double b, double v, int nTimeSteps, int mPxSteps,double pxEpsilon, double vol0, int ivMaxIterations);

	static double calcImpVolByTypeInt(int methodInt, int exerciseStyleInt, int cpInt, double S, double X, double T, double r, double b, double v, int nTimeSteps, int mPxSteps, double pxEpsilon, double vol0, int ivMaxIterations);

	static double calcImpVolByTypeStr(const std::string& methodStr, const std::string&  exerciseStyleStr, const std::string& cpStr, double S, double X, double T, double r, double b, double v, int nTimeSteps, int mPxSteps, double pxEpsilon, double vol0, int ivMaxIterations);


	/**
	* @brief alculate implied vol using bisection method
	*
	* @param method BSM, BAW, or CRR
	* @param exerciseStyle American or European
	* @param cp Call, Put, or Straddle
	* @param S underlying price
	* @param X strike price
	* @param T time(in year) to expire
	* @param r risk free interest rate
	* @param b carry cost
	* @param v volatility or option price for implied vol calculation
	* @param nTimeSteps number of time steps for tree calculation
	* @param mPxSteps number of price steps for fdm
	* @param vol0 start implied volatility
	* @param pxEpsilon, usually use half px tick, default is 0.00382
	* @param ivMaxIterations max iterations for loops
	*
	* @return calculated value
	*/
	static double calcImpVolBisection(OptionPxMethod::enumtype method, OptionExerciseStyle::enumtype exerciseStyle, CallPutType::enumtype cp, double S, double X, double T, double r, double b, double v, int nTimeSteps, int mPxSteps, double pxEpsilon, double vol0, int ivMaxIterations);

	static double calcImpVolBisectionByTypeInt(int methodInt, int exerciseStyleInt, int cpInt, double S, double X, double T, double r, double b, double v, int nTimeSteps, int mPxSteps, double pxEpsilon, double vol0, int ivMaxIterations);

	static double calcImpVolBisectionByTypeStr(const std::string& methodStr, const std::string&  exerciseStyleStr, const std::string& cpStr, double S, double X, double T, double r, double b, double v, int nTimeSteps, int mPxSteps, double pxEpsilon, double vol0, int ivMaxIterations);

	/**
	* @brief calculate implied vol using newton-raphson method
	*
	* @param method BSM, BAW, or CRR
	* @param exerciseStyle American or European
	* @param cp Call, Put, or Straddle
	* @param S underlying price
	* @param X strike price
	* @param T time(in year) to expire
	* @param r risk free interest rate
	* @param b carry cost
	* @param v volatility or option price for implied vol calculation
	* @param nTimeSteps number of time steps for tree calculation
	* @param mPxSteps number of price steps for fdm
	* @param vol0 start implied volatility
	* @param pxEpsilon, usually use half px tick, default is 0.00382
	* @param ivMaxIterations max iterations for loops
	*
	* @return calculated value
	*/
	static double calcImpVolNewtonRaphson(OptionPxMethod::enumtype method, OptionExerciseStyle::enumtype exerciseStyle, CallPutType::enumtype cp, double S, double X, double T, double r, double b, double v, int nTimeSteps, int mPxSteps, double pxEpsilon, double vol0, int ivMaxIterations);

	static double calcImpVolNewtonRaphsonByTypeInt(int methodInt, int exerciseStyleInt, int cpInt, double S, double X, double T, double r, double b, double v, int nTimeSteps, int mPxSteps, double pxEpsilon, double vol0, int ivMaxIterations);

	static double calcImpVolNewtonRaphsonByTypeStr(const std::string& methodStr, const std::string&  exerciseStyleStr, const std::string& cpStr, double S, double X, double T, double r, double b, double v, int nTimeSteps, int mPxSteps, double pxEpsilon, double vol0, int ivMaxIterations);


	/**
	* @brief get seed value for implied vol calculation(Manaster and Keohler)
	*
	* @param S as underlying price
	* @param X as strike price
	* @param T as expiration in year
	* @param r as interest rate
	*
	* @return calculated value
	*/
	static double getImpVolSeed(double S, double x, double T, double r);


	///@}
	//end calc functions

	/**
	* @name european option pricing
	*/
	///@{

	/**
	* @brief get d1 of bsm formula
	*
	* @param S as underlying price
	* @param X as strike price
	* @param T as expiration in year
	* @param r as interest rate
	* @param b as carry rate
	* @param v as volatility
	*
	* @return calculated value
	*/
	static double d1(double S, double X, double T, double r, double b, double v);

	/**
	* @brief get d2 of bsm formula
	*
	* @param S as underlying price
	* @param X as strike price
	* @param T as expiration in year
	* @param r as interest rate
	* @param b as carry rate
	* @param v as volatility
	*
	* @return calculated value
	*/
	static double d2(double S, double X, double T, double r, double b, double v);

	/**
	* @brief Generalized Black-Scholes-Merton formula
	*
	* @param cp as CallPutType
	* @param S as underlying price
	* @param X as strike price
	* @param T as expiration in year
	* @param r as interest rate
	* @param b as carry rate
	* @param v as volatility
	*
	* @return calculated value
	*/
	static double bsm(CallPutType::enumtype cp, double S, double x, double T, double r, double b, double v);

	/**
	* @brief calculate Black-Scholes-Merton Call analytic Delta
	*
	* @param S as underlying price
	* @param X as strike price
	* @param T as expiration in year
	* @param r as interest rate
	* @param b as carry rate
	* @param v as volatility
	*
	* @return calculated value
	*/
	static double bsmCallDelta(double S, double x, double T, double r, double b, double v);

	/**
	* @brief calculate Black-Scholes-Merton Put analytic Delta
	*
	* @param S as underlying price
	* @param X as strike price
	* @param T as expiration in year
	* @param r as interest rate
	* @param b as carry rate
	* @param v as volatility
	*
	* @return calculated value
	*/
	static double bsmPutDelta(double S, double x, double T, double r, double b, double v);

	/**
	* @brief calculate Black-Scholes-Merton analytic Gamma
	*
	* @param S as underlying price
	* @param X as strike price
	* @param T as expiration in year
	* @param r as interest rate
	* @param b as carry rate
	* @param v as volatility
	*
	* @return calculated value
	*/
	static double bsmGamma(double S, double x, double T, double r, double b, double v);

	/**
	* @brief calculate Black-Scholes-Merton formula analytic vega
	*
	* @param S as underlying price
	* @param X as strike price
	* @param T as expiration in year
	* @param r as interest rate
	* @param b as carry rate
	* @param v as volatility
	*
	* @return calculated value
	*/
	static double bsmVega(double S, double x, double T, double r, double b, double v);

	/**
	* @brief calculate Black-Scholes-Merton formula analytic Call Rho
	*
	* @param S as underlying price
	* @param X as strike price
	* @param T as expiration in year
	* @param r as interest rate
	* @param b as carry rate
	* @param v as volatility
	*
	* @return calculated value
	*/
	static double bsmCallRho(double S, double x, double T, double r, double b, double v);

	/**
	* @brief calculate Black-Scholes-Merton formula analytic Put Rho
	*
	* @param S as underlying price
	* @param X as strike price
	* @param T as expiration in year
	* @param r as interest rate
	* @param b as carry rate
	* @param v as volatility
	*
	* @return calculated value
	*/
	static double bsmPutRho(double S, double x, double T, double r, double b, double v);

	/**
	* @brief calculate Black-Scholes-Merton formula analytic Call Theta
	*
	* @param S as underlying price
	* @param X as strike price
	* @param T as expiration in year
	* @param r as interest rate
	* @param b as carry rate
	* @param v as volatility
	*
	* @return calculated value
	*/
	static double bsmCallTheta(double S, double x, double T, double r, double b, double v);

	/**
	* @brief calculate Black-Scholes-Merton formula analytic Put Theta
	*
	* @param S as underlying price
	* @param X as strike price
	* @param T as expiration in year
	* @param r as interest rate
	* @param b as carry rate
	* @param v as volatility
	*
	* @return calculated value
	*/
	static double bsmPutTheta(double S, double x, double T, double r, double b, double v);

	///**
	//* calculate Generalized Black-Scholes-Merton formula
	//*/
	//static double bsmCalc(OptionCalcType calcType, CallPutType cp, double S, double x, double T, double r, double b, double v, double dS);

	/**
	* @brief calculate Generalized Black-Scholes-Merton formula
	*
	* @param calcType as OptionCalcType
	* @param cp as CallPutType
	* @param S as underlying price
	* @param X as strike price
	* @param T as expiration in year
	* @param r as interest rate
	* @param b as carry rate
	* @param v as volatility
	* @param pxEpsilon as price epsilon
	*
	* @return calculated value
	*/
	static double calcBSM(OptionCalcType::enumtype calcType, CallPutType::enumtype cp, double S, double X, double T, double r, double b, double v, double pxEpsilon );

 
	///@}
	//end european option pricing

	/**
	* @name BAW american option pricing
	*/
	///@{
	//BAW american call

	/**
	* @brief Newton Raphson algorithm to solve for the critical commodity price for a Call
	*
	* @param X as strike price
	* @param T as expiration in year
	* @param r as interest rate
	* @param b as carry rate
	* @param v as volatility
	*
	* @return calculated value
	*/
	static double Kc(double X, double T, double r, double b, double v);

	/**
	* @brief BAW American call approximation
	*
	* @param S as underlying price
	* @param X as strike price
	* @param T as expiration in year
	* @param r as interest rate
	* @param b as carry rate
	* @param v as volatility
	* @param pxEpsilon as price epsilon
	*
	* @return calculated value
	*/
	static double bawAmericanCallApprox(double S, double X, double T, double r, double b, double v);

	/**
	* @brief Newton Raphson algorithm to solve for the critical commodity price for a Put
	*
	* @param X as strike price
	* @param T as expiration in year
	* @param r as interest rate
	* @param b as carry rate
	* @param v as volatility
	*
	* @return calculated value
	*/
	static double Kp(double X, double T, double r, double b, double v);

	/**
	* @brief BAW American put approximation
	*
	* @param S as underlying price
	* @param X as strike price
	* @param T as expiration in year
	* @param r as interest rate
	* @param b as carry rate
	* @param v as volatility
	*
	* @return calculated value
	*/
	static double bawAmericanPutApprox(double S, double X, double T, double r, double b, double v);

	/**
	* @brief BAW American approximation
	*
	* @param cp as CallPutType
	* @param S as underlying price
	* @param X as strike price
	* @param T as expiration in year
	* @param r as interest rate
	* @param b as carry rate
	* @param v as volatility
	*
	* @return calculated value
	*/
	static double bawAmericanApprox(CallPutType::enumtype cp, double S, double X, double T, double r, double b, double v);

 

	/**
	* @brief BAW American approximation calc
	*
	* @param calcType as OptionCalcType
	* @param cp as CallPutType
	* @param S as underlying price
	* @param X as strike price
	* @param T as expiration in year
	* @param r as interest rate
	* @param b as carry rate
	* @param v as volatility
	* @param pxEpsilon as price epsilon
	*
	* @return calculated value
	*/
	static double calcBAW(OptionCalcType::enumtype calcType, CallPutType::enumtype cp, double S, double X, double T, double r, double b, double v, double pxEpsilon);

 
	///@}
	//end BAW american option pricing

	/**
	* @name BS2002 american option pricing
	*/
	///@{
	/**
	* @brief phi in BS2002 american option pricing
	*
	* @param S as underlying price
	* @param T as expiration in year
	* @param gamma
	* @param h
	* @param i
	* @param r as interest rate
	* @param b as carry rate
	* @param v as volatility
	*
	* @return calculated value
	*/
	static double phi(double S, double T, double gamma, double h, double i, double r, double b, double v);

	/**
	* @brief phi2 in BS2002 american option pricing
	*
	* @param S as underlying price
	* @param T2 
	* @param gamma
	* @param h
	* @param i
	* @param r as interest rate
	* @param b as carry rate
	* @param v as volatility
	*
	* @return calculated value
	*/
	static double phi2(double S, double T2, double gamma, double h, double i, double r, double b, double v);

	/**
	* @brief ksi in BS2002 american option pricing
	*
	* @param S as underlying price
	* @param T2 
	* @param gamma 
	* @param h
	* @param I2
	* @param I1
	* @param t1
	* @param r as interest rate
	* @param b as carry rate
	* @param v as volatility
	*
	* @return calculated value
	*/
	static double ksi(double S, double T2, double gamma, double h, double I2, double I1, double t1, double r, double b, double v);

	/**
	* @brief Bjerksund and Stensland 2002 american call approximation
	*
	* @param S as underlying price
	* @param X as strike price
	* @param T as expiration in year
	* @param r as interest rate
	* @param b as carry rate
	* @param v as volatility
	*
	* @return calculated value
	*/
	 static double bsAmericanCallApprox2002(double S, double X, double T, double r, double b, double v);

	 /**
	 * @brief Bjerksund and Stensland 2002 american approximation
	 *
	 * @param cp as CallPutType
	 * @param S as underlying price
	 * @param X as strike price
	 * @param T as expiration in year
	 * @param r as interest rate
	 * @param b as carry rate
	 * @param v as volatility
	 *
	 * @return calculated value
	 */
	 static double bsAmericanApprox2002(CallPutType::enumtype cp, double S, double X, double T, double r, double b, double v);

 
	 /**
	 * @brief Bjerksund and Stensland 2002 american approximation calculation
	 *
	 * @param calcType as OptionCalcType
	 * @param cp as CallPutType
	 * @param S as underlying price
	 * @param X as strike price
	 * @param T as expiration in year
	 * @param r as interest rate
	 * @param b as carry rate
	 * @param v as volatility
	 * @param pxEpsilon as price epsilon
	 *
	 * @return calculated value
	 */
	 static double calcBS2002American(OptionCalcType::enumtype calcType, CallPutType::enumtype cp, double S, double X, double T, double r, double b, double v, double pxEpsilon);

	 ///@}

	//end BS2002 american option pricing

	 /**
	 * @brief CRR binomial tree  
	 *
	 * @param calcType as OptionCalcType
	 * @param exerciseStyle as OptionExerciseStyle
	 * @param cp as CallPutType
	 * @param S as underlying price
	 * @param X as strike price
	 * @param T as expiration in year
	 * @param r as interest rate
	 * @param b as carry rate
	 * @param v as volatility
	 * @param n as time steps
	 *
	 * @return calculated value
	 */
	 static double crrBinomial(OptionCalcType::enumtype  calcType, OptionExerciseStyle::enumtype exerciseStyle, CallPutType::enumtype cp, double S, double X, double T, double r, double b, double v, int n);
	 
 
	 /**
	 * @brief CRR binomial tree calculation
	 *
	 * @param calcType as OptionCalcType  
	 * @param exerciseStyle as OptionExerciseStyle 
	 * @param cp as CallPutType 
	 * @param S as underlying price
	 * @param X as strike price
	 * @param T as expiration in year
	 * @param r as interest rate
	 * @param b as carry rate
	 * @param v as volatility
	 * @param n as time steps
	 * @param pxEpsilon as price epsilon
	 *
	 * @return calculated value
	 */
	 static double calcCRRTree(OptionCalcType::enumtype  calcType, OptionExerciseStyle::enumtype exerciseStyle, CallPutType::enumtype cp, double S, double X, double T, double r, double b, double v, int n, double pxEpsilon);


	 
}; //end PxUtil
} //end namespace XT

#endif
