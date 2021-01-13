#pragma once
#ifndef XT_SIM_TRADER_GATEWAY_H
#define XT_SIM_TRADER_GATEWAY_H

#include <string>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <vector>
#include <set>

#include <memory>
#include <thread>

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

#include "Symbol.h"
#include "MarketHandler.h"
#include "XTOrder.h"
#include "XTOrderBook.h"
#include "MarketManager.h"
#include "SimOrderMgr.h"
namespace XT
{

	struct SimTrdTask
	{
		int task_tag;
		boost::any task_data;
	};


	class XT_COMMON_API SimTraderGateway: public MarketHandler
	{

	public:
		SimTraderGateway();
		virtual ~SimTraderGateway();

	public:
		virtual void start();

	public:
		XT::GatewayCfgDataPtr& cfgData();
		XT::GatewayDataPtr& data();
	public:
		void updateCfgData();

		void setInstrPrefixesStr(const std::string& s);
		bool hasValidInstrPrefix(const std::string& instrid);

		void setExchidsStr(const std::string & s);
		bool hasExchid(const std::string& exchid);

		void setProductsStr(const std::string & s);
		bool hasProduct(const std::string& product);

		int getTaskQueueSz(int flag);

	protected:

		XT::GatewayCfgDataPtr m_cfgData;
		XT::GatewayDataPtr m_data;

		std::thread* m_task_thread;
		ConcurrentQueue<SimTrdTask> m_task_queue;


		std::set<std::string> m_instrPrefixSet;///< instrument prefixes set
		std::set<std::string> m_productSet; ///< products
		std::set<std::string> m_exchidSet; ///< exchange ids
										   //////////////////////////

	public:
		void queryInstrFor(const std::string& instrid);
		void queryInstrForAll();

		void queryTradeFor(const std::string& instrid);
		void queryTradeForAll();

		void queryPositionFor(const std::string& instrid);
		void queryPositionForAll();


///////////
 
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


	};

	typedef std::shared_ptr<SimTraderGateway> SimTraderGatewayPtr;

}//namespace

#endif