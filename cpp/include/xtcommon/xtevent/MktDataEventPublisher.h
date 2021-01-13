#pragma once
#ifndef XT_MKT_DATA_EVENT_PUBLISHER_H
#define XT_MKT_DATA_EVENT_PUBLISHER_H

/**
* \file MktDataEventPublisher.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for publishing market data events.
*
* \description
*	This component provides a class for publishing market data events.
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

	class XT_COMMON_API MktDataEventPublisher
	{

	public:
		/**
		* @name Constructor and Destructor
		*/
		///@{

		/**
		* @brief constructor
		*/
		MktDataEventPublisher();

		/**
		* @brief default copy constructor
		*/
		MktDataEventPublisher(const MktDataEventPublisher& from);

		/**
		* @brief default copy assignment
		*/
		MktDataEventPublisher& operator=(const MktDataEventPublisher& from);

		/**
		* @brief destructor
		*/
		virtual ~MktDataEventPublisher();

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
		void publish( int iid);

		/**
		* @brief signal
		*
		* @return signal
		*/
		std::shared_ptr< boost::signals2::signal<void(int)> >& signal();
	protected:
		std::string m_topic;
		std::shared_ptr< boost::signals2::signal<void(int)> > m_signal;

		 
	};

	//////typedef for MktDataEventPublisher
#if defined(USE_BOOST_SHARED_PTR)

	typedef boost::shared_ptr<MktDataEventPublisher> MktDataEventPublisherPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef std::shared_ptr<MktDataEventPublisher> MktDataEventPublisherPtr;

#elif defined(USE_SAFE_PTR)

	typedef sf::safe_ptr<MktDataEventPublisher> MktDataEventPublisherPtr;

#else

	typedef boost::shared_ptr<MktDataEventPublisher> MktDataEventPublisherPtr;
#endif


	typedef sf::safe_ptr<MktDataEventPublisher> MktDataEventPublisherSafePtr;

	typedef sf::contfree_safe_ptr<MktDataEventPublisher> MktDataEventPublisherContFreePtr;
	//////end typedef for MktDataEventPublisher

}//namespace

#endif