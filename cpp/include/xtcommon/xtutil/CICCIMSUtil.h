#pragma once
#ifndef XT_CICCIMSUTIL_H
#define XT_CICCIMSUTIL_H

/**
* \file CICCIMSUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a manager class for CICC IMS utilities.
*
* \description
*	Designed for managing CICC IMS utilities.
*/

#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#include "XTConfig.h"
#include "LogUtil.h"
#include "Util.h"
#include "Instr.h"
#include "InstrMgr.h"
#include "OrderQuoteMgr.h"
#include "RequestMgr.h"

#include "SettingsMgr.h"

 
#include <google/protobuf/util/json_util.h>
#include "XTEnum.pb.h"
#include "XTData.pb.h"
 

#include "PBUtil.h"
#include "ZMQMgr.h"

namespace XT
{

class XT_COMMON_API CICCIMSUtil  
{

public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	CICCIMSUtil() {}

	/**
	* @brief copy constructor
	*/
	CICCIMSUtil(const CICCIMSUtil& from) {}// = delete;

	/**
	* @brief copy assignment
	*/
	CICCIMSUtil& operator=(const CICCIMSUtil& from) { return *this; }// = delete;

	/**
	* @brief destructor
	*/
	virtual ~CICCIMSUtil() {}

	///@}

public:
	/**
	* @brief get order insert string
	*
	* @param mkt as market code
	* @param instrid
	* @param bstype as buy sell type
	* @param speculatortype
	* @param lotoramount as lot or amount
	* @param amount
	* @param ordersz as order size
	* @param pricetype
	* @param price
	* @param currencytype
	* @param remarks
	* 
	* @return order insert string
	*/
	static std::string getOrderInsertStr(const std::string& mkt, const std::string& instrid, const std::string& bstype, const std::string& speculatortype, const std::string& lotoramount, 
		double amount, int ordersz,const std::string& pricetype, double price, const std::string& currencytype,const std::string& remarks );

	/**
	* @brief get order cancel string
	*
	* @param mkt as market code
	* @param instrid
	* @param orderid as order id
	* @param trader
	* @param basketID as basket id
	* @param remarks
	*
	* @return order cancel string
	*/
	static std::string getOrderCancelStr(const std::string& mkt, const std::string& instrid, const std::string& orderid, 
		const std::string& trader, const std::string& basketID, const std::string& remarks);

	
public:
	/**
	* @brief get buy code
	*
	* @return buy code
	*/
	static std::string getBuyCode();
	/**
	* @brief get sell code
	*
	* @return sell code
	*/
	static std::string getSellCode();

	/**
	* @brief get open buy code
	*
	* @return open buy code
	*/
	static std::string getOpenBuyCode();
	/**
	* @brief get open sell code
	*
	* @return open sell code
	*/
	static std::string getOpenSellCode();
	/**
	* @brief get close buy code
	*
	* @return close buy code
	*/
	static std::string getCloseBuyCode();
	/**
	* @brief get close sell code
	*
	* @return close sell code
	*/
	static std::string getCloseSellCode();

	/**
	* @brief get by amount code
	*
	* @return by amount code
	*/
	static std::string getByAmountCode();
	/**
	* @brief get by size code
	*
	* @return by size code
	*/
	static std::string getBySizeCode();

	/**
	* @brief get limit price code
	*
	* @return limit price code
	*/
	static std::string getLimitPriceCode();
	/**
	* @brief get any price code
	*
	* @return any price code
	*/
	static std::string getAnyPriceCode();

	/**
	* @brief get CNY code
	*
	* @return CNY code
	*/
	static std::string getCNYCode();
	/**
	* @brief get USD code
	*
	* @return USD code
	*/
	static std::string getUSDCode();
	/**
	* @brief get HKD code
	*
	* @return HKD code
	*/
	static std::string getHKDCode();

	/**
	* @brief get SSE code
	*
	* @return SSE code
	*/
	static std::string getSSECode();
	/**
	* @brief get SZSE code
	*
	* @return SZSE code
	*/
	static std::string getSZSECode();

	/**
	* @brief get SHHK code
	*
	* @return SHHK code
	*/
	static std::string getSHHKCode();

	/**
	* @brief get DCE code
	*
	* @return DCE code
	*/
	static std::string getDCECode();

	/**
	* @brief get CZCE code
	*
	* @return CZCE code
	*/
	static std::string getCZCECode();

	/**
	* @brief get CFFEX code
	*
	* @return CFFEX code
	*/
	static std::string getCFFEXCode();

	/**
	* @brief get SHFE code
	*
	* @return SHFE code
	*/
	static std::string getSHFECode();

	/**
	* @brief get SZHK code
	*
	* @return SZHK code
	*/
	static std::string getSZHKCode();

	/**
	* @brief get HK code
	*
	* @return HK code
	*/
	static std::string getHKCode();

	/**
	* @brief get HKSH code
	*
	* @return HKSH code
	*/
	static std::string getHKSHCode();

	/**
	* @brief get HKSZ code
	*
	* @return HKSZ code
	*/
	static std::string getHKSZCode();


};	

}//namespace

#endif