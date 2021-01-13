#pragma once
#ifndef XT_MEMDB_DATA_H
#define XT_MEMDB_DATA_H


#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include <memory>

#include "XTConfig.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"

#include "fmt/format.h"
#include "MemDBUtil.h" 


namespace XT
{
#ifdef _WIN32
#pragma  pack(push, 1)
#endif
	struct TimeRequest
	{
		int32_t id;
		int64_t duration;
		int64_t repeat;
#ifndef _WIN32
	} __attribute__((packed));

#else
};
#endif

	struct RequestReadFrom
	{
		uint32_t source_id;
		int64_t from_time;

#ifndef _WIN32
	} __attribute__((packed));

#else
				};
#endif

	struct RequestWriteTo
	{
		uint32_t dest_id;

#ifndef _WIN32
	} __attribute__((packed));

#else
				};
#endif


	struct Channel
	{
		uint32_t source_id;
		uint32_t dest_id;
#ifndef _WIN32
	} __attribute__((packed));
#else
			};
#endif

#ifdef _WIN32
#pragma pack(pop)
#endif
/////////////////////////
	class MemDBLocator;// forward declaration
	typedef std::shared_ptr<MemDBLocator> MemDBLocatorPtr;
	
	class MemDBLocation; //forward declaration
	typedef std::shared_ptr<MemDBLocation> MemDBLocationPtr;
	
	class MemDBLocator
	{
	public:
		MemDBLocator() = default;

		virtual ~MemDBLocator() = default;

		virtual bool has_env(const std::string &name) const = 0;

		virtual const std::string get_env(const std::string &name) const = 0;

		virtual const std::string layout_dir(MemDBLocationPtr& location, int dsttype) const = 0;

		virtual const std::string layout_file(MemDBLocationPtr& location, int  dsttype, const std::string &name) const = 0;

		virtual const std::string default_to_system_db(MemDBLocationPtr& location, const std::string &name) const = 0;

		virtual const std::vector<int> list_page_id(MemDBLocationPtr& location, uint32_t dest_id) const = 0;
	};

	class MemDBLocation : public std::enable_shared_from_this<MemDBLocation>
	{
	public:
		MemDBLocation(int m, int c, std::string g, std::string n, MemDBLocatorPtr l) :
			mode(m), category(c), group(std::move(g)), name(std::move(n)), locator(std::move(l)),
			uname(fmt::format("{}/{}/{}/{}", (XT::EventCategoryType_enumtype_IsValid(c) ? XT::EventCategoryType_enumtype_Name((XT::EventCategoryType::enumtype)c) : "Unknown"), group, name, (XT::EventModeType_enumtype_IsValid(m) ? XT::EventModeType_enumtype_Name((XT::EventModeType::enumtype)m) : "Unknown"))),
			uid(MemDBUtil::hash_str_32(uname))
		{
 
		}

		virtual ~MemDBLocation() = default;

		const int mode;
		const int  category;
		const std::string group;
		const std::string name;
		const std::string uname;
		const uint32_t uid;
		const MemDBLocatorPtr locator;

		static inline MemDBLocationPtr make(int mode, int category , std::string group, std::string name, MemDBLocatorPtr locator)
		{
			return std::make_shared<MemDBLocation>(mode, category, group, name, locator);
		}
	};

////////////

	class URLFactory
	{
	public:
		virtual const std::string make_path_bind(MemDBLocationPtr& location, int protocol ) const = 0;

		virtual const std::string make_path_connect(MemDBLocationPtr& location, int protocol ) const = 0;
	};
	typedef std::shared_ptr<URLFactory> URLFactoryPtr;
}//namespace 


#endif //