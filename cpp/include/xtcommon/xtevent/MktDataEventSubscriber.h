#pragma once
#ifndef XT_MKT_DATA_EVENT_SUBSCRIBER_H
#define XT_MKT_DATA_EVENT_SUBSCRIBER_H

/**
* \file MktDataEventSubscriber.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a singleton manager for subscribing market data events.
*
* \description
*	This component provides a class for subscribing market data events.
*/

#include <cstdint>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream>
#include <cstdio>
#include <boost/signals2.hpp>

#include <memory>

#include "XTConfig.h"
#include "LogUtil.h"

#include "Util.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "InstrMgr.h"
#include "Containers.h"

#include "MktDataEventPublisher.h"

namespace XT
{

class XT_COMMON_API MktDataEventSubscriber
{
public:
	/**
	* @name Constructor and Initialization
	*/
	///@{
	/**
	* @brief constructor
	*/
	MktDataEventSubscriber();

	/**
	* @brief default copy constructor
	*/
	MktDataEventSubscriber(const MktDataEventSubscriber& from);// = default;

	/**
	* @brief default copy assignment
	*/
	MktDataEventSubscriber& operator=(const MktDataEventSubscriber& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~MktDataEventSubscriber();


	///@}

	/**
	* @brief get name
	*
	* @return name
	*/
	const std::string& getName();

	/**
	* @brief set name
	*
	* @param name
	*/
	void setName(const std::string& name);

	/**
	* @brief get topic string
	*
	* @return topic string
	*/
	const std::string& getTopic();

	/**
	* @brief set topic string
	*
	* @param topic
	*/
	void setTopic(const std::string& topic);



	/**
	* @brief get max events
	*
	* @return max events
	*/
	int getMaxEvents();

	/**
	* @brief set max events
	*
	* @param v as number
	*
	*/
	void setMaxEvents(int v);

	/**
	* @brief event queue
	*
	* @return reference of event queue
	*/
	std::shared_ptr<ConcurrentQueue<int> >& eventQutue();

	/**
	* @brief subscribe
	*
	* @param publisher
	*/
	void subscribe(MktDataEventPublisherPtr & publisher);

	/**
	* @brief slot function
	*
	* @param iid
	*/
	void onEvent(int iid);

protected:
	std::string m_name; ///< subscirber name
	std::string m_topic; ///< topic 
 
	boost::signals2::connection m_connection; ///< connection
	int m_maxEvents; ///< max number of event in queue
	std::shared_ptr<ConcurrentQueue<int> > m_eventQueue; ///< event queue


};

//////typedef for MktDataEventSubscriber
#if defined(USE_BOOST_SHARED_PTR)

typedef boost::shared_ptr<MktDataEventSubscriber> MktDataEventSubscriberPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef std::shared_ptr<MktDataEventSubscriber> MktDataEventSubscriberPtr;

#elif defined(USE_SAFE_PTR)

typedef sf::safe_ptr<MktDataEventSubscriber> MktDataEventSubscriberPtr;

#else

typedef boost::shared_ptr<MktDataEventSubscriber> MktDataEventSubscriberPtr;
#endif


typedef sf::safe_ptr<MktDataEventSubscriber> MktDataEventSubscriberSafePtr;

typedef sf::contfree_safe_ptr<MktDataEventSubscriber> MktDataEventSubscriberContFreePtr;
//////end typedef for MktDataEventSubscriber


}//namespace

#endif