#pragma once
#ifndef XT_INSTR_EVENT_HANDLER_H
#define XT_INSTR_EVENT_HANDLER_H

/**
* \file InstrEventHandler.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for handling market data and order events.
*
* \description
*	This component provides a class for handling market data and order events.
*/

#include <cstdint>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream>
#include <cstdio>

#include <unordered_set>

#include <memory>
#include <chrono>
#include <thread>
#include <boost/signals2.hpp>

#include "XTConfig.h"
#include "log4z.h"

#include "Util.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"


#include "Containers.h"
#include "ThreadUtil.h"

namespace XT
{

class XT_COMMON_API InstrEventHandler
{

public:
	/**
	* @name Constructor and Initialization
	*/
	///@{
	/**
	* @brief constructor
	*/
	InstrEventHandler();

	/**
	* @brief default copy constructor
	*/
	InstrEventHandler(const InstrEventHandler& from);// = default;

	/**
	* @brief default copy assignment
	*/
	InstrEventHandler& operator=(const InstrEventHandler& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~InstrEventHandler();

	///@}

public:

	/**
	* @brief get instr event task name
	*
	* @return instr event task name
	*/
	const std::string& getInstrEventTaskName();

	/**
	* @brief set instr event task name
	*
	* @param s as task name
	*
	*/
	void setInstrEventTaskName(const std::string& s);

	/**
	* @brief get max events
	*
	* @return max events
	*/
	int getMaxInstrEvents();

	/**
	* @brief set max events
	*
	* @param v as number
	*
	*/
	void setMaxInstrEvents(int v);

	/**
	* @brief add iid to valid iid set
	*
	* @param iid
	*/
	void addValidIid(int iid);

	/**
	* @brief is iid valid
	*
	* @param iid
	* 
	* @return if iid is valid or not
	*/
	bool isValidIid(int iid);

	/**
	* @brief remove iid from valid iid set
	*
	* @param iid
	*/
	void removeValidIid(int iid);

	/**
	* @brief clear valid iid set
	*/
	void clearValidIidSet();



	/**
	* @brief signal connection
	*/
	boost::signals2::connection& connectionInstrEvent();

	/**
	* @brief subscribe
	*/
	void subscribeInstrEvent();

	/**
	* @brief unsubscribe
	*/
	void unsubscribeInstrEvent();

public:

	/**
	* @brief on event function
	*
	* @param iid
	* @param oid
	* @param qid
	* @param eventtype
	*/
	virtual void onInstrEvent(int iid, int oid, int qid, int flag);

	/**
	* @brief start task thread
	*/
	virtual void startInstrEventTask();

	/**
	* @brief thread task
	*/
	virtual void processInstrEventTask();

	/**
	* @brief process InstrEvent
	*/
	virtual void onInstrEventInfo(InstrEventInfo& mktevent);

protected:
	boost::signals2::connection m_connectionInstrEvent; ///< connection
	int m_maxInstrEvents; ///< max number of event in queue
	std::string m_instrEventTaskName;

	std::shared_ptr<ConcurrentQueue<InstrEventInfo> > m_instrEventInfoQueue; ///< event queue
	std::thread* m_instrEventTaskThread;
	int m_instrEventTaskFlag;

	std::unordered_set<int> m_validIidSet;
	
};//class

  //////typedef for InstrEventHandler
#if defined(USE_BOOST_SHARED_PTR)

typedef boost::shared_ptr<InstrEventHandler> InstrEventHandlerPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef std::shared_ptr<InstrEventHandler> InstrEventHandlerPtr;

#elif defined(USE_SAFE_PTR)

typedef sf::safe_ptr<InstrEventHandler> InstrEventHandlerPtr;

#else

typedef std::shared_ptr<InstrEventHandler> InstrEventHandlerPtr;
#endif


typedef sf::safe_ptr<InstrEventHandler> InstrEventHandlerSafePtr;

typedef sf::contfree_safe_ptr<InstrEventHandler> InstrEventHandlerContFreePtr;
//////end typedef for InstrEventHandler

}//namespace XT


#endif