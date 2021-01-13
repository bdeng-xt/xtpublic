#pragma once
#ifndef XT_MARKET_HANDLER_H
#define XT_MARKET_HANDLER_H

/**
* \file MarketHandler.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for market handler.
*
* \description
*	Designed for use for market handler.
*/

#include <cassert>
#include <string>
#include <iostream>
#include <sstream>
#include "safe_ptr.h"

#include "Level.h"
#include "XTOrder.h"
#include "XTOrderBook.h"



namespace XT
{

	//! Market handler class
	/*!
		Market handler is used to handle all market events from MarketManager
		with a custom actions. Custom implementations of the market handler
		could be used to monitor the following changes in the market:
		\li Add/Remove/Modify symbols
		\li Add/Remove/Modify orders
		\li Order executions
		\li Order book updates

		Not thread-safe.
	*/
	class MarketHandler
	{
		friend class MarketManager;

	public:
		MarketHandler() = default;
		MarketHandler(const MarketHandler&) = delete;
		MarketHandler(MarketHandler&&) = delete;
		virtual ~MarketHandler() = default;

		MarketHandler& operator=(const MarketHandler&) = delete;
		MarketHandler& operator=(MarketHandler&&) = delete;

	protected:
		// Symbol handlers
		virtual void onAddSymbol(const Symbol& symbol) {}
		virtual void onDeleteSymbol(const Symbol& symbol) {}

		// Order book handlers
		virtual void onAddOrderBook(const XTOrderBook& order_book) {}
		virtual void onUpdateOrderBook(const XTOrderBook& order_book, bool top) {}
		virtual void onDeleteOrderBook(const XTOrderBook& order_book) {}

		// Price level handlers
		virtual void onAddLevel(const XTOrderBook& order_book, const Level& level, bool top) {}
		virtual void onUpdateLevel(const XTOrderBook& order_book, const Level& level, bool top) {}
		virtual void onDeleteLevel(const XTOrderBook& order_book, const Level& level, bool top) {}

		// Order handlers
		virtual void onAddOrder(const XTOrder& order) {}
		virtual void onUpdateOrder(const XTOrder& order) {}
		virtual void onDeleteOrder(const XTOrder& order) {}

		// Order execution handlers
		virtual void onExecuteOrder(const XTOrder& order, int64_t price, int64_t quantity) {}
	};//class MarketHandler

////////////
  //////typedef for MarketHandler

#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<MarketHandler> MarketHandlerPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<MarketHandler> MarketHandlerPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<MarketHandler> MarketHandlerPtr;

#else

	typedef ::boost::shared_ptr<MarketHandler> MarketHandlerPtr;
#endif


	typedef ::sf::safe_ptr<MarketHandler> MarketHandlerSafePtr;

	typedef sf::contfree_safe_ptr<MarketHandler> MarketHandlerContFreePtr;

}//namespace 


#endif