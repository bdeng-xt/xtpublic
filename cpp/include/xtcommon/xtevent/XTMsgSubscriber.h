#pragma once
#ifndef XT_XTMSG_SUBSCIBER_H
#define XT_XTMSG_SUBSCIBER_H

/**
* \file XTMsgSubscriber.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for subscribing XTMsg.
*
* \description
*	This component provides a class for subscribing XTMsg.
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
#include "XTConfig.h"
#include "LogUtil.h"

#include "Util.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "InstrMgr.h"

#include "XTMsgPublisher.h"

namespace XT
{

	class XT_COMMON_API XTMsgSubscriber
	{
	public:
		/**
		* @name Constructor and Initialization
		*/
		///@{
		/**
		* @brief constructor
		*/
		XTMsgSubscriber();

		/**
		* @brief default copy constructor
		*/
		XTMsgSubscriber(const XTMsgSubscriber& from);// = default;

		/**
		* @brief default copy assignment
		*/
		XTMsgSubscriber& operator=(const XTMsgSubscriber& from);// = default;

		/**
		* @brief destructor
		*/
		virtual ~XTMsgSubscriber();


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
		void subscribe(XTMsgPublisherPtr & publisher);

		/**
		* @brief slot function
		*
		* @param iid
		*/
		void onEvent(int iid, int oid, int qid, int eventtype);

	protected:
		std::string m_name; ///< subscirber name
		std::string m_topic; ///< topic 

		boost::signals2::connection m_connection; ///< connection
		int m_maxEvents; ///< max number of event in queue
		std::shared_ptr<ConcurrentQueue<int> > m_eventQueue; ///< event queue


	};

	//////typedef for XTMsgSubscriber
#if defined(USE_BOOST_SHARED_PTR)

	typedef boost::shared_ptr<XTMsgSubscriber> XTMsgSubscriberPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef std::shared_ptr<XTMsgSubscriber> XTMsgSubscriberPtr;

#elif defined(USE_SAFE_PTR)

	typedef sf::safe_ptr<XTMsgSubscriber> XTMsgSubscriberPtr;

#else

	typedef boost::shared_ptr<XTMsgSubscriber> XTMsgSubscriberPtr;
#endif


	typedef sf::safe_ptr<XTMsgSubscriber> XTMsgSubscriberSafePtr;

	typedef sf::contfree_safe_ptr<XTMsgSubscriber> XTMsgSubscriberContFreePtr;
	//////end typedef for XTMsgSubscriber

}//namespace

#endif