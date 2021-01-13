#pragma once
#ifndef XT_ORDER_MGR_H
#define XT_ORDER_MGR_H

/**
 * * \file OrderMgr.h
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
#include <deque>
#include <unordered_set>
#include <unordered_map>

#include <boost/unordered_map.hpp>
#include <boost/smart_ptr.hpp>

//#include "tbb/concurrent_unordered_map.h"
//#include "tbb/concurrent_queue.h"
//#include "tbb/concurrent_unordered_set.h"
//#include "tbb/concurrent_vector.h"


#include "XTConfig.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "log4z.h"
#include "safe_ptr.h"

#include "EnumUtil.h"
#include "Util.h"
#include "TimeUtil.h"
#include "PBUtil.h"
#include "CfgMgr.h"

#include "XTTimer.h"

#include "OrderQuoteInfo.h" 

namespace XT {




class XT_COMMON_API OrderMgr {
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	OrderMgr();

	/**
	* @brief default copy constructor
	*/
	OrderMgr(const OrderMgr& from) {}// = delete;

	/**
	* @brief default copy assignment
	*/
	OrderMgr& operator=(const OrderMgr& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~OrderMgr();
	
	///@}
	
public:
	/**
	* @brief get singleton instance
	*
	* @return singleton instance
	*/
	static OrderMgr* getInstance();



protected:
	OrderMgrCfgDataPtr m_cfgData;
	OrderMgrDataPtr m_data;

	std::string m_emptyString; ///< empty string


	OrderInfoPtr m_nullOrderInfo; ///< empty OrderInfo
	sf::contfree_safe_ptr<std::unordered_map<int, int> > m_oidToIidMap; ///< map for orderId to Iid
	sf::contfree_safe_ptr<std::unordered_map<int, int> > m_oidToIdxMap; ///< map for orderId to idx
	sf::contfree_safe_ptr<std::vector<OrderInfoPtr > > m_orderInfoPool;
	sf::contfree_safe_ptr<std::deque<int> > m_availableOrderIdxs;


	QuoteInfoPtr m_nullQuoteInfo; ///< null QuoteInfo
//	boost::shared_ptr<OrderQuoteInfo> m_nullOrderQuoteInfo; ///< null OrderQuoteInfo
	sf::contfree_safe_ptr<std::unordered_map<int, int> > m_oidToQidMap; ///< map for oid to qid
	sf::contfree_safe_ptr<std::unordered_map<int, int> > m_qidToIidMap; ///< map for Qid to Iid
	sf::contfree_safe_ptr<std::unordered_map<int, int> > m_qidToIdxMap;///< map for Qid to idx
	sf::contfree_safe_ptr<std::vector<QuoteInfoPtr > > m_quoteInfoPool;
	sf::contfree_safe_ptr<std::deque<int> > m_availableQuoteIdxs;


public:
	/**
	* @brief null OrderInfo
	*
	* @return null OrderInfo
	*/
	OrderInfoPtr& nullOrderInfo();

	/**
	* @brief null QuoteInfo
	*
	* @return null QuoteInfo
	*/
	QuoteInfoPtr& nullQuoteInfo();

protected:
	int64_t m_currTs;
	int m_currIntTime;
	int m_currSeqId;
	int m_currFemasSeqId;

	int m_maxReqPerSec;
	int m_maxFemasReqPerSec;

protected:
	void updateIntTime();
 
	bool hasAvailableOrderInfo();

	bool hasAvailableQuoteInfo();

public:
	/**
	* @brief is oid is orderid for quote
	*
	* @param orderid
	*
	* @return if oid is for quote or not
	*/
	bool isQuoteOid(int oid);

	/**
	* @brief add oid qid 
	*
	* @param oid
	* @param qid
	*/
	void addOidQid(int oid, int qid);


	/**
	* @brief get qid for orderid
	*
	* @param orderid
	*
	* @return qid
	*/
	int getQidForOid(int oid);

	/**
	* @brief has oid
	*
	* @return if it has order id
	*/
	bool hasOid(int oid);

	/**
	* @brief get Iid by Oid
	*
	* @param oid as order id
	*
	* @return integer id
	*/
	int getIidByOid(int oid);

	/**
	* @brief has quoteid
	*
	* @return if it has quote id
	*/
	bool hasQid(int qid);


	/**
	* @brief get Iid by Qid
	*
	* @param qid as quote id
	*
	* @return integer id
	*/
	int getIidByQid(int qid);

	/**
	* @brief get OrderInforPtr for oid
	*
	* @param orderid
	*
	* @return OrderInfoPtr
	*/
	OrderInfoPtr& getOrderInfoForOid(int oid);

	/**
	* @brief get QuoteInforPtr for quote oid
	*
	* @param orderid
	*
	* @return QuoteInfoPtr
	*/
	QuoteInfoPtr& getQuoteInfoForQuoteOid(int oid);

	/**
	* @brief get QuoteInforPtr for qid
	*
	* @param qid
	*
	* @return QuoteInfoPtr
	*/
	QuoteInfoPtr& getQuoteInfoForQid(int qid);

	/**
	* @brief get opensz for oid
	*
	* @param oid
	*
	* @return open sz
	*/
	int64_t getOpenSzForOid(int oid);

	/**
	* @brief get bidopensz for qid
	*
	* @param qid
	*
	* @return bid open sz
	*/
	int64_t getBidOpenSzForQid(int qid);


	/**
	* @brief get askopensz for qid
	*
	* @param qid
	*
	* @return ask open sz
	*/
	int64_t getAskOpenSzForQid(int qid);


///////
	/**
	* @brief get status for oid
	*
	* @param oid
	*
	* @return status
	*/
	int getStatusForOid(int oid);

	/**
	* @brief get status for qid
	*
	* @param oid
	*
	* @return status
	*/
	int getStatusForQid(int qid);

	/**
	* @brief get ocflag for oid
	*
	* @param oid
	*
	* @return ocflag
	*/
	int getOcflagForOid(int oid);

	/**
	* @brief get bid ocflag for qid
	*
	* @param qid
	*
	* @return ocflag
	*/
	int getBidOcflagForQid(int qid);

	/**
	* @brief get ask ocflag for qid
	*
	* @param qid
	*
	* @return ocflag
	*/
	int getAskOcflagForQid(int qid);

	/**
	* @brief get price for oid
	*
	* @param oid
	*
	* @return price
	*/
	double getPxForOid(int oid);

	/**
	* @brief get bid price for qid
	*
	* @param qid
	*
	* @return bid price
	*/
	double getBidPxForQid(int qid);

	/**
	* @brief get ask price for qid
	*
	* @param qid
	*
	* @return ask price
	*/
	double getAskPxForQid(int qid);

	/**
	* @brief get bstype for oid
	*
	* @param oid
	*
	* @return bstype
	*/
	int getBstypeForOid(int oid);

 
	/**
	* @brief get timestamp for oid
	*
	* @param oid
	*/
	int64_t getTsForOid(int oid, int tstype);

	/**
	* @brief get timestamp for qid
	*
	* @param qid
	*/
	int64_t getTsForQid(int qid, int tstype);

	

public:
	/**
	* @brief next OrderInfo
	*
	* @param orderid
	* @param bs as buy sell type
	*
	* @return next OrderInfo
	*/
	OrderInfoPtr& nextOrderInfo(int iid, int oid);

	/**
	* @brief next QuoteInfo
	*
	* @param apitype
	*
	* @return next QuoteInfo
	*/
	QuoteInfoPtr& nextQuoteInfo(int iid, int qid, int bidoid, int askoid);


 
public:
//	/**
//	* get next quote id
//	*/
//	int nextQid();
//
//	/**
//	* get next order id
//	*/
//	int nextOid(BuySellType::enumtype bs);
//
//
//	/**
//	* get order id from quote id
//	* @param bs Buy or Sell
//	* @param qid quote id
//	*/
//	int getOidFromQid(BuySellType::enumtype bs, int qid);
//
//	/**
//	* get quote id from order id
//	* @param oid order id
//	*/
//	int getQidFromOid(int oid);
//
//	/**
//	* get coupled order id for an order id
//	* @param oid order id
//	*/
//	int getCoupledOid(int oid);
////
///**
//* get next quote id
//*/
//	int nextFemasQid();
//
//	/**
//	* get next order id
//	*/
//	int nextFemasOid(BuySellType::enumtype bs);
//
//
//	/**
//	* get order id from quote id
//	* @param bs Buy or Sell
//	* @param qid quote id
//	*/
//	int getFemasOidFromQid(BuySellType::enumtype bs, int qid);
//
//	/**
//	* get quote id from order id
//	* @param oid order id
//	*/
//	int getFemasQidFromOid(int oid);
//
//	/**
//	* get coupled order id for an order id
//	* @param oid order id
//	*/
//	int getFemasCoupledOid(int oid);
//
// //
// /**
// * get next quote id
// */
//	int nextQidByApi(int apitype);
//
//	/**
//	* get next order id
//	*/
//	int nextOidByApi(BuySellType::enumtype bs, int apitype);
//
//
//	/**
//	* get order id from quote id
//	* @param bs Buy or Sell
//	* @param qid quote id
//	*/
//	int getOidFromQidByApi(BuySellType::enumtype bs, int qid, int apitype);
//
//	/**
//	* get quote id from order id
//	* @param oid order id
//	*/
//	int getQidFromOidByApi(int oid, int apitype);
//
//	/**
//	* get coupled order id for an order id
//	* @param oid order id
//	*/
//	int getCoupledOidByApi(int oid, int apitype);
public:
	/**
	* @brief get empty string
	*
	* @return empty string
	*/
	const std::string& getEmptyString();

	///**
	//* @brief get oid to iid map
	//*
	//* @return map for oid to iid
	//*/
	//std::unordered_map<int, int>& oidToIidMap();






	///**
	//* @brief get next OrderInfo
	//*
	//* @param bs as buy sell type
	//* @param apitype
	//*
	//* @return next OrderInfo
	//*/
	//OrderInfoPtr getNextOrderInfo(BuySellType::enumtype bs, int apitype);

	///**
	//* @brief get quote id to integer id map
	//*
	//* @return quote id to integer id map
	//*/
	//std::unordered_map<int, int>& qidToIidMap();




 


	///**
	//* @brief get next QuoteInfo
	//*
	//* @param apitype
	//*
	//* @return next QuoteInfo
	//*/
	//QuoteInfoPtr getNextQuoteInfo(int apitype);

 ////////
	
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
	* @brief json string of OrderInfo
	*
	* @param orderinfo
	*
	* @return json string
	*/
	std::string jsonStrOfOrderInfo(const OrderInfoPtr& orderinfo);


	/**
	* @brief json string of QuoteInfo
	*
	* @param quoteinfo
	*
	* @return json string
	*/
	std::string jsonStrOfQuoteInfo(const QuoteInfoPtr& quoteinfo);
	///////////////////////////////////
	/**
	* @brief log summary
	*/
	void logSummary();	

 

}; //class OrderQuoteMgr



} //namespace XT



#endif
