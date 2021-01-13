#pragma once
#ifndef XT_MATCHING_ENUMS_H
#define XT_MATCHING_ENUMS_H

/**
* \file MathingEnums.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide enums for matching.
*
* \description
*	Designed for use for matching enums and their utilities.
*/

#include <assert.h>
#include <string>
#include <sstream>
#include <map>

#include "XTConfig.h"

namespace XT
{

class Oid64SuffixType
{
public:
	enum enumtype
	{
		Unknown = 0,
		Buy1 = 1,
		Sell2 = 2,
		Buy3 = 3,
		Sell4 = 4,
		Buy5 = 5,
		Sell6 = 6,
		Buy7 = 7,
		Sell8 = 8

	};

};

	//! Error code
class MatchingErrorCode
{
public:
	enum enumtype
	{
		OK,
		SYMBOL_DUPLICATE,
		SYMBOL_NOT_FOUND,
		ORDER_BOOK_DUPLICATE,
		ORDER_BOOK_NOT_FOUND,
		ORDER_DUPLICATE,
		ORDER_NOT_FOUND,
		ORDER_ID_INVALID,
		ORDER_TYPE_INVALID,
		ORDER_PARAMETER_INVALID,
		ORDER_QUANTITY_INVALID
	};

};

template <class TOutputStream>
inline TOutputStream& operator<<(TOutputStream& stream, MatchingErrorCode::enumtype error)
{
	switch (error)
	{
	case MatchingErrorCode::OK:
		stream << "OK";
		break;
	case MatchingErrorCode::SYMBOL_DUPLICATE:
		stream << "SYMBOL_DUPLICATE";
		break;
	case MatchingErrorCode::SYMBOL_NOT_FOUND:
		stream << "SYMBOL_NOT_FOUND";
		break;
	case MatchingErrorCode::ORDER_BOOK_DUPLICATE:
		stream << "ORDER_BOOK_DUPLICATE";
		break;
	case MatchingErrorCode::ORDER_BOOK_NOT_FOUND:
		stream << "ORDER_BOOK_NOT_FOUND";
		break;
	case MatchingErrorCode::ORDER_DUPLICATE:
		stream << "ORDER_DUPLICATE";
		break;
	case MatchingErrorCode::ORDER_NOT_FOUND:
		stream << "ORDER_NOT_FOUND";
		break;
	case MatchingErrorCode::ORDER_ID_INVALID:
		stream << "ORDER_ID_INVALID";
		break;
	case MatchingErrorCode::ORDER_TYPE_INVALID:
		stream << "ORDER_TYPE_INVALID";
		break;
	case MatchingErrorCode::ORDER_PARAMETER_INVALID:
		stream << "ORDER_PARAMETER_INVALID";
		break;
	case MatchingErrorCode::ORDER_QUANTITY_INVALID:
		stream << "ORDER_QUANTITY_INVALID";
		break;
	default:
		stream << "<unknown>";
		break;
	}
	return stream;
}

class UpdateType
{
public:
	enum enumtype
	{
		LEVEL_NONE,
		LEVEL_ADD,
		LEVEL_UPDATE,
		LEVEL_DELETE
	};

};

class LevelType
{
public:
	enum enumtype
	{
		BID,
		ASK
	};
};
 
template <class TOutputStream>
inline TOutputStream& operator<<(TOutputStream& stream, LevelType type)
{
	switch (type)
	{
	case LevelType::BID:
		stream << "BID";
		break;
	case LevelType::ASK:
		stream << "ASK";
		break;
	default:
		stream << "<unknown>";
		break;
	}
	return stream;
}
//////////////////////

//! Order side
/*!
	Possible values:
	\li <b>Buy</b> -  Buy side is the side of orders made up of investing institutions
		such as mutual funds, pension funds and insurance firms that tend to buy large
		portions of securities for money-management purposes.
	\li <b>Sell</b> - The opposite side to buy made up of investing institutions that
		tend to sell large portions of securities for money-management purposes.
*/
class OrderSide
{
public:
	enum enumtype
	{
		BUY,
		SELL
	};
};
 
template <class TOutputStream>
TOutputStream& operator<<(TOutputStream& stream, OrderSide side)
{
	switch (side)
	{
	case OrderSide::BUY:
		stream << "BUY";
		break;
	case OrderSide::SELL:
		stream << "SELL";
		break;
	default:
		stream << "<unknown>";
		break;
	}
	return stream;
}

//! Order type
/*!
	Possible values:
	\li <b>Market order</b> - A market order is an order to buy or sell a stock at the best
		available price. Generally, this type of order will be executed immediately. However,
		the price at which a market order will be executed is not guaranteed. It is important
		for investors to remember that the last-traded price is not necessarily the price at
		which a market order will be executed. In fast-moving markets, the price at which a
		market order will execute often deviates from the last-traded price or "real time"
		quote.
	\li <b>Limit order</b> - A limit order is an order to buy or sell a stock at a specific
		price or better. A buy limit order can only be executed at the limit price or lower,
		and a sell limit order can only be executed at the limit price or higher. A limit
		order is not guaranteed to execute. A limit order can only be filled if the stock's
		market price reaches the limit price. While limit orders do not guarantee execution,
		they help ensure that an investor does not pay more than a predetermined price for a
		stock.
	\li <b>Stop order</b> - A stop order, also referred to as a stop-loss order, is an order
		to buy or sell a stock once the price of the stock reaches a specified price, known
		as the stop price. When the stop price is reached, a stop order becomes a market order.
		A buy stop order is entered at a stop price above the current market price. Investors
		generally use a buy stop order to limit a loss or to protect a profit on a stock that
		they have sold short. A sell stop order is entered at a stop price below the current
		market price. Investors generally use a sell stop order to limit a loss or to protect
		a profit on a stock that they own.
	\li <b>Stop-limit order</b> - A stop-limit order is an order to buy or sell a stock that
		combines the features of a stop order and a limit order. Once the stop price is reached,
		a stop-limit order becomes a limit order that will be executed at a specified price (or
		better). The benefit of a stop-limit order is that the investor can control the price at
		which the order can be executed.
	\li <b>Trailing stop order</b> - A trailing stop order is entered with a stop parameter
		that creates a moving or trailing activation price, hence the name. This parameter
		is entered as a percentage change or actual specific amount of rise (or fall) in the
		security price. Trailing stop sell orders are used to maximize and protect profit as
		a stock's price rises and limit losses when its price falls.
	\li <b>Trailing stop-limit order</b> - A trailing stop-limit order is similar to a trailing
		stop order. Instead of selling at market price when triggered, the order becomes a limit
		order.
*/

class OrderType
{
public:
	enum enumtype
	{
		MARKET,
		LIMIT,
		STOP,
		STOP_LIMIT,
		TRAILING_STOP,
		TRAILING_STOP_LIMIT
	};
};

 
template <class TOutputStream>
TOutputStream& operator<<(TOutputStream& stream, OrderType type)
{
	switch (type)
	{
	case OrderType::MARKET:
		stream << "MARKET";
		break;
	case OrderType::LIMIT:
		stream << "LIMIT";
		break;
	case OrderType::STOP:
		stream << "STOP";
		break;
	case OrderType::STOP_LIMIT:
		stream << "STOP-LIMIT";
		break;
	case OrderType::TRAILING_STOP:
		stream << "TRAILING-STOP";
		break;
	case OrderType::TRAILING_STOP_LIMIT:
		stream << "TRAILING-STOP-LIMIT";
		break;
	default:
		stream << "<unknown>";
		break;
	}
	return stream;
}

//! Order Time in Force
/*!
	Possible values:
	\li <b>Good-Till-Cancelled (GTC)</b> - A GTC order is an order to buy or sell a stock that
		lasts until the order is completed or cancelled.
	\li <b>Immediate-Or-Cancel (IOC)</b> - An IOC order is an order to buy or sell a stock that
		must be executed immediately. Any portion of the order that cannot be filled immediately
		will be cancelled.
	\li <b>Fill-Or-Kill (FOK)</b> - An FOK order is an order to buy or sell a stock that must
		be executed immediately in its entirety; otherwise, the entire order will be cancelled
		(i.e., no partial execution of the order is allowed).
	\li <b>All-Or-None (AON)</b> - An All-Or-None (AON) order is an order to buy or sell a stock
		that must be executed in its entirety, or not executed at all. AON orders that cannot be
		executed immediately remain active until they are executed or cancelled.
*/
class OrderTimeInForce
{
public:
	enum enumtype
	{
		GTC,    //!< Good-Till-Cancelled
		IOC,    //!< Immediate-Or-Cancel
		FOK,    //!< Fill-Or-Kill
		AON     //!< All-Or-None
	};
};
 
template <class TOutputStream>
TOutputStream& operator<<(TOutputStream& stream, OrderTimeInForce tif)
{
	switch (tif)
	{
	case OrderTimeInForce::GTC:
		stream << "GTC";
		break;
	case OrderTimeInForce::IOC:
		stream << "IOC";
		break;
	case OrderTimeInForce::FOK:
		stream << "FOK";
		break;
	case OrderTimeInForce::AON:
		stream << "AON";
		break;
	default:
		stream << "<unknown>";
		break;
	}
	return stream;
}

 
//////////////////////
 
 
 
 


}//namespace


#endif