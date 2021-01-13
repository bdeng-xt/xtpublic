#pragma once
#ifndef XT_ORDER_QUOTE_MGR_H
#define XT_ORDER_QUOTE_MGR_H

/**
 * * \file OrderQuoteMgr.h
 * *
 * * \author Bin Deng (bdeng@xtal-tech.com)
 * *
 * * \brief  Provide a manager for all orders and quotes.
 * *
 * * \description
 * *       Designed for managing id information for all orders and quotes.
 * */

#include <cstdint>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <queue>

#include <boost/unordered_map.hpp>
#include <boost/smart_ptr.hpp>


#include "XTConfig.h"
#include "XTEnum.pb.h"
#include "LogUtil.h"
#include "EnumUtil.h"
#include "Util.h"
 

namespace XT {




class XT_COMMON_API OrderQuoteMgr {
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	OrderQuoteMgr();

	/**
	* @brief default copy constructor
	*/
	OrderQuoteMgr(const OrderQuoteMgr& from) {} // = delete;

	/**
	* @brief default copy assignment
	*/
	OrderQuoteMgr& operator=(const OrderQuoteMgr& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~OrderQuoteMgr();
	
	///@}
	
public:
	/**
	* @brief get singleton instance
	*
	* @return singleton instance
	*/
	static OrderQuoteMgr* getInstance();

protected:
	std::string s_EmptyString; ///< empty string
	boost::unordered_map<int, int> m_oidToIidMap; ///< map for orderId to Iid
	boost::unordered_map<int, int> m_qidToIidMap; ///< map for Qid to Iid

	boost::unordered_map<int, BrokerApiType::enumtype> m_oidToBrokerApiTypeMap; ///< map for orderId to BrokerApiType
	boost::unordered_map<int, BrokerApiType::enumtype> m_qidToBrokerApiTypeMap; ///< map for qid to BrokerApiType
														 
	int m_ordersSent; ///< number of orders sent
	int m_ordersCxled; ///< number of orders cancelled
	int m_ordersRejected; ///< number of orders rejected
	int m_ordersCxlRejected; ///< number of orders cancel rejected
	
	int m_MaxOrdersSent; ///< max number for orders sent
	int m_MaxOrdersCxled; ///< max number for orders cancelled
	///
	int64_t m_tsSuspendInsertOrder; ///< timestamp for suspending new orders
	int64_t m_tdSuspendInsertOrder; ///< time duration for suspending new orders

	///
	int64_t m_currTs; ///< current timestamp
	int32_t m_currWeekIntTime; ///< current week int time
	int32_t m_currSeqId; ///< current sequence id
	///
	std::queue<std::string> m_sentOrderInfoStrQueue; ///< sent orderinfo string queue
	std::queue<std::string> m_canceledOrderInfoStrQueue;///<  cancelled orderinfo string queue

	///
 

public:
	/**
	* @brief get empty string
	*
	* @return empty string
	*/
	const std::string& getEmptyString();

	/**
	* @brief get oid to iid map
	*
	* @return map for oid to iid
	*/
	 boost::unordered_map<int, int>& oidToIidMap();

	/**
	* @brief add orderId to Iid
	*
	* @param oid as order id
	* @param iid as integer id
	*/
	void addOidIid(int32_t oid, int32_t iid);

	/**
	* @brief get Iid by Oid
	*
	* @param oid as order id
	* 
	* @return integer id
	*/
	int32_t getIidByOid(int32_t oid);

	/**
	* @brief has oid
	*
	* @return if it has order id
	*/
	bool hasOid(int oid);

	/**
	* @brief get quote id to integer id map
	*
	* @return quote id to integer id map
	*/
	boost::unordered_map<int, int>& qidToIidMap();

	/**
	* @brief add quoteId to Iid
	*
	* @param qid as quote id
	* @param iid as integer id
	*/
	void addQidIid(int32_t qid, int32_t iid);

	/**
	* @brief get Iid by Qid
	*
	* @param qid as quote id
	* 
	* @return integer id
	*/
	int32_t getIidByQid(int32_t qid);

	/**
	* @brief add BrokerApiType for order id
	*
	* @param oid as order id
	* @param api as BrokerApiType
	*/
	void addBrokerApiTypeForOid(int oid, BrokerApiType::enumtype api);

	/**
	* @brief get BrokerApiType for order id
	*
	* @param oid as order id
	*/
	BrokerApiType::enumtype getBrokerApiTypeByOid(int oid);

	/**
	* @brief add BrokerApiType for quote id
	*
	* @param qid as quote id
	* @param api as BrokerApiType
	*/
	void addBrokerApiTypeForQid(int qid, BrokerApiType::enumtype api);

	/**
	* @brief get BrokerApiType for quote id
	*
	* @param qid as quote id
	*
	* @return BrokerApitype
	*/
	BrokerApiType::enumtype getBrokerApiTypeByQid(int qid);
	
	/**
	* @brief get number of orders sent
	*
	* @return number of sent orders
	*/
	int getOrdersSent();

	/**
	* @brief set number of orders sent
	*
	* @param v as number of sent orders
	*/
	void setOrdersSent(int v);

	/**
	* @brief increase number of orders cancelled
	*/
	void increaseOrdersSent();

	/**
	* @brief get number of orders rejected
	*
	* @return number of rejected orders
	*/
	int getOrdersRejected();

	/**
	* @brief set number of orders rejected
	*
	* @param v as cancel rejected orders
	*/
	void setOrdersRejected(int v);

	/**
	* @brief increase number of orders rejected
	*/
	void increaseOrdersRejected();


	/**
	* @brief get number of orders cancelled
	*
	* @return number of cancelled orders
	*/
	int getOrdersCxled();

	/**
	* @brief set orders cancelled
	* 
	* @param v as number of cancelled orders
	*/
	void setOrdersCxled(int v);

	/**
	* @brief increase orders cancelled
	*/
	void increaseOrdersCxled();

	/**
	* @brief get number of orders cancel rejected
	*
	* @return number of cancel rejected orders
	*/
	int getOrdersCxlRejected();

	/**
	* @brief set orders cancel rejected
	*
	* @param v as number of cancel rejected orders
	*/
	void setOrdersCxlRejected(int v);

	/**
	* @brief increase orders cancel rejected
	*/
	void increaseOrdersCxlRejected();

	/**
	* @brief get maximum number for order sent
	*
	* @return max number of orders sent
	*/
	int getMaxOrdersSent();

	/**
	* @brief set maximum number for order sent
	*
	* @param v as max number of orders sent
	*/
	void setMaxOrdersSent(int v);

	/**
	* @brief get maximum number for order cancellation
	*
	* @return max number of cancelled orders
	*/
	int getMaxOrdersCxled();

	/**
	* @brief set maximum number for order cancellation
	*
	* @param v as max number
	*/
	void setMaxOrdersCxled(int v);

	/**
	* @brief get time stamp for suspending order insertion
	*
	* @return timestamp
	*/
	int64_t getTsSuspendInsertOrder();

	/**
	* @brief set time stamp for suspending order insertion
	*
	* @param v as timestamp
	*/
	void setTsSuspendInsertOrder(int64_t v);

	/**
	* @brief get time duration for suspending order insertion
	*
	* @return time duration
	*/
	int64_t getTdSuspendInsertOrder();

	/**
	* @brief set time duration for suspending order insertion
	*
	* @param v as time duration
	*/
	void setTdSuspendInsertOrder(int64_t v);


	/**
	* @brief is or not suspending insert order
	*
	* @param ts as timestamp
	*
	* @return if it is suspending
	*/
	bool isSuspendingInsertOrder(int64_t ts);

	/**
	* @brief is or not over traded
	*
	* @return if it is over traded
	*/
	bool isOverTraded();

public:
 
	/**
	* @brief update current timestamp
	*
	* @param ts as current timestamp
	*/
	void updateCurrTs(int64_t ts);


	/**
	* @brief get order id from quote id
	*
	* @param bs as buy sell type
	* @param qid as quoe id
	* 
	* @return order id
	*/
	int32_t getOidFromQid(BuySellType::enumtype bs,int qid) ;

	/**
	* @brief get quote id from order id
	*
	* @param oid as order id
	*
	* @return quote id
	*/
	int32_t getQidFromOid(int oid) ;

	/**
	* @brief get coupled order id
	*
	* @param oid as order id
	* 
	* @return coupled order id
	*/
	int32_t getCoupledOid(int oid) ;

	/**
	* @brief get next order id
	* 
	* @param bs as buy sell type
	*
	* @return next order id
	*/
	int32_t getNextOid(BuySellType::enumtype bs);

	/**
	* @brief get next order id with timestamp
	*
	* @param ts as timestamp
	* @param bs as buy sell type
	*
	* @return next order id
	*/
	int32_t getNextOidWithTs(int64_t ts, BuySellType::enumtype bs);

	/**
	* @brief get next quote id
	*
	* @return next quote id
	*/
	int32_t getNextQid();

	/**
	* @brief get next quote id with timestamp
	*
	* @param ts as timestamp
	*
	* @return next quote id
	*/
	int32_t getNextQidWithTs(int64_t ts);

	/**
	* @brief get BuySellType for Oid
	*
	* @param oid as order id
	*
	* @return buy sell type
	*/
	BuySellType::enumtype getBuySellTypeForOid(int oid);

	////////////////////////////////////////////////////////////////////////
      
	/**
	* @name sent and canceled orderinfos
	*/
	///@{

	/**
	* @brief has sent orderinfo
	*
	* @return if the queue has sent orderinfor or not
	*/
	bool hasSentOrderInfo();

	/**
	* @brief add send orderinfo
	*
	* @param s as protobuf string of orderinfo
	*
	*/
	void addSentOrderInfo(const std::string& s);

	/**
	* @brief get and pop sent orderinfo string
	*
	* @return protobuf string of orderinfo
	*/
	std::string getAndPopSentOrderInfo();
	

	/**
	* @brief has canceled orderinfo
	*
	* @return if the queue has canceled orderinfor or not
	*/
	bool hasCanceledOrderInfo();

	/**
	* @brief add canceled orderinfo
	*
	* @param s as protobuf string of orderinfo
	*
	*/
	void addCanceledOrderInfo(const std::string& s);

	/**
	* @brief get and pop canceled orderinfo string
	*
	* @return protobuf string of orderinfo
	*/
	std::string getAndPopCanceledOrderInfo();

	///@}

	///////////////////////////////////
	/**
	* @brief log summary
	*/
	void logSummary();	

 

}; //class OrderQuoteMgr



} //namespace XT



#endif
