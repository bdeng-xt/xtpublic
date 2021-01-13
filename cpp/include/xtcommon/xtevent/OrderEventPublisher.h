#pragma once
#ifndef XT_ORDER_EVENT_PUBLISHER_H
#define XT_ORDER_EVENT_PUBLISHER_H

/**
* \file OrderEventPublisher.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for publishing order events.
*
* \description
*	This component provides a class for publishing order events.
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




namespace XT
{

 

	class XT_COMMON_API OrderEventPublisher
	{

	public:
		/**
		* @name Constructor and Destructor
		*/
		///@{

		/**
		* @brief constructor
		*/
		OrderEventPublisher();

		/**
		* @brief default copy constructor
		*/
		OrderEventPublisher(const OrderEventPublisher& from);

		/**
		* @brief default copy assignment
		*/
		OrderEventPublisher& operator=(const OrderEventPublisher& from);

		/**
		* @brief destructor
		*/
		virtual ~OrderEventPublisher();

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
		void publish(int iid,int oid, int qid, int eventtype);

		/**
		* @brief signal
		*
		* @return signal
		*/
		std::shared_ptr< boost::signals2::signal<void(int,int,int,int)> >& signal();
	protected:
		std::string m_topic;
		std::shared_ptr< boost::signals2::signal<void(int,int,int,int)> > m_signal;


	};

	//////typedef for OrderEventPublisher
#if defined(USE_BOOST_SHARED_PTR)

	typedef boost::shared_ptr<OrderEventPublisher> OrderEventPublisherPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef std::shared_ptr<OrderEventPublisher> OrderEventPublisherPtr;

#elif defined(USE_SAFE_PTR)

	typedef sf::safe_ptr<OrderEventPublisher> OrderEventPublisherPtr;

#else

	typedef boost::shared_ptr<OrderEventPublisher> OrderEventPublisherPtr;
#endif


	typedef sf::safe_ptr<OrderEventPublisher> OrderEventPublisherSafePtr;

	typedef sf::contfree_safe_ptr<OrderEventPublisher> OrderEventPublisherContFreePtr;
	//////end typedef for OrderEventPublisher

}//namespace

#endif