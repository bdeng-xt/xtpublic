#pragma once
#ifndef XT_REQUESTMGR_H
#define XT_REQUESTMGR_H
/**
 * * \file RequestMgr.h
 * *
 * * \author Bin Deng (bdeng@xtal-tech.com)
 * *
 * * \brief  Provide a manager for all requests.
 * *
 * * \description
 * *       Designed for managing id information for all requests.
 * */

#include <cstdint>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <memory>

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/smart_ptr.hpp>

#include "XTConfig.h"
#include "LogUtil.h"
#include "EnumUtil.h"
#include "Util.h"
#include "TimeUtil.h"

#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "RequestId32.h"

namespace XT {

 



//////////////////////////////////////////////


class XT_COMMON_API RequestMgr
{
public:

	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	RequestMgr();

	/**
	* @brief default copy constructor
	*/
	RequestMgr(const RequestMgr& from) {} // = delete;

	/**
	* @brief default copy assignment
	*/
	RequestMgr& operator=(const RequestMgr& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~RequestMgr();

	///@}

public:
	/**
	* @brief get singleton instance
	*
	* @return singleton instance
	*/
	static RequestMgr* getInstance();

public:
 

	/**
	* @brief get next request id
	*
	* @return next request id
	*/
	int getNextReqId(int64_t ts);

	/**
	* @brief get next request id by now time
	*
	* @return now request id
	*/
	int getNowReqId();


	/**
	* @brief get next request 64bit request id
	*
	* @return next 64bit request id
	*/
	int64_t getNextReqId64(int64_t ts);

	/**
	* @brief get now request 64bit request id
	*
	* @return now 64bit request id
	*/
	int64_t getNowReqId64();

//////
	/**
	* @brief get Qid from ReqId
	*/
	static int getQidFromReqId(int reqid);

	/**
	* get order id from quote id
	* @param bs Buy or Sell
	* @param qid quote id
	*/
	static int getOidFromQid(int bsint, int qid);

	/**
	* get quote id from order id
	* @param oid order id
	*/
	static int getQidFromOid(int oid);

	/**
	* get coupled order id for an order id
	* @param oid order id
	*/
	static int getCoupledOid(int oid);

//////
	/**
	* @brief get femas qid from reqid
	*/
	static int getFemasQidFromReqId(int reqid);

	/**
	* get order id from quote id
	* @param bs Buy or Sell
	* @param qid quote id
	*/
	static int getFemasOidFromQid(int bsint, int qid);

	/**
	* get quote id from order id
	* @param oid order id
	*/
	static int getFemasQidFromOid(int oid);

	/**
	* get coupled order id for an order id
	* @param oid order id
	*/
	static int getFemasCoupledOid(int oid);

////
	/**
	* @brief get 64bit qid from 64bit reqid
	*
	* @param reqid64
	*
	* @return 64bit qid
	*/
	static int64_t getQid64FromReqId64(int64_t reqid64);

	/**
	* @brief get 64bit oid from 64bit qid
	*
	* @param bsint
	* @param 64bit qid
	*
	* @return 64bit oid
	*/
	static int64_t getOid64FromQid64(int bsint,int64_t qid64);

	/**
	* @brief get 64bit qid form 64bit oid
	*
	* @param 64bit oid
	*
	* @return 64bit qid
	*/
	static int64_t getQid64FromOid64(int64_t oid64);

	/**
	* @brief get coupled oid
	*
	* @param 64bit oid
	*
	* @return coupled oid
	*/
	static int64_t getCoupleOid64(int64_t oid64);



	///**
	//* @brief add request id for qry position
	//*
	//* @param id as request id
	//*/
	//void addRequestIdForQryPosition(int id);

	///**
	//* @brief if it has request id
	//*
	//* @param id as request id
	//*/
	//bool hasRequestIdForQryPosition(int id);

	///**
	//* @brief add request id for qry instrument
	//*
	//* @param id as request id
	//*/
	//void addRequestIdForQryInstrument(int id);

	///**
	//* @brief if it has request id for qry instrument
	//*
	//* @param id as request id
	//*/
	//bool hasRequestIdForQryInstrument(int id);

//protected:
//	std::unordered_set<int> m_requestIdsForQryPosition; ///< request id set for qry position
//	std::unordered_set<int> m_requestIdsForQryInstrument; ///< request id set for qry instrument

protected:
	static int64_t s_thousand; //10^3
	static int64_t s_million; //10^6
	static int64_t s_billion; //10^9


	int m_currIntTime;
	int m_prevIntTime;
	int m_currReqIdInSec;
	int m_maxReqIdPerSec;


	int64_t m_currIntDateTime;
	int64_t m_prevIntDateTime;
//	int64_t m_currEpochSec;
//	int64_t m_prevEpochSec;
	int64_t m_currReqId64InSec;
	int64_t m_maxReqId64PerSec;



};//class RequestMgr

} //namespace XT


#endif
