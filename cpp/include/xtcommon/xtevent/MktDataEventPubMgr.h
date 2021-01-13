#pragma once
#ifndef XT_MKT_DATA_EVENT_PUB_MGR_H
#define XT_MKT_DATA_EVENT_PUB_MGR_H

/**
* \file MktDataEventPubMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a singleton manager for handling market data events.
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

#include "MktDataEventSubscriber.h"
#include "MktDataEventPublisher.h"


namespace XT
{

class XT_COMMON_API MktDataEventPubMgr
{

public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	MktDataEventPubMgr();

	/**
	* @brief default copy constructor
	*/
	MktDataEventPubMgr(const MktDataEventPubMgr& from) {}// = delete;

	/**
	* @brief default copy assignment
	*/
	MktDataEventPubMgr& operator=(const MktDataEventPubMgr& from) { return *this; }// = delete;

	/**
	* @brief destructor
	*/
	virtual ~MktDataEventPubMgr();

	///@}

public:
	/**
	* @brief get singleton instance
	*
	* @return singleton instance
	*/
	static MktDataEventPubMgr* getInstance();

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
	void publishEvent(const std::string& topic, int iid);

	/**
	* @brief publish event
	*
	* @param integer id
	*/
	void publishMktEvent(int iid);

	/**
	* @brief publish optmkt event
	*
	* @param integer id
	*/
	void publishOptMktEvent(int iid);

protected:
	std::shared_ptr< MktDataEventPublisher > m_mktPub;
	std::shared_ptr< MktDataEventPublisher > m_optMktPub;

	std::unordered_map<std::string, std::shared_ptr< MktDataEventPublisher > > m_pubMap;
 

};

}//namespace

#endif