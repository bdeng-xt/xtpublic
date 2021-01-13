#pragma once
#ifndef XT_SOCKET_POLLER_H
#define XT_SOCKET_POLLER_H

#include <cstdint>
#include <sstream>
#include <string>
#include <memory>
#include <vector>
#include <functional>

#include "log4z.h"
#if defined ( __linux__ )
#define SYS_LINUX
#elif ( (!defined(__linux__)) && ( defined(__unix__) || ( defined(__APPLE__) && defined(__MACH__) ) || defined(__QNX__) ) )
#define SYS_BSD
#elif ( defined(_WIN32) || defined(_WIN64) )
#define SYS_NT
#endif

#if defined(SYS_LINUX) || defined(SYS_BSD)
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <err.h>
#include <signal.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netdb.h>
#include <net/if.h>
#include <netinet/ip.h>
#include <net/ethernet.h>

#include <pcap.h>

#include <sys/epoll.h>

#if defined(SYS_LINUX)
inline uint16_t source_port(const struct tcphdr* header) { return ntohs(header->source); }
inline uint16_t dest_port(const struct tcphdr* header) { return ntohs(header->dest); }
inline uint16_t source_port(const struct udphdr* header) { return ntohs(header->source); }
inline uint16_t dest_port(const struct udphdr* header) { return ntohs(header->dest); }
inline uint16_t len(const struct udphdr* header) { return ntohs(header->len); }
#elif defined(SYS_BSD)
inline uint16_t source_port(const struct tcphdr* header) { return ntohs(header->th_sport); }
inline uint16_t dest_port(const struct tcphdr* header) { return ntohs(header->th_dport); }
inline uint16_t source_port(const struct udphdr* header) { return ntohs(header->uh_sport); }
inline uint16_t dest_port(const struct udphdr* header) { return ntohs(header->uh_dport); }
inline uint16_t len(const struct udphdr* header) { return ntohs(header->uh_ulen); }
#endif
#endif

namespace XT
{
#define SOCKET_MAX_EVENTS 100
#define SOCKET_RCV_BUFFER_SIZE 2048
#define SOCKET_POLL_IN_EVENT 1
#define SOCKET_POLL_OUT_EVENT 2

	typedef std::function<void(const char* data, size_t length)> socket_rcv_handler_t;

	struct socket_poll_event
	{
		int fd;
		uint32_t events;
		socket_rcv_handler_t rcv_handler;
	};

	inline socket_poll_event socket_poll_event_in(int fd, socket_rcv_handler_t rcv_handler)
	{
		socket_poll_event e;
		memset(&e, 0, sizeof(socket_poll_event));
		e.fd = fd;
		e.events |= SOCKET_POLL_IN_EVENT;
		e.rcv_handler = rcv_handler;
		return e;
	}

#if defined(SYS_LINUX)

	class SocketPoller
	{
	public:
		SocketPoller() : live_(false)
		{
			epoll_fd_ = epoll_create1(0);
			if (epoll_fd_ == -1)
			{
				std::stringstream logss;
				logss << "epoll_create1 error, errno:" << errno << ", error msg:" << strerror(errno);
				LOGE(logss.str());
				 
			}
		}

		bool live() const { return live_; }

		void stop() { live_ = false; }

		void poll(std::vector<socket_poll_event> events)
		{
			for (size_t idx = 0; idx < events.size(); idx++)
			{
				const socket_poll_event& poll_ev = events[idx];
				std::stringstream logss;
				logss << "add event, idx: " << idx << ", fd:" << poll_ev.fd << ",events:" << poll_ev.events;
				LOGD(logss.str());
				 
				struct epoll_event epoll_ev;
				epoll_ev.data.u64 = idx;
				if (poll_ev.events & SOCKET_POLL_IN_EVENT)
				{
					epoll_ev.events |= EPOLLIN;
				}
				if (poll_ev.events & SOCKET_POLL_OUT_EVENT)
				{
					epoll_ev.events |= EPOLLOUT;
				}
				int s = epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, poll_ev.fd, &epoll_ev);
				if (s == -1)
				{
					std::stringstream logsse;
					logsse << "epoll_ctl error, epfd:" << epoll_fd_ << ", errno:" << errno << ",error msg:" << strerror(errno);
					LOGE(logsse.str());
				}
			}

			live_ = true;
			while (live_)
			{
				int n = epoll_wait(epoll_fd_, epoll_events_, SOCKET_MAX_EVENTS, 0);
				for (size_t idx = 0; idx < n; idx++)
				{
					const epoll_event& epoll_ev = epoll_events_[idx];
					if (epoll_ev.events & EPOLLIN)
					{
						const socket_poll_event& poll_ev = events.at(epoll_ev.data.u64);
						memset(buffer_, 0, sizeof(buffer_));
						size_t data_length = read(poll_ev.fd, buffer_, SOCKET_RCV_BUFFER_SIZE);
						if (data_length > 0)
						{
							poll_ev.rcv_handler(buffer_, data_length);
						}
					}
				}
			}
		}

	private:
		bool live_;
		char buffer_[SOCKET_RCV_BUFFER_SIZE];
		int epoll_fd_;
		struct epoll_event epoll_events_[SOCKET_MAX_EVENTS];

	};
	typedef std::shared_ptr<SocketPoller> SocketPollerPtr;

#elif defined(SYS_BSD)

	class SocketPoller
	{
	public:
		SocketPoller() : live_(false) {}
		void stop() { live_ = false; }
		void poll(std::vector <poll_event> events)
		{}

	private:
		bool live_;
	};
	typedef std::shared_ptr<SocketPoller> SocketPollerPtr;

#endif
	


}


#endif