#pragma once
#ifndef XT_MEMDB_IO_H
#define XT_MEMDB_IO_H


#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include <memory>

#include "XTConfig.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"

#include "fmt/format.h"
#include "MemDBData.h"
#include "MemDBUtil.h"
#include "MemDBFrame.h"
#include "MemDBPage.h"
#include "MemDBJournal.h"

#include "NNGSocket.h"
#include "NNGUtil.h"

namespace XT
{
	class IpcURLFactory : public URLFactory
	{
	public:

		const std::string make_path_bind(MemDBLocationPtr& location, int protocol) const override
		{
			return location->locator->layout_file(location, (int)EventDataDstType::NNG, NNGUtil::get_protocol_name(protocol));
		}

		const std::string make_path_connect(MemDBLocationPtr& location, int protocol) const override
		{
			return location->locator->layout_file(location, (int)EventDataDstType::NNG, NNGUtil::get_protocol_name(NNGUtil::get_opposite_protocol(protocol)));
		}
	};
	typedef std::shared_ptr<IpcURLFactory> IpcURLFactoryPtr;

	class MemDBIODevice
	{
	public:

		MemDBIODevice(MemDBLocationPtr home, bool low_latency, bool lazy);

		const MemDBLocationPtr get_home() const
		{
			return home_;
		}

		const MemDBLocationPtr get_live_home() const
		{
			return live_home_;
		}

		bool is_low_latency()
		{
			return low_latency_;
		}

		MemDBReaderPtr open_reader_to_subscribe();

		MemDBReaderPtr open_reader(const MemDBLocationPtr &location, uint32_t dest_id);

		MemDBWriterPtr open_writer(uint32_t dest_id);

		MemDBWriterPtr open_writer_at(const MemDBLocationPtr &location, uint32_t dest_id);

		NNGSocketPtr
			connect_socket(MemDBLocationPtr &location, int protocol, int timeout = 0);

		NNGSocketPtr
			bind_socket(int protocol, int timeout = 0);

		URLFactoryPtr get_url_factory() const
		{
			return url_factory_;
		}

		MsgPublisherPtr get_publisher()
		{
			return publisher_;
		}

		MsgSubscriberPtr get_observer()
		{
			return observer_;
		}

	protected:
		MemDBLocationPtr home_;
		MemDBLocationPtr live_home_;
		const bool low_latency_;
		const bool lazy_;
		URLFactoryPtr url_factory_;
		MsgPublisherPtr publisher_;
		MsgSubscriberPtr observer_;
	};

	typedef std::shared_ptr<MemDBIODevice> MemDBIODevicePtr;

	class MemDBIODeviceWithReply : public MemDBIODevice
	{
	public:

		MemDBIODeviceWithReply(MemDBLocationPtr home, bool low_latency, bool lazy);

		NNGSocketPtr get_rep_sock() const
		{
			return rep_sock_;
		}

	protected:
		NNGSocketPtr rep_sock_;
	};

	typedef std::shared_ptr<MemDBIODeviceWithReply> MemDBIODeviceWithReplyPtr; //  

	class MemDBIODeviceMaster : public MemDBIODeviceWithReply
	{
	public:
		MemDBIODeviceMaster(MemDBLocationPtr home, bool low_latency);
	};

	typedef std::shared_ptr<MemDBIODeviceMaster> MemDBIODeviceMasterPtr; // 

	class MemDBIODeviceClient : public MemDBIODeviceWithReply
	{
	public:
		MemDBIODeviceClient(MemDBLocationPtr home, bool low_latency);
	};

	typedef std::shared_ptr<MemDBIODeviceClient> MemDBIODeviceClientPtr; //  

////////////////////




}//namespace 


#endif