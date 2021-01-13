#pragma once
#ifndef XT_WEB_TRADER_GATEWAY_H
#define XT_WEB_TRADER_GATEWAY_H

/**
* \file WebTraderGateway.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a manager class for web trader gateway.
*
* \description
*	Designed for managing web trader gateway.
*/


#include <string>
#include <iostream>
#include <sstream>

#include <boost/unordered_map.hpp>


#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>			//任务队列的线程功能
#include <boost/bind.hpp>			//任务队列的线程功能
#include <boost/any.hpp>	//任务队列的任务实现
//#include <boost/lockfree/queue.hpp>
//#include <boost/lockfree/spsc_queue.hpp>
#include "Containers.h"

 
#include <boost/smart_ptr.hpp>
#include "safe_ptr.h"
 

#include "XTConfig.h"


#include <google/protobuf/util/json_util.h>
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"
 

#include "ServerSettingsMgr.h"
#include "InstrSettingsMgr.h"
#include "SettingsMgr.h"
#include "InstrMgr.h"

#include "Util.h"
#include "TimeUtil.h"
#include "PBUtil.h"
#include "LogUtil.h"
 
#include "TagDataWrapper.h"
#include "InstrMgr.h"
#include "OrderQuoteMgr.h"
#include "WebMgr.h"
//#include <RepeatedTimer.h>

namespace XT
{

//struct WebTrdTask
//{
//	int task_tag;
//	boost::any task_data;
////	boost::any task_info;
////	int task_id;
////	bool task_last;
//}; //struct WebTrdTask

 

class XT_COMMON_API WebTraderGateway
{
protected:
	TagDataWrapperPtr m_data; ///< extra data

	boost::thread * m_task_thread; ///< task thread
	//	boost::lockfree::spsc_queue<WebTrdTask,boost::lockfree::capacity<1024> > m_task_queue;
//	ConcurrentQueue<WebTrdTask> m_task_queue;

protected:
	 

	ConnectionStatus::enumtype m_connectionStatus; ///< connection status
	LogInStatus::enumtype m_logInOutStatus; ///< login or logout status

	int m_ReqAllInstrsFlag; ///< flag for requesting all instruments
	AsyncTaskStatus::enumtype m_ReqAllInstrsStatus; ///< asynchronous status for requesting all instruments

	int m_AddingInstrOnRspFlag; ///< flag for adding instruments on response
	int m_UpdateInstrFlag; ///< flag for updaing instruments
	int m_TimerTaskSeconds; ///< timer task seconds

	std::string m_serverSettingName; ///< server setting name



	bool m_hasQueryedPositionAll; ///< flag to indicate if all positions were queryed or not


	bool m_isRunningTask; ///< flag for running task

private:



public:
	/** 
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	WebTraderGateway();
	 
	/**
	* @brief default copy constructor
	*/
	WebTraderGateway(const WebTraderGateway& from);// = default;

	/**
	* @brief default copy assignment
	*/
	WebTraderGateway& operator=(const WebTraderGateway& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~WebTraderGateway();

	///@}

	/**
	* @brief check if task is running or not
	*/
	bool isRunningTask();

	/**
	* @brief stop Task
	*/
	void stopRunningTask();

	/**
	* @brief start Task
	*/
	void startRunningTask();
 
	/**
	* @briefupdate settings
	*/
	void updateSettingData();
	
	/**
	* @brief initialize
	*/
	void init();

	/**
	* @brief release
	*/
	void release();

	/**
	* @brief login
	*/
	void login();

	/**
	* @brief logout
	*/
	void logout();

	/**
	* @brief get server setting name
	*/
	const std::string& getServerSettingName();

	/**
	* @brief set server setting name
	* @param s for setting name
	*/
	void setServerSettingName(const std::string& s);

	///**
	//* @brief get frontid
	//* 
	//* @return front id
	//*/
	//const std::string& getFrontID();

	///**
	//* set frontid
	//*/
	//void setFrontID(const std::string& s);
	///**
	//* get brokerid
	//*/
	//const std::string& getBrokerID();
	///**
	//* set brokerid
	//*/
	//void setBrokerID(const std::string& s);
	///**
	//* get accountid
	//*/
	//const std::string& getAccountID();
	///**
	//* set accountid
	//*/
	//void setAccountID(const std::string& s);
	///**
	//* get password
	//*/
	//const std::string& getPasswd();
	///**
	//* set password
	//*/
	//void setPasswd(const std::string& s);

	/**
	* @brief get connection status
	*
	* @return connection status
	*/
	ConnectionStatus::enumtype getConnectionStatus();
	
	/**
	* @brief set connection status
	*
	* @return login or logout status
	*/
	LogInStatus::enumtype getLogInStatus();

	/**
	* @brief check if it is connected or not
	*
	* @return if it is connected
	*/
	bool isConnected();
	
	/**
	* @brief check if it is logged in or not
	*
	* @return if it loggedin
	*/
	bool isLoggedIn();

	/**
	* @brief get flag for requesting all instruments
	*
	* @return flag
	*/
	int getReqAllInstrsFlag();

	/**
	* @brief set flag for requesting all instruments
	*
	* @param v for flag value
	*/
	void setReqAllInstrsFlag(int v);

	/**
	* @brief get asynchronous status for requesting all instruments
	*
	* @return status
	*/
	AsyncTaskStatus::enumtype getReqAllInstrsStatus();

	/**
	* @brief set asynchronous status for requesting all instruments
	*
	* @param v for status
	*/
	void setReqAllInstrsStatus(AsyncTaskStatus::enumtype v);
	
	/**
	* get flag for adding instrument on response
	*/
	int getAddingInstrOnRspFlag();

	/**
	* @brief set flag for adding instrument on response
	*
	* @param v for flag
	*/
	void setAddingInstrOnRspFlag(int v);

	/**
	* @brief get flag for updating instruments
	*
	* @return flag
	*/
	int getUpdateInstrFlag();

	/**
	* @brief set flag for updating instruments
	* 
	* @param v for flag
	*/
	void setUpdateInstrFlag(int v);

	/**
	* @brief get timer task seconds
	*
	* @return timer seconds
	*/
	int getTimerTaskSeconds();

	/**
	* @brief set timer task seconds
	*
	* @param v for timer seconds
	*/
	void setTimerTaskSeconds(int v);
 

public:
 
    


};//class WebTraderGateway

  //////typedef for WebTraderGateway
 
#if defined(USE_BOOST_SHARED_PTR)
 
typedef ::boost::shared_ptr<WebTraderGateway> WebTraderGatewayPtr;

#elif defined(USE_STD_SHARED_PTR)
 
typedef ::std::shared_ptr<WebTraderGateway> WebTraderGatewayPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<WebTraderGateway> WebTraderGatewayPtr;

#else
 
typedef ::boost::shared_ptr<WebTraderGateway> WebTraderGatewayPtr;
#endif


typedef ::sf::safe_ptr<WebTraderGateway> WebTraderGatewaySafePtr;

typedef sf::contfree_safe_ptr<WebTraderGateway> WebTraderGatewayContFreePtr;
//////end typedef for WebTraderGateway
 
}//namespace XT

#endif
