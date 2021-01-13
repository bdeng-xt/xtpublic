#pragma once
#ifndef XT_ORDER_BOOK_H
#define XT_ORDER_BOOK_H

/**
* \file XTOrderBook.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for order book.
*
* \description
*	Designed for use for order book.
*/

#include <cassert>
#include <string>
#include <iostream>
#include <sstream>

//#include <boost/intrusive/avltree.hpp>
//#include <boost/intrusive/avltree_algorithms.hpp>

#include "XTConfig.h"

#include "XTBinTreeAVL.h"
#include "MatchingEnums.h"
#include "Level.h"
#include "Symbol.h"
#include "XTPoolMemoryManager.h"

namespace XT
{

	class MarketManager;

	//! Order book
	/*!
		Order book is used to keep buy and sell orders in a price level order.

		Not thread-safe.
	*/
	class XT_COMMON_API XTOrderBook
	{
		friend class MarketManager;

	public:
		//! Price level container
		typedef XT::BinTreeAVL<LevelNode, std::less<LevelNode>> Levels; //typedef boost::intrusive::avltree<LevelNode> Levels;// typedef CppCommon::BinTreeAVL<LevelNode, std::less<LevelNode>> Levels;

		XTOrderBook(MarketManager& manager, const Symbol& symbol);
		XTOrderBook(const XTOrderBook&) = delete;
		XTOrderBook(XTOrderBook&&) = delete;
		~XTOrderBook();

		XTOrderBook& operator=(const XTOrderBook&) = delete;
		XTOrderBook& operator=(XTOrderBook&&) = delete;

		//! Check if the order book is not empty
		explicit operator bool() const noexcept { return !empty(); }

		//! Is the order book empty?
		bool empty() const noexcept { return size() == 0; }

		//! Get the order book size
		size_t size() const noexcept { return _bids.size() + _asks.size() + _buy_stop.size() + _sell_stop.size() + _trailing_buy_stop.size() + _trailing_sell_stop.size(); }

		//! Get the order book symbol
		const Symbol& symbol() const noexcept { return _symbol; }

		//! Get the order book best bid price level
		const LevelNode* best_bid() const noexcept { return _best_bid; }
		//! Get the order book best ask price level
		const LevelNode* best_ask() const noexcept { return _best_ask; }

		//! Get the order book bids container
		const Levels& bids() const noexcept { return _bids; }
		//! Get the order book asks container
		const Levels& asks() const noexcept { return _asks; }

		//! Get the order book best buy stop order price level
		const LevelNode* best_buy_stop() const noexcept { return _best_buy_stop; }
		//! Get the order book best sell stop order price level
		const LevelNode* best_sell_stop() const noexcept { return _best_sell_stop; }

		//! Get the order book buy stop orders container
		const Levels& buy_stop() const noexcept { return _buy_stop; }
		//! Get the order book sell stop orders container
		const Levels& sell_stop() const noexcept { return _sell_stop; }

		//! Get the order book best trailing buy stop order price level
		const LevelNode* best_trailing_buy_stop() const noexcept { return _best_trailing_buy_stop; }
		//! Get the order book best trailing sell stop order price level
		const LevelNode* best_trailing_sell_stop() const noexcept { return _best_trailing_sell_stop; }

		//! Get the order book trailing buy stop orders container
		const Levels& trailing_buy_stop() const noexcept { return _trailing_buy_stop; }
		//! Get the order book trailing sell stop orders container
		const Levels& trailing_sell_stop() const noexcept { return _trailing_sell_stop; }

		template <class TOutputStream>
		friend TOutputStream& operator<<(TOutputStream& stream, const XTOrderBook& order_book);

		//! Get the order book bid price level with the given price
		/*!
			\param price - Price
			\return Pointer to the order book bid price level with the given price or nullptr
		*/
		const LevelNode* GetBid(int64_t price) const noexcept;
		//! Get the order book ask price level with the given price
		/*!
			\param price - Price
			\return Pointer to the order book ask price level with the given price or nullptr
		*/
		const LevelNode* GetAsk(int64_t price) const noexcept;

		//! Get the order book buy stop level with the given price
		/*!
			\param price - Price
			\return Pointer to the order book buy stop level with the given price or nullptr
		*/
		const LevelNode* GetBuyStopLevel(int64_t price) const noexcept;
		//! Get the order book sell stop level with the given price
		/*!
			\param price - Price
			\return Pointer to the order book sell stop level with the given price or nullptr
		*/
		const LevelNode* GetSellStopLevel(int64_t price) const noexcept;

		//! Get the order book trailing buy stop level with the given price
		/*!
			\param price - Price
			\return Pointer to the order book trailing buy stop level with the given price or nullptr
		*/
		const LevelNode* GetTrailingBuyStopLevel(int64_t price) const noexcept;
		//! Get the order book trailing sell stop level with the given price
		/*!
			\param price - Price
			\return Pointer to the order book trailing sell stop level with the given price or nullptr
		*/
		const LevelNode* GetTrailingSellStopLevel(int64_t price) const noexcept;

	private:
		// Market manager
		MarketManager& _manager;

		// Order book symbol
		Symbol _symbol;

		// Bid/Ask price levels
		LevelNode* _best_bid;
		LevelNode* _best_ask;
		Levels _bids;
		Levels _asks;

		// Price level management
		LevelNode* GetNextLevel(LevelNode* level) noexcept;
		LevelNode* AddLevel(OrderNode* order_ptr);
		LevelNode* DeleteLevel(OrderNode* order_ptr);

		// Orders management
		LevelUpdate AddOrder(OrderNode* order_ptr);
		LevelUpdate ReduceOrder(OrderNode* order_ptr, int64_t quantity, int64_t hidden, int64_t visible);
		LevelUpdate DeleteOrder(OrderNode* order_ptr);

		// Buy/Sell stop orders levels
		LevelNode* _best_buy_stop;
		LevelNode* _best_sell_stop;
		Levels _buy_stop;
		Levels _sell_stop;

		// Stop orders price level management
		LevelNode* GetNextStopLevel(LevelNode* level) noexcept;
		LevelNode* AddStopLevel(OrderNode* order_ptr);
		LevelNode* DeleteStopLevel(OrderNode* order_ptr);

		// Stop orders management
		void AddStopOrder(OrderNode* order_ptr);
		void ReduceStopOrder(OrderNode* order_ptr, int64_t quantity, int64_t hidden, int64_t visible);
		void DeleteStopOrder(OrderNode* order_ptr);

		// Buy/Sell trailing stop orders levels
		LevelNode* _best_trailing_buy_stop;
		LevelNode* _best_trailing_sell_stop;
		Levels _trailing_buy_stop;
		Levels _trailing_sell_stop;

		// Trailing stop orders price level management
		LevelNode* GetNextTrailingStopLevel(LevelNode* level) noexcept;
		LevelNode* AddTrailingStopLevel(OrderNode* order_ptr);
		LevelNode* DeleteTrailingStopLevel(OrderNode* order_ptr);

		// Trailing stop orders management
		void AddTrailingStopOrder(OrderNode* order_ptr);
		void ReduceTrailingStopOrder(OrderNode* order_ptr, int64_t quantity, int64_t hidden, int64_t visible);
		void DeleteTrailingStopOrder(OrderNode* order_ptr);

		// Trailing stop price calculation
		int64_t CalculateTrailingStopPrice(const XTOrder& order) const noexcept;

		// Market last and trailing prices
		int64_t _last_bid_price;
		int64_t _last_ask_price;
		int64_t _matching_bid_price;
		int64_t _matching_ask_price;
		int64_t _trailing_bid_price;
		int64_t _trailing_ask_price;

		// Update market last prices
		int64_t GetMarketPriceBid() const noexcept;
		int64_t GetMarketPriceAsk() const noexcept;
		int64_t GetMarketTrailingStopPriceBid() const noexcept;
		int64_t GetMarketTrailingStopPriceAsk() const noexcept;
		void UpdateLastPrice(const XTOrder& order, int64_t price) noexcept;
		void UpdateMatchingPrice(const XTOrder& order, int64_t price) noexcept;
		void ResetMatchingPrice() noexcept;
	};

//////
	template <class TOutputStream>
	inline TOutputStream& operator<<(TOutputStream& stream, const XTOrderBook& order_book)
	{
		stream << "OrderBook(Symbol=" << order_book._symbol
			<< "; Bids=" << order_book._bids.size()
			<< "; Asks=" << order_book._asks.size()
			<< "; BuyStop=" << order_book._buy_stop.size()
			<< "; SellStop=" << order_book._sell_stop.size()
			<< "; TrailingBuyStop=" << order_book._trailing_buy_stop.size()
			<< "; TrailingSellStop=" << order_book._trailing_sell_stop.size()
			<< ")";
		return stream;
	}

	inline const LevelNode* XTOrderBook::GetBid(int64_t price) const noexcept
	{
		auto it = _bids.find(LevelNode(LevelType::BID, price));
		return (it != _bids.end()) ? it.operator->() : nullptr;
	}

	inline const LevelNode* XTOrderBook::GetAsk(int64_t price) const noexcept
	{
		auto it = _asks.find(LevelNode(LevelType::ASK, price));
		return (it != _asks.end()) ? it.operator->() : nullptr;
	}

	inline const LevelNode* XTOrderBook::GetBuyStopLevel(int64_t price) const noexcept
	{
		auto it = _buy_stop.find(LevelNode(LevelType::ASK, price));
		return (it != _buy_stop.end()) ? it.operator->() : nullptr;
	}

	inline const LevelNode* XTOrderBook::GetSellStopLevel(int64_t price) const noexcept
	{
		auto it = _sell_stop.find(LevelNode(LevelType::BID, price));
		return (it != _sell_stop.end()) ? it.operator->() : nullptr;
	}

	inline const LevelNode* XTOrderBook::GetTrailingBuyStopLevel(int64_t price) const noexcept
	{
		auto it = _trailing_buy_stop.find(LevelNode(LevelType::ASK, price));
		return (it != _trailing_buy_stop.end()) ? it.operator->() : nullptr;
	}

	inline const LevelNode* XTOrderBook::GetTrailingSellStopLevel(int64_t price) const noexcept
	{
		auto it = _trailing_sell_stop.find(LevelNode(LevelType::BID, price));
		return (it != _trailing_sell_stop.end()) ? it.operator->() : nullptr;
	}

	inline LevelNode* XTOrderBook::GetNextLevel(LevelNode* level) noexcept
	{
		if (level->IsBid())
		{
			Levels::reverse_iterator it(&_bids, level);
			++it;
			return it.operator->();
		}
		else
		{
			Levels::iterator it(&_asks, level);
			++it;
			return it.operator->();
		}
	}

	inline LevelNode* XTOrderBook::GetNextStopLevel(LevelNode* level) noexcept
	{
		if (level->IsBid())
		{
			Levels::reverse_iterator it(&_sell_stop, level);
			++it;
			return it.operator->();
		}
		else
		{
			Levels::iterator it(&_buy_stop, level);
			++it;
			return it.operator->();
		}
	}

	inline LevelNode* XTOrderBook::GetNextTrailingStopLevel(LevelNode* level) noexcept
	{
		if (level->IsBid())
		{
			Levels::reverse_iterator it(&_trailing_sell_stop, level);
			++it;
			return it.operator->();
		}
		else
		{
			Levels::iterator it(&_trailing_buy_stop, level);
			++it;
			return it.operator->();
		}
	}

	inline int64_t XTOrderBook::GetMarketPriceBid() const noexcept
	{
		int64_t matching_price = _matching_bid_price;
		int64_t best_price = (_best_bid != nullptr) ? _best_bid->Price : 0;
		return std::max(matching_price, best_price);
	}

	inline int64_t XTOrderBook::GetMarketPriceAsk() const noexcept
	{
		int64_t matching_price = _matching_ask_price;
		int64_t best_price = (_best_ask != nullptr) ? _best_ask->Price : std::numeric_limits<int64_t>::max();
		return std::min(matching_price, best_price);
	}

	inline int64_t XTOrderBook::GetMarketTrailingStopPriceBid() const noexcept
	{
		int64_t last_price = _last_bid_price;
		int64_t best_price = (_best_bid != nullptr) ? _best_bid->Price : 0;
		return std::min(last_price, best_price);
	}

	inline int64_t XTOrderBook::GetMarketTrailingStopPriceAsk() const noexcept
	{
		int64_t last_price = _last_ask_price;
		int64_t best_price = (_best_ask != nullptr) ? _best_ask->Price : std::numeric_limits<int64_t>::max();
		return std::max(last_price, best_price);
	}

	inline void XTOrderBook::UpdateLastPrice(const XTOrder& order, int64_t price) noexcept
	{
		if (order.IsBuy())
			_last_bid_price = price;
		else
			_last_ask_price = price;
	}

	inline void XTOrderBook::UpdateMatchingPrice(const XTOrder& order, int64_t price) noexcept
	{
		if (order.IsBuy())
			_matching_bid_price = price;
		else
			_matching_ask_price = price;
	}

	inline void XTOrderBook::ResetMatchingPrice() noexcept
	{
		_matching_bid_price = 0;
		_matching_ask_price = std::numeric_limits<int64_t>::max();
	}


}//namespace 


#endif