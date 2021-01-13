#pragma once
#ifndef XT_MYCUTIL_H
#define XT_MYCUTIL_H

/**
* \file MYCUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a manager class for all myc utilities.
*
* \description
*	Designed for managing all myc utilities.
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
#include <boost/unordered_map.hpp>

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
 
#include "MYCData.pb.h"

#include "InstrUtil.h"
#include "PBUtil.h"
#include "ZMQMgr.h"

namespace XT
{

class XT_COMMON_API MYCUtil
{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	MYCUtil() {}

	/**
	* @brief copy constructor
	*/
	MYCUtil(const MYCUtil& from) {} // = delete;

	/**
	* @brief copy assignment
	*/
	MYCUtil& operator=(const MYCUtil& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~MYCUtil() {}

	///@}
protected:
	static const std::string s_EmptyString; ///< empty string

	static boost::unordered_map<int, int64_t> m_oidToMYCOrderIdMap; ///< order id to myc order id map
	static boost::unordered_map<int64_t, int> m_mycOrderIdToOidMap; ///< myc order id to order oid map
	


public:
	/**
	* @brief get empty string
	*
	* @return empty string
	*/
	static const std::string& getEmptyString();  

	/**
	* @brief get next buy order id
	* 
	* @return order id
	*/
	static int getNextBuyOid();

	/**
	* @brief get next sell order id
	*
	* @return order id
	*/
	static int getNextSellOid();

	/**
	* @brief add order id and myc order id
	*
	* @param oid as order id
	* @param mycorderid
	* 
	*/
	static void addOidMYCOrderId(int oid, int64_t mycorderid);

	/**
	* @brief get order id by myc order id
	*
	* @param mycorderid
	*
	* @return order id
	*/
	static int getOidByMYCOrderId(int64_t mycorderid);

	/**
	* @brief get myc order id by order id
	*
	* @param oid as order id
	*
	* @return myc order id
	*/
	static int64_t getMYCOrderIdByOid(int oid);


public:
	/**
	* @brief get exchid for myc_exchange
	*
	* @param exch as myc exchange
	*
	* @return exchange id
	*/
	static std::string getExchIDForMYC_Exchange(int exch);

	/**
	* @brief get exchange type for myc_exchange
	*
	* @param exch as myc exchange
	*
	* @return exchange type
	*/
	static ExchangeType::enumtype getExchangeTypeForMYC_Exchange(int exch);

 

public:
 
	/**
	* @name update functions
	*/
	///@{

	/**
	* @brief update on init
	*
	* @param config_type
	* @param d as MYC_config
	*/
	static void update_on_init(int config_type, const MYC::MYC_config& d);

	/**
	* @brief update on future quote
	*
	* @param d as MYC_future_quote
	* @param intdate as int date
	*/
	static void update_on_future_quote(const MYC::MYC_future_quote& d, int intdate);

	/**
	* @brief update on stock quote
	*
	* @param d as MYC_stock_quote
	*/
	static void update_on_stock_quote(const MYC::MYC_stock_quote& d);

	/**
	* @brief update on response
	*
	* @param d as MYC_response
	*/
	static void update_on_response(const MYC::MYC_response& d);

	/**
	* @brief update on finish
	*
	*/
	static void update_on_session_finish();

	///@}
//////

	/**
	* @brief add myc_contract
	*
	* @param c as MYC_config
	* @param d as MYC_contract
	* @param booklevels
	*/
	static void addMYC_contract(MYC::MYC_config&c, const MYC::MYC_contract& d, int booklevels);
 

public:
	/**
	* @brief add myc_account to MYC_config
	*
	* @param c as MYC_config
	* @param account
	* @param currency
	* @param cash_asset
	* @param cash_available
	* @param exch_rate
	*/
	static void add_account_to_MYC_config(MYC::MYC_config& c, const std::string& account, int currency, 
		double cash_asset,double cash_available, double exch_rate);

	///**
	//* @brief add contract to MYC_config
	//*
	//* @param c as MYC_config
	//* @param symbol
	//* @param exch as exchange
	//* @param max_accum_open_vol
	//* @param max_cancel_limit
	//* @param expiration_date
	//* @param tick_size
	//* @param multiple
	//* @param account
	//* @param yesterday_long_volume
	//* @param yesterday_long_price
	//* @param yesterday_short_volume
	//* @param yesterday_short_price
	//* @param today_long_volume
	//* @param today_long_price
	//* @param today_short_volume
	//* @param today_short_price
	//* @param fee_by_lot
	//* @param exchange_fee
	//* @param yes_exchange_fee
	//* @param broker_fee
	//* @param stamp_tax
	//* @param acc_transfer_fee
	//*/
	//static void add_contract_to_MYC_config(MYC::MYC_config&c,  const std::string& symbol, int exch,
	//	int   max_accum_open_vol, int  max_cancel_limit , 
	//	int expiration_date, double tick_size, double multiple, const std::string& account,
	//	int yesterday_long_volume, double yesterday_long_price, int yesterday_short_volume, double yesterday_short_price,
	//	int today_long_volume,  double today_long_price, int today_short_volume, double today_short_price,
	//	int fee_by_lot, double exchange_fee, double yes_exchange_fee,double broker_fee,double stamp_tax,double acc_transfer_fee
	//	);



public:
	/**
	* @brief get json string for MYC_contract
	*
	* @param m as MYC_contract
	*
	* @return json string
	*/
	static std::string getJsonStrForMYC_contract(const MYC::MYC_contract&  m);
	/**
	* @brief parse json string for MYC_contract
	*
	* @param s as json string
	* @param m as MYC_contract
	*
	* @return if it is parsed successfully
	*/
	static bool parseMYC_contractFromJsonStr(const std::string& s, MYC::MYC_contract&  m);

	/**
	* @brief get json string for MYC_account
	*
	* @param m as MYC_account
	*
	* @return json string
	*/
	static std::string getJsonStrForMYC_account(const MYC::MYC_account & m);
	/**
	* @brief parse json string for MYC_account
	*
	* @param s as json string
	* @param m as MYC_account
	*
	* @return if it is parsed successfully
	*/
	static bool parseMYC_accountFromJsonStr(const std::string& s, MYC::MYC_account& m);

	/**
	* @brief get json string for MYC_config
	*
	* @param m as MYC_config
	*
	* @return json string
	*/
	static std::string getJsonStrForMYC_config(const MYC::MYC_config & m);
	/**
	* @brief parse json string for MYC_config
	*
	* @param s as json string
	* @param m as MYC_config
	*
	* @return if it is parsed successfully
	*/
	static bool parseMYC_configFromJsonStr(const std::string& s, MYC::MYC_config& m);
 
	/**
	* @brief get json string for MYC_future_quote
	*
	* @param m as MYC_future_quote
	*
	* @return json string
	*/
	static std::string getJsonStrForMYC_future_quote(const MYC::MYC_future_quote & m);
	/**
	* @brief parse json string for MYC_future_quote
	*
	* @param s as json string
	* @param m as MYC_future_quote
	*
	* @return if it is parsed successfully
	*/
	static bool parseMYC_future_quoteFromJsonStr(const std::string& s, MYC::MYC_future_quote& m);

	/**
	* @brief get json string for MYC_stock_quote
	*
	* @param m as MYC_stock_quote
	*
	* @return json string
	*/
	static std::string getJsonStrForMYC_stock_quote(const MYC::MYC_stock_quote & m);
	/**
	* @brief parse json string for MYC_stock_quote
	*
	* @param s as json string
	* @param m as MYC_stock_quote
	*
	* @return if it is parsed successfully
	*/
	static bool parseMYC_stock_quoteFromJsonStr(const std::string& s, MYC::MYC_stock_quote& m);

	/**
	* @brief get json string for MYC_response
	*
	* @param m as MYC_response
	*
	* @return json string
	*/
	static std::string getJsonStrForMYC_response(const MYC::MYC_response & m);
	/**
	* @brief parse json string for MYC_response
	*
	* @param s as json string
	* @param m as MYC_response
	*
	* @return if it is parsed successfully
	*/
	static bool parseMYC_responseFromJsonStr(const std::string& s, MYC::MYC_response& m);



};//class


class XT_COMMON_API MYCStrategy
{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	MYCStrategy();

	/**
	* @brief destructor
	*/
	virtual ~MYCStrategy();

	///@}

	/**
	* @brief get config
	*
	* @return config
	*/
	MYC::MYC_config& config();

	/**
	* @brief get current response
	*
	* @return current response
	*/
	MYC::MYC_response& curr_response();

	/**
	* @brief get current stock quote
	*
	* @return current stock quote
	*/
	MYC::MYC_stock_quote& curr_stock_quote();

	/**
	* @brief get current future quote
	*
	* @return current future quote
	*/
	MYC::MYC_future_quote& curr_future_quote();

protected:
	MYC::MYC_config m_config; ///< config
	MYC::MYC_response m_curr_response; ///< current response
	MYC::MYC_stock_quote m_curr_stock_quote; ///< current stock quote
	MYC::MYC_future_quote m_curr_future_quote; ///< current future quote

};
typedef std::shared_ptr<MYCStrategy> MYCStrategyPtr;


}//namespace

#endif