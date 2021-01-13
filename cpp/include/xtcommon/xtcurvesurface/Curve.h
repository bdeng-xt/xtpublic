#pragma once
#ifndef XT_CURVE_H
#define XT_CURVE_H

/**
* \file Curve.h
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
#include "FIXData.pb.h"
#include "typedef_FIXData.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "Util.h"
#include "QLUtil.h"
#include "Loess.h"

#include "Point.h"
#include "DoubleFunction.h"

#include "safe_ptr.h"

//#include "ql/quantlib.hpp"

namespace XT {
 
	class Curve;

	//////typedef for Curve
	//#include "safe_ptr.h"
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<Curve> CurvePtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<Curve> CurvePtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<Curve> CurvePtr;

#else

	typedef ::boost::shared_ptr<Curve> CurvePtr;
#endif


	typedef ::sf::safe_ptr<Curve> CurveSafePtr;

	typedef sf::contfree_safe_ptr<Curve> CurveContFreePtr;
	//////end typedef for Curve



/**
* This is an abstract class for all curves
*/

//#if defined(USE_STD_SHARED_PTR)
//	class XT_COMMON_API Curve : public std::enable_shared_from_this<Curve> 
//#else
//class XT_COMMON_API Curve : public boost::enable_shared_from_this<Curve> 
//#endif
class XT_COMMON_API Curve : public std::enable_shared_from_this<Curve>
{
public:
	/** 
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	Curve();

	/**
	* @brief default copy constructor
	*/
	Curve(const Curve& from) ;

	/**
	* @brief default copy assignment
	*/
	Curve& operator=(const Curve& from) ;

	/**
	* @brief destructor
	*/
	virtual ~Curve();
	///@}



public:
	/**
	*  @name virutal functions
	*/
	///@{

	/**
	* @brief get converted x value
	*
	* @param x as original value
	* @param flag as integer
	*
	* @return converted x
	*/
	virtual double getX(double x, int flag);

	/**
	* @brief get curve value using control points given a x value
	*
	* @param x as x value
	*
	* @return double value for y
	*/
	virtual double getYByCtrlPoints(double x,int flag);

	/**
	* @brief get curve value using function give a x value
	*
	* @param x as x value
	* 
	* @return double value for y
	*/
	virtual double getYByFunc(double x, int flag);

	/**
	* @brief get curve value vector using function for all x values
	*
	* @return double value vector
	*/
	virtual std::vector<double> getYVectorByFunc( int flag);


	/**
	* @brief update weights
	*
	*/
	virtual void updateWeights();


	/**
	* @brief fit curve
	*
	*/
	virtual void fit( );

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


public:

	/** 
	* @name Data and Ctrl Points
	*/
	///@{
 

	/**
	* @brief set a data point
	*
	* @param tag as integer index
	* @param x as double
	* @param y as double
	* @param z as double
	* @param v as double
	* @param w as weight
	* @param flag as integer
	* @param ts as timestamp
	*/
	void setDataPoint(int tag, double x, double y, double z, double v, double w, int flag, int64_t ts);

	/**
	* @brief remove a data point
	*
	* @param tag as integer index
	*/
	void removeDataPoint(int tag);

	/**
	* @brief set a ctrl point
	*
	* @param tag as integer index
	* @param x as double
	* @param y as double
	* @param z as double
	* @param v as double
	* @param w as weight
	* @param flag as integer
	* @param ts as timestamp
	*/
	void setCtrlPoint(int tag, double x, double y, double z, double v, double w, int flag, int64_t ts);

	/**
	* @brief remove a ctrl point
	*
	* @param tag as integer index
	*/
	void removeCtrlPoint(int tag);

	/**
	* @brief has tag for data point
	*
	* @param tag as integer
	*
	* @return if the tag exits
	*/
	bool hasTagForDataPoint(int tag);

	/**
	* @brief has tag for ctrl point
	*
	* @param tag as integer
	*
	* @return if the tag exits
	*/
	bool hasTagForCtrlPoint(int tag);
 
////
	/**
	* @brief get data x
	*
	* @return data x
	*/
	double getDataX(int tag);


	/**
	* @brief get data y
	*
	* @return data y
	*/
	double getDataY(int tag);


	/**
	* @brief get data z
	*
	* @return data z
	*/
	double getDataZ(int tag);


	/**
	* @brief get data v
	*
	* @return data v
	*/
	double getDataV(int tag);


	/**
	* @brief get data w
	*
	* @return w
	*/
	double getDataW(int tag);


	/**
	* @brief get data flag
	*
	* @return flag
	*/
	int getDataFlag(int tag);

	/**
	* @brief update x for a point
	*
	* @param tag as integer index
	* @param x as double
	*/
	void setDataX(int tag, double x);

	/**
	* @brief set y for a data point
	*
	* @param tag as integer index
	* @param y as double
	*/
	void setDataY(int tag, double y);

	/**
	* @brief set z for a data point
	*
	* @param tag as integer index
	* @param z as double
	*/
	void setDataZ(int tag, double z);

	/**
	* @brief set v for a data point
	*
	* @param tag as integer index
	* @param v as double
	*/
	void setDataV(int tag, double v);

	/**
	* @brief set w for a data point
	*
	* @param tag as integer index
	* @param w as weight
	*/
	void setDataW(int tag, double w);

	/**
	* @brief set flag for a data point
	*
	* @param tag as integer index
	* @param flag as integer
	*/
	void setDataFlag(int tag, int flag);

////
/**
* @brief get ctrl x
*
* @return ctrl x
*/
	double getCtrlX(int tag);


	/**
	* @brief get ctrl y
	*
	* @return ctrl y
	*/
	double getCtrlY(int tag);


	/**
	* @brief get ctrl z
	*
	* @return ctrl z
	*/
	double getCtrlZ(int tag);


	/**
	* @brief get ctrl v
	*
	* @return ctrl v
	*/
	double getCtrlV(int tag);


	/**
	* @brief get ctrl w
	*
	* @return ctrl w
	*/
	double getCtrlW(int tag);


	/**
	* @brief get ctrl flag
	*
	* @return ctrl flag
	*/
	int getCtrlFlag(int tag);

	/**
	* @brief update x for a ctrl point
	*
	* @param tag as integer index
	* @param x as double
	*/
	void setCtrlX(int tag, double x);

	/**
	* @brief set y for a ctrl point
	*
	* @param tag as integer index
	* @param y as double
	*/
	void setCtrlY(int tag, double y);

	/**
	* @brief set z for a ctrl point
	*
	* @param tag as integer index
	* @param z as double
	*/
	void setCtrlZ(int tag, double z);

	/**
	* @brief set v for a ctrl point
	*
	* @param tag as integer index
	* @param v as double
	*/
	void setCtrlV(int tag, double v);

	/**
	* @brief set w for a ctrl point
	*
	* @param tag as integer index
	* @param w as weight
	*/
	void setCtrlW(int tag, double w);

	/**
	* @brief set flag for a ctrl point
	*
	* @param tag as integer index
	* @param flag as integer
	*/
	void setCtrlFlag(int tag, int flag);

//// vectors
	/**
	* @brief get data x vector
	*
	* @return data x vector
	*/
	std::vector<double> dataXVector();

	/**
	* @brief get data y vector
	*
	* @return data y vector
	*/
	std::vector<double> dataYVector();


	/**
	* @brief get data z vector
	*
	* @return data z vector
	*/
	std::vector<double> dataZVector();


	/**
	* @brief get data v vector
	*
	* @return data v vector
	*/
	std::vector<double> dataVVector();


	/**
	* @brief get data w vector
	*
	* @return data w vector
	*/
	std::vector<double> dataWVector();


	/**
	* @brief get data flag vector
	*
	* @return data flag vector
	*/
	std::vector<int> dataFlagVector();

//
/**
* @brief get ctrl x vector
*
* @return ctrl x vector
*/
	std::vector<double> ctrlXVector();

	/**
	* @brief get ctrl y vector
	*
	* @return ctrl y vector
	*/
	std::vector<double> ctrlYVector();


	/**
	* @brief get ctrl z vector
	*
	* @return ctrl z vector
	*/
	std::vector<double> ctrlZVector();


	/**
	* @brief get ctrl v vector
	*
	* @return ctrl v vector
	*/
	std::vector<double> ctrlVVector();


	/**
	* @brief get ctrl w vector
	*
	* @return ctrl w vector
	*/
	std::vector<double> ctrlWVector();


	/**
	* @brief get ctrl flag vector
	*
	* @return ctrl flag vector
	*/
	std::vector<int> ctrlFlagVector();

	/**
	* @brief get fit method
	*
	* @return fit method
	*/
	int getFitMethod();

	/**
	* @brief set fit method
	*
	* @param v as integer
	*/
	void setFitMethod(int v);

	/**
	* @brief get weight method
	*
	* @return weight method
	*/
	int getWeightMethod();

	/**
	* @brief set fit method
	*
	* @param v as integer
	*/
	void setWeightMethod(int v);

	///@}

	/** 
	* @name Calculation
	*/
	///@{



	/**
	* @brief do Loess calculation
	*/
	void calcLoess();

	///@}

	/**
	*  @name Setters and Getters 
	*/
	///@{

	/**
	* @brief get curve name
	*/
	const std::string& getName();

	/**
	* @brief set curve name
	*
	* @param s for curve name
	*/
	void setName(const std::string & s);

	/**
	* @brief get control points
	*
	* @return ctrl points map
	*/
	PointMapPtr& ctrlPoints();

	/**
	* @brief get data points
	*
	* @return data points map
	*/
	PointMapPtr& dataPoints();

	/**
	* @brief get function pointer
	*
	* @return function pointer
	*/
	DoubleFunctionPtr& func();

	/**
	* @brief cfg data
	*
	* @return cfg data
	*/
	CurveCfgDataPtr& cfgData();


	/**
	* @brief data
	*
	* @return data
	*/
	CurveDataPtr& data();


	/**
	* @brief point list
	*
	* @return point list
	*/
	PointListPtr& pointList(); 

	/**
	* @brief point map list
	*
	* @return point map list
	*/
	PointMapListPtr& pointMapList();



	/**
	* @brief is fitted or not
	*
	* @return if it is fitted
	*/
	bool isFitted();

	/**
	* @brief has weights or not
	*
	* @return if it has weights
	*/
	bool hasWeights();

	/**
	* @brief get parameter maxIterations
	* 
	* @return number of max iterations
	*/
	int getMaxIterations();

	/**
	* @brief set parameter maxIterations
	*
	* @param v for number of max iterations
	*/
	void setMaxIterations(int v);


	/**
	* @brief get parameter minStartIterations
	*
	* @return minimum number of start iterations
	*/
	int getMinStartIterations();

	/**
	* @brief set parameter minStartIterations
	*
	* param v as minumum number of start iterations
	*/
	void setMinStartIterations(int v);

	/**
	* @brief get parameter rootEpsilon
	*
	* @return root epsilon
	*/
	double getRootEpsilon();

	/**
	* @brief set parameter rootEpsilon
	*
	* @param v as root epsilon
	*/
	void setRootEpsilon(double v);

	/**
	* @brief get parameter functionEpsilon
	*
	* @return function epsilon
	*/
	double getFunctionEpsilon();

	/**
	* @brief set parameter functionEpsilon
	*
	* @param v for function epsilon
	*/
	void setFunctionEpsilon(double v);

	/**
	* @brief get parameter gradientNormEpsilon
	*
	* @return gradient norm epsilon
	*/
	double getGradientNormEpsilon();

	/**
	* @brief set parameter gradientNormEpsilon
	*
	* @param v for gradient norm epsilon
	*/
	void setGradientNormEpsilon(double v);

	/**
	* @brief get solver endCriteria
	*
	* @return end criteria 
	*/
	int getEndCriteriaType();



	/**
	* @brief get fitFuncCount
	*
	* @return iteration count for fitting
	*/
	int getFitFuncCount();

	/**
	* @brief get fitFuncValue
	*
	* @return fitted function value
	*/
	double getFitFuncValue();

 

	/**
	* @brief get loess function
	*
	* @return loess function
	*/
	LoessPtr& loessFunc();

	///@}

	/**
	* @brief is valid x
	*
	* @param x
	* @return if the value is valid for x
	*/
	bool isValidX(double x);

	/**
	* @brief is valid y
	*
	* @param y
	* @return if the value is valid for y
	*/
	bool isValidY(double y);





	/** 
	* @name String Functions
	*/
	///@{
	/**
	* @brief string function
	*
	* @return string
	*/
	virtual std::string str();

	virtual std::string getStr(int flag);

	virtual bool updateFromStr(const std::string& s, int flag);
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
	static CurvePtr create();
	///@}

//protected:
 

protected:


	CurveCfgDataPtr m_cfgData;
	CurveDataPtr m_data;

	PointMapPtr m_ctrlPoints; ///< control points
	PointMapPtr m_dataPoints; ///< data points

	PointListPtr m_pointList; ///< point list

	PointMapListPtr m_pointMapList;///< point map list

	DoubleFunctionPtr m_func; ///< function
protected:
	LoessPtr m_loess; ///< an instance of Loess

protected:
	mutable boost::shared_mutex m_mutex;

}; //end class Curve


 


 


} //end namespace XT

#endif