#pragma once
#ifndef XT_SIM_TRADER_H
#define XT_SIM_TRADER_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>

#include <memory>

#include <boost/unordered_map.hpp>
#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>		 
#include <boost/bind.hpp>			 
#include <boost/any.hpp>	 
//#include <boost/lockfree/queue.hpp>
//#include <boost/lockfree/spsc_queue.hpp>
#include "Containers.h"

#include "XTConfig.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "log4z.h"
#include "CfgMgr.h"
#include "Util.h"
#include "DataUtil.h"
#include "ThreadUtil.h"
#include "InstrMgr.h"

#include "SimTraderGateway.h"
#include "XTTimer.h"
 

namespace XT
{

class XT_COMMON_API SimTrader : public SimTraderGateway, public std::enable_shared_from_this<SimTrader>
{

public:
	SimTrader();
	virtual ~SimTrader();

public:
	void start();

public:
	/**
	* @brief update mktdataquote
	*/
	virtual void onMktQuoteData(MktQuoteDataPtr& mktdata);

	/**
	* @brief update on data string
	*
	* @param line
	* @param datatype
	*/
	virtual void onDataStr(const std::string& line, const std::string& datatype);

protected:
	virtual void onAddSymbol(const Symbol& symbol);

	virtual void onDeleteSymbol(const Symbol& symbol);

	virtual void onAddOrderBook(const XTOrderBook& order_book);

	virtual void onUpdateOrderBook(const XTOrderBook& order_book, bool top);

	virtual void onDeleteOrderBook(const XTOrderBook& order_book);

	virtual void onAddLevel(const XTOrderBook& order_book, const Level& level, bool top);

	virtual void onUpdateLevel(const XTOrderBook& order_book, const Level& level, bool top);

	virtual void onDeleteLevel(const XTOrderBook& order_book, const Level& level, bool top);

	virtual void onAddOrder(const XTOrder& order);

	virtual void onUpdateOrder(const XTOrder& order);

	virtual void onDeleteOrder(const XTOrder& order);

	virtual void onExecuteOrder(const XTOrder& order, int64_t price, int64_t quantity);
public:
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
	virtual int sendInstrOrder(XT::InstrPtr& instr, XT::BuySellType::enumtype bs, double price, int sz, XT::OpenCloseFlag::enumtype ocflag = XT::OpenCloseFlag::Unknown, int oqrtypeMask = 0, const std::string& sendmemo = "");

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
	virtual int cancelInstrOrder(XT::InstrPtr& instr, int oid, int flag = 0, const std::string& cxlmemo = "");


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
	virtual int sendInstrQuote(XT::InstrPtr& instr, double bidPx, int bidSz, XT::OpenCloseFlag::enumtype bidOCFlag, double askPx, int askSz, XT::OpenCloseFlag::enumtype askOCFlag, int oqrtypeMask, const std::string& forQuoteSysID = "", const std::string& sendmemo = "");

	/**
	* @brief cancel quote for instrument
	*
	* @param instr for instrument
	* @param qid
	* @param reasonflag
	* @param cxlmemo
	* @return size of cancelling quotes
	*/
	virtual int cancelInstrQuote(XT::InstrPtr& instr, int qid, int reasonflag, const std::string& cxlmemo = "");


	/**
	* @brief send order
	*
	* @param orderinfo
	*
	* @return oid
	*/
	virtual int sendOrder(XT::OrderInfoPtr& orderinfo);

	/**
	* @brief send quote
	*
	* @param quoteinfo
	*
	* @return qid
	*/
	virtual int sendQuote(XT::QuoteInfoPtr& orderinfo);

protected:
	void processTask();

protected:
	MarketManagerPtr m_mktMgr;

};

typedef std::shared_ptr<SimTrader> SimTraderPtr;

}//namespace

#endif
