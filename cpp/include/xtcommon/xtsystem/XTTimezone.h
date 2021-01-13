#pragma once
#ifndef XT_XTTIMEZONE_H
#define XT_XTTIMEZONE_H

/**
* \file XTTimezone.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for timezone.
*
* \description
*	Designed for use for timezone.
*/

#include <cstdint>
#include <string>
#include "XTConfig.h"

#include "XTTime.h"

namespace XT
{

	//! Time zone
	/*!
		Time zone wraps the current time zone and dynamic daylight saving time settings.

		Not thread-safe.
	*/
	class XT_COMMON_API XTTimezone
	{
	public:
		//! Initialize timezone with a current local time zone
		XTTimezone();
		//! Initialize time zone with a given local time offset and daylight saving time offset
		/*!
			\param name - Time zone name
			\param offset - Local time offset
			\param dstoffset - Daylight saving time offset (default is Timespan::zero())
		*/
		explicit XTTimezone(const std::string& name, const XTTimespan& offset, const XTTimespan& dstoffset = XTTimespan::zero())
			: _name(name), _offset(offset), _dstoffset(dstoffset)
		{}
		XTTimezone(const XTTimezone&) = default;
		XTTimezone(XTTimezone&&) = default;
		~XTTimezone() = default;

		XTTimezone& operator=(const XTTimezone&) = default;
		XTTimezone& operator=(XTTimezone&&) = default;

		// XTTimezone comparison
		friend bool operator==(const XTTimezone& timezone1, const XTTimezone& timezone2) noexcept
		{
			return timezone1.total() == timezone2.total();
		}
		friend bool operator!=(const XTTimezone& timezone1, const XTTimezone& timezone2) noexcept
		{
			return timezone1.total() != timezone2.total();
		}
		friend bool operator>(const XTTimezone& timezone1, const XTTimezone& timezone2) noexcept
		{
			return timezone1.total() > timezone2.total();
		}
		friend bool operator<(const XTTimezone& timezone1, const XTTimezone& timezone2) noexcept
		{
			return timezone1.total() < timezone2.total();
		}
		friend bool operator>=(const XTTimezone& timezone1, const XTTimezone& timezone2) noexcept
		{
			return timezone1.total() >= timezone2.total();
		}
		friend bool operator<=(const XTTimezone& timezone1, const XTTimezone& timezone2) noexcept
		{
			return timezone1.total() <= timezone2.total();
		}

		//! Get time zone name
		const std::string& name() const noexcept { return _name; }
		//! Get time zone offset
		const XTTimespan& offset() const noexcept { return _offset; }
		//! Get time zone daylight saving time offset
		const XTTimespan& daylight() const noexcept { return _dstoffset; }

		//! Get time zone total offset
		XTTimespan total() const noexcept { return _offset + _dstoffset; }

		//! Convert UTC time to local time using the current time zone
		/*!
			\param utctime - UTC time
			\return Local time
		*/
		XTLocalTime Convert(const XTUtcTime& utctime)
		{
			return XTLocalTime(utctime + total());
		}
		//! Convert local time to UTC time using the current time zone
		/*!
			\param localtime - Local time
			\return Local time
		*/
		XTUtcTime Convert(const XTLocalTime& localtime)
		{
			return XTUtcTime(localtime - total());
		}

		//! Get the UTC time zone (Greenwich Mean Time)
		/*!
			Thread-safe.

			\return UTC time zone
		*/
		static XTTimezone utc()
		{
			return XTTimezone("GMT", XTTimespan::zero());
		}

		//! Get the local time zone
		/*!
			Thread-safe.

			\return Local time zone
		*/
		static XTTimezone local()
		{
			return XTTimezone();
		}

		//! Swap two instances
		void swap(XTTimezone& timezone) noexcept;
		friend void swap(XTTimezone& timezone1, XTTimezone& timezone2) noexcept;

	protected:
		//! Time zone name
		std::string _name;
		//! Time zone offset
		XTTimespan _offset;
		//! Time zone daylight saving time offset
		XTTimespan _dstoffset;
	};//class XTTimezone

}//namespace XT


namespace XT {

	inline void XTTimezone::swap(XTTimezone& timezone) noexcept
	{
		using std::swap;
		swap(_name, timezone._name);
		swap(_offset, timezone._offset);
		swap(_dstoffset, timezone._dstoffset);
	}

	inline void swap(XTTimezone& timezone1, XTTimezone& timezone2) noexcept
	{
		timezone1.swap(timezone2);
	}

} // namespace XT

namespace std {

	template <>
	struct hash<XT::XTTimezone>
	{
		typedef XT::XTTimezone argument_type;
		typedef size_t result_type;

		result_type operator () (const argument_type& value) const
		{
			result_type result = 17;
			result = result * 31 + std::hash<std::string>()(value.name());
			result = result * 31 + std::hash<XT::XTTimespan>()(value.offset());
			result = result * 31 + std::hash<XT::XTTimespan>()(value.daylight());
			return result;
		}
	};

} // namespace std


#endif