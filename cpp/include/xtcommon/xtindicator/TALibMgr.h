#pragma once
#ifndef XT_TALIBMGR_H
#define XT_TALIBMGR_H

/**
* \file TALibMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide classes for TALibMgr.
*
* \description
*	Designed for mangaing  TALibMgr.
*/

#include <cstdint>
#include <set>
#include <vector>
#include <map>

#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/smart_ptr.hpp>

#include "XTConfig.h"
#include "LogUtil.h"
#include "StringMap.h"
#include "TagDataWrapper.h"
#include "ta_libc.h"
#include "TALibFuncInfo.h"

namespace XT
{

class XT_COMMON_API TALibMgr {
public:
	/**
	* @name constructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	TALibMgr();

	/**
	* @brief default copy constructor
	*/
	TALibMgr(const TALibMgr& from) {}// = delete;

	/**
	* @brief default copy assignment
	*/
	TALibMgr& operator=(const TALibMgr& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~TALibMgr();

	///@}
public:

	/**
	* @brief get singleton instance
	*
	* @return singleton instance
	*/
	static TALibMgr* getInstance();

public:
	/**
	* @brief get talib version
	*
	* @return version string
	*/
	std::string getTALibVersionStr();

	/**
	* @brief get tablib groups
	*
	* @return vector of talib group names
	*/
	std::vector<std::string> getTALibGroups();

	/**
	* @brief get talib function names for group
	*
	* @param group
	*
	* @return vector of function names
	*/
	std::vector<std::string> getTALibFunctionsForGroup(const std::string& group);

	/**
	* @brief get talib default parameters
	*
	* @name as function name
	*
	* @return StringMapPtr as parameters
	*/
	StringMapPtr getTALibDefaultParameters(const std::string& name);

	/**
	* @brief get talib function information as json string
	*
	* @name as function name
	* 
	* @return json string for function information
	*/
	std::string getTALibFuncInfoJsonStr(const std::string& name);

	/**
	* @brief get TALibFuncInfo for function name
	*
	* @name as function name
	*
	* @return TALibFuncInfo pointer
	*/
	TALibFuncInfoPtr getTALibFuncInfo(const std::string& name);

};//class XT_COMMON_API TALibMgr

}//namespace XT

#endif