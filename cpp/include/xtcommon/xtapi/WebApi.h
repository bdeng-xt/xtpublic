#pragma once
#ifndef XT_WEBAPI_H
#define XT_WEBAPI_H

/**
* \file WebApi.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a manager class for web api.
*
* \description
*	Designed for managing web api.
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

#include <boost/config.hpp>
#include <boost/dll/import.hpp>

#include <boost/smart_ptr.hpp>
#include "safe_ptr.h"

#include "XTConfig.h"
#include "LogUtil.h"
#include "Util.h"
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

#include "WebMgr.h"
#include "WebMdGateway.h"
#include "WebTraderGateway.h"

namespace XT
{

	class XT_COMMON_API WebApi : public XT::XTApi
	{
	public:
		/** 
		* @name Constructor and Initialization
		*/
		///@{
		/**
		* @brief constructor
		*/
		WebApi();

		/**
		* @brief default copy constructor
		*/
		WebApi(const WebApi& from) = default;

		/**
		* @brief default copy assignment
		*/
		WebApi& operator=(const WebApi& from) = default;

		/**
		* @brief destructor
		*/
		virtual ~WebApi();
		///@}
	public:
		/**
		* @brief initialize web api
		* 
		* @param flag as integer
		*/
		virtual void init(int flag);

		/**
		* @brief release web api
		*
		* @param flag as integer
		*/
		virtual void release(int flag);

		/**
		* @brief check if MdTask is running or not
		*
		* @return if task is running
		*/
		virtual bool isRunningMdTask();

		/**
		* @brief stop MdTask
		*/
		virtual void stopRunningMdTask();

		/**
		* @brief start MdTask
		*/
		virtual void startRunningMdTask();

		/**
		* @brief check if TrdTask is running or not
		*
		* @return if trader task is running
		*/
		virtual bool isRunningTrdTask();

		/**
		* @brief stop TrdTask
		*/
		virtual void stopRunningTrdTask();

		/**
		* @brief start TrdTask
		*/
		virtual void startRunningTrdTask();

		/**
		* @brief send PBTagMsg encoded as string
		*
		* @param msgstr as encoded message
		*/
		virtual void sendPBTagMsg(const std::string& msgstr);

		/**
		* @brief subscribe market data for instruments
		* 
		* @param instrids as vector of instrids
		*/
		virtual void subscribeMarketData(std::vector<std::string>& instrids);

		/**
		* @brief unsubscribe market data for instruments
		* 
		* @param instrids as vector of instrids
		*/
		virtual void unsubscribeMarketData(std::vector<std::string>& instrids);

		/**
		* @brief subscribe market data for instrument
		*
		* @param instrid for instrid
		*/
		virtual void subscribeMarketDataFor(const std::string& instrid);

		/**
		* @brief unsubscribe market data for instrument
		*
		* @param instrid for instrid
		*/
		virtual void unsubscribeMarketDataFor(const std::string& instrid);

		/**
		* @brief subscribe market daat for all instruments
		*/
		virtual void subscribeMarketDataForAll();

		/**
		* @brief unsubscribe market data for all instruments
		*/
		virtual void unsubscribeMarketDataForAll();

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
		*
		* @param instrid for instrid
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
		*
		* @param instrid for instrid
		*/
		virtual void queryPositionFor(const std::string& instrid);

		/**
		* @brief query positions for all instruments
		*/
		virtual void queryPositionForAll();

		/**
		* @brief send order for instrument
		*
		* @param instr for instrument
		* @param bs for buy or sell
		* @param price for order price
		* @param sz for order size
		* @param ocflag for open close flag
		* @param oqrtypemask for order quote reason mask
		*
		* @return orderid
		*/
		virtual int sendInstrOrder(InstrPtr& instr, BuySellType::enumtype bs, double price, int64_t sz, OpenCloseFlag::enumtype ocflag, int oqrtypemask);

		/**
		* @brief cancel order for instrument
		*
		* @param instr for instrument
		* @param oid for orderid
		*
		* @return size of cancelling orders
		*/
		virtual int64_t cancelInstrOrder(InstrPtr& instr, int oid);

	public:
		/**
		* @brief initialize web market data api
		*/
		void initWebMd();

		/**
		* @brief release web market data api
		*/
		void releaseWebMd();

		/**
		* @brief initialize web trader api
		*/
		void initWebTrader();

		/**
		* @brief release web trader api
		*/
		void releaseWebTrader();
	protected:
		WebMdGatewayPtr m_webMdGateway;///< web market data gateway
		WebTraderGatewayPtr m_webTraderGateway; ///< web trader gateway

	protected:
		/**
		* @brief update config settings for web market data web api
		*/
		void updateCfgForWebMd();

		/**
		* @brief udpate config settings for web trader api
		*/
		void updateCfgForWebTrader();

	};//class


	  //////typedef for WebApi

#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<WebApi> WebApiPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<WebApi> WebApiPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<WebApi> WebApiPtr;

#else

	typedef ::boost::shared_ptr<WebApi> WebApiPtr;
#endif


	typedef ::sf::safe_ptr<WebApi> WebApiSafePtr;

	typedef sf::contfree_safe_ptr<WebApi> WebApiContFreePtr;
	//////end typedef for WebApi


}//namespace XT


#endif