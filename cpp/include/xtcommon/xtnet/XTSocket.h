#pragma once
#ifndef XT_SOCKET_H
#define XT_SOCKET_H


#include <cstdint>
#include <memory>

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

#if (defined(_WIN32) || defined(_WIN64) )
#include <Ws2tcpip.h>
#include <WinSock2.h>
#include  <fcntl.h> 
 
#endif

#include "log4z.h"
#include "StringUtil.h"

namespace XT
{


	class socket
	{
	public:
		socket(int domain, int type, int protocol = 0)
		{

#if (defined(_WIN32) || defined(_WIN64) )
			WSADATA wsaData = { 0 };
			WORD wVersion = MAKEWORD(2, 2);
			int wsOk = WSAStartup(wVersion, &wsaData);
			if (wsOk != 0)
			{
				std::cout << "socket, failed to initialized winsock" << std::endl;
				return; // exit(-1);
			}
			else
			{
				std::cout << "socket, the winsock status is " << wsaData.szSystemStatus << std::endl;
			}
#endif

			sock_ = ::socket(domain, type, protocol);
			if (sock_ < 0)
			{
				LOGE("create socket error");
			}
		}

		~socket()
		{
#if (defined(_WIN32) || defined(_WIN64) )
			if (sock_ == INVALID_SOCKET)
			{
				WSACleanup();
			}
#endif
			close(); 
		}

		int sockfd() const { return sock_; }

		int make_non_blocking()
		{
#if (defined(_WIN32) || defined(_WIN64) )
			u_long iMode = 1; //0: blocking is enabled; 1: non-blocking is enablaled
			int iresult = ioctlsocket(sock_, FIONBIO, &iMode);
#else
			int flags, s;
			flags = fcntl(this->sockfd(), F_GETFL, 0);
			if (flags == -1)
			{
				LOGE("fcntl");
				return -1;
			}
			flags |= O_NONBLOCK;
			s = fcntl(this->sockfd(), F_SETFL, flags);
			if (s == -1)
			{
				LOGE("fcntl");
				return -1;
			}
			return 0;
#endif
		}

		int make_reusable()
		{
			int yes = 1;
			return this->setsockopt(SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
		}

		int join_group(const std::string &local_address, const std::string &group_address)
		{
			struct ip_mreq mreq;
			memset(&mreq, 0, sizeof(struct ip_mreq));
			mreq.imr_multiaddr.s_addr = inet_addr(group_address.c_str());
			mreq.imr_interface.s_addr = inet_addr(local_address.c_str());

			return this->setsockopt(IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(struct ip_mreq));
		}

		int bind(const struct sockaddr *addr, socklen_t addrlen)
		{
			return ::bind(this->sockfd(), addr, addrlen);
		}

		int connect(const struct sockaddr *addr, socklen_t addrlen)
		{
			return ::connect(this->sockfd(), addr, addrlen);
		}

		int getsockopt(int level, int optname, void *optval, socklen_t *optlen)
		{
#if (defined(_WIN32) || defined(_WIN64) )
			return ::getsockopt(this->sockfd(), level, optname, (char *)optval, optlen);
#else
			return ::getsockopt(this->sockfd(), level, optname, optval, optlen);
#endif
		}

		int setsockopt(int level, int optname, const void *optval, socklen_t optlen)
		{
#if (defined(_WIN32) || defined(_WIN64) )
			return ::setsockopt(this->sockfd(), level, optname, (const char*)optval, optlen);
#else
			return ::setsockopt(this->sockfd(), level, optname, optval, optlen);
#endif
		}

		void close()
		{
#if (defined(_WIN32) || defined(_WIN64) )
			int closestatus = closesocket(this->sockfd());
			std::cout << "XTSocket::close(), closestatus:" << closestatus << std::endl;
			LOGI("XTSocke::close(), closestatus:" + StringUtil::intToStr(closestatus));
#else
			::close(this->sockfd());
#endif
		}

		int send(const char* data, size_t length) const
		{
#if (defined(_WIN32) || defined(_WIN64) )
			int status =  ::send(sock_, data, length,0);
			return status;
#else
			return ::write(sock_, data, length);
#endif
		};

	private:
		int sock_;
	};

	typedef std::shared_ptr<socket> socket_ptr;

	class socket_factory
	{
	public:
		static socket_ptr tcp_client(const std::string &host, int port)
		{
			int sock_type = SOCK_STREAM;
			socket_ptr sock = std::make_shared<socket>(AF_INET, sock_type, 0);
			if (sock->sockfd() < 0)
			{
				return nullptr;
			}
			if (sock->make_reusable() != 0)
			{
				LOGE("fail to allow port reuse");
				return nullptr;
			}
			if (sock->make_non_blocking() != 0)
			{
				LOGE("fail to set socket non-blocking");
				return nullptr;
			}

			struct sockaddr_in serv_addr;
			memset(&serv_addr, 0, sizeof(sockaddr_in));
			struct hostent *server = gethostbyname(host.c_str());
			serv_addr.sin_family = AF_INET;
#if (defined(_WIN32) || defined(_WIN64) )
			memcpy(server->h_addr, &serv_addr.sin_addr.s_addr, server->h_length);
#else
			bcopy(server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
#endif
			serv_addr.sin_port = htons(port);

			if (sock->connect((struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1 && errno != EINPROGRESS)
			{
				return nullptr;
			}
			else
			{
				return sock;
			}
		}

		static socket_ptr udp_client(int listen_port)
		{
			struct addrinfo hints;
			struct addrinfo *result, *rp;
			memset(&hints, 0, sizeof(struct addrinfo));
			hints.ai_family = AF_UNSPEC;     /* Return IPv4 and IPv6 choices */
			hints.ai_flags = AI_PASSIVE;     /* All interfaces */
			hints.ai_socktype = SOCK_DGRAM;
			int s = getaddrinfo(NULL, std::to_string(listen_port).c_str(), &hints, &result);
			if (s != 0)
			{
				std::stringstream logss;
				logss << "getaddrinfo: " << gai_strerror(s);
				LOGE(logss.str());
 
				return nullptr;
			}

			socket_ptr sock = nullptr;
			for (rp = result; rp != NULL; rp = rp->ai_next)
			{
				sock = std::make_shared<socket>(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
				if (sock->sockfd() == -1)
					continue;
				int s = sock->make_reusable();
				if (s != 0)
				{
					std::stringstream logss;
					logss << "trying to set SO_REUSEADDR faild, ERRNO:" << errno << "|" << strerror(errno);
					LOGD(logss.str());
	 
					continue;
				}
				else
				{
					LOGI("trying to set SO_REUSEADDR succeed!");
				}

				s = sock->bind(rp->ai_addr, rp->ai_addrlen);
				if (s == 0)
				{
					std::stringstream logss;
					logss << "success to bind to port " << listen_port;
					LOGI(logss.str());
 
					break;
				}
				else
				{
					std::stringstream logss;
					logss << "try to bind failed, ERRNO: " << errno << " " << strerror(errno);
					LOGD(logss.str());
 
					sock->close();
				}
			}

			if (rp == NULL)
			{
				std::stringstream logss;
				logss << "could not bind to port " << listen_port;
				LOGE(logss.str());
 
				return nullptr;
			}

			freeaddrinfo(result);

			s = sock->make_non_blocking();
			if (s == -1)
			{
				std::stringstream logss;
				logss << "make socket non blocking failed, sockfd:" << sock->sockfd();
				LOGE(logss.str());
 
				sock->close();
				return nullptr;
			}
			else
			{
				LOGI("success to set socket non-blocking");
				return sock;
			}
		}

		static socket_ptr udp_multicast_client(int listen_port, const std::string &local_address, const std::string &group_address)
		{
			socket_ptr sock = udp_client(listen_port);
			if (sock == nullptr)
			{
				return sock;
			}
			else
			{
				if (sock->join_group(local_address, group_address) == -1)
				{
					LOGE("failed to setsockopt IP_ADD_MEMBERSHIP");
					return nullptr;
				}
				else
				{
					LOGI("success to setsockopt IP_ADD_MEMBERSHIP");
					return sock;
				}
			}
		}
	};


}//namespace



#endif