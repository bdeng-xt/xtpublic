#pragma once
#ifndef XT_WEB_MD_GATEWAY_H
#define XT_WEB_MD_GATEWAY_H

/**
* \file WebMdGateway.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a manager class for web gateway.
*
* \description
*	Designed for managing web gateway.
*/

#include <string>
#include <iostream>
#include <sstream>

#include <vector>
#include <set>

#include <boost/unordered_map.hpp>
#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>			
#include <boost/bind.hpp>			
#include <boost/any.hpp>	
//#include <boost/lockfree/queue.hpp>
//#include <boost/lockfree/spsc_queue.hpp>
#include "Containers.h"

 
#include <boost/smart_ptr.hpp>
#include "safe_ptr.h"


#include "XTConfig.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h" 

#include "ServerSettingsMgr.h"
#include "InstrSettingsMgr.h"
#include "SettingsMgr.h"
#include "InstrMgr.h"

#include "Util.h"
#include "PBUtil.h"
#include "LogUtil.h"
 

#include "TagDataWrapper.h"

#include "InstrUtil.h"
#include "PBUtil.h"
#include "ZMQMgr.h"
#include "WebMgr.h"
namespace XT
{


struct WebMdTask
{
	int task_tag;///< task tag
	boost::any task_data; ///< task data
//	boost::any task_info;
//	int task_id;
//	bool task_last;
}; //struct WebMdTask

//////typedef for WebMdTask
#if defined(USE_BOOST_SHARED_PTR)

typedef boost::shared_ptr<WebMdTask> WebMdTaskPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef std::shared_ptr<WebMdTask> WebMdTaskPtr;

#elif defined(USE_SAFE_PTR)

typedef sf::safe_ptr<WebMdTask> WebMdTaskPtr;

#else

typedef boost::shared_ptr<WebMdTask> WebMdTaskPtr;
#endif


typedef sf::safe_ptr<WebMdTask> WebMdTaskSafePtr;

typedef sf::contfree_safe_ptr<WebMdTask> WebMdTaskContFreePtr;
//////end typedef for WebMdTask


class XT_COMMON_API WebMdGateway
{


	//////////////////////////
protected:
//	TagDataWrapperPtr m_data; ///< extra data

	boost::shared_ptr<boost::thread> m_producer_thread;///< boost::thread * m_producer_thread;
	boost::shared_ptr<boost::thread> m_task_thread; ///< boost::thread * m_task_thread;


	//	boost::lockfree::spsc_queue<WebMdTask,boost::lockfree::capacity<1024> > m_task_queue;
	ConcurrentQueue<WebMdTask> m_task_queue; ///< concurrent task queue

	boost::shared_ptr<PBOutputFile> m_mktdataPBOutputFile; ///< market data file

	int m_mktdataLogCountMax; ///< maximum number of data items in one single data file
	int m_mktdataLogCount; ///< count of current data items
	/**
	* create market data output file
	*/
	void createMktDataPBOutputFile();

protected:

//	CThostFtdcMdApi* m_pMdApi;

	ConnectionStatus::enumtype m_connectionStatus;///< connection status
	LogInStatus::enumtype m_logInOutStatus; ///< login or logout status

	int m_AddingInstrOnRspFlag; ///< flag for adding instr on response
	int m_SubAllInstrsMktDataFlag; ///< flag for subscribing market data for all instruments
	AsyncTaskStatus::enumtype m_SubAllInstrsMktDataStatus; ///<asynchronous status for market data subscription

	int m_UpdateInstrFlag; ///< flag for updating instrument
	int m_LogMktDataFlag; ///< flag for logging market data
	int m_TimerTaskSeconds; ///< task timer seconds

	std::string m_serverSettingName; ///< settings name


	std::set<std::string> m_mktInstrumentSet; ///< market data instruments

	int m_timerCount; ///< timer count

	int m_chinaIntDate; ///< china intdate
	int64_t m_chinaStockMorningStart; ///< morning start time for china stock market
	int64_t m_chinaStockMorningEnd; ///< morning end time for china stock market
	int64_t m_chinaStockAfternoonStart; ///< afternoon start time for china stock market
	int64_t m_chinaStockAfternoonEnd; ///< afternoon end time for china stock market

	int64_t m_chinaCurrTs; ///< current timestamp for china market
 
	bool m_isRunningTask; ///< is task running or not
	bool m_isRunningThread;///< is thread running or not

 

public:
	/** @name Constructor and Destructor
	*
	*/
	///@{

	/**
	* @brief constructor
	*/
	WebMdGateway();

	/**
	* @brief default copy constructor
	*/
	WebMdGateway(const WebMdGateway& from);// = default;

	/**
	* @brief default copy assignment
	*/
	WebMdGateway& operator=(const WebMdGateway& from);// = default;

	/**
	* @briefdestructor
	*/
	virtual ~WebMdGateway();
	///@}
 
	/**
	* @brief check if task is running or not
	*
	* @return if task is running
	*/
	bool isRunningTask();

	/**
	* @brief stop task
	*/
	void stopRunningTask();

	/**
	* @brief start task
	*/
	void startRunningTask();

	/**
	* @brief stop thread
	*/
	void stopThread();

	///**
	//* @brief update settings
	//*/
	//void updateSettingData();

protected:
	XT::GatewayCfgDataPtr m_cfgData;
	XT::GatewayDataPtr m_data;

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
	std::set<std::string> m_instrPrefixSet;///< instrument prefixes set
	std::set<std::string> m_productSet; ///< products
	std::set<std::string> m_exchidSet; ///< exchange ids
									   //////////////////////////

public:

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
	*
	* @return setting name
	*/
	const std::string& getServerSettingName();

	/**
	* @brief set server setting name
	*
	* @param s for setting name
	*/
	void setServerSettingName(const std::string& s);


	/**
	* @brief get connection status
	*
	* @return connection status
	*/
	ConnectionStatus::enumtype getConnectionStatus();

	/**
	* @brief get login or logout status
	*
	* @return login status
	*/
	LogInStatus::enumtype getLogInStatus();

	/**
	* @brief check if it is connected or not
	*
	* @return if it is connected
	*/
	bool isConnected();

	/**
	* @brief check if it is logged in
	*
	* @return if it is loggedin
	*/
	bool isLoggedIn();

	/**
	* @brief get flag for subscribing market data for all instruments
	*
	* @return flag
	*/
	int getSubAllInstrsMktDataFlag();

	/**
	* @brief set flag for subscribing market data for all instruments
	*
	* @param v for flag value
	*/
	void setSubAllInstrsMktDataFlag(int v);

	/**
	* @brief get asynchronous status for subscribing market data for all instruments
	*
	* @return status
	*/
	AsyncTaskStatus::enumtype getSubAllInstrsMktDataStatus();

	/**
	* @brief set asynchronous status for subscribing market data for all instruments
	*
	* @param v for status
	*/
	void setSubAllInstrsMktDataStatus(AsyncTaskStatus::enumtype v);

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
	* @brief get flag for logging market data
	*
	* @return flag
	*/
	int getLogMktDataFlag();

	/**
	* @brief set flag for logging market data
	*
	* @param v for flag
	*/
	void setLogMktDataFlag(int v);

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




	void subscribeMktDataFor(std::vector<std::string>& instruments);
	void unsubscribeMktDataFor(std::vector<std::string>& instruments);

	void subscribeMktDataForAll();

	void unsubscribeMktDataForAll();

	/**
	* @brief subscribe market data by filter type
	*/
	void subscribeMktDataByFilterType(const std::string& filterstr, int filtertype);

	/**
	* @brief unsubscribe market data by filter type
	*/
	void unsubscribeMktDataByFilterType(const std::string& filterstr, int filtertype);

public:
   
 
 protected:
	 /**
	 * @brief produce task
	 */
	 void produceTask();

	 /**
	 * @brief process task
	 */
	 void processTask();

	 /**
	 * @brief process SinaQuoteData
	 *
	 * @param task for WebMdTask
	 */
	 void processOnSinaQuoteData(const WebMdTask& task);

protected:
	/**
	* @brief process SinaQuoteData lines
	*
	* @param s for data string
	*/
	void onSinaQuoteDataLines(const std::string& s);


};

//////typedef for WebMdGateway
 
#if defined(USE_BOOST_SHARED_PTR)
 
typedef ::boost::shared_ptr<WebMdGateway> WebMdGatewayPtr;

#elif defined(USE_STD_SHARED_PTR)
 
typedef ::std::shared_ptr<WebMdGateway> WebMdGatewayPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<WebMdGateway> WebMdGatewayPtr;

#else
 
typedef ::boost::shared_ptr<WebMdGateway> WebMdGatewayPtr;
#endif


typedef ::sf::safe_ptr<WebMdGateway> WebMdGatewaySafePtr;

typedef sf::contfree_safe_ptr<WebMdGateway> WebMdGatewayContFreePtr;
//////end typedef for WebMdGateway
 
} //namespace XT

#endif
