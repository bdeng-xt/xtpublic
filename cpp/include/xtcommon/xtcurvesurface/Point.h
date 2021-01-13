#pragma once
#ifndef XT_POINT_H
#define XT_POINT_H

/**
* \file Point.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for point.
*
* \description
*	Designed for point(x,y) with weight and flag.
*/

#include <string>
#include <sstream>

#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <boost/smart_ptr.hpp>
#include "XTConfig.h"

#include "Util.h"
#include "PBUtil.h"

#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "safe_ptr.h"

namespace XT {

	class Point;
	//////typedef for Point
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<Point> PointPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<Point> PointPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<Point> PointPtr;

#else

	typedef ::boost::shared_ptr<Point> PointPtr;
#endif


	typedef ::sf::safe_ptr<Point> PointSafePtr;

	typedef sf::contfree_safe_ptr<Point> PointContFreePtr;
	//////end typedef for Point

	class PointMap;
	//////typedef for PointMap
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<PointMap> PointMapPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<PointMap> PointMapPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<PointMap> PointMapPtr;

#else

	typedef ::boost::shared_ptr<PointMap> PointMapPtr;
#endif


	typedef ::sf::safe_ptr<PointMap> PointMapSafePtr;

	typedef sf::contfree_safe_ptr<PointMap> PointMapContFreePtr;
	//////end typedef for PointMap

	class PointMapList;

	//////typedef for PointMapList
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<PointMapList> PointMapListPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<PointMapList> PointMapListPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<PointMapList> PointMapListPtr;

#else

	typedef ::boost::shared_ptr<PointMapList> PointMapListPtr;
#endif


	typedef ::sf::safe_ptr<PointMapList> PointMapListSafePtr;

	typedef sf::contfree_safe_ptr<PointMapList> PointMapListContFreePtr;
	//////end typedef for PointMapList

	class PointList;
	//////typedef for PointList
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<PointList> PointListPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<PointList> PointListPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<PointList> PointListPtr;

#else

	typedef ::boost::shared_ptr<PointList> PointListPtr;
#endif


	typedef ::sf::safe_ptr<PointList> PointListSafePtr;

	typedef sf::contfree_safe_ptr<PointList> PointListContFreePtr;
	//////end typedef for PointList

class XT_COMMON_API Point
{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	Point();

	/**
	*  @brief constructor with parameters
	*
	* @param in_x as x value
	* @param in_y as y value
	* @param in_z as z value
	* @param in_v as value
	* @param in_w as weight value
	* @param flag as integer flag
	* @param ts as timestamp
	*/
	Point(double in_x, double in_y, double in_z, double in_v, double in_w, int in_flag, int64_t in_ts);

	/**
	* @brief default copy constructor
	*/
	Point(const Point& from) = default;

	/**
	* @brief default copy assignment
	*/
	Point& operator=(const Point& from) = default;

	/**
	* @brief destructor
	*/
	virtual ~Point();
	///@}

	/**
	* @name data
	*/
	///@{

	/**
	* @brief pointdata
	*
	* @return   pointdata
	*/
	PointDataPtr& data();
	
	///@}

	/**
	* @name static functions
	*/
	///@{

	/**
	* @brief create
	*
	* @return   point
	*/
	static PointPtr create();

	///@}

protected:
	PointDataPtr m_data;

};//class XT_COMMON_API Point



class XT_COMMON_API PointComparator
{
public:
	/**
	* @brief operator() for function object
	*
	* @param p1 as point1
	* @param p2 as pont2
	*
	* @return if p1 is less than p2
	*/
	bool operator() (const PointPtr & p1, const PointPtr & p2);
};

class XT_COMMON_API PointMap
{
public:
	/** @name Constructor
	*
	*/
	///@{
	/**
	* @brief constructor
	*/
	PointMap();

	/**
	* @brief default copy constructor
	*/
	PointMap(const PointMap& from) = default;

	/**
	* @brief default copy assignment
	*/
	PointMap& operator=(const PointMap& from) = default;

	/**
	* @brief destructor
	*/
	virtual ~PointMap() {};

	///@}

	/**
	* @name data
	*/
	///@{

	/**
	* @brief pointdatamap
	*
	* @return   pointdatamap
	*/
	PointDataMapPtr& data();

	/**
	* @brief get timestamp
	*
	* @return timestamp
	*/
	int64_t getTs();

	/**
	* @brief has tag double
	*
	* @param tag
	*
	* @return if tag exists
	*/
	bool hasTagPoint(int64_t tag);

	/**
	* @brief has tag double
	*
	* @param tag
	*
	* @return if tag exists
	*/
	bool hasTagDouble(int tag);

	/**
	* @brief get tag double
	*
	* @param tag
	*
	* @return double
	*/
	double getTagDouble(int tag);

	/**
	* @brief get tag vector
	*
	* @return tag vector
	*/
	std::vector<int64_t> getTagVector();

	/**
	* @brief get x
	*
	* @return x
	*/
	double getX(int64_t tag);

	/**
	* @brief get x vector
	*
	* @return x vector
	*/
	std::vector<double> getXVector();

	/**
	* @brief get y
	*
	* @return y
	*/
	double getY(int64_t tag);

	/**
	* @brief get y vector
	*
	* @return y vector
	*/
	std::vector<double> getYVector();

	/**
	* @brief get z
	*
	* @return z
	*/
	double getZ(int64_t tag);

	/**
	* @brief get z vector
	*
	* @return z vector
	*/
	std::vector<double> getZVector();

	/**
	* @brief get v
	*
	* @return v
	*/
	double getV(int64_t tag);

	/**
	* @brief get v vector
	*
	* @return v vector
	*/
	std::vector<double> getVVector();

	/**
	* @brief get w
	*
	* @return w
	*/
	double getW(int64_t tag);

	/**
	* @brief get w vector
	*
	* @return w vector
	*/
	std::vector<double> getWVector();

	/**
	* @brief get flag
	*
	* @return flag
	*/
	int getFlag(int64_t tag);

	/**
	* @brief get flag vector
	*
	* @return flag vector
	*/
	std::vector<int> getFlagVector();

	///@}

	/** @name Updating Functions
	*
	*/
	///@{
	/**
	* @brief set a point
	*
	* @param tag as integer index
	* @param x as double
	* @param y as double
	* @param z as double
	* @param v as double
	* @param w as weight
	* @param flag as integer
	* @param ts ad timestamp
	*/
	void setPoint(int64_t tag, double x, double y, double z, double v, double w, int flag, int64_t ts);

//	void setPointByRawPtr(PointDataMap* rawp, int64_t tag, double x, double y, double z, double v, double w, int flag, int64_t ts);

	///@{
	/**
	* @brief remove a point
	*
	* @param tag as integer index
	*/
	void removePoint(int64_t tag);

	
	/**
	* @brief update timestamp for a point
	*
	* @param ts as timestamp
	*/
	void setTs(int64_t ts);

	/**
	* @brief set tag double 
	*
	* @param tag
	* @param v
	*/
	void setTagDouble(int tag, double v);

	/**
	* @brief update x for a point
	*
	* @param tag as integer index
	* @param x as double
	*/
	void setX(int64_t tag, double x);

	/**
	* @brief set y for a point
	*
	* @param tag as integer index
	* @param y as double
	*/
	void setY(int64_t tag, double y);

	/**
	* @brief set z for a point
	*
	* @param tag as integer index
	* @param z as double
	*/
	void setZ(int64_t tag, double z);

	/**
	* @brief set v for a point
	*
	* @param tag as integer index
	* @param v as double
	*/
	void setV(int64_t tag, double v);

	/**
	* @brief set w for a point
	*
	* @param tag as integer index
	* @param w as weight
	*/
	void setW(int64_t tag, double w);

	/**
	* @brief set flag for a point
	*
	* @param tag as integer index
	* @param flag as integer
	*/
	void setFlag(int64_t tag, int flag);

	///@}

	/** @name String Functions
	*
	*/
	///@{
	/**
	* @brief string function
	*
	* @return string
	*/
	std::string str();

	std::string getStr(int flag);

	bool updateFromStr(const std::string& s, int flag);

	///@}


	/**
	* @name static functions
	*/
	///@{

	/**
	* @brief create
	*
	* @return pointmap
	*/
	static PointMapPtr create();

	///@}

protected:
//	void generateDataVectors();

	void updateDataVectorsByRawPtr(PointDataMap* rawp);

protected:
	PointDataMapPtr m_data;

	//std::map<int, int> m_tagToIdxMap;

	//std::vector<int> m_tags;
	//
	//std::vector<double> m_xs;
	//std::vector<double> m_ys;
	//std::vector<double> m_zs;
	//std::vector<double> m_vs;
	//std::vector<double> m_ws;

	//std::vector<int> m_flags;
	 

};





////
class XT_COMMON_API PointMapList {
public:
	/**
	* @name Constructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	PointMapList();

	/**
	* @brief default copy constructor
	*/
	PointMapList(const PointMapList& from) = default;

	/**
	* @brief default copy assignment
	*/
	PointMapList& operator=(const PointMapList& from) = default;

	/**
	* @brief destructor
	*/
	virtual ~PointMapList();

	///@}


	/**
	* @brief get point list
	*
	* @return point list
	*/
	std::list< PointMapPtr >& pointMapList();

	/**
	* @brief add pointmap
	*
	* @param pointmap
	*/
	void addPointMap(const PointMapPtr& pm);


	/**
	* @name static functions
	*/
	///@{

	/**
	* @brief create
	*
	* @return pointlist
	*/
	static PointMapListPtr create();

	///@}

protected:
	std::list< PointMapPtr > m_dataMapList;

	RollingType::enumtype m_rollingType; ///< rolling type

	int m_span; ///< span

};




////

class XT_COMMON_API PointList {
public:
	/**
	* @name Constructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	PointList();

	/**
	* @brief default copy constructor
	*/
	PointList(const PointList& from) = default;

	/**
	* @brief default copy assignment
	*/
	PointList& operator=(const PointList& from) = default;

	/**
	* @brief destructor
	*/
	virtual ~PointList();

	///@}

	/**
	* @brief add point data
	*
	* @param x as double
	* @param y as double
	* @param z as double
	* @param v as double
	* @param w as weight
	* @param flag as integer
	* @param ts ad timestamp
	*/
	void addData(double x, double y, double z, double v, double w, int flag, int64_t ts);

	/**
	* @brief add point  
	*
	* @param point
	*/
	void addPoint(PointPtr p);

	/**
	* @brief get point list
	*
	* @return point list
	*/
	std::list< PointPtr >& pointList();


	/**
	* @name static functions
	*/
	///@{

	/**
	* @brief create
	*
	* @return pointlist
	*/
	static PointListPtr create();

	///@}

protected:
	std::list< PointPtr > m_dataList;

	RollingType::enumtype m_rollingType; ///< rolling type
	 
	int m_span; ///< span


};//class XT_COMMON_API PointList





//////////////////////////
//class XT_COMMON_API PointXY {
//public:
//
//	/** 
//	* @name Constructor
//	*/
//	///@{
//
//	/**
//	* @brief constructor
//	*/
//	PointXY();
//
//	/**
//	*  @brief constructor with parameters
//	*
//	* @param in_x as x value
//	* @param in_y as y value
//	* @param in_w as weight value
//	* @param flag as integer flag
//	*/
//	PointXY(double in_x,double in_y,double in_w,int in_flag);
//	///@}
//
//	/** 
//	* @name Setters and Getters
//	*/
//	///@{
//
//	/**
//	* @brief get x
//	*
//	* @return x value
//	*/
//	double getX();
//
//	/**
//	* @brief set x
//	*
//	* @param v as x value
//	*/
//	void setX(double v);
//
//	/**
//	* @brief get y
//	*
//	* @return y value
//	*/
//	double getY();
//
//	/**
//	* @brief set y
//	*
//	* @param v as y value
//	*/
//	void setY(double v);
//
//	/**
//	* @brief get yhat
//	*
//	* @return estimated value
//	*/
//	double getYhat();
//
//	/**
//	* @brief set yhat
//	* 
//	* @param v as y esitimated value
//	*/
//	void setYhat(double v);
//
//	/**
//	* @brief get weight
//	*
//	* @return weight value
//	*/
//	double getWeight();
//
//	/**
//	* @brief set weight
//	*
//	* @param v as weight value
//	*/
//	void setWeight(double v);
//
//	/**
//	* @brief get flag
//	*
//	* @return flag value
//	*/
//	int getFlag();
//
//	/**
//	* @brief set flag
//	*
//	* @param v as flag value
//	*/
//	void setFlag(int v);
//
//	///@}
//
//
//	/** @name Factory
//	*
//	*/
//	///@{
//	/**
//	* @brief factory function of PointXY
//	* @param x 
//	* @param y
//	* @param w as weight
//	* @pram flag as integer
//	*/
//	static boost::shared_ptr<PointXY>  create(double x, double y, double w, int flag);
//	///@}
//
//
//	/** @name String Function
//	*
//	*/
//	///@{
//	/**
//	* @brief string function
//	*
//	* @return string
//	*/
//	std::string str();
//	///@}
//
//protected:
//	double m_x; ///< x of a point
//	double m_y; ///< y of a point
//	double m_yh; ///< y hat(estimation) of a point
//	double m_w; ///< weight of a point
//	int m_flag; ///< flag of a point
//
//}; //end struct PointXY
//typedef ::boost::shared_ptr<PointXY> PointXYPtr;
//
//class XT_COMMON_API PointXYComparator {
//public:
//	/**
//	* @brief operator() for function object
//	* 
//	* @param p1 as point1
//	* @param p2 as pont2
//	*
//	* @return if p1 is less than p2
//	*/
//	bool operator() (const boost::shared_ptr<PointXY> & p1, const boost::shared_ptr<PointXY> & p2);
//};
//
//class XT_COMMON_API PointXYMap {
//public:
//
//	/** @name Constructor
//	*
//	*/
//	///@{
//	/**
//	* @brief constructor
//	*/
//	PointXYMap();
//
//	///@}
//
//	/** @name Updating Functions
//	*
//	*/
//	///@{
//	/**
//	* @brief update a point
//	*
//	* @param tag as integer index
//	* @param p as other point
//	*/
//	void updatePoint(int tag,const boost::shared_ptr<PointXY>& p);
//
//	/**
//	* @brief update a point by providing values of x,y,yh,w and flag
//	*
//	* @param tag as integer
//	* @param x as double
//	* @param y as double
//	* @param w as weight
//	* @param flag as integer
//	**/
//	void updateXY(int tag, double x, double y, double yh, double w, int flag);
//
//	///@}
//
//	/** @name Getters
//	*
//	*/
//	///@{
//	/**
//	* @brief get a point by tag
//	*
//	* @param tag as integer index
//	*
//	* @return point for tag
//	*/
//	boost::shared_ptr<PointXY>& pointByTag(int tag);
//
//	/**
//	* @brief get points map
//	*
//	* @return reference to points map
//	*/
//	std::map<int,boost::shared_ptr<PointXY> >& pointsMap();
//
//	///@}
//
//	/** @name String Functions
//	*
//	*/
//	///@{
//	/**
//	* @brief string function
//	*
//	* @return string
//	*/
//	std::string str();
//
//	///@}
//
//	/** @name Factory
//	*
//	*/
//	///@{
//
//	/**
//	* @brief factory function
//	*
//	* @return points map
//	*/
//	static boost::shared_ptr<PointXYMap> create() ;
//	///@}
//
//
//protected:
//	std::map<int,boost::shared_ptr<PointXY> > m_points; ///< map of points, key is tag, value is point
//
//}; 

}//end namespace XT
#endif
