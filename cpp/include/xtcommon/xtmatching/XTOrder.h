#pragma once
#ifndef XT_ORDER_H
#define XT_ORDER_H

/**
* \file Order.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for book order.
*
* \description
*	Designed for use for book order.
*/

#include <cassert>
#include <string>
//#include <cstdint>
#include <stdint.h>
#include <sstream>
#include <map>

#include <algorithm>
#include <cstdint>
#include <limits>

//#include <boost/intrusive/list.hpp>
//#include <boost/intrusive/avltree.hpp>
//#include <boost/intrusive/avltree_algorithms.hpp>

#include "XTConfig.h"
#include "XTList.h"
#include "MatchingEnums.h"
namespace XT
{

	//! Order
	/*!
		An order is an instruction to buy or sell on a trading venue such as a stock market,
		bond market, commodity market, or financial derivative market. These instructions can
		be simple or complicated, and can be sent to either a broker or directly to a trading
		venue via direct market access.
	*/
	class XT_COMMON_API XTOrder
	{
	public:
		//! Order Id
		int64_t Id;
		//! Symbol Id
		uint32_t SymbolId;
		//! Order type
		OrderType::enumtype Type;
		//! Order side
		OrderSide::enumtype Side;
		//! Order price
		int64_t Price;
		//! Order stop price
		int64_t StopPrice;

		//! Order quantity
		int64_t Quantity;
		//! Order executed quantity
		int64_t ExecutedQuantity;
		//! Order leaves quantity
		int64_t LeavesQuantity;

		//! Time in Force
		OrderTimeInForce::enumtype TimeInForce;

		//! Order max visible quantity
		/*!
			This property allows to prepare 'iceberg'/'hidden' orders with the
			following rules:
			\li <b>MaxVisibleQuantity >= LeavesQuantity</b> - Regular order
			\li <b>MaxVisibleQuantity == 0</b> - 'Hidden' order
			\li <b>MaxVisibleQuantity < LeavesQuantity</b> - 'Iceberg' order

			Supported only for limit and stop-limit orders!
		*/
		int64_t MaxVisibleQuantity;
		//! Order hidden quantity
		int64_t HiddenQuantity() const noexcept { return (LeavesQuantity > MaxVisibleQuantity) ? (LeavesQuantity - MaxVisibleQuantity) : 0; }
		//! Order visible quantity
		int64_t VisibleQuantity() const noexcept { return std::min(LeavesQuantity, MaxVisibleQuantity); }

		//! Market order slippage
		/*!
			Slippage is useful to protect market order from executions at prices
			which are too far from the best price. If the slippage is provided
			for market order its execution will be stopped when the price run
			out of the market for the given slippage value. Zero slippage will
			allow to execute market order only at the best price, non executed
			part of the market order will be canceled.

			Supported only for market and stop orders!
		*/
		int64_t Slippage;

		//! Order trailing distance to market
		/*!
			Positive value represents absolute distance from the market.
			Negative value represents percentage distance from the market
			with 0.01% precision (-1 means 0.01, -10000 means 100%).

			Supported only for trailing stop orders!
		*/
		int64_t TrailingDistance;
		//! Order trailing step
		/*!
			Positive value represents absolute step from the market.
			Negative value represents percentage step from the market
			with 0.01% precision (-1 means 0.01%, -10000 means 100%).

			Supported only for trailing stop orders!
		*/
		int64_t TrailingStep;

		XTOrder() noexcept = default;
		XTOrder(int64_t id, uint32_t symbol, OrderType::enumtype type, OrderSide::enumtype side, int64_t price, int64_t stop_price, int64_t quantity,
			OrderTimeInForce::enumtype tif = OrderTimeInForce::GTC,
			int64_t max_visible_quantity = std::numeric_limits<int64_t>::max(),
			int64_t slippage = std::numeric_limits<int64_t>::max(),
			int64_t trailing_distance = 0,
			int64_t trailing_step = 0) noexcept;
		XTOrder(const XTOrder&) noexcept = default;
		XTOrder(XTOrder&&) noexcept = default;
		~XTOrder() noexcept = default;

		XTOrder& operator=(const XTOrder&) noexcept = default;
		XTOrder& operator=(XTOrder&&) noexcept = default;

		template <class TOutputStream>
		friend TOutputStream& operator<<(TOutputStream& stream, const XTOrder& order);

		//! Is the market order?
		bool IsMarket() const noexcept { return Type == OrderType::MARKET; }
		//! Is the limit order?
		bool IsLimit() const noexcept { return Type == OrderType::LIMIT; }
		//! Is the stop order?
		bool IsStop() const noexcept { return Type == OrderType::STOP; }
		//! Is the stop-limit order?
		bool IsStopLimit() const noexcept { return Type == OrderType::STOP_LIMIT; }
		//! Is the trailing stop order?
		bool IsTrailingStop() const noexcept { return Type == OrderType::TRAILING_STOP; }
		//! Is the trailing stop-limit order?
		bool IsTrailingStopLimit() const noexcept { return Type == OrderType::TRAILING_STOP_LIMIT; }

		//! Is the order with buy side?
		bool IsBuy() const noexcept { return Side == OrderSide::BUY; }
		//! Is the order with sell side?
		bool IsSell() const noexcept { return Side == OrderSide::SELL; }

		//! Is the 'Good-Till-Cancelled' order?
		bool IsGTC() const noexcept { return TimeInForce == OrderTimeInForce::GTC; }
		//! Is the 'Immediate-Or-Cancel' order?
		bool IsIOC() const noexcept { return TimeInForce == OrderTimeInForce::IOC; }
		//! Is the 'Fill-Or-Kill' order?
		bool IsFOK() const noexcept { return TimeInForce == OrderTimeInForce::FOK; }
		//! Is the 'All-Or-None' order?
		bool IsAON() const noexcept { return TimeInForce == OrderTimeInForce::AON; }

		//! Is the 'Hidden' order?
		bool IsHidden() const noexcept { return MaxVisibleQuantity == 0; }
		//! Is the 'Iceberg' order?
		bool IsIceberg() const noexcept { return MaxVisibleQuantity < std::numeric_limits<int64_t>::max(); }

		//! Is the order have slippage?
		bool IsSlippage() const noexcept { return Slippage < std::numeric_limits<int64_t>::max(); }

		//! Validate order parameters
		MatchingErrorCode::enumtype Validate() const noexcept;

		//! Prepare a new market order
		static XTOrder Market(int64_t id, uint32_t symbol, OrderSide::enumtype side, int64_t quantity, int64_t slippage = std::numeric_limits<int64_t>::max()) noexcept;
		//! Prepare a new buy market order
		static XTOrder BuyMarket(int64_t id, uint32_t symbol, int64_t quantity, int64_t slippage = std::numeric_limits<int64_t>::max()) noexcept;
		//! Prepare a new sell market order
		static XTOrder SellMarket(int64_t id, uint32_t symbol, int64_t quantity, int64_t slippage = std::numeric_limits<int64_t>::max()) noexcept;

		//! Prepare a new limit order
		static XTOrder Limit(int64_t id, uint32_t symbol, OrderSide::enumtype side, int64_t price, int64_t quantity, OrderTimeInForce::enumtype tif = OrderTimeInForce::GTC, int64_t max_visible_quantity = std::numeric_limits<int64_t>::max()) noexcept;
		//! Prepare a new buy limit order
		static XTOrder BuyLimit(int64_t id, uint32_t symbol, int64_t price, int64_t quantity, OrderTimeInForce::enumtype tif = OrderTimeInForce::GTC, int64_t max_visible_quantity = std::numeric_limits<int64_t>::max()) noexcept;
		//! Prepare a new sell limit order
		static XTOrder SellLimit(int64_t id, uint32_t symbol, int64_t price, int64_t quantity, OrderTimeInForce::enumtype tif = OrderTimeInForce::GTC, int64_t max_visible_quantity = std::numeric_limits<int64_t>::max()) noexcept;

		//! Prepare a new stop order
		static XTOrder Stop(int64_t id, uint32_t symbol, OrderSide::enumtype side, int64_t stop_price, int64_t quantity, OrderTimeInForce::enumtype tif = OrderTimeInForce::GTC, int64_t slippage = std::numeric_limits<int64_t>::max()) noexcept;
		//! Prepare a new buy stop order
		static XTOrder BuyStop(int64_t id, uint32_t symbol, int64_t stop_price, int64_t quantity, OrderTimeInForce::enumtype tif = OrderTimeInForce::GTC, int64_t slippage = std::numeric_limits<int64_t>::max()) noexcept;
		//! Prepare a new sell stop order
		static XTOrder SellStop(int64_t id, uint32_t symbol, int64_t stop_price, int64_t quantity, OrderTimeInForce::enumtype tif = OrderTimeInForce::GTC, int64_t slippage = std::numeric_limits<int64_t>::max()) noexcept;

		//! Prepare a new stop-limit order
		static XTOrder StopLimit(int64_t id, uint32_t symbol, OrderSide::enumtype side, int64_t stop_price, int64_t price, int64_t quantity, OrderTimeInForce::enumtype tif = OrderTimeInForce::GTC, int64_t max_visible_quantity = std::numeric_limits<int64_t>::max()) noexcept;
		//! Prepare a new buy stop-limit order
		static XTOrder BuyStopLimit(int64_t id, uint32_t symbol, int64_t stop_price, int64_t price, int64_t quantity, OrderTimeInForce::enumtype tif = OrderTimeInForce::GTC, int64_t max_visible_quantity = std::numeric_limits<int64_t>::max()) noexcept;
		//! Prepare a new sell stop-limit order
		static XTOrder SellStopLimit(int64_t id, uint32_t symbol, int64_t stop_price, int64_t price, int64_t quantity, OrderTimeInForce::enumtype tif = OrderTimeInForce::GTC, int64_t max_visible_quantity = std::numeric_limits<int64_t>::max()) noexcept;

		//! Prepare a new trailing stop order
		static XTOrder TrailingStop(int64_t id, uint32_t symbol, OrderSide::enumtype side, int64_t stop_price, int64_t quantity, int64_t trailing_distance, int64_t trailing_step = 0, OrderTimeInForce::enumtype tif = OrderTimeInForce::GTC, int64_t slippage = std::numeric_limits<int64_t>::max()) noexcept;
		//! Prepare a new trailing buy stop order
		static XTOrder TrailingBuyStop(int64_t id, uint32_t symbol, int64_t stop_price, int64_t quantity, int64_t trailing_distance, int64_t trailing_step = 0, OrderTimeInForce::enumtype tif = OrderTimeInForce::GTC, int64_t slippage = std::numeric_limits<int64_t>::max()) noexcept;
		//! Prepare a new trailing sell stop order
		static XTOrder TrailingSellStop(int64_t id, uint32_t symbol, int64_t stop_price, int64_t quantity, int64_t trailing_distance, int64_t trailing_step = 0, OrderTimeInForce::enumtype tif = OrderTimeInForce::GTC, int64_t slippage = std::numeric_limits<int64_t>::max()) noexcept;

		//! Prepare a new trailing stop-limit order
		static XTOrder TrailingStopLimit(int64_t id, uint32_t symbol, OrderSide::enumtype side, int64_t stop_price, int64_t price, int64_t quantity, int64_t trailing_distance, int64_t trailing_step = 0, OrderTimeInForce::enumtype tif = OrderTimeInForce::GTC, int64_t max_visible_quantity = std::numeric_limits<int64_t>::max()) noexcept;
		//! Prepare a new trailing buy stop-limit order
		static XTOrder TrailingBuyStopLimit(int64_t id, uint32_t symbol, int64_t stop_price, int64_t price, int64_t quantity, int64_t trailing_distance, int64_t trailing_step = 0, OrderTimeInForce::enumtype tif = OrderTimeInForce::GTC, int64_t max_visible_quantity = std::numeric_limits<int64_t>::max()) noexcept;
		//! Prepare a new trailing sell stop-limit order
		static XTOrder TrailingSellStopLimit(int64_t id, uint32_t symbol, int64_t stop_price, int64_t price, int64_t quantity, int64_t trailing_distance, int64_t trailing_step = 0, OrderTimeInForce::enumtype tif = OrderTimeInForce::GTC, int64_t max_visible_quantity = std::numeric_limits<int64_t>::max()) noexcept;
	};

	template <class TOutputStream>
	inline TOutputStream& operator<<(TOutputStream& stream, const XTOrder& order)
	{
		stream << "Order(Id=" << order.Id
			<< "; SymbolId=" << order.SymbolId
			<< "; Type=" << order.Type
			<< "; Side=" << order.Side
			<< "; Price=" << order.Price
			<< "; StopPrice=" << order.StopPrice
			<< "; Quantity=" << order.Quantity
			<< "; ExecutedQuantity=" << order.ExecutedQuantity
			<< "; LeavesQuantity=" << order.LeavesQuantity
			<< "; " << order.TimeInForce;
		if (order.IsTrailingStop() || order.IsTrailingStopLimit())
		{
			stream << "; TrailingDistance=" << order.TrailingDistance;
			stream << "; TrailingStep=" << order.TrailingStep;
		}
		if (order.IsHidden() || order.IsIceberg())
			stream << "; MaxVisibleQuantity=" << order.MaxVisibleQuantity;
		if (order.IsSlippage())
			stream << "; Slippage=" << order.Slippage;
		stream << ")";
		return stream;
	}

	struct LevelNode;

	//! Order node
	struct OrderNode : public XTOrder, public XT::List<OrderNode>::Node // public Order, public boost::intrusive::list_base_hook<>// public CppCommon::List<OrderNode>::Node
	{
		LevelNode* Level;

		OrderNode(const XTOrder& order) noexcept;
		OrderNode(const OrderNode&) noexcept = default;
		OrderNode(OrderNode&&) noexcept = default;
		~OrderNode() noexcept = default;

		OrderNode& operator=(const XTOrder& order) noexcept;
		OrderNode& operator=(const OrderNode&) noexcept = default;
		OrderNode& operator=(OrderNode&&) noexcept = default;
	};

}//namespace


#endif