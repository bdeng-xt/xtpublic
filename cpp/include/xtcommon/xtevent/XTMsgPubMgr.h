#pragma once
#ifndef XT_XTMSG_PUB_MGR_H
#define XT_XTMSG_PUB_MGR_H

/**
* \file XTMsgPubMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a singleton manager for handling order events.
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

	class XT_COMMON_API XTMsgPubMgr
	{

	public:
		/**
		* @name Constructor and Destructor
		*/
		///@{

		/**
		* @brief constructor
		*/
		XTMsgPubMgr();

		/**
		* @brief default copy constructor
		*/
		XTMsgPubMgr(const XTMsgPubMgr& from) {}// = delete;

														 /**
														 * @brief default copy assignment
														 */
		XTMsgPubMgr& operator=(const XTMsgPubMgr& from) { return *this; }// = delete;

																				   /**
																				   * @brief destructor
																				   */
		virtual ~XTMsgPubMgr();

		///@}

	public:
		/**
		* @brief get singleton instance
		*
		* @return singleton instance
		*/
		static XTMsgPubMgr* getInstance();

	public:
		/**
		* @brief add topic
		*
		* @param topic
		*/
		void addTopic(const std::string& topic);

		/**
		* @brief add subscriber

		*/

		/**
		* @brief publish event
		*
		* @param topic
		* @param integer id
		*/
		void publishEvent(const std::string& topic, int iid, int oid, int qid, int eventtype);

		/**
		* @brief publish event
		*
		* @param integer id
		*/
		void publishXTMsg(int iid, int oid, int qid, int eventtype);



	protected:
		std::shared_ptr< XTMsgPublisher > m_orderPub;

		std::unordered_map<std::string, std::shared_ptr< XTMsgPublisher > > m_pubMap;


	};

}//namespace

#endif