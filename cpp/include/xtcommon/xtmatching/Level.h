#pragma once
#ifndef XT_LEVEL_H
#define XT_LEVEL_H

/**
* \file Level.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for book level.
*
* \description
*	Designed for use for book level.
*/

#include <assert.h>
#include <string>
#include <sstream>
#include <map>

//#include <boost/intrusive/list.hpp>
//#include <boost/intrusive/avltree.hpp>
//#include <boost/intrusive/avltree_algorithms.hpp>

#include "XTConfig.h"

#include "XTBinTree.h"
#include "XTBinTreeAVL.h"

#include "MatchingEnums.h"
#include "XTOrder.h"


namespace XT
{

	//! Price level
	class Level
	{
	public:
		//! Level type
		LevelType::enumtype Type;
		//! Level price
		uint64_t Price;
		//! Level volume
		uint64_t TotalVolume;
		//! Level hidden volume
		uint64_t HiddenVolume;
		//! Level visible volume
		uint64_t VisibleVolume;
		//! Level orders
		size_t Orders;

		Level(LevelType::enumtype type, uint64_t price) noexcept
			: Type(type),
			Price(price),
			TotalVolume(0),
			HiddenVolume(0),
			VisibleVolume(0),
			Orders(0)
		{
		}
		Level(const Level&) noexcept = default;
		Level(Level&&) noexcept = default;
		~Level() noexcept = default;

		Level& operator=(const Level&) noexcept = default;
		Level& operator=(Level&&) noexcept = default;

		// Price level comparison
		friend bool operator==(const Level& level1, const Level& level2) noexcept
		{
			return level1.Price == level2.Price;
		}
		friend bool operator!=(const Level& level1, const Level& level2) noexcept
		{
			return level1.Price != level2.Price;
		}
		friend bool operator<(const Level& level1, const Level& level2) noexcept
		{
			return level1.Price < level2.Price;
		}
		friend bool operator>(const Level& level1, const Level& level2) noexcept
		{
			return level1.Price > level2.Price;
		}
		friend bool operator<=(const Level& level1, const Level& level2) noexcept
		{
			return level1.Price <= level2.Price;
		}
		friend bool operator>=(const Level& level1, const Level& level2) noexcept
		{
			return level1.Price >= level2.Price;
		}

		template <class TOutputStream>
		friend TOutputStream& operator<<(TOutputStream& stream, const Level& level);

		//! Is the bid price level?
		bool IsBid() const noexcept { return Type == LevelType::BID; }
		//! Is the ask price level?
		bool IsAsk() const noexcept { return Type == LevelType::ASK; }
	};

	template <class TOutputStream>
	inline TOutputStream& operator<<(TOutputStream& stream, const Level& level)
	{
		stream << "Level(Type=" << level.Type
			<< "; Price=" << level.Price
			<< "; TotalVolume=" << level.TotalVolume
			<< "; HiddenVolume=" << level.HiddenVolume
			<< "; VisibleVolume=" << level.VisibleVolume
			<< "; Orders=" << level.Orders
			<< ")";
		return stream;
	}

	//! Price level node
	class LevelNode : public Level, public XT::BinTreeAVL<LevelNode>::Node// public boost::intrusive::avl_set_base_hook<>  // public CppCommon::BinTreeAVL<LevelNode>::Node
	{
	public:
		//! Price level orders
		XT::List<OrderNode> OrderList;  //boost::intrusive::list<OrderNode> OrderList;//  CppCommon::List<OrderNode> OrderList;

		LevelNode(LevelType::enumtype type, uint64_t price) noexcept
			: Level(type, price)
		{
		}
		LevelNode(const Level& level) noexcept
			:Level(level)
		{
		}
		LevelNode(const LevelNode&) noexcept = default;
		LevelNode(LevelNode&&) noexcept = default;
		~LevelNode() noexcept = default;

		LevelNode& operator=(const Level& level) noexcept
		{
			Level::operator=(level);
			OrderList.clear();
			return *this;
		}
		LevelNode& operator=(const LevelNode&) noexcept = default;
		LevelNode& operator=(LevelNode&&) noexcept = default;

		// Price level comparison
		friend bool operator==(const LevelNode& level1, const LevelNode& level2) noexcept
		{
			return level1.Price == level2.Price;
		}
		friend bool operator!=(const LevelNode& level1, const LevelNode& level2) noexcept
		{
			return level1.Price != level2.Price;
		}
		friend bool operator<(const LevelNode& level1, const LevelNode& level2) noexcept
		{
			return level1.Price < level2.Price;
		}
		friend bool operator>(const LevelNode& level1, const LevelNode& level2) noexcept
		{
			return level1.Price > level2.Price;
		}
		friend bool operator<=(const LevelNode& level1, const LevelNode& level2) noexcept
		{
			return level1.Price <= level2.Price;
		}
		friend bool operator>=(const LevelNode& level1, const LevelNode& level2) noexcept
		{
			return level1.Price >= level2.Price;
		}
	};

	//! Price level update
	class LevelUpdate
	{
	public:
		//! Update type
		UpdateType::enumtype Type;
		//! Level update value
		Level Update;
		//! Top of the book flag
		bool Top;

		LevelUpdate(UpdateType::enumtype type, const Level& update, bool top) noexcept
			: Type(type),
			Update(update),
			Top(top)
		{
		}
		LevelUpdate(const LevelUpdate&) noexcept = default;
		LevelUpdate(LevelUpdate&&) noexcept = default;
		~LevelUpdate() noexcept = default;

		LevelUpdate& operator=(const LevelUpdate&) noexcept = default;
		LevelUpdate& operator=(LevelUpdate&&) noexcept = default;

		template <class TOutputStream>
		friend TOutputStream& operator<<(TOutputStream& stream, const LevelUpdate& update);
	};

	template <class TOutputStream>
	inline TOutputStream& operator<<(TOutputStream& stream, const LevelUpdate& update)
	{
		stream << "LevelUpdate(Type=" << update.Type
			<< "; Update=" << update.Update
			<< "; Top=" << update.Top
			<< ")";
		return stream;
	}

}//namespace

#endif