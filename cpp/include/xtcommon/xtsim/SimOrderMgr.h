#pragma once
#ifndef XT_SIM_ORDERMGR_H
#define XT_SIM_ORDERMGR_H


/**
* \file SimOrderMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a manager class for sim orders.
*
* \description
*	Designed for managing all sim orders.
*/

#include <cstdint>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <memory>

#include "XTConfig.h"
#include "safe_ptr.h"

#include <google/protobuf/util/json_util.h>
#include "XTEnum.pb.h"
#include "XTData.pb.h"

#include "RequestId32.h"

#include "CfgMgr.h"
#include "InstrMgr.h"

#include "OrderMgr.h"

namespace XT
{

class XT_COMMON_API SimOrderMgr {

public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	SimOrderMgr();

	/**
	* @brief destructor
	*/
	virtual ~SimOrderMgr();

	///@}

	/**
	* @brief get singleton instance
	*
	* @return singleton instance
	*/
	static SimOrderMgr* getInstance();

	/**
	* @brief get request id
	*
	* @return requestid
	*/
	RequestId32Ptr& reqid();

public:
	/**
	* @brief add oid int64id pair
	*/
	void addOidInt64Id(int oid, int64_t int64id);

	/**
	* @brief has Oid for Int64Id
	*/
	bool hasOidForInt64Id(int64_t int64id);

	/**
	* @brief get Oid ForInt64Id
	*/
	int getOidForInt64Id(int64_t int64id);

	/**
	* @brief has Int64Id for Oid
	*/
	bool hasInt64IdForOid(int oid);

	/**
	* @brief get Int64Id for Oid
	*/
	int64_t getInt64IdForOid(int oid);

protected:
	std::string m_emptyString;

	RequestId32Ptr m_reqid;

	sf::contfree_safe_ptr<std::unordered_map<int, int64_t> > m_oidToInt64IdMap;
	sf::contfree_safe_ptr<std::unordered_map<int64_t, int> > m_int64IdToOidMap;


};//class XT_COMMON_API SimOrderMgr {

}//namespace

#endif