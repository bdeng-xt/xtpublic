#pragma once
#ifndef XT_XTMSG_PUBLISHER_H
#define XT_XTMSG_PUBLISHER_H

/**
* \file XTMsgPublisher.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for publishing xtmsg.
*
* \description
*	This component provides a class for publishing xtmsg.
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
#include <unordered_map>

#include <boost/signals2.hpp>
#include "XTConfig.h"
#include "LogUtil.h"

#include "Util.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "InstrMgr.h"

#include "XTMsg.h"


namespace XT
{



	class XT_COMMON_API XTMsgPublisher
	{

	public:
		/**
		* @name Constructor and Destructor
		*/
		///@{

		/**
		* @brief constructor
		*/
		XTMsgPublisher();

		/**
		* @brief default copy constructor
		*/
		XTMsgPublisher(const XTMsgPublisher& from);

		/**
		* @brief default copy assignment
		*/
		XTMsgPublisher& operator=(const XTMsgPublisher& from);

		/**
		* @brief destructor
		*/
		virtual ~XTMsgPublisher();

		///@}



	public:

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
		* @brief publish event
		*
		* @param integer id
		*/
		void publish(int iid, int oid, int qid, int eventtype);

		/**
		* @brief signal
		*
		* @return signal
		*/
		std::shared_ptr< boost::signals2::signal<void(int, int, int, int)> >& signal();
	protected:
		std::string m_topic;
		std::shared_ptr< boost::signals2::signal<void(int, int, int, int)> > m_signal;


	};

	//////typedef for XTMsgPublisher
#if defined(USE_BOOST_SHARED_PTR)

	typedef boost::shared_ptr<XTMsgPublisher> XTMsgPublisherPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef std::shared_ptr<XTMsgPublisher> XTMsgPublisherPtr;

#elif defined(USE_SAFE_PTR)

	typedef sf::safe_ptr<XTMsgPublisher> XTMsgPublisherPtr;

#else

	typedef boost::shared_ptr<XTMsgPublisher> XTMsgPublisherPtr;
#endif


	typedef sf::safe_ptr<XTMsgPublisher> XTMsgPublisherSafePtr;

	typedef sf::contfree_safe_ptr<XTMsgPublisher> XTMsgPublisherContFreePtr;
	//////end typedef for XTMsgPublisher

}//namespace

#endif