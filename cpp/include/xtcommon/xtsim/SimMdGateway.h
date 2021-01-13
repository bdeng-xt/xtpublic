#pragma once
#ifndef XT_SIM_MD_GATEWAY_H
#define XT_SIM_MD_GATEWAY_H

#include <string>
#include <iostream>
#include <sstream>

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

namespace XT
{

	struct SimMdTask
	{
		int task_tag;
		boost::any task_data;
	};


	class XT_COMMON_API SimMdGateway
	{

	public:
		SimMdGateway();
		virtual ~SimMdGateway();

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
		ConcurrentQueue<SimMdTask> m_task_queue;


		std::set<std::string> m_instrPrefixSet;///< instrument prefixes set
		std::set<std::string> m_productSet; ///< products
		std::set<std::string> m_exchidSet; ///< exchange ids
										   //////////////////////////

	public:


		void subscribeMktDataFor(std::vector<std::string>& instruments);
		void unsubscribeMktDataFor(std::vector<std::string>& instruments);

		void subscribeMktDataForAll();

		void unsubscribeMktDataForAll();

	};

	typedef std::shared_ptr<SimMdGateway> SimMdGatewayPtr;

}//namespace

#endif