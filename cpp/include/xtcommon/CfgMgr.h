#pragma once
#ifndef XT_CFG_MGR_H
#define XT_CFG_MGR_H

/**
* \file CfgMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for managing all config data.
*
* \description
*	Designed for managing all config data.
*/

#include <cstdint>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/unordered_set.hpp>
#include <boost/signals2.hpp>



#define BOOST_SYSTEM_NO_LIB
#define BOOST_FILESYSTEM_NO_LIB
#include <boost/filesystem.hpp>

#include "XTConfig.h"

#include "LogUtil.h"

#include "FIXEnum.pb.h"
#include "FIXData.pb.h"
#include "typedef_FIXData.pb.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "TagDataWrapper.h"

#include "Util.h"
#include "StringMap.h"
#include "XTSimpleIni.h"



namespace XT
{

class XT_COMMON_API CfgMgr {
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	CfgMgr();

	/**
	* @brief copy constructor
	*/
	CfgMgr(const CfgMgr& from) {} // = delete;

	/**
	* @brief copy assignment
	*/
	CfgMgr& operator=(const CfgMgr& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~CfgMgr();

	///@}
public:
 

	/**
	* @brief get singleton instance
	*
	* @return singleton instance
	*/
	static CfgMgr* getInstance();

////

	/**
	* @brief load ini file
	*
	* @param inifile as input file name
	*/
	void loadCfgIni(const std::string& inifile);

	/**
	* @brief access cfg ini data
	* 
	* @return cfgIniData
	*/
	XTSimpleIniPtr& cfgIniData();


	/**
	* @brief read ini file
	*
	* @return XTSimpleIniPtr
	*/
	XTSimpleIniPtr readIni(const std::string& inifile);

////

//	/**
//	* @brief global cfg data
//	*
//	* @return globalCfgData
//	*/
//	GlobalCfgDataPtr& globalCfgData();
//
///////////////
//	/**
//	* @brief strategy cfg data
//	*
//	* @return stratCfgData
//	*/
//	StratCfgDataPtr& stratCfgData();

	///**
	//* @brief get trading days between
	//*
	//* @param exchid
	//* @param productid
	//* @param tradingday
	//* @param expiredate
	//*/
	//int getTradingDaysBetween(const std::string& exchid, const std::string& productid, int tradingday, int expiredate);

protected:
	std::string m_iniFileName;
	XTSimpleIniPtr m_cfgIniData;

	std::string m_emptyString;

//	GlobalCfgDataPtr m_globalCfgData;

//	StratCfgDataPtr m_stratCfgData;



};//class

}//namespace

#endif