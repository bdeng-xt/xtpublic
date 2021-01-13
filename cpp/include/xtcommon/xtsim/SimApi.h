#pragma once
#ifndef XT_SIMAPI_H
#define XT_SIMAPI_H

/**
* \file SimApi.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a manager class for simulation api.
*
* \description
*	Designed for managing simulation api.
*/

#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/unordered_map.hpp>

#include <boost/smart_ptr.hpp>

#include <boost/config.hpp>
#include <boost/dll/import.hpp>

#include "safe_ptr.h"

#include "XTConfig.h"
#include "LogUtil.h"
#include "Util.h"
#include "TimeUtil.h"
#include "Instr.h"
#include "InstrMgr.h"
#include "OrderQuoteMgr.h"
#include "RequestMgr.h"

#include "SettingsMgr.h"


#include <google/protobuf/util/json_util.h>
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "PBUtil.h"
#include "ZMQMgr.h"

#include "XTApi.h"

#include "SimMd.h"
#include "SimTrader.h"
 

namespace XT
{

	class XT_COMMON_API SimApi : public XT::XTApi
	{
	public:
		/** 
		* @name Constructor and Initialization
		*/
		///@{
		/**
		* @brief constructor
		*/
		SimApi();

		/**
		* @brief default copy constructor
		*/
		SimApi(const SimApi& from) = default;

		/**
		* @brief default copy assignment
		*/
		SimApi& operator=(const SimApi& from) = default;

		/**
		* @brief destructor
		*/
		virtual ~SimApi();
		///@}


	public:
		SimMdPtr& md();
		SimTraderPtr& trd();

	public:
		void initMd();
		void releaseMd();

		void initTrader();
		void releaseTrader();

	protected:
		void updateCfgForMd();
		void updateCfgForTrader();
	protected:
		SimMdPtr m_md;
		SimTraderPtr m_trd;

	public:
		/**
		* @brief initialization
		*
		* @param flag as integer
		*/
		virtual void init(int flag);

		/**
		* @brief release all resources
		*
		* @param flag as integer
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
		* @brief get task queue size
		*
		* @return task queue size
		*/
		virtual int getQueueSz(int flag);


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
		virtual const std::string& getProductsStr(int flag);

		/**
		* @brief get exchids Csv str
		*
		* @return exchids separated by ,
		*/
		virtual const std::string& getExchIDsStr(int flag);


		/**
		* @brief send general XTMsg
		*
		* @param msg as XTMsg
		*/
		virtual int handleXTMsg(XT::XTMsgPtr& msg);

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

//////////////////////

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
		virtual int sendInstrOrder(InstrPtr& instr, BuySellType::enumtype bs, double price, int64_t sz, OpenCloseFlag::enumtype ocflag = OpenCloseFlag::Unknown, int oqrtypeMask = 0, const std::string& sendmemo = "");

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
		virtual int64_t cancelInstrOrder(InstrPtr& instr, int oid, int flag = 0, const std::string& cxlmemo = "");


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
		virtual int sendInstrQuote(InstrPtr& instr, double bidPx, int64_t bidSz, OpenCloseFlag::enumtype bidOCFlag, double askPx, int64_t askSz, OpenCloseFlag::enumtype askOCFlag, int oqrtypeMask, const std::string& forQuoteSysID = "", const std::string& sendmemo = "");

		/**
		* @brief cancel quote for instrument
		*
		* @param instr for instrument
		* @param qid
		* @param reasonflag
		* @param cxlmemo
		* @return size of cancelling quotes
		*/
		virtual int64_t cancelInstrQuote(InstrPtr& instr, int qid, int reasonflag, const std::string& cxlmemo = "");


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




 
 

	};//class
	  //////typedef for SimApi

#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<SimApi> SimApiPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<SimApi> SimApiPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<SimApi> SimApiPtr;

#else

	typedef ::boost::shared_ptr<SimApi> SimApiPtr;
#endif


	typedef ::sf::safe_ptr<SimApi> SimApiSafePtr;

	typedef sf::contfree_safe_ptr<SimApi> SimApiContFreePtr;
	//////end typedef for SimApi

}//namespace XT


#endif