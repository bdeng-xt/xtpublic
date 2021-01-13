#pragma once
#ifndef XT_QLUTIL_H
#define XT_QLUTIL_H

/**
* \file QLUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide Quantlib wrapper functions.
*
* \description
*	This component provides functions to wrap Quantlib functions.
*/

#include <vector>
#include <boost/smart_ptr.hpp>

#include "XTConfig.h"
#include "Point.h"
//#include "ql/quantlib.hpp"

namespace XT {



////
class XT_COMMON_API QLUtil {
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	QLUtil() {}

	/**
	* @brief copy constructor
	*/
	QLUtil(const QLUtil& from) {} // = delete;

	/**
	* @brief copy assignment
	*/
	QLUtil& operator=(const QLUtil& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~QLUtil() {}

	///@}
public:

	/** 
	* @name Interpolation Functions
	*/
	///@{
	/**
	* @brief linear interpolation
	*
	* @param xs as vector of x
	* @param ys as vector of y
	* @param x
	* 
	* @retrun interpolated value 
	*/
	static double calcLinearInterp(const std::vector<double>& xs, const std::vector<double>& ys, double x);

	static std::vector<double> calcLinearInterpWithDerivatives(const std::vector<double>& xs, const std::vector<double>& ys, double x);

	/**
	* @brief natural cubic spline interpolation
	*
	* @param xs as vector of x
	* @param ys as vector of y
	* @param x
	*
	* @retrun interpolated value
	*/
	static double calcCubicNaturalSpline(const std::vector<double>& xs, const std::vector<double>& ys, double x);

	static std::vector<double> calcCubicNaturalSplineWithDerivatives(const std::vector<double>& xs, const std::vector<double>& ys, double x);

	/**
	* @brief akima interpolation
	*
	* @param xs as vector of x
	* @param ys as vector of y
	* @param x
	*
	* @retrun interpolated value
	*/
	static double calcAkimaCubicInterp(const std::vector<double>& xs, const std::vector<double>& ys, double x);

	static std::vector<double> calcAkimaCubicInterpWithDerivatives(const std::vector<double>& xs, const std::vector<double>& ys, double x);

	///@}

}; //end class QLUtil


} //end namespace XT

#endif