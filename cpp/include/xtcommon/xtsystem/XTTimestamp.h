#pragma once
#ifndef XT_XTTIMESTAMP_H
#define XT_XTTIMESTAMP_H

/**
* \file XTTimestamp.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for timestamp.
*
* \description
*	Designed for use for timestamp.
*/

#include <cstdint>
#include <cstring>
#include <chrono>
#include "XTConfig.h"

#include "XTTimespan.h"
#include "MathUtil.h"
namespace XT
{

	//! XTTimestamp
	/*!
		XTTimestamp wraps time moment in nanoseconds and allows to get separate values of days,
		hours, minutes, seconds, milliseconds, microseconds or nanoseconds. Also it is possible
		to get difference between two timestamps as a timespan.

		Nanosecond timestamp based on 64-bit integer can represent each nanosecond in the time
		range of ~584.554531 years. Therefore timestamp bounds from 01.01.1970 to 31.12.2553.

		XTTimestamp epoch January 1, 1970 at 00:00:00

		Not thread-safe.
	*/
	class XT_COMMON_API XTTimestamp
	{
	public:
		//! Initialize timestamp with an epoch time
		XTTimestamp() noexcept : _timestamp(epoch()) {}
		//! Initialize timestamp with a given time moment in nanoseconds
		/*!
			\param timestamp - Time moment in nanoseconds
		*/
		explicit XTTimestamp(uint64_t timestamp) noexcept : _timestamp(timestamp) {}
		//! Initialize timestamp with a given std::chrono time point
		/*!
			\param time_point - std::chrono time point
		*/
		template <class Clock, class Duration>
		explicit XTTimestamp(const std::chrono::time_point<Clock, Duration>& time_point) noexcept : _timestamp(std::chrono::duration_cast<std::chrono::nanoseconds>(time_point.time_since_epoch()).count()) {}
		XTTimestamp(const XTTimestamp&) noexcept = default;
		XTTimestamp(XTTimestamp&&) noexcept = default;
		~XTTimestamp() noexcept = default;

		XTTimestamp& operator=(uint64_t timestamp) noexcept
		{
			_timestamp = timestamp; return *this;
		}
		XTTimestamp& operator=(const XTTimestamp&) noexcept = default;
		XTTimestamp& operator=(XTTimestamp&&) noexcept = default;

		// XTTimestamp offset operations
		XTTimestamp& operator+=(int64_t offset) noexcept
		{
			_timestamp += offset; return *this;
		}
		XTTimestamp& operator+=(const XTTimespan& offset) noexcept
		{
			_timestamp += offset.total(); return *this;
		}

		XTTimestamp& operator-=(int64_t offset) noexcept
		{
			_timestamp -= offset; return *this;
		}
		XTTimestamp& operator-=(const XTTimespan& offset) noexcept
		{
			_timestamp -= offset.total(); return *this;
		}

		friend XTTimestamp operator+(const XTTimestamp& timestamp, int64_t offset) noexcept
		{
			return XTTimestamp(timestamp.total() + offset);
		}
		friend XTTimestamp operator+(int64_t offset, const XTTimestamp& timestamp) noexcept
		{
			return XTTimestamp(offset + timestamp.total());
		}
		friend XTTimestamp operator+(const XTTimestamp& timestamp, const XTTimespan& offset) noexcept
		{
			return XTTimestamp(timestamp.total() + offset.total());
		}
		friend XTTimestamp operator+(const XTTimespan& offset, const XTTimestamp& timestamp) noexcept
		{
			return XTTimestamp(offset.total() + timestamp.total());
		}

		friend XTTimestamp operator-(const XTTimestamp& timestamp, int64_t offset) noexcept
		{
			return XTTimestamp(timestamp.total() - offset);
		}
		friend XTTimestamp operator-(int64_t offset, const XTTimestamp& timestamp) noexcept
		{
			return XTTimestamp(offset - timestamp.total());
		}
		friend XTTimestamp operator-(const XTTimestamp& timestamp, const XTTimespan& offset) noexcept
		{
			return XTTimestamp(timestamp.total() - offset.total());
		}
		friend XTTimestamp operator-(const XTTimespan& offset, const XTTimestamp& timestamp) noexcept
		{
			return XTTimestamp(offset.total() - timestamp.total());
		}

		friend XTTimespan operator-(const XTTimestamp& timestamp1, const XTTimestamp& timestamp2) noexcept
		{
			return XTTimespan(timestamp1.total() - timestamp2.total());
		}

		// XTTimestamp comparison
		friend bool operator==(const XTTimestamp& timestamp1, uint64_t timestamp2) noexcept
		{
			return timestamp1.total() == timestamp2;
		}
		friend bool operator==(uint64_t timestamp1, const XTTimestamp& timestamp2) noexcept
		{
			return timestamp1 == timestamp2.total();
		}
		friend bool operator==(const XTTimestamp& timestamp1, const XTTimestamp& timestamp2) noexcept
		{
			return timestamp1.total() == timestamp2.total();
		}

		friend bool operator!=(const XTTimestamp& timestamp1, uint64_t timestamp2) noexcept
		{
			return timestamp1.total() != timestamp2;
		}
		friend bool operator!=(uint64_t timestamp1, const XTTimestamp& timestamp2) noexcept
		{
			return timestamp1 != timestamp2.total();
		}
		friend bool operator!=(const XTTimestamp& timestamp1, const XTTimestamp& timestamp2) noexcept
		{
			return timestamp1.total() != timestamp2.total();
		}

		friend bool operator>(const XTTimestamp& timestamp1, uint64_t timestamp2) noexcept
		{
			return timestamp1.total() > timestamp2;
		}
		friend bool operator>(uint64_t timestamp1, const XTTimestamp& timestamp2) noexcept
		{
			return timestamp1 > timestamp2.total();
		}
		friend bool operator>(const XTTimestamp& timestamp1, const XTTimestamp& timestamp2) noexcept
		{
			return timestamp1.total() > timestamp2.total();
		}

		friend bool operator<(const XTTimestamp& timestamp1, uint64_t timestamp2) noexcept
		{
			return timestamp1.total() < timestamp2;
		}
		friend bool operator<(uint64_t timestamp1, const XTTimestamp& timestamp2) noexcept
		{
			return timestamp1 < timestamp2.total();
		}
		friend bool operator<(const XTTimestamp& timestamp1, const XTTimestamp& timestamp2) noexcept
		{
			return timestamp1.total() < timestamp2.total();
		}

		friend bool operator>=(const XTTimestamp& timestamp1, uint64_t timestamp2) noexcept
		{
			return timestamp1.total() >= timestamp2;
		}
		friend bool operator>=(uint64_t timestamp1, const XTTimestamp& timestamp2) noexcept
		{
			return timestamp1 >= timestamp2.total();
		}
		friend bool operator>=(const XTTimestamp& timestamp1, const XTTimestamp& timestamp2) noexcept
		{
			return timestamp1.total() >= timestamp2.total();
		}

		friend bool operator<=(const XTTimestamp& timestamp1, uint64_t timestamp2) noexcept
		{
			return timestamp1.total() <= timestamp2;
		}
		friend bool operator<=(uint64_t timestamp1, const XTTimestamp& timestamp2) noexcept
		{
			return timestamp1 <= timestamp2.total();
		}
		friend bool operator<=(const XTTimestamp& timestamp1, const XTTimestamp& timestamp2) noexcept
		{
			return timestamp1.total() <= timestamp2.total();
		}

		//! Convert timestamp to the std::chrono time point
		std::chrono::system_clock::time_point chrono() const noexcept
		{
			return std::chrono::time_point_cast<std::chrono::system_clock::duration>((std::chrono::time_point<std::chrono::system_clock>() + std::chrono::nanoseconds(_timestamp)));
		}

		//! Get total days of the current timestamp
		uint64_t days() const noexcept
		{
			return _timestamp / (24 * 60 * 60 * 1000000000ull);
		}
		//! Get total hours of the current timestamp
		uint64_t hours() const noexcept
		{
			return _timestamp / (60 * 60 * 1000000000ull);
		}
		//! Get total minutes of the current timestamp
		uint64_t minutes() const noexcept
		{
			return _timestamp / (60 * 1000000000ull);
		}
		//! Get total seconds of the current timestamp
		uint64_t seconds() const noexcept
		{
			return _timestamp / 1000000000;
		}
		//! Get total milliseconds of the current timestamp
		uint64_t milliseconds() const noexcept
		{
			return _timestamp / 1000000;
		}
		//! Get total microseconds of the current timestamp
		uint64_t microseconds() const noexcept
		{
			return _timestamp / 1000;
		}
		//! Get total nanoseconds of the current timestamp
		uint64_t nanoseconds() const noexcept
		{
			return _timestamp;
		}

		//! Get total value of the current timestamp (total nanoseconds)
		uint64_t total() const noexcept { return _timestamp; }

		//! Create the timestamp based on the given days value
		static XTTimestamp days(int64_t days) noexcept
		{
			return XTTimestamp(days * 24 * 60 * 60 * 1000000000ull);
		}
		//! Create the timestamp based on the given hours value
		static XTTimestamp hours(int64_t hours) noexcept
		{
			return XTTimestamp(hours * 60 * 60 * 1000000000ull);
		}
		//! Create the timestamp based on the given minutes value
		static XTTimestamp minutes(int64_t minutes) noexcept
		{
			return XTTimestamp(minutes * 60 * 1000000000ull);
		}
		//! Create the timestamp based on the given seconds value
		static XTTimestamp seconds(int64_t seconds) noexcept
		{
			return XTTimestamp(seconds * 1000000000);
		}
		//! Create the timestamp based on the given milliseconds value
		static XTTimestamp milliseconds(int64_t milliseconds) noexcept
		{
			return XTTimestamp(milliseconds * 1000000);
		}
		//! Create the timestamp based on the given microseconds value
		static XTTimestamp microseconds(int64_t microseconds) noexcept
		{
			return XTTimestamp(microseconds * 1000);
		}
		//! Create the timestamp based on the given nanoseconds value
		static XTTimestamp nanoseconds(int64_t nanoseconds) noexcept
		{
			return XTTimestamp(nanoseconds);
		}

		//! Get the epoch timestamp
		/*!
			Thread-safe.

			\return Epoch timestamp
		*/
		static uint64_t epoch() noexcept { return 0; }

		//! Get the UTC timestamp
		/*!
			Thread-safe.

			\return UTC timestamp
		*/
		static uint64_t utc();

		//! Get the local timestamp
		/*!
			Thread-safe.

			\return Local timestamp
		*/
		static uint64_t local();

		//! Get the high resolution timestamp
		/*!
			Thread-safe.

			\return High resolution timestamp
		*/
		static uint64_t nano();

		//! Get the current value of RDTS (Read Time Stamp Counter)
		/*!
			Counts the number of CPU cycles since reset. The Time Stamp Counter (TSC)
			is a 64-bit register present on all x86 processors since the Pentium.

			Thread-safe.

			https://en.wikipedia.org/wiki/Time_Stamp_Counter

			\return Number of CPU cycles since the last system reset
		*/
		static uint64_t rdts();

		//! Swap two instances
		void swap(XTTimestamp& timestamp) noexcept;
		friend void swap(XTTimestamp& timestamp1, XTTimestamp& timestamp2) noexcept;

	protected:
		//! XTTimestamp value
		uint64_t _timestamp;
	};

	//! UTC timestamp
	class XT_COMMON_API XTUtcTimestamp : public XTTimestamp
	{
	public:
	//	using Timestamp::Timestamp;

		//! Initialize UTC timestamp with a current UTC time
		XTUtcTimestamp() : XTTimestamp(XTTimestamp::utc()) {}
		//! Initialize UTC timestamp with another timestamp value
		XTUtcTimestamp(const XTTimestamp& timestamp) : XTTimestamp(timestamp) {}

		XTUtcTimestamp(uint64_t ts) : XTTimestamp(ts) {}
	};

	//! Local timestamp
	class XT_COMMON_API XTLocalTimestamp : public XTTimestamp
	{
	public:
//		using Timestamp::Timestamp;

		//! Initialize local timestamp with a current local time
		XTLocalTimestamp() : XTTimestamp(XTTimestamp::local()) {}
		//! Initialize local timestamp with another timestamp value
		XTLocalTimestamp(const XTTimestamp& timestamp) : XTTimestamp(timestamp) {}

		XTLocalTimestamp(uint64_t ts) : XTTimestamp(ts) {}
	};

	//! High resolution timestamp
	class XT_COMMON_API XTNanoTimestamp : public XTTimestamp
	{
	public:
//		using Timestamp::Timestamp;

		//! Initialize high resolution timestamp with a current high resolution time
		XTNanoTimestamp() : XTTimestamp(XTTimestamp::nano()) {}
		//! Initialize high resolution timestamp with another timestamp value
		XTNanoTimestamp(const XTTimestamp& timestamp) : XTTimestamp(timestamp) {}

		XTNanoTimestamp(uint64_t ts) : XTTimestamp(ts) {}
	};

	//! RDTS timestamp
	class XT_COMMON_API XTRdtsTimestamp : public XTTimestamp
	{
	public:
//		using Timestamp::Timestamp;

		//! Initialize RDTS timestamp with a current RDTS time
		XTRdtsTimestamp() : XTTimestamp(XTTimestamp::rdts()) {}
		//! Initialize RDTS timestamp with another timestamp value
		XTRdtsTimestamp(const XTTimestamp& timestamp) : XTTimestamp(timestamp) {}

		XTRdtsTimestamp(uint64_t ts) : XTTimestamp(ts) {}
	};

////
	inline void XTTimestamp::swap(XTTimestamp& timestamp) noexcept
	{
		using std::swap;
		swap(_timestamp, timestamp._timestamp);
	}

	inline void swap(XTTimestamp& timestamp1, XTTimestamp& timestamp2) noexcept
	{
		timestamp1.swap(timestamp2);
	}

}//namespace XT


namespace std {

	template <>
	struct hash<XT::XTTimestamp>
	{
		typedef XT::XTTimestamp argument_type;
		typedef size_t result_type;

		result_type operator () (const argument_type& value) const
		{
			result_type result = 17;
			result = result * 31 + std::hash<int64_t>()(value.total());
			return result;
		}
	};
}//namespace std

#endif