#pragma once
#ifndef XT_MEMDB_JOURNAL_H
#define XT_MEMDB_JOURNAL_H


#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include <memory>
#include <thread>
#include <mutex>

#include "XTConfig.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "log4z.h"

#include "StringUtil.h"
#include "TimeUtil.h"

#include "MemDBData.h"
//#include "MemDBCommon.h"
#include "MemDBFrame.h"
#include "MemDBPage.h"

namespace XT
{

	/**
	* Journal class, the abstraction of continuous memory access
	*/
	class MemDBJournal;
	typedef std::shared_ptr<MemDBJournal> MemDBJournalPtr;

	class MemDBJournal
	{
	public:
		MemDBJournal(MemDBLocationPtr location, uint32_t dest_id, bool is_writing, bool lazy) :
			location_(std::move(location)), dest_id_(dest_id), is_writing_(is_writing), lazy_(lazy),
			frame_(std::shared_ptr<MemDBFrame>(new MemDBFrame())), page_frame_nb_(0)
		{}

		~MemDBJournal();

		MemDBFramePtr& current_frame()
		{
			return frame_;
		}

		/**
		* move current frame to the next available one
		*/
		void next();

		/**
		* makes sure after this call, next time user calls current_frame() gets the right available frame
		* (gen_time() > nanotime or writable)
		* @param nanotime
		*/
		void seek_to_time(int64_t nanotime);

	private:
		MemDBLocationPtr location_;  //const MemDBLocationPtr location_;
		const uint32_t dest_id_;
		const bool is_writing_;
		const bool lazy_;
		MemDBPagePtr current_page_;
		MemDBFramePtr frame_;
		int page_frame_nb_;

		void load_page(int page_id);

		/** load next page, current page will be released if not empty */
		void load_next_page();

		friend class MemDBReader;

		friend class MemDBWriter;
	};


	//////

	class MemDBReader
	{
	public:
		explicit MemDBReader(bool lazy) : lazy_(lazy), current_(nullptr)
		{};

		~MemDBReader();

		/**
		* join journal at given data location
		* @param location where the journal locates
		* @param dest_id journal dest id
		* @param from_time subscribe events after this time, 0 means from start
		*/
		void join(const MemDBLocationPtr &location, uint32_t dest_id, int64_t from_time);

		void disjoin(uint32_t location_uid);

		MemDBFramePtr current_frame()
		{
			return current_->current_frame();
		}

		bool data_available();

		/** seek journal to time */
		void seek_to_time(int64_t nanotime);

		/** seek next frame */
		void next();

		void sort();

	private:
		const bool lazy_;
		MemDBJournal *current_;
		std::vector<MemDBJournalPtr> journals_;
	};
	typedef std::shared_ptr<MemDBReader> MemDBReaderPtr;

	class MemDBWriter
	{
	public:
		MemDBWriter(const MemDBLocationPtr &location, uint32_t dest_id, bool lazy, MsgPublisherPtr publisher);

		const MemDBLocationPtr &get_location() const
		{
			return journal_->location_;
		}

		uint32_t get_dest() const
		{
			return journal_->dest_id_;
		}

		uint64_t current_frame_uid();

		MemDBFramePtr open_frame(int64_t trigger_time, int32_t msg_type, uint32_t length);

		void close_frame(size_t data_length);

		void mark(int64_t trigger_time, int32_t msg_type);

		void mark_with_time(int64_t trigger_time, int32_t msg_type);

		/**
		* Using auto with the return mess up the reference with the undlerying memory address, DO NOT USE it.
		* @tparam T
		* @param trigger_time
		* @param msg_type
		* @return a casted reference to the underlying memory address in mmap file
		*/
		template<typename T>
		T &open_data(int64_t trigger_time, int32_t msg_type)
		{
			auto frame = open_frame(trigger_time, msg_type, sizeof(T));
			size_to_write_ = sizeof(T);
			return const_cast<T &>(frame->data<T>());
		}

		void close_data()
		{
			size_t length = size_to_write_;
			size_to_write_ = 0;
			close_frame(length);
		}

		template<typename T>
		void write(int64_t trigger_time, int32_t msg_type, const T &data)
		{
			auto frame = open_frame(trigger_time, msg_type, sizeof(T));
			close_frame(frame->copy_data<T>(data));
		}

		template<typename T>
		void write_with_time(int64_t gen_time, int32_t msg_type, const T &data)
		{
			assert(sizeof(MemDBFrameHeader) + sizeof(T) + sizeof(MemDBFrameHeader) <= journal_->current_page_->get_page_size());
			if (journal_->current_frame()->address() + sizeof(MemDBFrameHeader) + sizeof(T) > journal_->current_page_->address_border())
			{
				mark(gen_time, MemDBMsgType::PageEnd);
				journal_->load_next_page();
			}
			auto frame = journal_->current_frame();
			frame->set_header_length();
			frame->set_trigger_time(0);
			frame->set_msg_type(msg_type);
			frame->set_source(journal_->location_->uid);
			frame->set_dest(journal_->dest_id_);

			frame->copy_data<T>(data);
			frame->set_gen_time(gen_time);
			frame->set_data_length(sizeof(T));
			journal_->current_page_->set_last_frame_position(frame->address() - journal_->current_page_->address());
			journal_->next();
		}

		void write_raw(int64_t trigger_time, int32_t msg_type, uintptr_t data, uint32_t length);

	private:
		std::mutex writer_mtx_;
		MemDBJournalPtr journal_;
		uint64_t frame_id_base_;
		MsgPublisherPtr publisher_;
		size_t size_to_write_;

		void close_page(int64_t trigger_time);
	};
	typedef std::shared_ptr<MemDBWriter> MemDBWriterPtr;
/////////////////

}//namespace 

#endif