#pragma once
#ifndef XT_MARKET_MANAGER_H
#define XT_MARKET_MANAGER_H

/**
* \file MarketManager.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for market manager.
*
* \description
*	Designed for use for market manager.
*/

#include <cassert>
#include <string>
#include <iostream>
#include <sstream>

#include <cassert>
#include <vector>

#include <unordered_map>

#include "Util.h"
#include "StringUtil.h"

#include "XTHashMap.h"
#include "MarketHandler.h"
#include "XTAllocator.h"
#include "XTPoolMemoryManager.h"




namespace XT
{

	//! Market manager
	/*!
		Market manager is used to manage the market with symbols, orders and order books.

		Automatic orders matching can be enabled with EnableMatching() method or can be
		manually performed with Match() method.

		Not thread-safe.
	*/
	class XT_COMMON_API MarketManager
	{
		friend class XTOrderBook;

	public:
		//! Symbols container
		typedef std::vector<Symbol*> Symbols;
		//! Order books container
		typedef std::vector<XTOrderBook*> OrderBooks;
		//! Orders container
		typedef XT::HashMap<int64_t, OrderNode* > Orders;  //typedef std::unordered_map<int64_t, OrderNode*> Orders;// typedef CppCommon::HashMap<int64_t, OrderNode*, FastHash> Orders;

		MarketManager();
		MarketManager(MarketHandlerPtr market_handler);
		MarketManager(const MarketManager&) = delete;
		MarketManager(MarketManager&&) = delete;
		~MarketManager();

		MarketManager& operator=(const MarketManager&) = delete;
		MarketManager& operator=(MarketManager&&) = delete;

		//! Get the symbols container
		const Symbols& symbols() const noexcept { return _symbols; }
		//! Get the order books container
		const OrderBooks& order_books() const noexcept { return _order_books; }
		//! Get the orders container
		const Orders& orders() const noexcept { return _orders; }

		//! Get the symbol with the given Id
		/*!
			\param id - Symbol Id
			\return Pointer to the symobl with the given Id or nullptr
		*/
		const Symbol* GetSymbol(int id) const noexcept;
		//! Get the order book for the given symbol Id
		/*!
			\param id - Symbol Id of the order book
			\return Pointer to the order book with the given symbol Id or nullptr
		*/
		const XTOrderBook* GetOrderBook(int id) const noexcept;
		//! Get the order with the given Id
		/*!
			\param id - Order Id
			\return Pointer to the order with the given Id or nullptr
		*/
		const XTOrder* GetOrder(int64_t id) const noexcept;

		//! Add a new symbol
		/*!
			\param symbol - Symbol to add
			\return Error code
		*/
		MatchingErrorCode::enumtype AddSymbol(const Symbol& symbol);
		//! Delete the symbol
		/*!
			\param id - Symbol Id
			\return Error code
		*/
		MatchingErrorCode::enumtype DeleteSymbol(int id);

		bool HasInstrId(const std::string& instrid);

		int GetIidForInstrId(const std::string& instrid);

		//! Add a new order book
		/*!
			\param symbol - Symbol of the order book to add
			\return Error code
		*/
		MatchingErrorCode::enumtype AddOrderBook(const Symbol& symbol);
		//! Delete the order book
		/*!
			\param id - Symbol Id of the order book
			\return Error code
		*/
		MatchingErrorCode::enumtype DeleteOrderBook(int id);

		//! Add a new order
		/*!
			\param order - Order to add
			\return Error code
		*/
		MatchingErrorCode::enumtype AddOrder(const XTOrder& order);
		//! Reduce the order by the given quantity
		/*!
			\param id - Order Id
			\param quantity - Order quantity to reduce
			\return Error code
		*/
		MatchingErrorCode::enumtype ReduceOrder(int64_t id, int64_t quantity);
		//! Modify the order
		/*!
			Order new quantity will be calculated in a following way:
			\code{.cpp}
			oder.Quantity = new_quantity;
			oder.LeavesQuantity = new_quantity;
			\endcode

			\param id - Order Id
			\param new_price - Order price to modify
			\param new_quantity - Order quantity to modify
			\return Error code
		*/
		MatchingErrorCode::enumtype ModifyOrder(int64_t id, int64_t new_price, int64_t new_quantity);
		//! Mitigate the order
		/*!
			The in-flight mitigation functionality prevents an order from being filled
			for a quantity greater than the quantity requested by the user. It protects
			from the risk of a resting order being filled between the time an order
			modification is submitted and the time the order modification is processed
			and applied to the order.

			Order new quantity will be calculated in a following way:
			\code{.cpp}
			if (new_quantity > oder.ExecutedQuantity)
			{
				oder.Quantity = new_quantity;
				oder.LeavesQuantity = new_quantity - oder.ExecutedQuantity;

				// Order will be modified...
			}
			else
			{
				oder.Quantity = new_quantity;
				oder.LeavesQuantity = 0;

				// Order will be canceled...
			}
			\endcode

			\param id - Order Id
			\param new_price - Order price to mitigate
			\param new_quantity - Order quantity to mitigate
			\return Error code
		*/
		MatchingErrorCode::enumtype MitigateOrder(int64_t id, int64_t new_price, int64_t new_quantity);
		//! Replace the order with a similar order but different Id, price and quantity
		/*!
			\param id - Order Id
			\param new_id - Order Id to replace
			\param new_price - Order price to replace
			\param new_quantity - Order quantity to replace
			\return Error code
		*/
		MatchingErrorCode::enumtype ReplaceOrder(int64_t id, int64_t new_id, int64_t new_price, int64_t new_quantity);
		//! Replace the order with a new one
		/*!
			\param id - Order Id
			\param new_order - Order to replace
			\return Error code
		*/
		MatchingErrorCode::enumtype ReplaceOrder(int64_t id, const XTOrder& new_order);
		//! Delete the order
		/*!
			\param id - Order Id
			\return Error code
		*/
		MatchingErrorCode::enumtype DeleteOrder(int64_t id);

		std::vector<int64_t> GetOrderIdsEndsWith(int instrid, int ordersuffix);

		void DeleteInstrOrdersWithOrderIdEndsWith(int instrid, int ordersuffix);

		//! Execute the order
		/*!
			\param id - Order Id
			\param quantity - Order executed quantity
			\return Error code
		*/
		MatchingErrorCode::enumtype ExecuteOrder(int64_t id, int64_t quantity);
		//! Execute the order
		/*!
			\param id - Order Id
			\param price - Order executed price
			\param quantity - Order executed quantity
			\return Error code
		*/
		MatchingErrorCode::enumtype ExecuteOrder(int64_t id, int64_t price, int64_t quantity);

		//! Is automatic matching enabled?
		bool IsMatchingEnabled() const noexcept { return _matching; }
		//! Enable automatic matching
		void EnableMatching() { _matching = true; Match(); }
		//! Disable automatic matching
		void DisableMatching() { _matching = false; }

		//! Match crossed orders in all order books
		/*!
			Method will match all crossed orders in each order book. Buy orders will be
			matched with sell orders at arbitrage price starting from the top of the book.
			Matched orders will be executed with deleted form the order book. After the
			matching operation each order book will have the best bid price guarantied
			less than the best ask price!
		*/
		void Match();

	private:
		// Market handler
		static MarketHandlerPtr _default;// static MarketHandler _default;
		MarketHandlerPtr _market_handler;// MarketHandler& _market_handler;

		// Auxiliary memory manager
		XT::DefaultMemoryManager _auxiliary_memory_manager;// CppCommon::DefaultMemoryManager _auxiliary_memory_manager;

		// Bid/Ask price levels
		XT::PoolMemoryManager<XT::DefaultMemoryManager> _level_memory_manager;//  CppCommon::PoolMemoryManager<CppCommon::DefaultMemoryManager> _level_memory_manager;
		XT::PoolAllocator<LevelNode, XT::DefaultMemoryManager> _level_pool;// CppCommon::PoolAllocator<LevelNode, CppCommon::DefaultMemoryManager> _level_pool;

		// Symbols
		XT::PoolMemoryManager<XT::DefaultMemoryManager> _symbol_memory_manager;// CppCommon::PoolMemoryManager<CppCommon::DefaultMemoryManager> _symbol_memory_manager;
		XT::PoolAllocator<Symbol, XT::DefaultMemoryManager> _symbol_pool;// CppCommon::PoolAllocator<Symbol, CppCommon::DefaultMemoryManager> _symbol_pool;
		Symbols _symbols;

		std::unordered_map<std::string, int> m_instridToIidMap;

		// Order books
		XT::PoolMemoryManager< XT::DefaultMemoryManager> _order_book_memory_manager;// CppCommon::PoolMemoryManager<CppCommon::DefaultMemoryManager> _order_book_memory_manager;
		XT::PoolAllocator<XTOrderBook, XT::DefaultMemoryManager> _order_book_pool;// CppCommon::PoolAllocator<OrderBook, CppCommon::DefaultMemoryManager> _order_book_pool;
		OrderBooks _order_books;

		// Orders
		XT::PoolMemoryManager<XT::DefaultMemoryManager> _order_memory_manager;//  CppCommon::PoolMemoryManager<CppCommon::DefaultMemoryManager> _order_memory_manager;
		XT::PoolAllocator<OrderNode, XT::DefaultMemoryManager> _order_pool;// CppCommon::PoolAllocator<OrderNode, CppCommon::DefaultMemoryManager> _order_pool;
		Orders _orders;

		MatchingErrorCode::enumtype AddMarketOrder(const XTOrder& order, bool internal);
		MatchingErrorCode::enumtype AddLimitOrder(const XTOrder& order, bool internal);
		MatchingErrorCode::enumtype AddStopOrder(const XTOrder& order, bool internal);
		MatchingErrorCode::enumtype AddStopLimitOrder(const XTOrder& order, bool internal);
		MatchingErrorCode::enumtype ReduceOrder(int64_t id, int64_t quantity, bool internal);
		MatchingErrorCode::enumtype ModifyOrder(int64_t id, int64_t new_price, int64_t new_quantity, bool mitigate, bool internal);
		MatchingErrorCode::enumtype ReplaceOrder(int64_t id, int64_t new_id, int64_t new_price, int64_t new_quantity, bool internal);
		MatchingErrorCode::enumtype DeleteOrder(int64_t id, bool internal);

		// Matching
		bool _matching;

		void Match(XTOrderBook* order_book_ptr, bool internal);
		void MatchMarket(XTOrderBook* order_book_ptr, XTOrder* order_ptr);
		void MatchLimit(XTOrderBook* order_book_ptr, XTOrder* order_ptr);
		void MatchOrder(XTOrderBook* order_book_ptr, XTOrder* order_ptr);

		bool ActivateStopOrders(XTOrderBook* order_book_ptr);
		bool ActivateStopOrders(XTOrderBook* order_book_ptr, LevelNode* level_ptr, int64_t stop_price);
		bool ActivateStopOrder(XTOrderBook* order_book_ptr, OrderNode* order_ptr);
		bool ActivateStopLimitOrder(XTOrderBook* order_book_ptr, OrderNode* order_ptr);

		int64_t CalculateMatchingChain(XTOrderBook* order_book_ptr, LevelNode* level_ptr, int64_t price, int64_t volume);
		int64_t CalculateMatchingChain(XTOrderBook* order_book_ptr, LevelNode* bid_level_ptr, LevelNode* ask_level_ptr);
		void ExecuteMatchingChain(XTOrderBook* order_book_ptr, LevelNode* level_ptr, int64_t price, int64_t volume);
		void RecalculateTrailingStopPrice(XTOrderBook* order_book_ptr, LevelNode* level_ptr);

		void UpdateLevel(const XTOrderBook& order_book, const LevelUpdate& update) const;
	};

///////////////
  //////typedef for MarketManager

#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<MarketManager> MarketManagerPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<MarketManager> MarketManagerPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<MarketManager> MarketManagerPtr;

#else

	typedef ::boost::shared_ptr<MarketManager> MarketManagerPtr;
#endif


	typedef ::sf::safe_ptr<MarketManager> MarketManagerSafePtr;

	typedef sf::contfree_safe_ptr<MarketManager> MarketManagerContFreePtr;

//////
	inline MarketManager::MarketManager()
		: MarketManager(MarketHandlerPtr(new MarketHandler()))
	{
	}

	inline MarketManager::MarketManager(MarketHandlerPtr market_handler)
		: _market_handler(market_handler),
		_auxiliary_memory_manager(),
		_level_memory_manager(_auxiliary_memory_manager),
		_level_pool(_level_memory_manager),
		_symbol_memory_manager(_auxiliary_memory_manager),
		_symbol_pool(_symbol_memory_manager),
		_order_book_memory_manager(_auxiliary_memory_manager),
		_order_book_pool(_order_book_memory_manager),
		_order_memory_manager(_auxiliary_memory_manager),
		_order_pool(_order_memory_manager),
		_orders(16384, 0),
		_matching(false)
	{

	}

	inline const Symbol* MarketManager::GetSymbol(int id) const noexcept
	{
		return ( id < ((int)(_symbols.size()) ) ? _symbols[id] : nullptr);
	}

	inline const XTOrderBook* MarketManager::GetOrderBook(int id) const noexcept
	{
		return ( id < ((int)(_order_books.size())) ? _order_books[id] : nullptr);
	}

	inline const XTOrder* MarketManager::GetOrder(int64_t id) const noexcept
	{
		assert((id > 0) && "Order Id must be greater than zero!");
		if (id == 0)
			return nullptr;

		auto it = _orders.find(id);
		return ((it != _orders.end()) ? it->second : nullptr);
	}

}//namespace 


#endif
