#pragma once
#ifndef XT_MEMDB_PAGE_H
#define XT_MEMDB_PAGE_H


#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include <memory>

#include "XTConfig.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "log4z.h"

#include "StringUtil.h"
#include "TimeUtil.h"

#include "MemDBData.h"
 
#include "MemDBFrame.h"

namespace XT
{

#ifdef _WIN32
#pragma  pack(push, 1)
#endif
	struct MemDBPageHeader
	{
		uint32_t version;
		uint32_t page_header_length;
		uint32_t page_size;
		uint32_t frame_header_length;
		uint64_t last_frame_position;
#ifndef _WIN32
	} __attribute__((packed));
#else
};
#pragma pack(pop)
#endif

	class MemDBPage;
	typedef std::shared_ptr<MemDBPage> MemDBPagePtr;

	class MemDBPage
	{
	public:
		~MemDBPage();

		uint32_t get_page_size() const
		{
			return header_->page_size;
		}

		MemDBLocationPtr get_location() const
		{
			return location_;
		}

		uint32_t get_dest_id() const
		{
			return dest_id_;
		}

		int get_page_id() const
		{
			return page_id_;
		}

		int64_t begin_time() const
		{
			return reinterpret_cast<MemDBFrameHeader *>(first_frame_address())->gen_time;
		}

		int64_t end_time() const
		{
			return reinterpret_cast<MemDBFrameHeader *>(last_frame_address())->gen_time;
		}

		uintptr_t address() const
		{
			return reinterpret_cast<uintptr_t>(header_);
		}

		uintptr_t address_border() const
		{
			return address() + header_->page_size - sizeof(MemDBFrameHeader);
		}

		uintptr_t first_frame_address() const
		{
			return address() + header_->page_header_length;
		}

		uintptr_t last_frame_address() const
		{
			return address() + header_->last_frame_position;
		}

		bool is_full() const
		{
			return last_frame_address() + reinterpret_cast<MemDBFrameHeader *>(last_frame_address())->length > address_border();
		}

		static MemDBPagePtr load(MemDBLocationPtr& location, uint32_t dest_id, int page_id, bool is_writing, bool lazy);

		static std::string get_page_path(MemDBLocationPtr& location, uint32_t dest_id, int id);

		static int find_page_id(MemDBLocationPtr& location, uint32_t dest_id, int64_t time);

		static uint32_t find_page_size(MemDBLocationPtr& location, uint32_t dest_id);
	private:

		const MemDBLocationPtr location_;
		const uint32_t dest_id_;
		const int page_id_;
		const bool lazy_;
		const size_t size_;
		const MemDBPageHeader *header_;

		MemDBPage(const MemDBLocationPtr& location, uint32_t dest_id, int page_id, size_t size, bool lazy, uintptr_t address);

		/**
		* update page header when new frame added
		*/
		void set_last_frame_position(uint64_t position);

		friend class MemDBJournal;
		friend class MemDBWriter;
		friend class MemDBReader;
	};//class MemDBPage


}//namespace


#endif