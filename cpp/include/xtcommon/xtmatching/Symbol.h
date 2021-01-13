#pragma once
#ifndef XT_SYMBOL_H
#define XT_SYMBOL_H

/**
* \file Symbol.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for instrument symbol.
*
* \description
*	Designed for use for instrument symbol.
*/

#include <cassert>
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>

namespace XT
{

	//! Symbol
	struct Symbol
	{
		//! Symbol Id
		int Id;
		//! Symbol name
		char Name[32];

		Symbol() noexcept = default;
		Symbol(int id, const char name[32]) noexcept
			:Id(id)
		{
			std::memcpy(Name, name, sizeof(Name));
		}

		Symbol(const Symbol&) noexcept = default;
		Symbol(Symbol&&) noexcept = default;
		~Symbol() noexcept = default;

		Symbol& operator=(const Symbol&) noexcept = default;
		Symbol& operator=(Symbol&&) noexcept = default;

		template <class TOutputStream>
		friend TOutputStream& operator<<(TOutputStream& stream, const Symbol& symbol);
	};

	template <class TOutputStream>
	inline TOutputStream& operator<<(TOutputStream& stream, const Symbol& symbol)
	{
		stream << "Symbol(Id=" << symbol.Id
			<< "; Name=" << (symbol.Name)
			<< ")";
		return stream;
	}

}//namespace

#endif