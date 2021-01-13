#pragma once
#ifndef XT_MEMDB_FRAME_H
#define XT_MEMDB_FRAME_H


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
#include "MemDBEvent.h"

namespace XT
{

#ifdef _WIN32
#pragma  pack(push, 1)
#endif
	struct MemDBFrameHeader
	{
		/** total frame length (including header and data body) */
		volatile uint32_t length;
		/** header length */
		uint32_t header_length;
		/** generate time of the frame data */
		int64_t gen_time;
		/** trigger time for this frame, use for latency stats */
		int64_t trigger_time;
		/** msg type of the data in frame */
		volatile int32_t msg_type;
		/** source of this frame */
		uint32_t source;
		/** dest of this frame */
		uint32_t dest;
#ifndef _WIN32
	} __attribute__((packed));
#else
};
#pragma pack(pop)
#endif


	/**
	* Basic memory unit,
	* holds header / data / errorMsg (if needs)
	*/
	class MemDBFrame : public MsgEvent
	{
	public:

		~MemDBFrame() override = default;

		bool has_data() const
		{
			return header_->length > 0 && header_->msg_type > 0;
		}

		uintptr_t address() const
		{
			return reinterpret_cast<uintptr_t>(header_);
		}

		uint32_t frame_length() const
		{
			return header_->length;
		}

		uint32_t header_length() const
		{
			return header_->header_length;
		}

		uint32_t data_length() const override
		{
			return frame_length() - header_length();
		}

		int64_t gen_time() const override
		{
			return header_->gen_time;
		}

		int64_t trigger_time() const override
		{
			return header_->trigger_time;
		}

		int32_t msg_type() const override
		{
			return header_->msg_type;
		}

		uint32_t source() const override
		{
			return header_->source;
		}

		uint32_t dest() const override
		{
			return header_->dest;
		}

		const char *data_as_bytes() const override
		{
			return reinterpret_cast<char *>(address() + header_length());
		}

		const std::string data_as_string() const override
		{
			return std::string(data_as_bytes());
		}

		const std::string to_string() const override
		{
			return std::string(reinterpret_cast<char *>(address()));
		}

		template<typename T>
		size_t copy_data(const T& data)
		{
			size_t length = sizeof(T);
			memcpy(const_cast<void *>(data_address()), &data, length);
			return length;
		}

	protected:
		const void *data_address() const override
		{
			return reinterpret_cast<void *>(address() + header_length());
		}

	private:

		/** address with type,
		* will keep moving forward until change page */
		MemDBFrameHeader *header_;

		MemDBFrame() = default;

		void set_address(uintptr_t address)
		{
			header_ = reinterpret_cast<MemDBFrameHeader *>(address);
		}

		void move_to_next()
		{
			set_address(address() + frame_length());
		}

		void set_header_length()
		{
			header_->header_length = sizeof(MemDBFrameHeader);
		}

		void set_data_length(uint32_t length)
		{
			header_->length = header_length() + length;
		}

		void set_gen_time(int64_t gen_time)
		{
			header_->gen_time = gen_time;
		}

		void set_trigger_time(int64_t trigger_time)
		{
			header_->trigger_time = trigger_time;
		}

		void set_msg_type(int32_t msg_type)
		{
			header_->msg_type = msg_type;
		}

		void set_source(uint32_t source)
		{
			header_->source = source;
		}

		void set_dest(uint32_t dest)
		{
			header_->dest = dest;
		}

		friend class MemDBJournal;

		friend class MemDBWriter;
	};
	typedef std::shared_ptr<MemDBFrame> MemDBFramePtr;




}//namespace 

#endif