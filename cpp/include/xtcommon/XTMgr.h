#pragma once
#ifndef XT_XTMGR_H
#define XT_XTMGR_H

/**
* \file XTMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a manager class for all global management.
*
* \description
*	Designed for managing all globals.
*/

#include <cstdint>
#include <vector>
#include <map>
#include <set>
 
#include <boost/unordered_map.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/unordered_set.hpp>
 

#include "XTConfig.h"
#include "LogUtil.h"
 

#include "SQLiteMgr.h"

//#include <CurlUtil.h>
#include <HttpUtil.h>

#include <bson.h>
#include <bcon.h>
#include <mongoc.h>
#include "MongoDBMgr.h"

#include <google/protobuf/stubs/common.h>

#include <ZMQMgr.h>

#include "InstrMgr.h"

#include "XTApiMgr.h"
#include "StratMgr.h"
namespace XT
{

class XT_COMMON_API XTMgr
{
 
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	XTMgr();

	/**
	* @brief default copy constructor
	*/
	XTMgr(const XTMgr& from) {} // = delete;

	/**
	* @brief default copy assignment
	*/
	XTMgr& operator=(const XTMgr& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~XTMgr();

	///@}
public:
	/**
	* @brief get singleton instance
	*
	* @return singleton instance
	*/
	static XTMgr* getInstance();
public:
	/**
	* @brief initialization
	*
	* @param intdate as int date
	* @param cfgfile as cfg file, default is cfg.json
	* @param profile as property file, defatul is cfg.ini
	*/
	void init(int intdate  , const std::string& cfgfile  , const std::string& propfile  );
 
	/**
	* @brief release all resources
	*/
	void release();

protected:
	std::string m_baseDir; ///< base directory
public:
	/**
	* @brief get base directory
	*
	* @return base directory
	*/
	std::string getBaseDir();

	/**
	* @brief set base directory
	*
	* @param s as base directory
	*/
	void setBaseDir(const std::string& s);


};//class

}//namespace

#endif
