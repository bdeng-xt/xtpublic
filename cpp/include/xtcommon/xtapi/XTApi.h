#pragma once
#ifndef XT_XTAPI_H
#define XT_XTAPI_H

/**
* \file XTApi.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a base class for xt api.
*
* \description
*	Designed for xt api base.
*/

#include <cstdint>
#include <vector>
#include <map>
#include <set>

#include <boost/unordered_map.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/unordered_set.hpp>

#include <boost/config.hpp>
#include <boost/dll/import.hpp>

#include <boost/smart_ptr.hpp>
#include "safe_ptr.h"

#include "XTConfig.h"
#include "LogUtil.h"

#include <google/protobuf/util/json_util.h>
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"
#include "PBUtil.h"
#include "DataUtil.h"

#include "XTMsg.h"

#include "InstrSpec.h"
#include "Instr.h"
#include "InstrMgr.h"

#include "RequestMgr.h"
#include "OrderMgr.h"




namespace XT
{

class XT_COMMON_API XTApi
{
 

public:
	/** 
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	XTApi();

	/**
	* @brief default copy constructor
	*/
	XTApi(const XTApi& from) = default;

	/**
	* @brief default copy assignment
	*/
	XTApi& operator=(const XTApi& from) = default;

	/**
	* @brief destructor
	*/
	virtual ~XTApi();
	///@}

	/**
	* @brief data
	*/
	ApiDataPtr& data();



	///**
	//* @brief get api type
	//*/
	//int getApiType();

	/**
	* @brief get api name
	*/
	const std::string& getApiName();





protected:
	/**
	* @brief update initialization flag
	*
	* @param flag to indicate trd or md or both
	*/
	void updateInitFlag(int flag);

	/**
	* @brief update release flag
	*/
	void updateReleaseFlag(int flag);

public:
	/**
	*  @name virtual functions
	*/
	///@{

	/**
	* @brief initialize api
	*
	* @param flag to indicate trd or md or both
	*/
	virtual void init(int flag);

	/**
	* @brief get initialization flag
	*/
	virtual int getInitFlag();

	/**
	* @brief release api
	*
	* @param flag to indicate trd or md or both
	*/
	virtual void release(int flag);

	/**
	* check if task is running or not
	*
	* @param flag to indicate trd or md or both
	*/
	virtual bool isRunning(int flag);

	/**
	* @brief start market data task
	*
	* @param flag to indicate trd or md or both
	*/
	virtual void start(int flag);


	///**
	//* @brief stop market data task
	//*
	//* @param flag to indicate trd or md or both
	//*/
	//virtual void stop(int flag);



	/**
	* @brief get task status flag, 1: md, 2:trd
	*
	* @return task status
	*/
	virtual int getTaskStatus(int flag);

	/**
	* @brief set task status flag, 1: md, 2:trd
	*
	* @return task status
	*/
	virtual void setTaskStatus(int flag, int status);

	/**
	* @brief get task queue size
	*
	* @return task queue size
	*/
	virtual int getTaskQueueSz(int flag);

	/**
	* @brief get task total message size
	*
	* @return task total message size
	*/
	virtual int getTaskMsgSz(int flag);


	//////

	/**
	* @brief get exchids Csv str
	*
	* @return exchids separated by ,
	*/
	virtual const std::string& getInstrPrefixesStr(int flag);

	/**
	* @brief get products Csv str
	*
	* @return products separated by ,
	*/
	virtual const std::string& getProductIDsStr(int flag);

	/**
	* @brief get exchids Csv str
	*
	* @return exchids separated by ,
	*/
	virtual const std::string& getExchIDsStr(int flag);


	/**
	* @brief get config section name
	* 
	* @return section name
	*/
	virtual std::string getStrParamsSectionName(int flag);


	///**
	//* @brief get config section name
	//*
	//* @return section name
	//*/
	//virtual std::vector<std::string> getStrParamsKeys(int flag);

	///**
	//* @brief get str parameters value
	//* 
	//* @param flag
	//* @param key
	//* 
	//* @return value
	//*/
	//virtual std::string getStrParamsValue(int flag, const std::string& key);

	///**
	//* @brief set string parameters value
	//*
	//* @param flag
	//* @param key
	//* @param value
	//*/
	//virtual void setStrParamsKeyValue(int flag, const std::string& key, const std::string& value);

	/**
	* @brief string parameters
	*
	* @return string parameters
	*/
	virtual StringMapPtr getStrParams(int flag);

	/**
	* @brief update string parameters
	*
	* @param flag
	* @param smp
	*/
	virtual void updateStrParams(int flag, const StringMapPtr& smp);

	//////
	/**
	* @brief handle general XTMsg
	*
	* @param msg as XTMsg
	*/
	virtual int handleXTMsg(XTMsgPtr& msg);

	/**
	* @brief subsribe market data for instruments
	* @param instrs vector of instruments
	*/
	virtual void subscribeMktData(std::vector<std::string>& instrs);

	/**
	* @brief unsubsribe market data for instruments
	* @param instrs vector of instruments
	*/
	virtual void unsubscribeMktData(std::vector<std::string>& instrs);

	/**
	* @brief subscribe market data for instrument
	* @param instrid instrumentid
	*/
	virtual void subscribeMktDataFor(const std::string& instrid);

	/**
	* @brief unsubscribe market data for instrument
	* @param instrid instrumentid
	*/
	virtual void unsubscribeMktDataFor(const std::string& instrid);

	/**
	* @brief subscribe market data for all instruments
	*/
	virtual void subscribeMktDataForAll();

	/**
	* @brief unsubscribe market data for all instruments
	*/
	virtual void unsubscribeMktDataForAll();


	/**
	* @brief subscribe market data by filter type
	*/
	virtual void subscribeMktDataByFilterType(const std::string& filterstr, int filtertype);

	/**
	* @brief unsubscribe market data by filter type
	*/
	virtual void unsubscribeMktDataByFilterType(const std::string& filterstr, int filtertype);

	/**
	* @brief query instrument
	* @param instrid instrumentid
	*/
	virtual void queryInstrFor(const std::string& instrid);

	/**
	* @brief query all instruments
	*/
	virtual void queryInstrForAll();

	/**
	* @brief query trade
	* @param instrid
	*/
	virtual void queryTradeFor(const std::string& instrid);

	/**
	* @brief query all trades
	*/
	virtual void queryTradeForAll();


	/**
	* @brief query position for instrument
	* @param instrid instrumentid
	*/

	virtual void queryPositionFor(const std::string& instrid);

	/**
	* @brief query all positions
	*/
	virtual void queryPositionForAll();

//////////////////

	/**
	* @brief get next oid
	*
	* @return oid
	*/
	virtual int getNextOid(int bsint);

	/**
	* @brief get next qid
	*
	* @return qid
	*/
	virtual int getNextQid();

	/**
	* @brief get Oid for qid
	*
	* @param qid
	* @param bs
	*
	* @return oid
	*/
	virtual int getOidFromQid(int bsint, int qid);

	/**
	* @brief get Qid for Oid
	*
	* @param oid
	*
	* @reutnr qid
	*/
	virtual int getQidFromOid(int oid);

	/**
	* get coupled order id for an order id
	* @param oid order id
	*/
	virtual int getCoupledOid(int oid);




//////////////////////////////////////////////////////
	/**
	* @brief send order for instrument
	*
	* @param instr for instrument
	* @param bs for buy or sell
	* @param price for order price
	* @param sz for order size
	* @param ocflag for open close flag
	* @param oqrtypemask for order quote reason mask
	* @param sendmemo as memo string
	*
	* @return orderid
	*/
	virtual int sendInstrOrder(InstrPtr& instr, BuySellType::enumtype bs, double price, int64_t sz, OpenCloseFlag::enumtype ocflag = OpenCloseFlag::Unknown, int oqrtypeMask = 0, const std::string& sendmemo ="");

	/**
	* @brief cancel order for instrument
	*
	* @param instr for instrument
	* @param oid for orderid
	* @param flag
	* @param cxlmemo
	*
	* @return size of cancelling orders
	*/
	virtual int64_t cancelInstrOrder(InstrPtr& instr, int oid, int flag = 0, const std::string& cxlmemo="");


	/**
	* @brief send quote for instrument
	*
	* @param instr for instrument
	* @param bidPx
	* @param bidSz
	* @param bidOCFlag
	* @param askPx
	* @param askSz
	* @param askOCFlag
	* @param oqrtypeMask
	* @param forQuoteSysID
	* @param sendmemo
	*
	* @return qid
	*/
	virtual int sendInstrQuote(InstrPtr& instr, double bidPx, int64_t bidSz, OpenCloseFlag::enumtype bidOCFlag, double askPx, int64_t askSz, OpenCloseFlag::enumtype askOCFlag, int oqrtypeMask, const std::string& forQuoteSysID="", const std::string& sendmemo="");

	/**
	* @brief cancel quote for instrument
	*
	* @param instr for instrument
	* @param qid
	* @param reasonflag
	* @param cxlmemo
	* @return size of cancelling quotes
	*/
	virtual int64_t cancelInstrQuote(InstrPtr& instr, int qid, int reasonflag, const std::string& cxlmemo="");


	/**
	* @brief send order
	*
	* @param orderinfo
	*
	* @return oid
	*/
	virtual int sendOrder(OrderInfoPtr& orderinfo);

	/**
	* @brief send quote
	* 
	* @param quoteinfo
	*
	* @return qid
	*/
	virtual int sendQuote(QuoteInfoPtr& orderinfo);

 
	///@}

protected:
	//int m_apiType; ///< api type
	//std::string m_apiName; ///< api name
	//std::string m_version; ///< version
	//int m_initFlag; ///< initialization flag

	ApiDataPtr m_data; ///< data
	StringMapPtr m_strParams; ///< string parameters

};//class
  //////typedef for XTApi
 
#if defined(USE_BOOST_SHARED_PTR)
 
typedef ::boost::shared_ptr<XTApi> XTApiPtr;

#elif defined(USE_STD_SHARED_PTR)
 
typedef ::std::shared_ptr<XTApi> XTApiPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<XTApi> XTApiPtr;

#else
 
typedef ::boost::shared_ptr<XTApi> XTApiPtr;
#endif


typedef ::sf::safe_ptr<XTApi> XTApiSafePtr;

typedef sf::contfree_safe_ptr<XTApi> XTApiContFreePtr;
//////end typedef for XTApi

class XT_COMMON_API XTApiPlugin
{
public:
	/** 
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	XTApiPlugin();

	/**
	* @brief default copy constructor
	*/
	XTApiPlugin(const XTApiPlugin& from) = default;

	/**
	* @brief default copy assignment
	*/
	XTApiPlugin& operator=(const XTApiPlugin& from) = default;

	/**
	* @brief destructor
	*/
	virtual ~XTApiPlugin();
	///@}
public:

	/**
	* @name virtual functions
	*/
	///@{

	///**
	//* @brief get api type
	//*
	//* @return api type as integer
	//*/
	//virtual int getApiType();

	/**
	* @brief get api name
	*
	* @return api name
	*/
	virtual const std::string& getApiName();


	/**
	* @brief get plugin file
	*
	* @return plugin file
	*/
	virtual const std::string& getPluginFile();

	/**
	* @brief set plugin file
	*
	* @param plugin file
	*/
	virtual void setPluginFile(const std::string& pluginfile);

	/**
	* @brief get plugin name
	*
	* @return plugin name
	*/
	virtual const std::string& getPluginName();

	/**
	* @brief set plugin name
	*
	* @param plugin name
	*/
	virtual void setPluginName(const std::string& pluginname);

	/**
	* @brief create api pointer
	* 
	* @return api pointer
	*/
	virtual XTApiPtr create();

	///@}

protected:
	std::string m_apiName;
	std::string m_pluginFile;
	std::string m_pluginName;

};//

  //////typedef for XTApiPlugin
 
#if defined(USE_BOOST_SHARED_PTR)
 
typedef ::boost::shared_ptr<XTApiPlugin> XTApiPluginPtr;

#elif defined(USE_STD_SHARED_PTR)
 
typedef ::std::shared_ptr<XTApiPlugin> XTApiPluginPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<XTApiPlugin> XTApiPluginPtr;

#else
 
typedef ::boost::shared_ptr<XTApiPlugin> XTApiPluginPtr;
#endif


typedef ::sf::safe_ptr<XTApiPlugin> XTApiPluginSafePtr;

typedef sf::contfree_safe_ptr<XTApiPlugin> XTApiPluginContFreePtr;
//////end typedef for XTApiPlugin
}//namespace XT


#endif
