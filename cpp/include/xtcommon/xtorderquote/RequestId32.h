#pragma once
#ifndef XT_REQUESTID32_H
#define XT_REQUESTID32_H
/**
 * * \file RequestID32.h
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
#include "XTEnum.pb.h"

namespace XT {

	class XT_COMMON_API RequestId32
	{
	public:
		/**
		* @name Constructor and Destructor
		*/
		///@{

		/**
		* @brief constructor
		*/
		RequestId32();

		/**
		* @brief default copy constructor
		*/
		RequestId32(const RequestId32& from) {} // = delete;

		/**
		* @brief default copy assignment
		*/
		RequestId32& operator=(const RequestId32& from) { return *this; } // = delete;

		/**
		* @brief destructor
		*/
		virtual ~RequestId32() {}

		///@}

		/**
		* @brief data
		*
		* @return data
		*/
		RequestIdDataPtr& data();

	protected:
		RequestIdDataPtr m_data;


	public:
		/**
		* @brief set id type
		*
		* @param idtype, 0:default, 1:CTP, 2:FEMAS
		*/
		virtual void setIdType(int idtype);

		/**
		* @brief set start request id
		*/
		virtual void setStartReqId(int reqIdStart);

		/**
		* @brief get next request id
		*
		* @param timestamp
		*
		* @return next request id
		*/
		virtual int getNextReqIdForTs(int64_t ts);

		/**
		* @brief get next request id by inttime
		*
		* @param inttime
		*
		* @return next request id
		*/
		virtual int getNextReqIdForIntTime(int inttime);

		/**
		* @brief get next request id by now time
		*
		* @return now request id
		*/
		virtual int getNowReqId();

		/**
		* @brief get next Qid by now time
		*
		* @return now qid
		*/
		virtual int getNowQid();

		/**
		* @brief get next orderid by now time
		*
		* @return now orderid
		*/
		virtual int getNowOid(int bsint);

		//////
		/**
		* @brief get Qid from ReqId
		*/
		virtual int getQidFromReqId(int reqid);

		/**
		* get order id from quote id
		* @param bs Buy or Sell
		* @param qid quote id
		*/
		virtual int getOidFromQid(int bsint, int qid);

		/**
		* get quote id from order id
		* @param oid order id
		*/
		virtual int getQidFromOid(int oid);

		/**
		* get coupled order id for an order id
		* @param oid order id
		*/
		virtual int getCoupledOid(int oid);

	};//class XT_COMMON_API RequestId32
	typedef std::shared_ptr<RequestId32> RequestId32Ptr;




	//////////////////////////////////////////////
}//namespace


#endif
