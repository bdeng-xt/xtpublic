#pragma once
#ifndef XT_SETTINGSMGR_H
#define XT_SETTINGSMGR_H

/**
* \file SettingsMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for managing all settings.
*
* \description
*	Designed for specific information of an instrument.
*/

#include <cstdint>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

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
#include "XTEnum.pb.h"
#include "XTData.pb.h"

#include "TagDataWrapper.h"

#include "INIUtil.h"
#include "StringMap.h"
#include "Util.h"
#include "FileUtil.h"
#include "InstrSettingsMgr.h"
#include "ServerSettingsMgr.h"
//#include "SqliteUtil.h"
//#include "MongoUtil.h"

namespace XT {

 

class XT_COMMON_API SettingsMgr {

public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	SettingsMgr();

	/**
	* @brief default copy constructor
	*/
	SettingsMgr(const SettingsMgr& from) {} // = delete;

	/**
	* @brief default copy assignment
	*/
	SettingsMgr& operator=(const SettingsMgr& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~SettingsMgr();

	///@}
public:
	/**
	* @brief get singleton instance
	*
	* @return singleton instance
	*/
	static SettingsMgr* getInstance();

protected:
	StringMapPtr m_emptyStringMapPtr; ///< empty StringMapPtr

public:
	/**
	* @brief get empty StringMapPtr
	*
	* @return empty StringMapPtr
	*/
	const StringMapPtr& getEmptyStringMapPtr();

protected:
	int m_currIntDate; ///< current int date
	int m_timerCount; ///< timer count
	int m_timerSeconds; ///< timer seconds
public:
	/**
	* @brief get current int date
	*
	* @return current int date
	*/
	int getCurrIntDate();

	/**
	* @brief set current int date
	*
	* @param v as current int date
	*/
	void setCurrIntDate(int v);

	/**
	* @brief get timer count
	*
	* @return timer count
	*/
	int getTimerCount();

	/**
	* @brief set timer count
	*
	* @param v as timer count
	*/
	void setTimerCount(int v);

	/**
	* @brief increase timer count
	*/
	void increaseTimerCount();

	/**
	* @brief get timer seconds
	*
	* @return timer seconds
	*/
	int getTimerSeconds();

	/**
	* @brief set timer seconds
	*
	* @param v as timer seconds
	*/
	void setTimerSeconds(int v);


public:
	/**
	* @brief update base directory
	*
	* @param s as base directory
	*/
	void updateBaseDir(const std::string& s);

	/**
	* @brief get base directory
	*
	* @return base directory
	*/
	const std::string& getBaseDir();

	/**
	* @brief set library directory
	*
	* @param s as library directory
	*/
	void setLibDir(const std::string& s);

	/**
	* @brief get library directory
	*
	* @return library directory
	*/
	const std::string& getLibDir();

	/**
	* @brief set app directory
	*
	* @param s as app directory
	*/
	void setAppDir(const std::string& s);

	/**
	* @brief get app directory
	*
	* @return app directory
	*/
	const std::string& getAppDir();

	/**
	* @brief set data directory
	*
	* @param s as data directory
	*/
	void setDataDir(const std::string& s);

	/**
	* @brief get data directory
	*
	* @return data directory
	*/
	const std::string& getDataDir();

	/**
	* @brief get main database file
	*
	* @return main database file
	*/
	const std::string& getMainDbFile();

	/**
	* @brief get trade database file
	*
	* @return trade database file
	*/
	const std::string& getTrdDbFile();

protected:
	std::string m_baseDir; ///< base directory
	std::string m_libDir; ///< library directory
	std::string m_appDir; ///< app directory
	std::string m_dataDir; ///< data directory

	std::string m_mainDbFile; ///< main database file
	std::string m_trdDbFile; ///< trade database file

///flags
protected:
	int m_runningFlag; ///< current running flag

	int m_cfgLoadedFlag; ///< if config loaded
	int m_propLoadedFlag; ///< if prop loaded
	int m_positionLoadedFlag; ///< if position loaded

	int m_startTopicMgrFlag;///< if try to start TopicMgr

	int m_reqAllInstrsFlag; ///< if requesting all instruments or not, 0: not request; 1: request all
	int m_subAllInstrsMktDataFlag; ///< if subscribing all instruments market data or not, 0: not subscribing; 1: subscribing all
	int m_updateInstrFlag; ///< if update instr when for new maket data or order information
	int m_logMktDataFlag; ///< if logging mkt data or not, 0: not logging, 1: logging all mktdata
	int m_logOrderFlag; ///< if logging order related data or not, 0: not logging, 1: logging order data
	int m_logBarFlag; ///< if logging bar or not, 0: not logging, 1: loogin bar data
	int m_addInstrOnRspFlag; ///< is adding Instrument OnRspInstrument or not
	int m_saveBar60sToSqlFlag; ///< if saveBar60sToSql>0, save 1 minute bar to sql
	int m_addAllIndicatorFlag; ///< if adding all indicators or not, 0: not adding all, 1: adding all
	int m_saveBar60sToMongoFlag; ///< if saveBar60sToMongoFlag>0, save 1 minute bar to mongo

	int m_zmqInprocPubFlag; ///< if publish message in process or not
	int m_zmqPubFlag; ///< if publish message or not

//	std::string m_bar60sInstrIDs; ///<instrids for generate one-minute bars
	std::set<std::string> m_setBar60sInstrIDs; ///<instrids for generate one-minute bars
public:
	/**
	* @brief get running flag
	*
	* @return running flag
	*/
	int getRunningFlag();

	/**
	* @brief set running flag
	*
	* @param v as running flag
	*/
	void setRunningFlag(int v);

	/**
	* @brief get cfg loaded flag
	*
	* @return cfg loaded flag
	*/
	int getCfgLoadedFlag();

	/**
	* @brief set cfg loaded flag
	*
	* @param v as cfg loaded flag
	*/
	void setCfgLoadedFlag(int v);

	/**
	* @brief get prop loaded flag
	*
	* @return prop loaded flag
	*/
	int getPropLoadedFlag();

	/**
	* @brief set prop loaded flag
	*
	* @param v as prop loaded flag
	*/
	void setPropLoadedFlag(int v);

	/**
	* @brief get position loaded flag
	*
	* @return position loaded flag
	*/
	int getPositionLoadedFlag();

	/**
	* @brief set position loaded flag
	*
	* @param v as position loaded flag
	*/
	void setPositionLoadedFlag(int v);

	/**
	* @brief get start topic mgr flag
	*
	* @return start topic mgr flag
	*/
	int getStartTopicMgrFlag();

	/**
	* @brief set start topic mgr flag
	*
	* @param v as start topic mgr flag
	*/
	void setStartTopicMgrFlag(int v);

	/**
	* @brief get request all instrs flag
	*
	* @return request all instrs flag
	*/
	int getReqAllInstrsFlag();

	/**
	* @brief set request all instrs flag
	*
	* @param v as request all instrs flag
	*/
	void setReqAllInstrsFlag(int v);

	/**
	* @brief get subscribe market data for all instrs flag
	*
	* @return subscribe market data for all instrs flag
	*/
	int getSubAllInstrsMktDataFlag();

	/**
	* @brief set subscribe market data for all instrs flag
	*
	* @param v as subscribe market data for all instrs flag
	*/
	void setSubAllInstrsMktDataFlag(int v);

	/**
	* @brief get update instrs flag
	*
	* @return update instrs flag
	*/
	int getUpdateInstrFlag();

	/**
	* @brief set update instrs flag
	*
	* @param v as update instrs flag
	*/
	void setUpdateInstrFlag(int v);

	/**
	* @brief get log market data flag
	*
	* @return log market data flag
	*/
	int getLogMktDataFlag();

	/**
	* @brief set log market data flag
	*
	* @param v as log market data flag
	*/
	void setLogMktDataFlag(int v);

	/**
	* @brief get log orders flag
	*
	* @return log orders flag
	*/
	int getLogOrderFlag();

	/**
	* @brief set log orders flag
	*
	* @param v as log orders flag
	*/
	void setLogOrderFlag(int v);

	/**
	* @brief get log bar flag
	*
	* @return log bar flag
	*/
	int getLogBarFlag();

	/**
	* @brief set log bar flag
	*
	* @param v as log bar flag
	*/
	void setLogBarFlag(int v);

	/**
	* @brief get add instrs on response flag
	*
	* @return add instrs on response flag
	*/
	int getAddInstrOnRspFlag();

	/**
	* @brief set add instrs on response flag
	*
	* @param v as add instrs on response flag
	*/
	void setAddInstrOnRspFlag(int v);

	/**
	* @brief get save 60s bar to sql flag
	*
	* @return save 60s bar to sql flag
	*/
	int getSaveBar60sToSqlFlag();

	/**
	* @brief set save 60s bar to sql flag
	*
	* @param v as save 60s bar to sql flag
	*/
	void setSaveBar60sToSqlFlag(int v);

	/**
	* @brief get add all indicator flag
	*
	* @return add all indicator flag
	*/
	int getAddAllIndicatorFlag();

	/**
	* @brief set add all indicator flag
	*
	* @param v as add all indicator flag
	*/
	void setAddAllIndicatorFlag(int v);
 
	/**
	* @brief get save 60s bar to mongo flag
	*
	* @return save 60s bar to mongo flag
	*/
	int getSaveBar60sToMongoFlag();

	/**
	* @brief set save 60s bar to mongo flag
	*
	* @param v as save 60s bar to mongo flag
	*/
	void setSaveBar60sToMongoFlag(int v);

	/**
	* @brief get zmq inproc pub flag
	*
	* @return zmq inproc pub flag
	*/
	int getZMQInprocPubFlag(); 

	/**
	* @brief set zmq inproc pub flag
	*
	* @param v as zmq inproc pub flag
	*/
	void setZMQInprocPubFlag(int v);

	/**
	* @brief get zmq pub flag
	*
	* @return zmq pub flag
	*/
	int getZMQPubFlag(); 

	/**
	* @brief set zmq pub flag
	*
	* @param v as zmq pub flag
	*/
	void setZMQPubFlag(int v);

	/**
	* @brief get 60s bar instrids
	*
	* @return instrids separated by comma
	*/
	std::string getBar60sInstrIDsStr();

	/**
	* @brief add instrid for 60s bar
	*
	* @param v as instrid
	*/
	void addBar60sInstrIDsStr(const std::string& v);

	/**
	* @brief instrids for 60 seconds bar
	*
	* @return vector of instrids
	*/
	std::vector<std::string> getBar60sInstrIDs();
//	std::vector<std::string> getBar60sInstrIDs();

///////////////////////////////////////////////////////////////
//cfg file

	/**
	* @name cfg 
	*/
	///@{
protected:
	std::string m_cfgRoot; ///< config root name
	std::string m_cfgFileName; ///< config file name
	TagDataWrapperPtr m_cfgData; ///< cfg data

	std::string m_propFileName; ///< ini file name
	XTINIReaderPtr m_propData;///< property data reader

public:

	/**
	* @brief get cfg root
	*
	* @return cfg root
	*/
	const std::string& getCfgRoot();

	/**
	* @brief set cfg root
	*
	* @param v as cfg root
	*/
	void setCfgRoot(const std::string& v);


	/**
	* @brief get cfg file name
	*
	* @return cfg file name
	*/
	const std::string& getCfgFileName();

	/**
	* @brief set cfg file name
	*
	* @param v as cfg file name
	*/
	void setCfgFileName(const std::string & v);

	/**
	* @brief get cfgdata
	*
	* @return cfgdata
	*/
	TagDataWrapperPtr& cfgData();

	/**
	* @brief set cfgdata
	*
	* @param v as cfgdata
	*/
	void setCfgData(TagDataWrapperPtr& v);

	/**
	* @brief get prop file name
	*
	* @return prop file name
	*/
	const std::string& getPropFileName();

	/**
	* @brief set prop file name
	*
	* @param v as prop file name
	*/
	void setPropFileName(const std::string & v);

	/**
	* @brief get propdata
	*
	* @return propdata
	*/
	XTINIReaderPtr& propData();

	/**
	* @brief get default cfg
	*
	* @return default cfg
	*/
	TagDataWrapperPtr getDefaultCfg();

	/**
	* @brief add default to cfg
	*/
	void addDefaultToCfg();

	/**
	* @brief load cfg
	* 
	* @param cfgFile
	*/
	void loadCfg(const std::string& cfgFile);

	/**
	* @brief save cfg to cfgFileName
	*/
	void saveCfg();

	/**
	* @brief create a default template cfg file
	*/
	void createDefaultCfgFile();

	/**
	* @brief load property file
	*
	* @param propFile 
	*/
	void loadProp(const std::string& propFile);

	/**
	* @brief get strat names (section name starts with strat_)  from prop
	*
	* @return vector of strategy names
	*/
	std::vector<std::string> getStratNamesInProp();


	/**
	* @brief get instrids (seciton name starts with instr_) in prop
	*
	* @return vector of instrids
	*/
	std::vector<std::string> getInstrIDsInProp();

	/**
	* @brief get instrcombo names(section name starts with combo_) in prop
	*
	* @return vector of instrcombo names
	*/
	std::vector<std::string> getInstrComboNamesInProp();

	/**
	* @brief get 60s bar instrids in prop
	*
	* @return vector of instrids
	*/
	std::vector<std::string> getBar60sInstrIDsInProp();
	
	/**
	* @brief get string map for a section
	*
	* @param sectionname as string
	*
	* @return string map for the secion
	*/
	StringMapPtr getStringMapPtrForSectioninProp(const std::string& sectiionname);


protected:
	/**
	* @brief update flags from cfg
	*/
	void updateFlagsFromCfg();

	/**
	* @brief update bar60sinstrids from prop
	*/
	void updateInstrIDsFromProp();

///cfg parameter path
protected:
 
 

	std::string m_AccountCNFuturesPath;///< cn futures account path
	std::string m_AccountCNStocksPath; ///< cn stocks account path
	std::string m_AccountUSPath; ///< us account path

	std::string m_CNFuturesMdSettingName; ///< cn futures market data setting name
	std::string m_CNFuturesTrdSettingName; ///< cn futures trade setting name

	std::string m_CNStocksMdSettingName; ///< cn stocks market data setting name
	std::string m_CNStocksTrdSettingName; ///< cn stocks trade setting name

	std::string m_USMdSettingName; ///< us account market data setting name
	std::string m_USTrdSettingName; ///< us account trade setting name
public:
 
 
	/**
	* @brief get cn futures account path
	*
	* @return cn futures account path
	*/
	const std::string& getAccountCNFuturesPath();

	/**
	* @brief set cn futures account path
	*
	* @param v as cn futures account path
	*/
	void setAccountCNFuturesPath(const std::string& v);

	/**
	* @brief get cn stocks account path
	*
	* @return cn stocks account path
	*/
	const std::string& getAccountCNStocksPath();

	/**
	* @brief set cn stocks account path
	*
	* @param v as cn stocks account path
	*/
	void setAccountCNStocksPath(const std::string& v);

	/**
	* @brief get us account path
	*
	* @return us account path
	*/
	const std::string& getAccountUSPath();

	/**
	* @brief get us account path
	*
	* @param v as us account path
	*/
	void setAccountUSPath(const std::string& v);

	/**
	* @brief get cn futures market data setting name
	*
	* @return cn futures market data setting name
	*/
	const std::string& getCNFuturesMdSettingName();

	/**
	* @brief set cn futures setting name
	*
	* @param v as cn futures setting name
	*/
	void setCNFuturesMdSettingName(const std::string& v);

	/**
	* @brief get cn futures trade setting name
	*
	* @return cn futures trade setting name
	*/
	const std::string& getCNFuturesTrdSettingName();

	/**
	* @brief set cn futures trade setting name
	*
	* @param v as cn futures trade setting name
	*/
	void setCNFuturesTrdSettingName(const std::string& v);

	/**
	* @brief get cn stocks market data setting name
	*
	* @return cn stocks market data setting name
	*/
	const std::string& getCNStocksMdSettingName();

	/**
	* @brief set cn stocks market data setting name
	*
	* @param v as cn stocks market data setting name
	*/
	void setCNStocksMdSettingName(const std::string& v);

	/**
	* @brief get cn stocks trade setting name
	*
	* @return cn stocks trade setting name
	*/
	const std::string& getCNStocksTrdSettingName();

	/**
	* @brief set cn stocks trade setting name
	*
	* @param v as cn stocks trade setting name
	*/
	void setCNStocksTrdSettingName(const std::string& v);

	/**
	* @brief get us market data setting name
	*
	* @return  us market data setting name
	*/
	const std::string& getUSMdSettingName();

	/**
	* @brief set us market data setting name
	*
	* @param v as us market data setting name
	*/
	void setUSMdSettingName(const std::string& v);
	
	/**
	* @brief get us trade setting name
	*
	* @return  us trade setting name
	*/
	const std::string& getUSTrdSettingName();

	/**
	* @brief set us trade setting name
	*
	* @param v as us trade setting name
	*/
	void setUSTrdSettingName(const std::string& v);

//
  

	/**
	* @brief get instrid in cfg file
	*
	* @return vector of instrids
	*/
	std::vector<std::string> getInstrIDsInCfg();

	/**
	* @brief get trading instrid in cfg file
	//*/
	//std::vector<std::string> getTradingInstrIDsInCfg();



	//////////////////////////////


	///@}
   //end of cfg and prop

	/**
	* @name prop
	*/
	///@{



	///@}

protected:


	boost::unordered_map<int, BrokerApiType::enumtype> m_exchangeToMdApiTypeMap; ///< exchange to market data api map
	boost::unordered_map<int, BrokerApiType::enumtype> m_exchangeToTrdApiTypeMap; ///< exchange to trade api map
	
	BrokerApiType::enumtype m_MdApiTypeForCNFutureExchanges; ///< market data api for cn future exchanges
	BrokerApiType::enumtype m_MdApiTypeForCNStockExchanges; ///< market data api for cn stock exchanges

	BrokerApiType::enumtype m_TrdApiTypeForCNFutureExchanges; ///< trade api for cn future exchanges
	BrokerApiType::enumtype m_TrdApiTypeForCNStockExchanges; ///< trade api for cn stock exchanges

	boost::unordered_map<int, int> m_apiToAccountTypeMaskMap; ///< api to account mask map

	

protected:
	/**
	* @brief initialize api to account mask map
	*/
	void initApiToAccountTypeMaskMap();
public:

	/**
	* @brief set all api types to SIM
	*
	*/
	void setAllApiTypesToSIM();

	/**
	* @brief get account type for api
	*
	* @apitype api type value
	*
	* @return account type mask
	*/
	int getAccountTypeMaskForApi(int apitype);

	/**
	* @brief excahnge to market data api type map
	*
	* @return exchange to market data api type map
	*/
	boost::unordered_map<int, BrokerApiType::enumtype>& exchangeToMdApiTypeMap();

	/**
	* @brief excahnge to trade api type map
	*
	* @return exchange to trade api type map
	*/
	boost::unordered_map<int, BrokerApiType::enumtype>& exchangeToTrdApiTypeMap();

	/**
	* @brief update api types for cn future exchanges
	*/
	void updateApiTypesForCNFutureExchanges();

	/**
	* @brief update api types for cn stock exchanges
	*/
	void updateApiTypesForCNStockExchanges();

	/**
	* @brief update api types for us exchanges
	*/
	void updateApiTypesForUSExchanges();

	/**
	* @brief update api types for all exchanges
	*/
	void updateApiTypesForExchanges();

	/**
	* @brief set market data api types for exchange id
	* 
	* @param exchid as exchange id
	* @param api as api type
	*/
	void setMdApiTypeForExchID(const std::string& exchid, BrokerApiType::enumtype api);

	/**
	* @brief set market data api types for exchange type
	*
	* @param exchType as exchange type
	* @param api as api type
	*/
	void setMdApiTypeForExchangeType(ExchangeType::enumtype exchType, BrokerApiType::enumtype api);

	/**
	* @brief set market data api types for cn future exchanges
	*
	* @param api as api type
	*/
	void setMdApiTypeForCNFutureExchanges(BrokerApiType::enumtype api);

	/**
	* @brief set market data api types for cn stock exchanges
	*
	* @param api as api type
	*/
	void setMdApiTypeForCNStockExchanges(BrokerApiType::enumtype api);

	/**
	* @brief get market data api types for cn future exchanges
	*
	* @return api type
	*/
	BrokerApiType::enumtype getMdApiTypeForCNFutureExchanges( );

	/**
	* @brief get market data api types for cn stock exchanges
	*
	* @return api type
	*/
	BrokerApiType::enumtype getMdApiTypeForCNStockExchanges( );

	/**
	* @brief get market data api types for exchid
	*
	* @param exchid as exchange id
	*
	* @return api type
	*/
	BrokerApiType::enumtype getMdApiTypeForExchID(const std::string& exchid);

	/**
	* @brief get market data api types for exchangetype
	*
	* @param exchid as exchangetype
	*
	* @return api type
	*/
	BrokerApiType::enumtype getMdApiTypeForExchangeType(ExchangeType::enumtype exchType);

	/**
	* @brief set trade api type for exchid
	*
	* @param exchid as exchange id
	* @param api as api type
	*/
	void setTrdApiTypeForExchID(const std::string& exchid, BrokerApiType::enumtype api);

	/**
	* @brief set trade api type for exchangetype
	*
	* @param exchType as exchange type
	* @param api as api type
	*/
	void setTrdApiTypeForExchangeType(ExchangeType::enumtype exchType, BrokerApiType::enumtype api);

	/**
	* @brief set trade api type for cn future exchanges
	*
	* @param api as api type
	*/
	void setTrdApiTypeForCNFutureExchanges(BrokerApiType::enumtype api);

	/**
	* @brief set trade api type for cn stock exchanges
	*
	* @param api as api type
	*/
	void setTrdApiTypeForCNStockExchanges(BrokerApiType::enumtype api);

	/**
	* @brief get trade api type for cn future exchanges
	*
	* @return api type
	*/
	BrokerApiType::enumtype getTrdApiTypeForCNFutureExchanges( );

	/**
	* @brief get trade api type for cn stock exchanges
	*
	* @return api type
	*/
	BrokerApiType::enumtype getTrdApiTypeForCNStockExchanges( );

	/**
	* @brief get trade api type for exchid
	*
	* @param exchid as exchid
	* 
	* @return api type
	*/
	BrokerApiType::enumtype getTrdApiTypeForExchID(const std::string& exchid);

	/**
	* @brief get trade api type for exchangetype
	*
	* @param exchType as exchange type
	*
	* @return api type
	*/
	BrokerApiType::enumtype getTrdApiTypeForExchangeType(ExchangeType::enumtype exchType);
	
	/**
	* @brief get market data api types in cfg
	*
	* @return vector of market data api types
	*/
	std::vector<std::string> getMdApiTypeNamesInCfg();

	/**
	* @brief get market data api names in cfg
	*
	* @return vector of market data api names
	*/
	std::vector<std::string> getTrdApiTypeNamesInCfg();



/////
protected:
	std::set<std::string> m_mktDataInstrIDSet; ///< set for instruments to subscribe market data

	std::unordered_set<int> m_iidSetToPublishInprocMktData; ///< set for instrument iid to publish inproc message

public:
	/**
	* @brief get market data instrid set
	*
	* @return market data instrid set
	*/
	std::set<std::string>& mktDataInstrIDSet();

	/**
	* @brief add InstrID for market data
	*
	* @param instrid as instrid
	*/
	void addInstrForMktData(const std::string& instrid);

	/**
	* @brief remove InstrID for market data
	*
	* @param instrid as instrid
	*/
	void removeInstrForMktData(const std::string& instrid);

////////////////// 
	/**
	* @brief get instrids for market data
	*
	* @return vector of instrids
	*/
	std::vector<std::string> getInstrIDsForMktData();

	/**
	* @name ZMQ publish
	*/
	///@{

	/**
	* @brief add iid for public inproc market data
	*
	* @param iid as integer id
	*/
	void addIidToPublishInprocMktData(int iid);

	/**
	* @brief remove iid for public inproc market data
	*
	* @param iid as integer id
	*/
	void removeIidToPublishInprocMktData(int iid);

	/**
	* @brief if it has iid for public inproc market data
	*
	* @param iid as integer id
	*
	* @return if it has iid
	*/
	bool hasIidToPublishInprocMktData(int iid);

	///@}
//////////////////////////////////
//ctrl file

	/**
	* @name Ctrl file
	*/
	///@{
protected:
	std::string m_ctrlFileName; ///< control file name
	std::string m_ctrlRoot; ///< control root prefix
	TagDataWrapperPtr m_ctrlData; ///< control data
public:
	/**
	* @brief get ctrl root
	*
	* @return ctrl root
	*/
	const std::string& getCtrlRoot();

	/**
	* @brief set ctrl root
	*
	* @param v as ctrl root
	*/
	void setCtrlRoot(const std::string& v);

	/**
	* @brief get ctrl file name
	*
	* @return ctrl file name
	*/
	const std::string& getCtrlFileName();

	/**
	* @brief set ctrl file name
	*
	* @param v as ctrl file name
	*/
	void setCtrlFileName(const std::string& v);

	/**
	* @brief get ctrl data
	*
	* @return ctrl data
	*/
	TagDataWrapperPtr& ctrlData();

	/**
	* @brief set ctrl data
	*
	* @param v as TagDataWrapper poiniter
	*/
	void setCtrlData(TagDataWrapperPtr& v);


	/**
	* @brief get default ctrl
	*
	* @return TagDataWrapper pointer
	*/
	TagDataWrapperPtr getDefaultCtrl();

	/**
	* @brief load ctrl
	*
	* @param ctrlFile 
	*/
	void loadCtrl(const std::string& ctrlFile);

	/**
	* @brief create a default template ctrl file
	*/
	void createDefaultCtrlFile();

	///@}
///////////////////////end of ctrl

///////////////////////////////////////// 
 

public:
	/** @name events
	*
	*/
	///@{
	/**
	* @brief connect cfg loaded event
	*
	* @param subscriber
	*
	* @return connection
	*/
	boost::signals2::connection connectSignalCfgLoaded(const boost::signals2::signal<void()>::slot_type& subscriber);

	/**
	* @brief fire cfg loaded event
	*/
	void emitSignalCfgLoaded();


	/**
	* @brief connect ctrl loaded event
	*
	* @param subscriber
	*
	* @return connection
	*/
	boost::signals2::connection connectSignalCtrlLoaded(const boost::signals2::signal<void()>::slot_type& subscriber);

	/**
	* @brief fire ctrl loaded event
	*/
	void emitSignalCtrlLoaded();


	/**
	* @brief connect signal prop loaded event
	* 
	* @param subscriber
	*
	* @return connection
	*/
	boost::signals2::connection connectSignalPropLoaded(const boost::signals2::signal<void()>::slot_type& subscriber);

	/**
	* @brief fire property file loaded event
	*/
	void emitSignalPropLoaded();

	///@}
protected:
	boost::signals2::signal<void()> m_signalCfgLoaded; ///< cfg loaded signal
	boost::signals2::signal<void()> m_signalCtrlLoaded; ///< ctrl loaded signal
	boost::signals2::signal<void()> m_signalPropLoaded; ///< prop ini loaded signal




};//class SettingsMgr

}//namespace

#endif