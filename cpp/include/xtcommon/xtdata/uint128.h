#pragma once
#ifndef XT_UINT128_H
#define XT_UINT128_H

/**
* \file uint128.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide unsigned 128 bit int class .
*
* \description
*	Designed for unsigned 128 bit int class.
*/

#include <cstdint>
#include <string>
#include <iostream>

#include <stdexcept>
#include <type_traits>
#include <utility>

#include "XTConfig.h"

namespace XT
{

	//! Unsigned 128-bit integer type
	/*!
		Represents unsigned 128-bit integer type and provides basic arithmetic operations.
	*/
	class XT_COMMON_API uint128_t
	{
	public:
		uint128_t() noexcept;
		uint128_t(int8_t value) noexcept;
		uint128_t(uint8_t value) noexcept;
		uint128_t(int16_t value) noexcept;
		uint128_t(uint16_t value) noexcept;
		uint128_t(int32_t value) noexcept;
		uint128_t(uint32_t value) noexcept;
		uint128_t(int64_t value) noexcept;
		uint128_t(uint64_t value) noexcept;
		template <typename T>
		explicit uint128_t(const T& value) noexcept;
		template <typename TUpper, typename TLower>
		uint128_t(const TUpper& upper, const TLower& lower) noexcept;
		uint128_t(const uint128_t& value) noexcept = default;
		uint128_t(uint128_t&& value) noexcept = default;
		~uint128_t() noexcept = default;

		template <typename T>
		uint128_t& operator=(const T& value) noexcept;
		uint128_t& operator=(const uint128_t& value) noexcept = default;
		uint128_t& operator=(uint128_t&& value) noexcept = default;

		// Arithmetic operators
		uint128_t operator+() const noexcept { return *this; }
		uint128_t operator-() const noexcept { return ~*this + 1; }

		uint128_t& operator++() noexcept { return *this += 1; }
		uint128_t operator++(int) noexcept { uint128_t temp(*this); ++*this; return temp; }
		uint128_t& operator--() noexcept { return *this -= 1; }
		uint128_t operator--(int) noexcept { uint128_t temp(*this); --*this; return temp; }

		uint128_t& operator+=(const uint128_t& value) noexcept { return *this = *this + value; }
		uint128_t& operator-=(const uint128_t& value) noexcept { return *this = *this - value; }
		uint128_t& operator*=(const uint128_t& value) noexcept { return *this = *this * value; }
		uint128_t& operator/=(const uint128_t& value) { return *this = *this / value; }
		uint128_t& operator%=(const uint128_t& value) { return *this = *this % value; }

		template <typename T>
		uint128_t& operator+=(const T& value) noexcept { return *this = *this + uint128_t(value); }
		template <typename T>
		uint128_t& operator-=(const T& value) noexcept { return *this = *this - uint128_t(value); }
		template <typename T>
		uint128_t& operator*=(const T& value) noexcept { return *this = *this * uint128_t(value); }
		template <typename T>
		uint128_t& operator/=(const T& value) { return *this = *this / uint128_t(value); }
		template <typename T>
		uint128_t& operator%=(const T& value) { return *this = *this % uint128_t(value); }

		template <typename T>
		friend T& operator+=(T& value1, const uint128_t& value2) noexcept { return value1 = (T)(uint128_t(value1) + value2); }
		template <typename T>
		friend T& operator-=(T& value1, const uint128_t& value2) noexcept { return value1 = (T)(uint128_t(value1) - value2); }
		template <typename T>
		friend T& operator*=(T& value1, const uint128_t& value2) noexcept { return value1 = (T)(uint128_t(value1) * value2); }
		template <typename T>
		friend T& operator/=(T& value1, const uint128_t& value2) { return value1 = (T)(uint128_t(value1) / value2); }
		template <typename T>
		friend T& operator%=(T& value1, const uint128_t& value2) { return value1 = (T)(uint128_t(value1) % value2); }

		template <typename T>
		friend uint128_t operator+(const T& value1, const uint128_t& value2) noexcept { return uint128_t(value1) + value2; }
		template <typename T>
		friend uint128_t operator+(const uint128_t& value1, const T& value2) noexcept { return value1 + uint128_t(value2); }
		friend uint128_t operator+(const uint128_t& value1, const uint128_t& value2) noexcept;

		template <typename T>
		friend uint128_t operator-(const T& value1, const uint128_t& value2) noexcept { return uint128_t(value1) - value2; }
		template <typename T>
		friend uint128_t operator-(const uint128_t& value1, const T& value2) noexcept { return value1 - uint128_t(value2); }
		friend uint128_t operator-(const uint128_t& value1, const uint128_t& value2) noexcept;

		template <typename T>
		friend uint128_t operator*(const T& value1, const uint128_t& value2) noexcept { return uint128_t(value1) * value2; }
		template <typename T>
		friend uint128_t operator*(const uint128_t& value1, const T& value2) noexcept { return value1 * uint128_t(value2); }
		friend uint128_t operator*(const uint128_t& value1, const uint128_t& value2) noexcept;

		template <typename T>
		friend uint128_t operator/(const T& value1, const uint128_t& value2) { return uint128_t(value1) / value2; }
		template <typename T>
		friend uint128_t operator/(const uint128_t& value1, const T& value2) { return value1 / uint128_t(value2); }
		friend uint128_t operator/(const uint128_t& value1, const uint128_t& value2);

		template <typename T>
		friend uint128_t operator%(const T& value1, const uint128_t& value2) { return uint128_t(value1) % value2; }
		template <typename T>
		friend uint128_t operator%(const uint128_t& value1, const T& value2) { return value1 % uint128_t(value2); }
		friend uint128_t operator%(const uint128_t& value1, const uint128_t& value2);

		// Bit operators
		uint128_t operator~() const noexcept { return uint128_t(~_upper, ~_lower); }

		uint128_t& operator&=(const uint128_t& value) noexcept { return *this = *this & value; }
		uint128_t& operator|=(const uint128_t& value) noexcept { return *this = *this | value; }
		uint128_t& operator^=(const uint128_t& value) noexcept { return *this = *this ^ value; }

		template <typename T>
		uint128_t& operator&=(const T& value) noexcept { return *this = *this & uint128_t(value); }
		template <typename T>
		uint128_t& operator|=(const T& value) noexcept { return *this = *this | uint128_t(value); }
		template <typename T>
		uint128_t& operator^=(const T& value) noexcept { return *this = *this ^ uint128_t(value); }

		template <typename T>
		friend T& operator&=(T& value1, const uint128_t& value2) noexcept { return value1 = (T)(uint128_t(value1) & value2); }
		template <typename T>
		friend T& operator|=(T& value1, const uint128_t& value2) noexcept { return value1 = (T)(uint128_t(value1) | value2); }
		template <typename T>
		friend T& operator^=(T& value1, const uint128_t& value2) noexcept { return value1 = (T)(uint128_t(value1) ^ value2); }

		template <typename T>
		friend uint128_t operator&(const T& value1, const uint128_t& value2) noexcept { return uint128_t(value1) & value2; }
		template <typename T>
		friend uint128_t operator&(const uint128_t& value1, const T& value2) noexcept { return value1 & uint128_t(value2); }
		friend uint128_t operator&(const uint128_t& value1, const uint128_t& value2) noexcept;

		template <typename T>
		friend uint128_t operator|(const T& value1, const uint128_t& value2) noexcept { return uint128_t(value1) | value2; }
		template <typename T>
		friend uint128_t operator|(const uint128_t& value1, const T& value2) noexcept { return value1 | uint128_t(value2); }
		friend uint128_t operator|(const uint128_t& value1, const uint128_t& value2) noexcept;

		template <typename T>
		friend uint128_t operator^(const T& value1, const uint128_t& value2) noexcept { return uint128_t(value1) ^ value2; }
		template <typename T>
		friend uint128_t operator^(const uint128_t& value1, const T& value2) noexcept { return value1 ^ uint128_t(value2); }
		friend uint128_t operator^(const uint128_t& value1, const uint128_t& value2) noexcept;

		// Comparison operators
		template <typename T>
		friend bool operator==(const T& value1, const uint128_t& value2) noexcept { return uint128_t(value1) == value2; }
		template <typename T>
		friend bool operator==(const uint128_t& value1, const T& value2) noexcept { return value1 == uint128_t(value2); }
		friend bool operator==(const uint128_t& value1, const uint128_t& value2) noexcept;

		template <typename T>
		friend bool operator!=(const T& value1, const uint128_t& value2) noexcept { return uint128_t(value1) != value2; }
		template <typename T>
		friend bool operator!=(const uint128_t& value1, const T& value2) noexcept { return value1 != uint128_t(value2); }
		friend bool operator!=(const uint128_t& value1, const uint128_t& value2) noexcept;

		template <typename T>
		friend bool operator<(const T& value1, const uint128_t& value2) noexcept { return uint128_t(value1) < value2; }
		template <typename T>
		friend bool operator<(const uint128_t& value1, const T& value2) noexcept { return value1 < uint128_t(value2); }
		friend bool operator<(const uint128_t& value1, const uint128_t& value2) noexcept;

		template <typename T>
		friend bool operator>(const T& value1, const uint128_t& value2) noexcept { return uint128_t(value1) > value2; }
		template <typename T>
		friend bool operator>(const uint128_t& value1, const T& value2) noexcept { return value1 > uint128_t(value2); }
		friend bool operator>(const uint128_t& value1, const uint128_t& value2) noexcept;

		template <typename T>
		friend bool operator<=(const T& value1, const uint128_t& value2) noexcept { return uint128_t(value1) <= value2; }
		template <typename T>
		friend bool operator<=(const uint128_t& value1, const T& value2) noexcept { return value1 <= uint128_t(value2); }
		friend bool operator<=(const uint128_t& value1, const uint128_t& value2) noexcept;

		template <typename T>
		friend bool operator>=(const T& value1, const uint128_t& value2) noexcept { return uint128_t(value1) >= value2; }
		template <typename T>
		friend bool operator>=(const uint128_t& value1, const T& value2) noexcept { return value1 >= uint128_t(value2); }
		friend bool operator>=(const uint128_t& value1, const uint128_t& value2) noexcept;

		// Logical operators
		bool operator!() const noexcept { return !(bool)(_upper | _lower); }

		template <typename T>
		friend bool operator&&(const T& value1, const uint128_t& value2) noexcept { return uint128_t(value1) && value2; }
		template <typename T>
		friend bool operator&&(const uint128_t& value1, const T& value2) noexcept { return value1 && uint128_t(value2); }
		friend bool operator&&(const uint128_t& value1, const uint128_t& value2) noexcept;

		template <typename T>
		friend bool operator||(const T& value1, const uint128_t& value2) noexcept { return uint128_t(value1) || value2; }
		template <typename T>
		friend bool operator||(const uint128_t& value1, const T& value2) noexcept { return value1 || uint128_t(value2); }
		friend bool operator||(const uint128_t& value1, const uint128_t& value2) noexcept;

		// Shift operators
		uint128_t& operator<<=(const uint128_t& value) noexcept { return *this = *this << value; }
		uint128_t& operator>>=(const uint128_t& value) noexcept { return *this = *this >> value; }

		template <typename T>
		uint128_t& operator<<=(const T& value) noexcept { return *this = *this << uint128_t(value); }
		template <typename T>
		uint128_t& operator>>=(const T& value) noexcept { return *this = *this >> uint128_t(value); }

		template <typename T>
		friend T& operator<<=(T& value1, const uint128_t& value2) noexcept { return value1 = (T)(uint128_t(value1) << value2); }
		template <typename T>
		friend T& operator>>=(T& value1, const uint128_t& value2) noexcept { return value1 = (T)(uint128_t(value1) >> value2); }

		template <typename T>
		friend uint128_t operator<<(const uint128_t& value1, const T& value2) noexcept { return value1 << uint128_t(value2); }
		friend uint128_t operator<<(bool value1, const uint128_t& value2) noexcept { return uint128_t(value1) << value2; }
		friend uint128_t operator<<(int8_t value1, const uint128_t& value2) noexcept { return uint128_t(value1) << value2; }
		friend uint128_t operator<<(int16_t value1, const uint128_t& value2) noexcept { return uint128_t(value1) << value2; }
		friend uint128_t operator<<(int32_t value1, const uint128_t& value2) noexcept { return uint128_t(value1) << value2; }
		friend uint128_t operator<<(int64_t value1, const uint128_t& value2) noexcept { return uint128_t(value1) << value2; }
		friend uint128_t operator<<(uint8_t value1, const uint128_t& value2) noexcept { return uint128_t(value1) << value2; }
		friend uint128_t operator<<(uint16_t value1, const uint128_t& value2) noexcept { return uint128_t(value1) << value2; }
		friend uint128_t operator<<(uint32_t value1, const uint128_t& value2) noexcept { return uint128_t(value1) << value2; }
		friend uint128_t operator<<(uint64_t value1, const uint128_t& value2) noexcept { return uint128_t(value1) << value2; }
		friend uint128_t operator<<(const uint128_t& value1, const uint128_t& value2) noexcept;

		template <typename T>
		friend uint128_t operator>>(const uint128_t& value1, const T& value2) noexcept { return value1 >> uint128_t(value2); }
		friend uint128_t operator>>(bool value1, const uint128_t& value2) noexcept { return uint128_t(value1) >> value2; }
		friend uint128_t operator>>(int8_t value1, const uint128_t& value2) noexcept { return uint128_t(value1) >> value2; }
		friend uint128_t operator>>(int16_t value1, const uint128_t& value2) noexcept { return uint128_t(value1) >> value2; }
		friend uint128_t operator>>(int32_t value1, const uint128_t& value2) noexcept { return uint128_t(value1) >> value2; }
		friend uint128_t operator>>(int64_t value1, const uint128_t& value2) noexcept { return uint128_t(value1) >> value2; }
		friend uint128_t operator>>(uint8_t value1, const uint128_t& value2) noexcept { return uint128_t(value1) >> value2; }
		friend uint128_t operator>>(uint16_t value1, const uint128_t& value2) noexcept { return uint128_t(value1) >> value2; }
		friend uint128_t operator>>(uint32_t value1, const uint128_t& value2) noexcept { return uint128_t(value1) >> value2; }
		friend uint128_t operator>>(uint64_t value1, const uint128_t& value2) noexcept { return uint128_t(value1) >> value2; }
		friend uint128_t operator>>(const uint128_t& value1, const uint128_t& value2) noexcept;

		// Type cast
		operator bool() const noexcept { return (bool)(_upper | _lower); }
		operator uint8_t() const noexcept { return (uint8_t)_lower; }
		operator uint16_t() const noexcept { return (uint16_t)_lower; }
		operator uint32_t() const noexcept { return (uint32_t)_lower; }
		operator uint64_t() const noexcept { return (uint64_t)_lower; }

		//! Get the upper part of the 128-bit integer
		uint64_t upper() const noexcept { return _upper; }
		//! Get the lower part of the 128-bit integer
		uint64_t lower() const noexcept { return _lower; }

		//! Get the count of bits
		size_t bits() const noexcept;

		//! Get string from the current 128-bit integer
		/*!
			\param base - Conversion base in range [2, 16] (default is 10)
			\param length - Minimal string length (default is 0)
			\return Result string
		*/
		std::string string(size_t base = 10, size_t length = 0) const;
		//! Get wide string from the current 128-bit integer
		/*!
			\param base - Conversion base in range [2, 16] (default is 10)
			\param length - Minimal string length (default is 0)
			\return Result wide string
		*/
		std::wstring wstring(size_t base = 10, size_t length = 0) const;

		//! Calculate quotient and remainder when dividing X by Y
		/*!
			\param x - X value
			\param y - Y value
			\return Quotient and remainder pair
		*/
		static std::pair<uint128_t, uint128_t> divmod(const uint128_t& x, const uint128_t& y);

		//! Input instance from the given input stream
		friend std::istream& operator>>(std::istream& is, uint128_t& value)
		{
			is >> value._upper >> value._lower; return is;
		}
		//! Input instance from the given wide input stream
		friend std::wistream& operator>>(std::wistream& is, uint128_t& value)
		{
			is >> value._upper >> value._lower; return is;
		}
		//! Output instance into the given output stream
		friend std::ostream& operator<<(std::ostream& os, const uint128_t& value);
		//! Output instance into the given wide output stream
		friend std::wostream& operator<<(std::wostream& os, const uint128_t& value);

		//! Swap two instances
		void swap(uint128_t& value) noexcept;
		friend void swap(uint128_t& value1, uint128_t& value2) noexcept;

	private:
		uint64_t _upper;
		uint64_t _lower;
	};


//////////


///////////////////
	inline uint128_t::uint128_t() noexcept
		: _upper(0), _lower(0)
	{
	}

	inline uint128_t::uint128_t(int8_t value) noexcept
		: _upper(0), _lower(value)
	{
	}

	inline uint128_t::uint128_t(uint8_t value) noexcept
		: _upper(0), _lower(value)
	{
	}

	inline uint128_t::uint128_t(int16_t value) noexcept
		: _upper(0), _lower(value)
	{
	}

	inline uint128_t::uint128_t(uint16_t value) noexcept
		: _upper(0), _lower(value)
	{
	}

	inline uint128_t::uint128_t(int32_t value) noexcept
		: _upper(0), _lower(value)
	{
	}

	inline uint128_t::uint128_t(uint32_t value) noexcept
		: _upper(0), _lower(value)
	{
	}

	inline uint128_t::uint128_t(int64_t value) noexcept
		: _upper(0), _lower(value)
	{
	}

	inline uint128_t::uint128_t(uint64_t value) noexcept
		: _upper(0), _lower(value)
	{
	}

	template <typename T>
	inline uint128_t::uint128_t(const T& value) noexcept
		: _upper(0), _lower(value)
	{
		static_assert(std::is_integral<T>::value, "Input argument type must be an integer!");
	}

	template <typename TUpper, typename TLower>
	inline uint128_t::uint128_t(const TUpper& upper, const TLower& lower) noexcept
		: _upper(upper), _lower(lower)
	{
		static_assert((std::is_integral<TUpper>::value && std::is_integral<TLower>::value), "Input argument types must be integers!");
	}

	template <typename T>
	inline uint128_t& uint128_t::operator=(const T& value) noexcept
	{
		static_assert(std::is_integral<T>::value, "Input argument type must be an integer!");

		_upper = 0;
		_lower = value;
		return *this;
	}

	inline uint128_t operator+(const uint128_t& value1, const uint128_t& value2) noexcept
	{
		return uint128_t(value1._upper + value2._upper + (((value1._lower + value2._lower) < value1._lower) ? 1 : 0), value1._lower + value2._lower);
	}

	inline uint128_t operator-(const uint128_t& value1, const uint128_t& value2) noexcept
	{
		return uint128_t(value1._upper - value2._upper - (((value1._lower - value2._lower) > value1._lower) ? 1 : 0), value1._lower - value2._lower);
	}

	inline uint128_t operator/(const uint128_t& value1, const uint128_t& value2)
	{
		return uint128_t::divmod(value1, value2).first;
	}

	inline uint128_t operator%(const uint128_t& value1, const uint128_t& value2)
	{
		return uint128_t::divmod(value1, value2).second;
	}

	inline uint128_t operator&(const uint128_t& value1, const uint128_t& value2) noexcept
	{
		return uint128_t(value1._upper & value2._upper, value1._lower & value2._lower);
	}

	inline uint128_t operator|(const uint128_t& value1, const uint128_t& value2) noexcept
	{
		return uint128_t(value1._upper | value2._upper, value1._lower | value2._lower);
	}

	inline uint128_t operator^(const uint128_t& value1, const uint128_t& value2) noexcept
	{
		return uint128_t(value1._upper ^ value2._upper, value1._lower ^ value2._lower);
	}

	inline bool operator==(const uint128_t& value1, const uint128_t& value2) noexcept
	{
		return ((value1._upper == value2._upper) && (value1._lower == value2._lower));
	}

	inline bool operator!=(const uint128_t& value1, const uint128_t& value2) noexcept
	{
		return ((value1._upper != value2._upper) || (value1._lower != value2._lower));
	}

	inline bool operator<(const uint128_t& value1, const uint128_t& value2) noexcept
	{
		return (value1._upper == value2._upper) ? (value1._lower < value2._lower) : (value1._upper < value2._upper);
	}

	inline bool operator>(const uint128_t& value1, const uint128_t& value2) noexcept
	{
		return (value1._upper == value2._upper) ? (value1._lower > value2._lower) : (value1._upper > value2._upper);
	}

	inline bool operator<=(const uint128_t& value1, const uint128_t& value2) noexcept
	{
		return ((value1 < value2) || (value1 == value2));
	}

	inline bool operator>=(const uint128_t& value1, const uint128_t& value2) noexcept
	{
		return ((value1 > value2) || (value1 == value2));
	}

	inline bool operator&&(const uint128_t& value1, const uint128_t& value2) noexcept
	{
		return ((bool)value1 && (bool)value2);
	}

	inline bool operator||(const uint128_t& value1, const uint128_t& value2) noexcept
	{
		return ((bool)value1 || (bool)value2);
	}

	inline std::ostream& operator<<(std::ostream& os, const uint128_t& value)
	{
		if (os.flags() & os.oct)
			os << value.string(8);
		else if (os.flags() & os.dec)
			os << value.string(10);
		else if (os.flags() & os.hex)
			os << value.string(16);
		return os;
	}

	inline std::wostream& operator<<(std::wostream& os, const uint128_t& value)
	{
		if (os.flags() & os.oct)
			os << value.wstring(8);
		else if (os.flags() & os.dec)
			os << value.wstring(10);
		else if (os.flags() & os.hex)
			os << value.wstring(16);
		return os;
	}

	inline void uint128_t::swap(uint128_t& value) noexcept
	{
		using std::swap;
		swap(_upper, value._upper);
		swap(_lower, value._lower);
	}

	inline void swap(uint128_t& value1, uint128_t& value2) noexcept
	{
		value1.swap(value2);
	}

///////////////



}//namespace XT


// Type traits
namespace std
{
	template <> struct is_arithmetic<XT::uint128_t> : std::true_type {};
	template <> struct is_integral<XT::uint128_t> : std::true_type {};
	template <> struct is_unsigned<XT::uint128_t> : std::true_type {};
}

namespace std {

	template <>
	struct hash<XT::uint128_t>
	{
		typedef XT::uint128_t argument_type;
		typedef size_t result_type;

		result_type operator () (const argument_type& value) const
		{
			result_type result = 17;
			std::hash<uint64_t> hasher;
			result = result * 31 + hasher(value.upper());
			result = result * 31 + hasher(value.lower());
			return result;
		}
	};

} // namespace std


#endif