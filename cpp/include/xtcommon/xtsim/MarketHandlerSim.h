#pragma once
#ifndef XT_MARKET_HANDLER_SIM_H
#define XT_MARKET_HANDLER_SIM_H

/**
* \file MarketHandlerSim.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for market handler simulation.
*
* \description
*	Designed for use for market handler simulation.
*/

#include <cassert>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include "StringMap.h"
#include "XTConfig.h"

#include "GlobalMgr.h"
#include "InstrMgr.h"
#include "StratMgr.h"

#include "MarketHandler.h"
#include "MarketManager.h"

namespace XT
{

	class MarketHandlerSim : public MarketHandler
	{
	protected:
		void onAddSymbol(const Symbol& symbol) override
		{
			std::stringstream logss;
			logss << "Add symbol: " << symbol ;
			LOGI(logss.str());
		}
		void onDeleteSymbol(const Symbol& symbol) override
		{
			std::stringstream logss;
			logss << "Delete symbol: " << symbol ;
			LOGI(logss.str());
		}

		void onAddOrderBook(const XTOrderBook& order_book) override
		{
			std::stringstream logss;
			logss << "Add order book: " << order_book ;
			LOGI(logss.str());
		}
		void onUpdateOrderBook(const XTOrderBook& order_book, bool top) override
		{
			std::stringstream logss;
			logss << "Update order book: " << order_book << (top ? " - Top of the book!" : "") ;
			LOGI(logss.str());
		}
		void onDeleteOrderBook(const XTOrderBook& order_book) override
		{
			std::stringstream logss;
			logss << "Delete order book: " << order_book ;
			LOGI(logss.str());
		}

		void onAddLevel(const XTOrderBook& order_book, const Level& level, bool top) override
		{
			std::stringstream logss;
			logss << "Add level: " << level << (top ? " - Top of the book!" : "") ;
			LOGI(logss.str());
		}
		void onUpdateLevel(const XTOrderBook& order_book, const Level& level, bool top) override
		{
			std::stringstream logss;
			logss << "Update level: " << level << (top ? " - Top of the book!" : "") ;
			LOGI(logss.str());
		}
		void onDeleteLevel(const XTOrderBook& order_book, const Level& level, bool top) override
		{
			std::stringstream logss;
			logss << "Delete level: " << level << (top ? " - Top of the book!" : "") ;
			LOGI(logss.str());
		}

		void onAddOrder(const XTOrder& order) override
		{
			std::stringstream logss;
			logss << "Add order: " << order ;
			LOGI(logss.str());
		}
		void onUpdateOrder(const XTOrder& order) override
		{
			std::stringstream logss;
			logss << "Update order: " << order ;
			LOGI(logss.str());
		}
		void onDeleteOrder(const XTOrder& order) override
		{
			std::stringstream logss;
			logss << "Delete order: " << order ;
			LOGI(logss.str());
		}

		void onExecuteOrder(const XTOrder& order, int64_t price, int64_t quantity) override
		{
			std::stringstream logss;
			logss << "Execute order: " << order << " with price " << price << " and quantity " << quantity ;
			LOGI(logss.str());
		}
	};//

}//namespace XT

#endif