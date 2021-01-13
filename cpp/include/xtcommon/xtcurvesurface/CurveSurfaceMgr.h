#pragma once
#ifndef XT_CURVESURFACEMGR_H
#define XT_CURVESURFACEMGR_H

/**
* \file CurveSurfaceMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for managing all curves and surfaces.
*
* \description
*	Designed for managing all curves and surfaces.
*/

#include <cstdint>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

 

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>		 
#include <boost/bind.hpp>		 
#include <boost/any.hpp>
#include <boost/thread/shared_mutex.hpp>


#include "XTConfig.h"
#include "safe_ptr.h"

#include "log4z.h"


#include "TagDataWrapper.h"

#include "INIUtil.h"

#include "Util.h"
#include "StringUtil.h"
 
#include "Curve.h"
#include "DoubleWingCurve.h"
#include "FlatCurve.h"
#include "LineCurve.h"
#include "SwanCurve.h"
#include "TanhCurve.h"

namespace XT {

 

class XT_COMMON_API CurveSurfaceMgr 
{

public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	CurveSurfaceMgr();

	/**
	* @brief default copy constructor
	*/
	CurveSurfaceMgr(const CurveSurfaceMgr& from) {} //= delete;

	/**
	* @brief default copy assignment
	*/
	CurveSurfaceMgr& operator=(const CurveSurfaceMgr& from) { return *this; } //= delete;
	
	/**
	* @brief destructor
	*/
	virtual ~CurveSurfaceMgr();

	///@}

public:
	/**
	* @brief get singleton instance
	*
	* @return singleton raw pointer
	*/
	static CurveSurfaceMgr* getInstance();
 
public:

	/**
	* @brief create a curve
	*
	* @param curve type name
	*
	* @return curve
	*/
	CurvePtr createCurve(const std::string& curvetypename);

	/**
	* @brief has curve name
	*
	* @param curvename
	*
	* @return if curvename exists or not
	*/
	bool hasCurveName(const std::string& curvename);

	/**
	* @brief get curve by name
	*
	* @param name as curve name
	*
	* @return curve pointer
	*/
	CurvePtr& getCurveByName(const std::string& name);

	/**
	* @brief add curve
	*
	* @param c as curve
	*/
	void addCurve(CurvePtr& c);

	/**
	* @brief get all curve names
	*
	* @return all curve names vector
	*/
	std::vector<std::string> getAllCurveNames();

	/**
	* @brief get all curve names with prefixes
	*
	* @param prefixes
	*
	*@return curve names with prefixes
	*/
	std::vector<std::string> getCurveNamesByPrefix(const std::string& prefix);


protected:
	CurvePtr m_emptyCurve;///< null curve
	sf::contfree_safe_ptr<std::map<std::string, CurvePtr > > m_curveMap; ///< name to curve map


};//class CurveSurfaceMgr

}//namespace

#endif