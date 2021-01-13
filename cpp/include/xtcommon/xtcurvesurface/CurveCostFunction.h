#pragma once
#ifndef XT_CURVE_COST_FUNCTION_H
#define XT_CURVE_COST_FUNCTION_H

/**
* \file CurveCostFunction.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide an abstract class for Curve and CurveCostFunction.
*
* \description
*	Designed for base class for all curves and CurveCost Function.
*/

#include <string>
#include <sstream>
#include <map>
#include <unordered_map>
#include <boost/smart_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <boost/thread.hpp>		 
#include <boost/bind.hpp>		 
#include <boost/any.hpp>
#include <boost/thread/shared_mutex.hpp>

#include <chrono>

#include "XTConfig.h"
#include "safe_ptr.h"

#include "FIXData.pb.h"
#include "typedef_FIXData.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "ql/quantlib.hpp"

#include "Curve.h"

namespace XT
{

	class CurveCostFunction;
	//////typedef for CurveCostFunction
	//#include "safe_ptr.h"
#if defined(USE_BOOST_SHARED_PTR)
	typedef ::boost::shared_ptr<CurveCostFunction> CurveCostFunctionPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<CurveCostFunction> CurveCostFunctionPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<CurveCostFunction> CurveCostFunctionPtr;

#else

	typedef ::boost::shared_ptr<CurveCostFunction> CurveCostFunctionPtr;
#endif


	typedef ::sf::safe_ptr<CurveCostFunction> CurveCostFunctionSafePtr;

	typedef sf::contfree_safe_ptr<CurveCostFunction> CurveCostFunctionContFreePtr;
	//////end typedef for CurveCostFunction

	/**
	* This is a class for curve cost
	*/
	class XT_COMMON_API CurveCostFunction : public QuantLib::CostFunction {
	public:

		/**
		* @brief constructor
		*/
		CurveCostFunction();

		/**
		* @brief constructor
		*
		* @param c
		*/
		CurveCostFunction(CurvePtr c);

		/**
		* @brief destructor
		*/
		virtual ~CurveCostFunction();

		/**
		* @brief get curve
		*/
		CurvePtr& curve();



	public:
		/**
		* @brief implementation of value() from QuantLib::CostFunction
		*
		* @param x value
		*
		* @return curve value corresponding to x
		*/
		virtual QuantLib::Real value(const QuantLib::Array & x) const;


		/**
		* @brief implementation of values() from QuantLib::CostFunction
		*
		* @param x value array
		*
		* @return value array
		*/
		virtual QuantLib::Disposable<QuantLib::Array> values(const QuantLib::Array& x) const;



		/**
		* @brief string function
		*
		* @return string
		*/
		virtual std::string str();

		/**
		* @brief create
		*
		* @return CurveCostFunctionPtr
		*/
		static CurveCostFunctionPtr create(CurvePtr c);

	protected:
		//DoubleFunctionPtr m_func; ///< cost function
		//PointMapPtr m_dataPoints; ///< data points
		//PointListPtr m_pointList; ///< point list

		//PointMapListPtr m_pointMapList;///< point map list

		//CurveCfgDataPtr m_cfgData;

		CurvePtr m_curve;

	};



}//namespace 


#endif