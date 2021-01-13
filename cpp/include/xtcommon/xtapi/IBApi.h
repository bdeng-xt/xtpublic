#pragma once
#ifndef XT_IBAPI_H
#define XT_IBAPI_H

/**
* \file IBApi.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a manager class for IB Api.
*
* \description
*	Designed for managing IB api.
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

 
#include "IBGateway.h"
 

namespace XT
{

	class XT_COMMON_API IBApi : public XT::XTApi
	{
	public:
		/** 
		* @name Constructor and Initialization
		*/
		///@{
		/**
		* @brief constructor
		*/
		IBApi();

		/**
		* @brief default copy constructor
		*/
		IBApi(const IBApi& from) = default;

		/**
		* @brief default copy assignment
		*/
		IBApi& operator=(const IBApi& from) = default;

		/**
		* @brief destructor
		*/
		virtual ~IBApi();
		///@}
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
		virtual bool isTaskRunning(int flag);

		/**
		* @brief start market data task
		*
		* @param flag to indicate trd or md or both
		*/
		virtual void startTask(int flag);

		/**
		* @brief stop market data task
		*
		* @param flag to indicate trd or md or both
		*/
		virtual void stopTask(int flag);

		/**
		* @brief send PBTagMsg encoded as string
		*
		* @param msgstr as protobuf encoded string
		*/
		virtual void sendPBTagMsg(const std::string& msgstr);

		/**
		* @brief subscribe market data for instrids
		*
		* @param instrids as vector of instrids
		*/
		virtual void subscribeMarketData(std::vector<std::string>& instrids);

		/**
		* @brief unsubscribe market data for instrids
		*
		* @param instrids as vector of instrids
		*/
		virtual void unsubscribeMarketData(std::vector<std::string>& instrs);

		/**
		* @brief subscribe market data for instrid
		*
		* @param instrid as instrid
		*/
		virtual void subscribeMarketDataFor(const std::string& instrid);

		/**
		* @brief unsubscribe market data for instrid
		*
		* @param instrid as instrid
		*/
		virtual void unsubscribeMarketDataFor(const std::string& instrid);

		/**
		* @brief subscribe all market data
		*/
		virtual void subscribeMarketDataForAll();

		/**
		* @brief unsubscribe all market data
		*/
		virtual void unsubscribeMarketDataForAll();

		/**
		* @brief subscribe market data for all instrids in settings
		*/
		virtual void subscribeMktDataForInstrumentsInSettings();

		/**
		* @brief unsubscribe market data for all instrids in settings
		*/
		virtual void unsubscribeMktDataForInstrumentsInSettings();

		/**
		* @brief query instrument
		*
		* @param instrid for instrid
		*/
		virtual void queryInstrumentFor(const std::string& instrid);

		/**
		* @brief query all instruments
		*/
		virtual void queryInstrumentForAll();

		/**
		* @brief query position for instrid
		*
		* @param instrid for instrid
		*/
		virtual void queryPositionFor(const std::string& instrid);

		/**
		* @brief query all positions
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
		* @brief send order
		*
		* @param orderinfo
		*
		* @return oid
		*/
		virtual int sendOrder(OrderInfoPtr& orderinfo);

		/**
		* @brief cancel order for instrument
		*
		* @param instr for instrument
		* @param oid for orderid
		*
		* @return size of cancelling orders
		*/
		virtual int64_t cancelInstrOrder(InstrPtr& instr, int oid);


	protected:
		IBGatewayPtr m_ibGateway; ///<ib gateway
 
	protected:
		/**
		* @brief update config settings
		*/
		void updateCfgForIB();
 

	};//class

	  //////typedef for IBApi
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<IBApi> IBApiPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<IBApi> IBApiPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<IBApi> IBApiPtr;

#else

	typedef ::boost::shared_ptr<IBApi> IBApiPtr;
#endif


	typedef ::sf::safe_ptr<IBApi> IBApiSafePtr;

	typedef sf::contfree_safe_ptr<IBApi> IBApiContFreePtr;
	//////end typedef for IBApi

}//namespace XT


#endif