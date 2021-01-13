#pragma once
#ifndef STRATMGR_H
#define STRATMGR_H

/**
* \file StratMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a manager class for strategy.
*
* \description
*	Designed for managing all stategies.
*/


#include <cstdint>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
//#include <atomic>
#include <boost/unordered_map.hpp>
#include <boost/smart_ptr.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/unordered_set.hpp>
#include <boost/thread/thread.hpp>

#define BOOST_SYSTEM_NO_LIB
#define BOOST_FILESYSTEM_NO_LIB
#include <boost/filesystem.hpp>

#include "XTConfig.h"
//#include "LogUtil.h"
#include "LogUtil.h"

//#include "SettingsMgr.h"
#include "CfgMgr.h"

#include "XTData.pb.h"
#include "InstrSpec.h"
#include "Instr.h"
#include "InstrMgr.h"

#include "Util.h"
#include "SQLiteMgr.h"
#include "MongoDBMgr.h"
//#include "PgsqlUtil.h"
#include "OrderQuoteMgr.h"
#include "Strat.h"
 

#include "StringMap.h"

#include <boost/config.hpp>
#include <boost/dll/import.hpp>

#include "XTSingleton.h"

namespace XT
{




class XT_COMMON_API StratMgr  
{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	StratMgr();

	/**
	* @brief copy constructor
	*/
	StratMgr(const StratMgr& from) {} // = delete;

	/**
	* @brief copy assignment
	*/
	StratMgr& operator=(const StratMgr& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~StratMgr();

	///@}

public:
	/**
	* @brief get singleton instance
	*
	* @return singleton instance
	*/
	static StratMgr* getInstance();
 
public:
	/**
	* @brief initialization(load plugin files)
	*
	*/
	void init();
	
	/**
	* @brief start to create all strategies in settings
	*/
	void start();

	/**
	* @brief get plugin files
	*
	* @return vector of plugin files
	*/
	std::vector<std::string> getPluginFiles();

	/**
	* @brief load plugin from file
	*
	* @param pluginfile
	* 
	* @return StratPluginPtr
	*/
	StratPluginPtr loadPlugin(const std::string& pluginfile);

	/**
	* @brief load all plugin files
	*/
	void loadAllPlugins();

	/**
	* @brief get plugin names
	*
	* @return vector of plugin names
	*/
	std::vector<std::string> getPluginNames();

	/**
	* @brief get strategy names
	*
	* @return vector of strategy names
	*/
	std::vector<std::string> getStratNames();

	/**
	* @brief set trading status
	*
	* @param i as trading status
	*/
	void setTrdStatus(int i);

	/**
	* @brief update trading status from tagdata
	*
	* @param tdw as tagdatawrapper
	*/
	void updateTrdStatus(const TagDataWrapperPtr& tdw);

	/**
	* @brief has strategy name or not
	*
	* @param stratname as strategy name
	*
	* @return if strategy exists or not
	*/
	bool hasStrat(const std::string& stratname);

	StratPtr& getStratByName(const std::string& stratname);

	/**
	* @brief create strategy
	*
	* @param stratname as strategy name
	* @param pluginname as suggested plugin name, default is empty
	* 
	* @return StratPtr
	*/
	StratPtr createStrat(const std::string& stratname, const std::string& pluginname);

	/**
	* @brief add strategy
	*
	* @param strat as strategy
	*/
	void addStrat( StratPtr strat);

	/**
	* @brief add strategy by setting
	*
	* @param smp as StringMapPtr setting
	*/
	void addStratByName(const std::string& stratname);

	/**
	* @brief add strategy by setting
	*
	* @param smp as StringMapPtr setting
	*/
	void addStratBySetting(StringMapPtr smp);

	/**
	* @brief add default setting for strategy
	*
	* @param stratname as strategy name
	* @param pluginname as suggested plugin name, default is empty
	*/
	void addDefaultStratSetting(const std::string& stratname, const std::string& pluginname);

	/**
	* @brief get default setting for strategy
	*
	* @param stratname as strategy name
	*
	* @return StringMapPtr setting
	*/
	virtual StringMapPtr getDefaultStratSetting(const std::string& stratname, const std::string& pluginname);



protected:
//maps
	std::map<std::string,StratPtr > m_stratMap;///< strategy map 
	std::map<std::string, StratPluginPtr > m_stratPluginMap; ///< stratplugin map

	StratPtr m_emptyStrat;
	StratCfgDataPtr m_cfgData;

protected:
	boost::signals2::connection m_connectionOneSecondTimer; ///< one second timer connection
protected:
	/**
	* @brief on timer
	*/
	void onOneSecondTimer(int i);

	void processTimerTask();

protected:
	std::shared_ptr<ConcurrentQueue<int> > m_eventQueue; ///< event queue
	std::thread* m_taskThread;
	int m_taskFlag;

};//class

}//namespace 

#endif
