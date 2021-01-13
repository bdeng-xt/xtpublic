#pragma once
#ifndef XT_SIMMGR_H
#define XT_SIMMGR_H


#include <cstdint>
#include <vector>
#include <map>
#include <set>

#include "XTConfig.h"
#include "log4z.h"

#include "Util.h"
#include "DataUtil.h"

#include "SimMdGateway.h"
#include "SimMd.h"
#include "SimTraderGateway.h"
#include "SimTrader.h"

#include "SimApi.h"

#include "Instr.h"
#include "InstrMgr.h"
#include "StratMgr.h"
#include "StratMgr.h"
#include "SimUtil.h"

#include  "MarketSim.h"

namespace XT
{

class XT_COMMON_API SimMgr
{

public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	SimMgr();

	/**
	* @brief default copy constructor
	*/
	SimMgr(const SimMgr& from) {}// = delete;

	/**
	* @brief default copy assignment
	*/
	SimMgr& operator=(const SimMgr& from) { return *this; }// = delete;

	/**
	* @brief destructor
	*/
	virtual ~SimMgr();

	///@}

public:
	/**
	* @brief get singleton instance
	*
	* @return singleton instance
	*/
	static SimMgr* getInstance();

public:
	SimApiPtr& api();
	SimMdPtr& md();
	SimTraderPtr& trd();
	MarketSimPtr& marketSim();
protected:
	SimApiPtr m_api;
	SimMdPtr m_md;
	SimTraderPtr m_trd;
	MarketSimPtr m_marketSim;

	GatewayCfgDataPtr m_emptyGatewayCfgData;
	GatewayDataPtr m_emptyGatewayData;

protected:
	/**
	* @brief initilization
	*/
	void init(int flag);

public:
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

	/**
	* @brief stop market data task
	*
	* @param flag to indicate trd or md or both
	*/
	virtual void stop(int flag);

	/**
	* @brief md cfgdata
	*
	* @return md cfgdata
	*/
	virtual GatewayCfgDataPtr& mdCfgData();

	/**
	* @brief md data
	*
	* @return md data
	*/
	virtual GatewayDataPtr& mdData();

	/**
	* @brief trd cfgdata
	*
	* @return trd cfgdata
	*/
	virtual GatewayCfgDataPtr& trdCfgData();

	/**
	* @brief trd data
	*
	* @return trd data
	*/
	virtual GatewayDataPtr& trdData();

	/**
	* @brief set instr prefixes string
	*
	* @param s
	* @param flag
	*/
	virtual void setInstrPrefixesStr(const std::string& s,int flag);

	/**
	* @brief has valid instrid or not
	*
	* @param instrid
	* @param flag
	*
	* @return if instrid is valid or not
	*/
	virtual bool hasValidInstrPrefix(const std::string& instrid, int flag);

	/**
	* @brief set exchid string
	*
	* @param s
	* @param flag
	*/
	virtual void setExchidsStr(const std::string & s, int flag);

	/**
	* @brief has valid exchid or not
	*
	* @param exchid
	* @param flag
	*
	* @return if instrid is valid or not
	*/
	virtual bool hasExchid(const std::string& exchid, int flag);

	/**
	* @brief set productid string
	*
	* @param s
	* @param flag
	*/
	virtual void setProductsStr(const std::string & s, int flag);

	/**
	* @brief has valid productid or not
	*
	* @param productid
	* @param flag
	*
	* @return if instrid is valid or not
	*/
	virtual bool hasProduct(const std::string& product, int flag);

	/**
	* @brief get task queue size
	*
	* @return task queue size
	*/
	virtual int getQueueSz(int flag);


	///**
	//* @brief send general XTMsg
	//*
	//* @param msg as XTMsg
	//*/
	//virtual int handleXTMsg(XT::XTMsgPtr& msg);
	int handleXTMsgJsonStr(const std::string& s);

	/**
	* @brief subsribe market data for instruments
	* @param instrs vector of instruments
	*/
	void subscribeMktData(std::vector<std::string>& instrs);

	/**
	* @brief unsubsribe market data for instruments
	* @param instrs vector of instruments
	*/
	void unsubscribeMktData(std::vector<std::string>& instrs);

	/**
	* @brief subscribe market data for instrument
	* @param instrid instrumentid
	*/
	void subscribeMktDataFor(const std::string& instrid);

	/**
	* @brief unsubscribe market data for instrument
	* @param instrid instrumentid
	*/
	void unsubscribeMktDataFor(const std::string& instrid);

	/**
	* @brief subscribe market data for all instruments
	*/
	void subscribeMktDataForAll();

	/**
	* @brief unsubscribe market data for all instruments
	*/
	void unsubscribeMktDataForAll();

	/**
	* @brief query instrument
	* @param instrid instrumentid
	*/
	void queryInstrFor(const std::string& instrid);

	/**
	* @brief query all instruments
	*/
	void queryInstrForAll();

	/**
	* @brief query trade
	* @param instrid
	*/
	void queryTradeFor(const std::string& instrid);

	/**
	* @brief query all trades
	*/
	void queryTradeForAll();


	/**
	* @brief query position for instrument
	* @param instrid instrumentid
	*/

	void queryPositionFor(const std::string& instrid);

	/**
	* @brief query all positions
	*/
	void queryPositionForAll();

	//////
	/**
	* @brief send order for instrument
	*
	* @param instrid
	* @param bs integer for buy or sell
	* @param price for order price
	* @param sz for order size
	* @param ocflag for open close flag
	* @param oqrtypemask for order quote reason mask
	* @param sendmemo as memo string
	*
	* @return orderid
	*/
	int sendOrderForInstrID(const std::string& instrid, int bsint, double price, int sz, int ocflagint, int oqrtypeMask = 0, const std::string& sendmemo = "");


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
	int cancelOrderForInstrID(const std::string& instrid, int oid, int flag = 0, const std::string& cxlmemo = "");


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
	int sendQuoteForInstrID(const std::string& instrid, double bidPx, int bidSz, int  bidOCFlagInt, double askPx, int askSz, int askOCFlagInt, int oqrtypeMask, const std::string& forQuoteSysID = "", const std::string& sendmemo = "");


	/**
	* @brief cancel quote for instrument
	*
	* @param instr for instrument
	* @param qid
	* @param reasonflag
	* @param cxlmemo
	* @return size of cancelling quotes
	*/
	int cancelQuoteForInstrID(const std::string& instrid, int qid, int reasonflag, const std::string& cxlmemo = "");

	///////////////////////////////////////////////////////////////////////// 

protected:
 

public:

	/**
	* @brief init SimMarket
	*/
	void initMarketSim();

	/**
	* @brief start SimMarket
	*/
	void startMarketSim();

	/**
	* @brief daydata snapshot
	*/
	void handleSimMdOnDayData(DayDataPtr& daydata);
	
	/**
	* @brief on mktdata snapshot
	*/
	void handleSimMdOnMktQuoteData( MktQuoteDataPtr& mktdata); // , const DayDataPtr& daydata);

	/**
	 * @brief on mktdata snapshot
	*/
	void handleSimTrdOnMktQuoteData(MktQuoteDataPtr& mktdata); // , const DayDataPtr& daydata);


	/**
	* @brief on fill info
	*/
	void handleSimTrdOnFillInfo(FillInfoPtr& fillinfo);

	/**
	* @brief on order info
	*/
	void handleSimTrdOnOrderInfo(OrderInfoPtr& orderinfo);


};//class SimMgr


}//namespace




#endif
