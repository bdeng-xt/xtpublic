#pragma once
#ifndef XT_XTTIMESPAN_H
#define XT_XTTIMESPAN_H

/**
* \file XTTimespan.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for timespan.
*
* \description
*	Designed for use for timespan.
*/

#include <cstdint>
#include <cstring>

#include <chrono>
#include "XTConfig.h"

#include "XTExceptions.h"

namespace XT
{

	//! XTTimespan
	/*!
		XTTimespan wraps time duration in nanoseconds or difference between two timestamps
		and allows to get separate values of days, hours, minutes, seconds, milliseconds,
		microseconds or nanoseconds.

		Not thread-safe.
	*/
	class XTTimespan
	{
	public:
		//! Initialize timespan with a zero time duration
		XTTimespan() noexcept : _duration(0) {}
		//! Initialize timespan with a given time duration value in nanoseconds
		/*!
			\param duration - Time duration value in nanoseconds
		*/
		explicit XTTimespan(int64_t duration) noexcept : _duration(duration) {}
		//! Initialize timespan with a given std::chrono duration
		/*!
			\param duration - std::chrono duration
		*/
		template <class Rep, class Period>
		explicit XTTimespan(const std::chrono::duration<Rep, Period>& duration) noexcept : _duration(std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count()) {}
		XTTimespan(const XTTimespan&) noexcept = default;
		XTTimespan(XTTimespan&&) noexcept = default;
		~XTTimespan() noexcept = default;

		XTTimespan& operator=(int64_t duration) noexcept
		{
			_duration = duration; return *this;
		}
		XTTimespan& operator=(const XTTimespan&) noexcept = default;
		XTTimespan& operator=(XTTimespan&&) noexcept = default;

		// XTTimespan offset operations
		XTTimespan operator+() const
		{
			return XTTimespan(+_duration);
		}
		XTTimespan operator-() const
		{
			return XTTimespan(-_duration);
		}

		XTTimespan& operator+=(int64_t offset) noexcept
		{
			_duration += offset; return *this;
		}
		XTTimespan& operator+=(const XTTimespan& offset) noexcept
		{
			_duration += offset.total(); return *this;
		}

		XTTimespan& operator-=(int64_t offset) noexcept
		{
			_duration -= offset; return *this;
		}
		XTTimespan& operator-=(const XTTimespan& offset) noexcept
		{
			_duration -= offset.total(); return *this;
		}

		friend XTTimespan operator+(const XTTimespan& timespan, int64_t offset) noexcept
		{
			return XTTimespan(timespan.total() + offset);
		}
		friend XTTimespan operator+(int64_t offset, const XTTimespan& timespan) noexcept
		{
			return XTTimespan(offset + timespan.total());
		}
		friend XTTimespan operator+(const XTTimespan& timespan1, const XTTimespan& timespan2) noexcept
		{
			return XTTimespan(timespan1.total() + timespan2.total());
		}

		friend XTTimespan operator-(const XTTimespan& timespan, int64_t offset) noexcept
		{
			return XTTimespan(timespan.total() - offset);
		}
		friend XTTimespan operator-(int64_t offset, const XTTimespan& timespan) noexcept
		{
			return XTTimespan(offset - timespan.total());
		}
		friend XTTimespan operator-(const XTTimespan& timespan1, const XTTimespan& timespan2) noexcept
		{
			return XTTimespan(timespan1.total() - timespan2.total());
		}

		// XTTimespan comparison
		friend bool operator==(const XTTimespan& timespan, int64_t offset) noexcept
		{
			return timespan.total() == offset;
		}
		friend bool operator==(int64_t offset, const XTTimespan& timespan) noexcept
		{
			return offset == timespan.total();
		}
		friend bool operator==(const XTTimespan& timespan1, const XTTimespan& timespan2) noexcept
		{
			return timespan1.total() == timespan2.total();
		}

		friend bool operator!=(const XTTimespan& timespan, int64_t offset) noexcept
		{
			return timespan.total() != offset;
		}
		friend bool operator!=(int64_t offset, const XTTimespan& timespan) noexcept
		{
			return offset != timespan.total();
		}
		friend bool operator!=(const XTTimespan& timespan1, const XTTimespan& timespan2) noexcept
		{
			return timespan1.total() != timespan2.total();
		}

		friend bool operator>(const XTTimespan& timespan, int64_t offset) noexcept
		{
			return timespan.total() > offset;
		}
		friend bool operator>(int64_t offset, const XTTimespan& timespan) noexcept
		{
			return offset > timespan.total();
		}
		friend bool operator>(const XTTimespan& timespan1, const XTTimespan& timespan2) noexcept
		{
			return timespan1.total() > timespan2.total();
		}

		friend bool operator<(const XTTimespan& timespan, int64_t offset) noexcept
		{
			return timespan.total() < offset;
		}
		friend bool operator<(int64_t offset, const XTTimespan& timespan) noexcept
		{
			return offset < timespan.total();
		}
		friend bool operator<(const XTTimespan& timespan1, const XTTimespan& timespan2) noexcept
		{
			return timespan1.total() < timespan2.total();
		}

		friend bool operator>=(const XTTimespan& timespan, int64_t offset) noexcept
		{
			return timespan.total() >= offset;
		}
		friend bool operator>=(int64_t offset, const XTTimespan& timespan) noexcept
		{
			return offset >= timespan.total();
		}
		friend bool operator>=(const XTTimespan& timespan1, const XTTimespan& timespan2) noexcept
		{
			return timespan1.total() >= timespan2.total();
		}

		friend bool operator<=(const XTTimespan& timespan, int64_t offset) noexcept
		{
			return timespan.total() <= offset;
		}
		friend bool operator<=(int64_t offset, const XTTimespan& timespan) noexcept
		{
			return offset <= timespan.total();
		}
		friend bool operator<=(const XTTimespan& timespan1, const XTTimespan& timespan2) noexcept
		{
			return timespan1.total() <= timespan2.total();
		}

		//! Convert timespan to the std::chrono nanoseconds duration
		std::chrono::system_clock::duration chrono() const noexcept
		{
			return std::chrono::duration_cast<std::chrono::system_clock::duration>(std::chrono::nanoseconds(_duration));
		}

		//! Get total days of the current timespan
		int64_t days() const noexcept
		{
			return _duration / (24 * 60 * 60 * 1000000000ll);
		}
		//! Get total hours of the current timespan
		int64_t hours() const noexcept
		{
			return _duration / (60 * 60 * 1000000000ll);
		}
		//! Get total minutes of the current timespan
		int64_t minutes() const noexcept
		{
			return _duration / (60 * 1000000000ll);
		}
		//! Get total seconds of the current timespan
		int64_t seconds() const noexcept
		{
			return _duration / 1000000000;
		}
		//! Get total milliseconds of the current timespan
		int64_t milliseconds() const noexcept
		{
			return _duration / 1000000;
		}
		//! Get total microseconds of the current timespan
		int64_t microseconds() const noexcept
		{
			return _duration / 1000;
		}
		//! Get total nanoseconds of the current timespan
		int64_t nanoseconds() const noexcept
		{
			return _duration;
		}

		//! Get total value of the current timespan (total nanoseconds)
		int64_t total() const noexcept
		{
			return _duration;
		}

		//! Create the timespan based on the given days value
		static XTTimespan days(int64_t days) noexcept
		{
			return XTTimespan(days * 24 * 60 * 60 * 1000000000ll);
		}
		//! Create the timespan based on the given hours value
		static XTTimespan hours(int64_t hours) noexcept
		{
			return XTTimespan(hours * 60 * 60 * 1000000000ll);
		}
		//! Create the timespan based on the given minutes value
		static XTTimespan minutes(int64_t minutes) noexcept
		{
			return XTTimespan(minutes * 60 * 1000000000ll);
		}
		//! Create the timespan based on the given seconds value
		static XTTimespan seconds(int64_t seconds) noexcept
		{
			return XTTimespan(seconds * 1000000000);
		}
		//! Create the timespan based on the given milliseconds value
		static XTTimespan milliseconds(int64_t milliseconds) noexcept
		{
			return XTTimespan(milliseconds * 1000000);
		}
		//! Create the timespan based on the given microseconds value
		static XTTimespan microseconds(int64_t microseconds) noexcept
		{
			return XTTimespan(microseconds * 1000);
		}
		//! Create the timespan based on the given nanoseconds value
		static XTTimespan nanoseconds(int64_t nanoseconds) noexcept
		{
			return XTTimespan(nanoseconds);
		}

		//! Get zero timespan
		/*!
			Thread-safe.

			\return Zero timestamp
		*/
		static XTTimespan zero() noexcept { return XTTimespan(0); }

		//! Swap two instances
		void swap(XTTimespan& timespan) noexcept;
		friend void swap(XTTimespan& timespan1, XTTimespan& timespan2) noexcept;

	private:
		int64_t _duration;
	};

////
	inline void XTTimespan::swap(XTTimespan& timespan) noexcept
	{
		using std::swap;
		swap(_duration, timespan._duration);
	}

	inline void swap(XTTimespan& timespan1, XTTimespan& timespan2) noexcept
	{
		timespan1.swap(timespan2);
	}

} // namespace  XT

namespace std {

	template <>
	struct hash<XT::XTTimespan>
	{
		typedef XT::XTTimespan argument_type;
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