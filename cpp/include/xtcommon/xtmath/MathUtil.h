#pragma once
#ifndef XT_MATHUTIL_H
#define XT_MATHUTIL_H

/**
* \file MathUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide math functions.
*
* \description
*	This component provides math functions.
*/
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstdint>
#include "XTConfig.h"



namespace XT
{

	//! Math static class
	/*!
		Contains useful math functions.

		Thread-safe.
	*/
	class XT_COMMON_API MathUtil
	{
	public:
		MathUtil() {} // = delete;
		MathUtil(const MathUtil&) {} // = delete;
		MathUtil(MathUtil&&) {} // = delete;
		~MathUtil() {}// = delete;

		MathUtil& operator=(const MathUtil&) { return *this;  } // = delete;
		MathUtil& operator=(MathUtil&&) { return *this;  } // = delete;

	protected:
		static const int64_t s_Thousand;///< one thousand
		static const double s_Milli;///< 1/thousand

		static const int64_t s_Million; ///< one million
		static const double s_Micro; ///< micro, 10^-6, 1/million

		static const int64_t s_Billion; ///< one billion 10^9
		static const double s_Nano; ///< 10^-9 1/billion

		static const double s_Epsilon;///< epsilon

		static const double s_Pi; ///< pi
		static const double s_E; ///< Euler's number

	public:
		/**
		* @brief get pi value
		*
		* @return pi value
		*/
		static double getPi();

		/**
		* @brief get Euler's number
		*
		* @return Euler's number
		*/
		static double getE();

		//////local regression
	public:
		static std::vector<double> lowessInterpX(const std::vector<double> &x, const std::vector<double> &y, double xcalc, double xstep, double f, int nsteps);

		static std::vector<double> lowessInterp(const std::vector<double> &x, const std::vector<double> &y, std::vector<double> xcalc, double f, int nsteps);

		static void lowess(const std::vector<double> &x, const std::vector<double> &y, double f, int nsteps, std::vector<double> &ys);

	protected:
		static void lowessWithWeights(const std::vector<double> &x, const std::vector<double> &y, double f, int nsteps, double delta, std::vector<double> &ys, std::vector<double> &rw, std::vector<double> &res);

		

		static void lowest(const std::vector<double> &x, const std::vector<double> &y, double xs, double &ys, int nleft, int nright, std::vector<double> &w, bool userw, std::vector<double> &rw, bool &ok);


	public:

		//! Computes the greatest common divisor of a and b
		/*!
			\param a - Value a
			\param b - Value b
			\return Greatest common divisor of a and b
		*/
		template <typename T>
		static T GCD(T a, T b);

		//! Finds the smallest value x >= a such that x % k == 0
		/*!
			\param a - Value a
			\param k - Value k
			\return Value x
		*/
		template <typename T>
		static T RoundUp(T a, T k);

		//! Calculate (operant * multiplier / divider) with 64-bit unsigned integer values
		/*!
			\param operant - Operant
			\param multiplier - Multiplier
			\param divider - Divider
			\return Calculated value of (operant * multiplier / divider) expression
		*/
		static uint64_t MulDiv64(uint64_t operant, uint64_t multiplier, uint64_t divider);
	};

///////////////////
	template <typename T>
	inline T MathUtil::GCD(T a, T b)
	{
		T c = a % b;

		while (c != 0)
		{
			a = b;
			b = c;
			c = a % b;
		}

		return b;
	}

	template <typename T>
	inline T MathUtil::RoundUp(T a, T k)
	{
		return ((a + k - 1) / k) * k;
	}


}//namespace


#endif