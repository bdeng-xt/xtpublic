#pragma once
#ifndef XT_SHARED_RECURSIVE_MUTEX_H
#define XT_SHARED_RECURSIVE_MUTEX_H

/**
* \file shared_recursive_mutex.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  shared recursive mutex.
*
* \description
*	Designed for a shared recursive mutex.
*/

#include <string>
#include <map>
#include <queue>
#include <memory>

#include <unordered_map>

#include <boost/thread.hpp>		 
#include <boost/bind.hpp>		 
#include <boost/any.hpp>	 

#include <boost/thread/shared_mutex.hpp>

namespace XT
{

	class shared_recursive_mutex : public boost::shared_mutex
	{
	public:
		void lock(void) {
			std::thread::id this_id = std::this_thread::get_id();  //boost::thread::id this_id = boost::this_thread::get_id(); //	
			if (owner == this_id) {
				// recursive locking
				count++;
			}
			else {
				// normal locking
				boost::shared_mutex::lock();
				owner = this_id;
				count = 1;
			}
		}
		void unlock(void) {
			if (count > 1) {
				// recursive unlocking
				count--;
			}
			else {
				// normal unlocking
				owner = std::thread::id(); // boost::thread::id(); // std::thread::id();
				count = 0;
				boost::shared_mutex::unlock();
			}
		}

	private:
		std::atomic<std::thread::id> owner;  //boost::thread::id owner; // std::atomic<std::thread::id> owner;
		int count;
	};

}//namespace


#endif