#pragma once
#ifndef XT_ZMQMGR_H
#define XT_ZmQMGR_H

/**
* \file ZMQMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for managing zmq.
*
* \description
*	Designed for zmq.
*/

#include <cstdint>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/unordered_set.hpp>
#include <boost/signals2.hpp>

#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>			 
#include <boost/bind.hpp>			 
#include <boost/any.hpp>	 
//#include <boost/lockfree/queue.hpp>
//#include <boost/lockfree/spsc_queue.hpp>
#include "Containers.h"

#ifndef XT_DISABLE_ZMQ 

#include "XTConfig.h"

#include "LogUtil.h"



#include "FIXData.pb.h"
#include "XTData.pb.h"

#include "TagDataWrapper.h"

#include "Util.h"
#include "XTTimer.h"

#include "zmq.h"

#include "zmq.hpp"


namespace XT {

class XT_COMMON_API ZMQMgr
{

public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	ZMQMgr();

	/**
	* @brief default copy constructor
	*/
	ZMQMgr(const ZMQMgr& from) {}// = delete;

	/**
	* @brief default copy assignment
	*/
	ZMQMgr& operator=(const ZMQMgr& from) { return *this; } //= delete;

	/**
	* @brief destructor
	*/
	~ZMQMgr();

	///@}
public:
	/**
	* @brief get singleton instance
	*
	* @return singleton instance
	*/
	static ZMQMgr* getInstance();

	/**
	* @brief has instance
	*
	* @return if instance exists or not
	*/
	static bool hasInstance();

protected:
	static bool m_hasInstance;
public:

	/**
	* @brief is initialized or not
	*
	* @return if it is initialized or not
	*/
	bool isInitialized();

	/**
	* @brief initialize
	*/
	void init();

	/**
	* @brief release
	*/
	void release();

	
	/**
	* @brief get conext
	*
	* @return context
	*/
	void* getContext();

	/**
	* @brief get inproc publish socket
	*
	* @return inproc publish socket
	*/
	void* getInprocPublishSocket();

	/**
	* @brief get publish socket
	*
	* @return publish socket
	*/
	void* getPublishSocket();

	/**
	* @brief get subscribe socket
	*
	* @return subscribe socket
	*/
	void* getSubscribeSocket();

	/**
	* @brief get inproc publish bind string vector
	*
	* @return vector of bind string
	*/
	std::vector<std::string> getInprocPublishBindStrVector();

	/**
	* @brief get publish bind string vector
	*
	* @return vector of bind string
	*/
	std::vector<std::string> getPublishBindStrVector();

	/**
	* @brief get subscribe bind string vector
	*
	* @return vector of bind string
	*/
	std::vector < std::string> getSubscribeBindStrVector();

	/**
	* @brief bind inproc publish address
	*
	* @param s as address
	*/
	void bindInprocPublishAddress(const std::string& s);

	/**
	* @brief unbind inproc publish address
	*
	* @param s as address
	*/
	void unbindInprocPublishAddress(const std::string& s);

	/**
	* @brief publish inproc message
	*
	* @param s as message
	*/
	void publishInprocMessage(const std::string& s);

	/**
	* @brief bind publish address
	*
	* @param s as address
	*/
	void bindPublishAddress(const std::string& s);

	/**
	* @brief unbind publish address
	*
	* @param s as address
	*/
	void unbindPublishAddress(const std::string& s);

	/**
	* @brief publish inproc message
	*
	* @param s as message
	*/
	void publishMessage(const std::string& s);

	/**
	* @brief bind subscribe address
	*
	* @param s as address
	*/
	void bindSubscribeAddress(const std::string& s);

	/**
	* @brief unbind subscribe address
	*
	* @param s as address
	*/
	void unbindSubscribeAddress(const std::string& s);


protected:
	bool m_isInitialized; ///< is initialized or not

	void* m_context; ///< zmq context
	void* m_inproc_publish_socket; ///< zmq inproc publish socket
	void* m_publish_socket; ///< zmq publish socket
	void* m_subscribe_socket; ///< zmq subscribe socket

	std::unordered_set<std::string> m_set_inproc_publish_bind_str; ///< set of inproc publish bind addresses
	std::unordered_set<std::string> m_set_publish_bind_str; ///< set of publish bind addresses
	std::unordered_set<std::string> m_set_subscribe_bind_str; ///< set of subscribe addresses

protected:
	std::string m_inprocHeartbeatMsg; ///< inproc heart message

	/**
	* @brief on timer event
	*/
	void onTimer();

	boost::signals2::connection m_connectionTimer; ///< timer connection

};//

 

}//namespace


#endif //#ifndef XT_DISABLE_ZMQ

#endif