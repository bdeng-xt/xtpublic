#pragma once
#ifndef XT_XTAPIMGR_H
#define XT_XTAPIMGR_H

/**
* \file XTApiMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a manager class for xt apis.
*
* \description
*	Designed for managing xt apis.
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

#include "XTConfig.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"
#include "XTEnum.pb.h"
#include "LogUtil.h"

#include "Util.h"
#include "TimeUtil.h"

#include "Instr.h"
#include "InstrCombo.h"

#include "SettingsMgr.h"

#include "XTApi.h"

#include "SimApi.h"
#include "IBApi.h"
#include "WebApi.h"

 

namespace XT
{



class XT_COMMON_API XTApiMgr
{
public:
	/** @name Constructor and Destructor
	*
	*/
	///@{

	/**
	* @brief constructor
	*/
	XTApiMgr();

	/**
	* @brief default copy constructor
	*/
	XTApiMgr(const XTApiMgr& from) {} // {} //= delete;

	/**
	* @brief default copy assignment
	*/
	XTApiMgr& operator=(const XTApiMgr& from) { return *this; } // {} //= delete;

	/**
	* @brief destructor
	*/
	virtual ~XTApiMgr();

	///@}

 

public:
	/**
	* @brief get singleton instance
	*/
	static XTApiMgr* getInstance();
public:
	//void setApiPluginPath(const std::string& s);
	//std::string getApiPluginPath();

	//std::string getBaseDir();
	//void setBaseDir(const std::string& s);

public:
 
	/**
	* @ brief initialize
	*/
	void init( );
	/**
	* @brief release
	*/
	void release();
	/**
	* @brief start
	*/
	void start();
	/**
	* @brief check if has api with apitype
	*
	* @param apitype api type value
	*
	* @return has or not api
	*/
	bool hasApi(const std::string& apiname);

	/**
	* @brief get api by apiname
	*
	* @param apiname
	*
	* @return api
	*/
	XTApiPtr& apiByName(const std::string& apiname);

	/**
	* @brief initialize api
	*
	* @param apitype api type value
	*
	* @param flag flag value
	*/
	void initApi(const std::string& apiname, int flag);
	/**
	* @brief get plugin files under library directory
	*
	* @return vector of plugin files
	*/
	std::vector<std::string> getPluginFiles();
	/**
	* @brief load plugin from file
	*
	* @param pluginfile file name
	*
	* @return ApiPlugin pointer
	*/
	XTApiPluginPtr loadPlugin(const std::string& pluginfile);
	/**
	* @brief load all plugins
	*/
	void loadAllPlugins();
	///**
	//* @brief get plugin types
	//*
	//* @return vector of type values
	//*/
	//std::vector<int> getPluginTypes();

	/**
	* @brief get plugin names
	*
	* @return vector of plugin names
	*/
	std::vector<std::string> getPluginNames();

	/**
	* @brief get api names
	*
	* @return vector of api names
	*/
	std::vector<std::string> getApiNames();

	/**
	* @brief get api names
	*
	* @return vector of api names
	*/
	std::vector<std::string> getInitializedApiNames();

	/**
	* @brief add XTApi
	*
	* @param api
	*/
	void addApi(XTApiPtr& api);

	/**
	* @brief add XTApi by name
	*
	* @param name
	*/
	void addApiByName(const std::string& name);

protected:
	//std::string m_baseDir;

	XTApiPtr m_emptyApi; ///< null api
	//std::string m_xtapiPluginPath;
	std::map<std::string, XTApiPtr > m_xtapiMap; ///< api map
	std::map<std::string, XTApiPluginPtr >  m_xtapiPluginMap; ///< plugin map

	std::map<int, XTApiPtr > m_exchToMdApiMap; ///< exchange to market data XTApi map
	std::map<int, XTApiPtr > m_exchToTrdApiMap; ///< exchange to trd XTApi map

	std::map<std::string, XTApiPtr > m_instrprefixToMdApiMap; ///< instrprefix to market data XTApi map
	std::map<std::string, XTApiPtr > m_instrprefixToTrdApiMap; ///< instrprefix to trd XTApi map

	std::map<std::string, XTApiPtr > m_productToMdApiMap; ///< instrprefix to market data XTApi map
	std::map<std::string, XTApiPtr > m_productToTrdApiMap; ///< instrprefix to trd XTApi map


//	std::map<int, std::string> m_apiIntToNameMap; ///< api intid to name map
//	std::map<std::string, int> m_apiNameToIntMap; ///< api name to intid map
 
/////////////////////////////////////////

public:
	/**
	* @brief get market data api for instrument
	*
	* @param instr
	*
	* @return api
	*/
	XTApiPtr& getMdApiForInstr(InstrPtr& instr);

	/**
	* @brief get trd api for instrument
	*
	* @param instr
	*
	* @return api
	*/
	XTApiPtr& getTrdApiForInstr(InstrPtr& instr);

	  
/////////////////////////////////////////////////////
public:
	/**
	* @brief subscribe market data for instruments
	* 
	* @param instrs as vector of instrids
	*/
	void subscribeMktData(std::vector<std::string>& instrs);
	/**
	* @brief unsubscribe market data for instruments
	*
	* @param instrs as vector of instrids
	*/
	void unsubscribeMktData(std::vector<std::string>& instrs);
	/**
	* @brief subscribe market data for one instrument
	*
	* @param instrid as instrid
	*/
	void subscribeMktDataFor(const std::string& instrid);
	/**
	* @brief unsubscribe market data for one instrument
	*
	* @param instrid as instrid
	*/
	void unsubscribeMktDataFor(const std::string& instrid);
	/**
	* @brief subscribe market data for all instruments
	*
	*/
	void subscribeMktDataForAll();
	/**
	* @brief unsubscribe market data for all instruments
	*
	*/
	void unsubscribeMktDataForAll();
	///**
	//* @brief subscribe market data for instruments in settings
	//*
	//*/
	//void subscribeMktDataForInstrumentsInSettings();

	///**
	//* @brief unsubscribe market data for instruments in settings
	//*
	//*/
	//void unsubscribeMktDataForInstrumentsInSettings();

	/**
	* @brief query instrument
	* @param instrid as instrid
	*/
	void queryInstrFor(const std::string& instrid);

	/**
	* @brief query all instruments
	*
	*/
	void queryInstrForAll();

	/**
	* @brief query trades for instrument
	* @param instrid as instrid
	*/
	void queryTradeFor(const std::string& instrid);

	/**
	* @brief query trades for all instruments
	*
	*/
	void queryTradeForAll();

	/**
	* @brief query position for one instrument
	* @param instrid as instrid
	*/
	void queryPositionFor(const std::string& instrid);
	/**
	* @brief query all positions
	*
	*/
	void queryPositionForAll();

	/**
	* @brief send order for instrument
	*
	* @param instr for instrument
	* @param bs for buy or sell
	* @param price for order price
	* @param sz for order size
	* @param ocflag for open close flag
	* @param oqrtypemask for order quote reason mask
	* @param sendmemo
	*
	* @return orderid
	*/
	int sendInstrOrder(InstrPtr& instr, BuySellType::enumtype bs, double price, int64_t sz, OpenCloseFlag::enumtype ocflag, int oqrtypemask, const std::string& sendmemo="");
	
	/**
	* @brief cancel order for instrument
	*
	* @param instr for instrument
	* @param oid for orderid
	* @param flag for reason
	* @param cxlmemo
	*
	* @return size of cancelling orders
	*/
	int64_t cancelInstrOrder(InstrPtr& instr, int oid, int flag, const std::string& cxlmemo = "");


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
	int sendInstrQuote(InstrPtr& instr, double bidPx, int64_t bidSz, OpenCloseFlag::enumtype bidOCFlag, double askPx, int64_t askSz, OpenCloseFlag::enumtype askOCFlag, int oqrtypeMask, const std::string& forQuoteSysID = "", const std::string& sendmemo="");

	/**
	* @brief cancel quote for instrument
	*
	* @param instr for instrument
	* @param qid
	* @param reasonflag
	* @param cxlmemo
	*
	* @return size of cancelling quotes
	*/
	int64_t cancelInstrQuote(InstrPtr& instr, int qid, int reasonflag, const std::string& cxlmemo="");


	/**
	* @brief send order
	*
	* @param orderinfo
	*
	* @return oid
	*/
	int sendOrder(OrderInfoPtr& orderinfo);

	/**
	* @brief send quote
	*
	* @param quoteinfo
	*
	* @return qid
	*/
	int sendQuote(QuoteInfoPtr& orderinfo);

public:
	/**
	* @brief send order for instrument with automated open close flag
	*
	* @param instr for instrument
	* @param bs for buy or sell
	* @param price for order price
	* @param sz for order size
	* @param oqrtypemask for order quote reason mask
	*
	* @return last orderid
	*/
	int sendInstrOrderAutoFlag(InstrPtr& instr, XT::BuySellType::enumtype bs, double price, int64_t sz, int oqrtypeMask);

	/**
	* @brief send order for instrument with max size kept to flat
	*
	* @param instr for instrument
	* @param bs for buy or sell
	* @param price for order price
	* @param sz for order size
	* @param maxcanflat for max size kept to flat
	* @param oqrtypemask for order quote reason mask
	*
	* @return last orderid
	*/
	int sendInstrOrderWithMaxCanFlat(InstrPtr& instr, BuySellType::enumtype bs, double price, int64_t sz, int maxcanflat, int oqrtypemask);
	
	/**
	* @brief send order for instrument with automated open close flag and max distance to place flat orders
	*
	* @param instr for instrument
	* @param bs for buy or sell
	* @param price for order price
	* @param sz for order size
	* @param maxdist for max distance to place flat orders
	* @param oqrtypemask for order quote reason mask
	*
	* @return last orderid
	*/
	int sendInstrOrderAutoFlagWithMaxDist(InstrPtr& instr, XT::BuySellType::enumtype bs, double price, int64_t sz, int maxdist, int oqrtypemask);

	/**
	* @brief send order for instrument for profit taking
	*
	* @param instr for instrument
	* @param bs for buy or sell
	* @param price for order price
	* @param sz for order size
	* @param fillorderid for orderid to flat
	* @param profitticks for profit taking ticks
	*
	* @return last orderid
	*/
	int sendInstrOrderForProfitTaking(InstrPtr& instr, XT::BuySellType::enumtype bs, double price, int64_t sz, int fillorderid, int profitticks);

	/**
	* @brief cancel order for instrument on buy or sell side
	*
	* @param instr for instrument
	* @param bs for buy or sell side
	*
	* @return size of cancelling orders
	*/
	int64_t cancelInstrOrdersOnSide(InstrPtr& instr, BuySellType::enumtype bs);

	/**
	* @brief cancel all orders for instrument
	*
	* @param instr for instrument
	*
	* @return size of cancelling orders
	*/
	int64_t cancelInstrOrdersAll(InstrPtr& instr);

	/**
	* @brief cancel all orders for instrument with openclose flag
	*
	* @param instr for instrument
	* @param ocflag for open close flag
	*
	* @return size of cancelling orders
	*/
	int64_t cancelInstrOrdersByFlag(InstrPtr & instr, OpenCloseFlag::enumtype ocflag);

	/**
	* @brief cancel all orders for instrument on buy or sell side with price NOT between lowerpx and upperpx
	*
	* @param instr for instrument
	* @param bs for buy or sell side
	* @param lowerpx for lower price limit
	* @param upperpx for upper price limit
	*
	* @return size of cancelling orders
	*/
	int64_t cancelInstrOrdersOutOfRange(InstrPtr & instr, BuySellType::enumtype bs, double lowerpx, double upperpx);

	/**
	* @brief cancel all orders for instrument on buy or sell side with open close flag and with price NOT between lowerpx and upperpx
	*
	* @param instr for instrument
	* @param bs for buy or sell side
	* @param lowerpx for lower price limit
	* @param upperpx for upper price limit
	* @param ocflag for open close flag
	*
	* @return size of cancelling orders
	*/
	int64_t cancelInstrOrdersOutOfRangeByFlag(InstrPtr & instr, BuySellType::enumtype bs, double lowerpx, double upperpx, OpenCloseFlag::enumtype ocflag);

	/**
	* @brief cancel all orders for instrument on buy or sell side with price between lowerpx and upperpx
	*
	* @param instr for instrument
	* @param bs for buy or sell side
	* @param lowerpx for lower price limit
	* @param upperpx for upper price limit
	*
	* @return size of cancelling orders
	*/
	int64_t cancelInstrOrdersInRange(InstrPtr & instr, BuySellType::enumtype bs, double lowerPx, double upperPx);

	/**
	* @brief cancel all orders for instrument on buy or sell side with open close flag and with price between lowerpx and upperpx
	*
	* @param instr for instrument
	* @param bs for buy or sell side
	* @param lowerpx for lower price limit
	* @param upperpx for upper price limit
	* @param ocflag for open close flag
	*
	* @return size of cancelling orders
	*/
	int64_t cancelInstrOrdersInRangeByFlag(InstrPtr & instr, BuySellType::enumtype bs, double lowerpx, double upperpx, OpenCloseFlag::enumtype ocflag);


	/**
	* @brief cancel all orders for instrument on buy or sell side placed too long
	*
	* @param instr for instrument
	* @param bs for buy or sell side
	* @param maxseconds for maximum seconds placed
	*
	* @return size of cancelling orders
	*/
	int64_t cancelInstrOrdersTooLong(InstrPtr & instr, BuySellType::enumtype bs, int maxSeconds);

	/**
	* @brief cancel all orders for instrument on buy or sell side with open close flag with placed too long
	*
	* @param instr for instrument
	* @param bs for buy or sell side
	* @param maxseconds for maximum seconds placed
	* @param ocflag for open close flag
	*
	* @return size of cancelling orders
	*/
	int64_t cancelInstrOrdersTooLongByFlag(InstrPtr & instr, BuySellType::enumtype bs, int maxseconds, OpenCloseFlag::enumtype ocflag);

	/**
	* @brief cancel all orders for instrument on buy or sell side with price between lowerpx and upperpx
	*
	* @param instr for instrument
	* @param bs for buy or sell side
	* @param maxseconds for maximum seconds placed
	* @param lowerpx for lower price limit
	* @param upperpx for upper price limit
	*
	* @return size of cancelling orders
	*/
	int64_t cancelInstrOrdersTooLongInRange(InstrPtr & instr, BuySellType::enumtype bs, int maxseconds, double lowerpx, double upperpx);

	/**
	* @brief cancel all orders for instrument on buy or sell side with open close flag and with price between lowerpx and upperpx
	*
	* @param instr for instrument
	* @param bs for buy or sell side
	* @param maxseconds for maximum seconds placed
	* @param lowerpx for lower price limit
	* @param upperpx for upper price limit
	* @param ocflag for open close flag
	*
	* @return size of cancelling orders
	*/
	int64_t cancelInstrOrdersTooLongInRangeByFlag(InstrPtr & instr, BuySellType::enumtype bs, int maxseconds, double lowerpx, double upperpx, OpenCloseFlag::enumtype ocflag);

	/**
	* @brief cancel all orders for instrument on buy or sell side to target size 
	*
	* @param instr for instrument
	* @param bs for buy or sell side
	* @param tgtsz for target size
	* @param isaggressive for aggressive or not
	*
	* @return size of cancelling orders
	*/
	int64_t cancelInstrOrdersSzToLessThan(InstrPtr & instr, BuySellType::enumtype bs, int64_t tgtsz, bool isaggressive);

	/**
	* @brief cancel all orders for instrument on buy or sell side to target size within lowerpx and upperpx
	*
	* @param instr for instrument
	* @param bs for buy or sell side
	* @param tgtsz for target size
	* @param isaggressive for aggressive or not
	* @param lowerpx for lower price limit
	* @param upper px for upper price limit
	*
	* @return size of cancelling orders
	*/
	int64_t cancelInstrOrdersSzToLessThanInRange(InstrPtr & instr, BuySellType::enumtype bs, int64_t tgtsz, bool isaggressive, double lowerpx, double upperx);

	/**
	* @brief cancel all orders for instrument with specific order quote reason type
	*
	* @param instr for instrument
	* @param bs for buy or sell side
	* @param oqrtypemask for order quote reason mask
	*
	* @return size of cancelling orders
	*/
	int64_t cancelInstrOrdersByReason(InstrPtr & instr, int oqrtypemask);

	/**
	* @brief cancel all orders for instrument on buy or sell side to target size with specific reason NOT within lowerpx and upperpx
	*
	* @param instr for instrument
	* @param bs for buy or sell side
	* @param lowerpx for lower price limit
	* @param upper px for upper price limit
	* @param oqrtypemask for order quote reason
	*
	* @return size of cancelling orders
	*/
	int64_t cancelInstrOrdersOutOfRangeByReason(InstrPtr & instr, BuySellType::enumtype bs, double lowerpx, double upperpx, int oqrtypemask);

	/**
	* @brief cancel all orders for instrument on buy or sell side to target size with specific reason within lowerpx and upperpx
	*
	* @param instr for instrument
	* @param bs for buy or sell side
	* @param lowerpx for lower price limit
	* @param upper px for upper price limit
	* @param oqrtypemask for order quote reason
	*
	* @return size of cancelling orders
	*/
	int64_t cancelInstrOrdersInRangeByReason(InstrPtr & instr, BuySellType::enumtype bs, double lowerpx, double upperpx, int oqrtypemask);

	/**
	* @brief cancel all orders for instrument on buy or sell side to target size with maximum distance away best market
	*
	* @param instr for instrument
	* @param bs for buy or sell side
	* @param dist for maximum distance away from best market price
	*
	* @return size of cancelling orders
	*/
	int64_t cancelInstrOrdersAwayMkt(InstrPtr & instr, BuySellType::enumtype bs, int dist);

	/**
	* @brief hit market  for instrument to flat net positions 
	*
	* @param instr for instrument
	*
	* @return total sending size
	*/
	int64_t hitMktToFlatPositionForInstr(InstrPtr & instr);

	/**
	* @brief hit market  for instrument to flat all positions
	*
	* @param instr for instrument
	*
	* @return total sending size
	*/
	int64_t hitMktToFlatAllPositionsForInstr(InstrPtr& instr);

	/**
	* @brief hit market  for instrument to take profit
	*
	* @param instr for instrument
	* @param profittakingticks for profit taking ticks
	*
	* @return total sending size
	*/
	int64_t hitMktToTakeProfitForInstr(InstrPtr & instr, double profittakingticks);

	/**
	* @brief hit market  for instrument to puke
	*
	* @param instr for instrument
	* @param puketicks for puking ticks
	*
	* @return total sending size
	*/
	int64_t hitMktToPukeForInstr(InstrPtr & instr, double puketicks);

	/**
	* @brief hit market  for instrument to target position
	*
	* @param instr for instrument
	* @param tgtpos for target position
	*
	* @return total sending size
	*/
	int64_t hitMktToTgtPositionForInstr(InstrPtr & instr, int64_t tgtpos);

	/**
	* @brief hit market  for instrument to target position with maximum distance
	*
	* @param instr for instrument
	* @param tgtpos for target position
	* @param maxdist for maximum distance away from best market
	*
	* @return total sending size
	*/
	int64_t joinMktToTgtPositionForInstr(InstrPtr & instr, int64_t tgtPos, int maxdist = 1);

public:
	/**
	* @brief hit market  for instrcombo to target position
	*
	* @param instr for instrument
	* @param tgtpos for target position
	*
	* @return total sending size
	*/
	int64_t hitMktToTgtPositionForInstrCombo(InstrComboPtr & instrcombo, int64_t tgtPos);

	/**
	* @brief hit market  for instrcombo to target position with maximum distance
	*
	* @param instr for instrument
	* @param tgtpos for target position
	* @param maxdist for maximum distance away from best market
	*
	* @return total sending size
	*/
	int64_t joinMktToTgtPositionForInstrCombo(InstrComboPtr& instrcombo, int64_t tgtPos, int maxDist );





};//class


}//namespace XT


#endif