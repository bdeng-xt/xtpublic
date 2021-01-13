#pragma once
#ifndef XT_XTTIME_H
#define XT_XTTIME_H

/**
* \file XTTime.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for time.
*
* \description
*	Designed for use for time.
*/

#include <cstdint>
#include <cstring>

#include <chrono>

#include "XTConfig.h"

#include "XTTimestamp.h"

namespace XT
{

	//! XTTime
	/*!
		XTTime wraps date & time in a single object with a set of accessors - year, month, day,
		hours, minutes, seconds, milliseconds, microseconds or nanoseconds.

		32-bit: time is limited in range 1970-01-01T00:00:00Z - 2038-01-18T23:59:59Z
		64-bit: time is limited in range 1970-01-01T00:00:00Z - 3000-12-31T23:59:59Z

		Not thread-safe.
	*/
	class XT_COMMON_API XTTime
	{
	public:
		//! Initialize time with an epoch time
		XTTime() noexcept;
		//! Initialize time with a given date & time components (year, month, day, hour, minute, second, etc.)
		/*!
			\param year - Year value (1970-2038 for 32-bit or 1970-3000 for 64-bit)
			\param month - Month value (1-12)
			\param day - Day value (1-31)
			\param hour - Hour value (0-23) (default is 0)
			\param minute - Minute value (0-59) (default is 0)
			\param second - Second value (0-59) (default is 0)
			\param millisecond - Millisecond value (0-999) (default is 0)
			\param microsecond - Microsecond value (0-999) (default is 0)
			\param nanosecond - Nanosecond value (0-999) (default is 0)
		*/
		explicit XTTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0, int nanosecond = 0);
		XTTime(const XTTime&) noexcept = default;
		XTTime(XTTime&&) noexcept = default;
		~XTTime() noexcept = default;

		XTTime& operator=(const XTTimestamp& timestamp)
		{
			return operator=(XTTime(timestamp));
		}
		XTTime& operator=(const XTTime&) noexcept = default;
		XTTime& operator=(XTTime&&) noexcept = default;

		// XTTime offset operations
		XTTime& operator+=(const XTTimespan& offset)
		{
			return operator=(XTTime(utcstamp() + offset));
		}

		XTTime& operator-=(const XTTimespan& offset)
		{
			return operator=(XTTime(utcstamp() - offset));
		}

		friend XTTime operator+(const XTTime& time, const XTTimespan& offset)
		{
			return XTTime(time.utcstamp() + offset);
		}
		friend XTTime operator+(const XTTimespan& offset, const XTTime& time)
		{
			return XTTime(offset + time.utcstamp());
		}

		friend XTTime operator-(const XTTime& time, const XTTimespan& offset)
		{
			return XTTime(time.utcstamp() - offset);
		}
		friend XTTime operator-(const XTTimespan& offset, const XTTime& time)
		{
			return XTTime(offset - time.utcstamp());
		}

		friend XTTimespan operator-(const XTTime& time1, const XTTime& time2)
		{
			return time1.utcstamp() - time2.utcstamp();
		}

		// XTTime comparison
		friend bool operator==(const XTTime& time, const XTTimestamp& timestamp)
		{
			return time == XTTime(timestamp);
		}
		friend bool operator==(const XTTimestamp& timestamp, const XTTime& time)
		{
			return XTTime(timestamp) == time;
		}
		friend bool operator==(const XTTime& time1, const XTTime& time2) noexcept;

		friend bool operator!=(const XTTime& time, const XTTimestamp& timestamp)
		{
			return time != XTTime(timestamp);
		}
		friend bool operator!=(const XTTimestamp& timestamp, const XTTime& time)
		{
			return XTTime(timestamp) != time;
		}
		friend bool operator!=(const XTTime& time1, const XTTime& time2) noexcept;

		friend bool operator>(const XTTime& time, const XTTimestamp& timestamp)
		{
			return time > XTTime(timestamp);
		}
		friend bool operator>(const XTTimestamp& timestamp, const XTTime& time)
		{
			return XTTime(timestamp) > time;
		}
		friend bool operator>(const XTTime& time1, const XTTime& time2) noexcept;

		friend bool operator<(const XTTime& time, const XTTimestamp& timestamp)
		{
			return time < XTTime(timestamp);
		}
		friend bool operator<(const XTTimestamp& timestamp, const XTTime& time)
		{
			return XTTime(timestamp) < time;
		}
		friend bool operator<(const XTTime& time1, const XTTime& time2) noexcept;

		friend bool operator>=(const XTTime& time, const XTTimestamp& timestamp)
		{
			return time >= XTTime(timestamp);
		}
		friend bool operator>=(const XTTimestamp& timestamp, const XTTime& time)
		{
			return XTTime(timestamp) >= time;
		}
		friend bool operator>=(const XTTime& time1, const XTTime& time2) noexcept;

		friend bool operator<=(const XTTime& time, const XTTimestamp& timestamp)
		{
			return time <= XTTime(timestamp);
		}
		friend bool operator<=(const XTTimestamp& timestamp, const XTTime& time)
		{
			return XTTime(timestamp) <= time;
		}
		friend bool operator<=(const XTTime& time1, const XTTime& time2) noexcept;

		//! Convert date & time to the std::chrono time point
		std::chrono::time_point<std::chrono::system_clock> chrono() const
		{
			return utcstamp().chrono();
		}

		//! Get year value (1970-2038 for 32-bit or 1970-3000 for 64-bit)
		int year() const noexcept { return _year; }
		//! Get month value (1-12)
		int month() const noexcept { return _month; }
		//! Get day value (1-31)
		int day() const noexcept { return _day; }
		//! Get hour value (0-23)
		int hour() const noexcept { return _hour; }
		//! Get minute value (0-59)
		int minute() const noexcept { return _minute; }
		//! Get second value (0-59)
		int second() const noexcept { return _second; }
		//! Get millisecond value (0-999)
		int millisecond() const noexcept { return _millisecond; }
		//! Get microsecond value (0-999)
		int microsecond() const noexcept { return _microsecond; }
		//! Get nanosecond value (0-999)
		int nanosecond() const noexcept { return _nanosecond; }

		//! Get UTC timestamp from the current date & time value
		XTUtcTimestamp utcstamp() const;
		//! Get local timestamp from the current date & time value
		XTLocalTimestamp localstamp() const;

		//! Get the epoch date & time
		/*!
			Thread-safe.

			\return Epoch date & time
		*/
		static XTTime epoch()
		{
			return XTTime(1970, 1, 1);
		}

		//! Swap two instances
		void swap(XTTime& time) noexcept;
		friend void swap(XTTime& time1, XTTime& time2) noexcept;

	protected:
		//! Year value
		int _year;
		//! Month value
		int _month;
		//! Day value
		int _day;
		//! Hour value
		int _hour;
		//! Minute value
		int _minute;
		//! Second value
		int _second;
		//! Millisecond value
		int _millisecond;
		//! Microsecond value
		int _microsecond;
		//! Nanosecond value
		int _nanosecond;

		//! Protected initialize time with a timestamp
		/*!
			\param timestamp - XTTimestamp
		*/
		explicit XTTime(const XTTimestamp& timestamp);
	};

	// Forward class declarations
	class XTUtcTime;
	class XTLocalTime;

	//! UTC time
	class XTUtcTime : public XTTime
	{
	public:
//		using Time::Time;
//		using Time::chrono;

		//! Initialize UTC time with a current value
		XTUtcTime() : XTUtcTime(XTUtcTimestamp()) {}
		//! Initialize UTC time with a given timestamp
		/*!
			\param timestamp - XTTimestamp
		*/
		explicit XTUtcTime(const XTTimestamp& timestamp);
		//! Initialize UTC time with a given std::chrono time point
		/*!
			\param time_point - std::chrono time point
		*/
		template <class Clock, class Duration>
		explicit XTUtcTime(const std::chrono::time_point<Clock, Duration>& time_point) : XTUtcTime(XTTimestamp(time_point)) {}
		//! Initialize UTC time with another time value
		XTUtcTime(const XTTime& time) : XTTime(time) {}
		//! Initialize UTC time with another local time value
		XTUtcTime(const XTLocalTime& time);
	};

	//! Local time
	class XTLocalTime : public XTTime
	{
	public:
//		using Time::Time;
//		using Time::chrono;

		//! Initialize local time with a current value
		XTLocalTime() : XTLocalTime(XTUtcTimestamp()) {}
		//! Initialize local time with a given timestamp
		/*!
			\param timestamp - XTTimestamp
		*/
		explicit XTLocalTime(const XTTimestamp& timestamp);
		//! Initialize local time with a given std::chrono time point
		/*!
			\param time_point - std::chrono time point
		*/
		template <class Clock, class Duration>
		explicit XTLocalTime(const std::chrono::time_point<Clock, Duration>& time_point) : XTLocalTime(XTTimestamp(time_point)) {}
		//! Initialize local time with another time value
		XTLocalTime(const XTTime& time) : XTTime(time) {}
		//! Initialize local time with another UTC time value
		XTLocalTime(const XTUtcTime& time);
	};


}//namespace XT
//////////////////////

namespace XT 
{

	inline XTTime::XTTime() noexcept
		: _year(1970),
		_month(1),
		_day(1),
		_hour(0),
		_minute(0),
		_second(0),
		_millisecond(0),
		_microsecond(0),
		_nanosecond(0)
	{
	}

	inline bool operator==(const XTTime& time1, const XTTime& time2) noexcept
	{
		return ((time1._year == time2._year) && (time1._month == time2._month) && (time1._day == time2._day) &&
			(time1._hour == time2._hour) && (time1._minute == time2._minute) && (time1._second == time2._second) &&
			(time1._millisecond == time2._millisecond) && (time1._microsecond == time2._microsecond) && (time1._nanosecond == time2._nanosecond));
	}

	inline bool operator!=(const XTTime& time1, const XTTime& time2) noexcept
	{
		return ((time1._year != time2._year) || (time1._month != time2._month) || (time1._day != time2._day) ||
			(time1._hour != time2._hour) || (time1._minute != time2._minute) || (time1._second != time2._second) ||
			(time1._millisecond != time2._millisecond) || (time1._microsecond != time2._microsecond) || (time1._nanosecond != time2._nanosecond));
	}

	inline bool operator>(const XTTime& time1, const XTTime& time2) noexcept
	{
		if (time1._year < time2._year)
			return false;
		else if (time1._year == time2._year)
		{
			if (time1._month < time2._month)
				return false;
			else if (time1._month == time2._month)
			{
				if (time1._day < time2._day)
					return false;
				else if (time1._day == time2._day)
				{
					if (time1._hour < time2._hour)
						return false;
					else if (time1._hour == time2._hour)
					{
						if (time1._minute < time2._minute)
							return false;
						else if (time1._minute == time2._minute)
						{
							if (time1._second < time2._second)
								return false;
							else if (time1._second == time2._second)
							{
								if (time1._millisecond < time2._millisecond)
									return false;
								else if (time1._millisecond == time2._millisecond)
								{
									if (time1._microsecond < time2._microsecond)
										return false;
									else if (time1._microsecond == time2._microsecond)
									{
										if (time1._nanosecond <= time2._nanosecond)
											return false;
									}
								}
							}
						}
					}
				}
			}
		}
		return true;
	}

	inline bool operator<(const XTTime& time1, const XTTime& time2) noexcept
	{
		if (time1._year > time2._year)
			return false;
		else if (time1._year == time2._year)
		{
			if (time1._month > time2._month)
				return false;
			else if (time1._month == time2._month)
			{
				if (time1._day > time2._day)
					return false;
				else if (time1._day == time2._day)
				{
					if (time1._hour > time2._hour)
						return false;
					else if (time1._hour == time2._hour)
					{
						if (time1._minute > time2._minute)
							return false;
						else if (time1._minute == time2._minute)
						{
							if (time1._second > time2._second)
								return false;
							else if (time1._second == time2._second)
							{
								if (time1._millisecond > time2._millisecond)
									return false;
								else if (time1._millisecond == time2._millisecond)
								{
									if (time1._microsecond > time2._microsecond)
										return false;
									else if (time1._microsecond == time2._microsecond)
									{
										if (time1._nanosecond >= time2._nanosecond)
											return false;
									}
								}
							}
						}
					}
				}
			}
		}
		return true;
	}

	inline bool operator>=(const XTTime& time1, const XTTime& time2) noexcept
	{
		if (time1._year < time2._year)
			return false;
		else if (time1._year == time2._year)
		{
			if (time1._month < time2._month)
				return false;
			else if (time1._month == time2._month)
			{
				if (time1._day < time2._day)
					return false;
				else if (time1._day == time2._day)
				{
					if (time1._hour < time2._hour)
						return false;
					else if (time1._hour == time2._hour)
					{
						if (time1._minute < time2._minute)
							return false;
						else if (time1._minute == time2._minute)
						{
							if (time1._second < time2._second)
								return false;
							else if (time1._second == time2._second)
							{
								if (time1._millisecond < time2._millisecond)
									return false;
								else if (time1._millisecond == time2._millisecond)
								{
									if (time1._microsecond < time2._microsecond)
										return false;
									else if (time1._microsecond == time2._microsecond)
									{
										if (time1._nanosecond < time2._nanosecond)
											return false;
									}
								}
							}
						}
					}
				}
			}
		}
		return true;
	}

	inline bool operator<=(const XTTime& time1, const XTTime& time2) noexcept
	{
		if (time1._year > time2._year)
			return false;
		else if (time1._year == time2._year)
		{
			if (time1._month > time2._month)
				return false;
			else if (time1._month == time2._month)
			{
				if (time1._day > time2._day)
					return false;
				else if (time1._day == time2._day)
				{
					if (time1._hour > time2._hour)
						return false;
					else if (time1._hour == time2._hour)
					{
						if (time1._minute > time2._minute)
							return false;
						else if (time1._minute == time2._minute)
						{
							if (time1._second > time2._second)
								return false;
							else if (time1._second == time2._second)
							{
								if (time1._millisecond > time2._millisecond)
									return false;
								else if (time1._millisecond == time2._millisecond)
								{
									if (time1._microsecond > time2._microsecond)
										return false;
									else if (time1._microsecond == time2._microsecond)
									{
										if (time1._nanosecond > time2._nanosecond)
											return false;
									}
								}
							}
						}
					}
				}
			}
		}
		return true;
	}

	inline void XTTime::swap(XTTime& time) noexcept
	{
		using std::swap;
		swap(_year, time._year);
		swap(_month, time._month);
		swap(_day, time._day);
		swap(_hour, time._hour);
		swap(_minute, time._minute);
		swap(_second, time._second);
		swap(_millisecond, time._millisecond);
		swap(_microsecond, time._microsecond);
		swap(_nanosecond, time._nanosecond);
	}

	inline void swap(XTTime& time1, XTTime& time2) noexcept
	{
		time1.swap(time2);
	}

	inline XTUtcTime::XTUtcTime(const XTLocalTime& time) : XTUtcTime(time.localstamp())
	{}

	inline XTLocalTime::XTLocalTime(const XTUtcTime& time) : XTLocalTime(time.utcstamp())
	{}

} // namespace XT

namespace std {

	template <>
	struct hash<XT::XTTime>
	{
		typedef XT::XTTime argument_type;
		typedef size_t result_type;

		result_type operator () (const argument_type& value) const
		{
			result_type result = 17;
			std::hash<int> hasher;
			result = result * 31 + hasher(value.year());
			result = result * 31 + hasher(value.month());
			result = result * 31 + hasher(value.day());
			result = result * 31 + hasher(value.hour());
			result = result * 31 + hasher(value.minute());
			result = result * 31 + hasher(value.second());
			result = result * 31 + hasher(value.millisecond());
			result = result * 31 + hasher(value.microsecond());
			result = result * 31 + hasher(value.nanosecond());
			return result;
		}
	};

} // namespace std

#endif