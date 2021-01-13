#pragma once
#ifndef XT_ORDER_QUOTE_INFO_H
#define XT_ORDER_QUOTE_INFO_H

/**
 * * \file OrderQuoteInfo.h
 * *
 * * \author Bin Deng (bdeng@xtal-tech.com)
 * *
 * * \brief  Provide a class for two side quote.
 * *
 * * \description
 * *       Designed for two side quote.
 * */

#include <cstdint>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>

#include <boost/unordered_map.hpp>
#include <boost/smart_ptr.hpp>

#include "safe_ptr.h"

#include "XTConfig.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"
#include "LogUtil.h"
#include "EnumUtil.h"
#include "Util.h"
#include "CfgMgr.h"

 namespace XT
 {


class XT_COMMON_API OrderQuoteInfo
{
public:
	OrderQuoteInfo();

	/**
	* @brief default copy constructor
	*/
	OrderQuoteInfo(const OrderQuoteInfo& from);// = default;

	/**
	* @brief default copy assignment
	*/
	OrderQuoteInfo& operator=(const OrderQuoteInfo& from);// = default;

	virtual ~OrderQuoteInfo();

public:
	OrderInfoPtr& bidOrderInfo();
	OrderInfoPtr& askOrderInfo();
	QuoteInfoPtr& quoteInfo();

protected:
	OrderInfoPtr m_bidOrderInfo;
	OrderInfoPtr m_askOrderInfo;
	QuoteInfoPtr m_quoteInfo;

};

//////typedef for OrderQuoteInfo
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<OrderQuoteInfo> OrderQuoteInfoPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<OrderQuoteInfo> OrderQuoteInfoPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<OrderQuoteInfo> OrderQuoteInfoPtr;

#else

typedef ::boost::shared_ptr<OrderQuoteInfo> OrderQuoteInfoPtr;
#endif


typedef ::sf::safe_ptr<OrderQuoteInfo> OrderQuoteInfoSafePtr;

typedef sf::contfree_safe_ptr<OrderQuoteInfo> OrderQuoteInfoContFreePtr;
//////end typedef for OrderQuoteInfo

 }//namespace

#endif