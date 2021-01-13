#pragma once
#ifndef XT_CONTAINERS_H
#define XT_CONTAINERS_H

/**
* \file Containers.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  customized containers.
*
* \description
*	Designed for customized containers for data.
*/

#include <string>
#include <queue>
#include <utility>

#include <boost/thread.hpp>		 
#include <boost/bind.hpp>		 
#include <boost/any.hpp>	 

namespace XT
{

///thread safe queue
template<typename T>
class ConcurrentQueue
{
private:
	std::queue<T> m_queue;///< queue								 
	mutable boost::mutex m_mutex;	 ///< mutex					 
	boost::condition_variable m_condition_variable; ///< condition variable			 

public:

	/**
	* @brief push data into queue
	*
	* @param data to be pushed
	*/
	void push(T const& data)
	{
		boost::mutex::scoped_lock lock(m_mutex);				//get mutex
		m_queue.push(data);							//push data
		lock.unlock();									//release lock
		m_condition_variable.notify_one();			//notify blocked waiting threads
	}

	/**
	* @brief emplace data right value into queue
	*
	* @param data to be pushed
	*/
	void emplace(T&&  data)
	{
		boost::mutex::scoped_lock lock(m_mutex);				//get mutex
//		std::cout << "queue::emplace..." << std::endl;
		m_queue.emplace(std::forward<T>(data));		//push data, if not use forward, it will call copy constructor
//		std::cout << "queue::emplace finished" << std::endl;
		lock.unlock();									//release lock
		m_condition_variable.notify_one();			//notify blocked waiting threads
	}

	/**
	* @brief check if queue is empty or not
	* 
	* @return if queue is empty or not
	*/
	bool empty() const
	{
		boost::mutex::scoped_lock lock(m_mutex);
		return m_queue.empty();
	}

	/**
	* @brief return current size
	*
	* @return size
	*/
	size_t size() const
	{

//#ifdef USE_BOOST_THREAD
		boost::mutex::scoped_lock lock(m_mutex);
		return m_queue.size();
//		return sz;
//#else
//		std::lock_guard<std::mutex> lock(m_mutex);// boost::mutex::scoped_lock lock(m_mutex);
//		size_t sz = m_queue.size();
//		return sz;
//#endif

	}

	/**
	* @brief get front
	*
	* @return front item
	*/
	T wait_and_pop()
	{
		boost::mutex::scoped_lock lock(m_mutex);

		while (m_queue.empty())						//while the queue is empty
		{
			m_condition_variable.wait(lock);			//wait for the condition variable
		}

		T popped_value = m_queue.front();			// get the front value
		m_queue.pop();								// pop out the value
		return popped_value;							//return the value

	}

	/**
	* @brief get front by move
	*
	* @return front item
	*/
	T wait_and_pop_move()
	{
		boost::mutex::scoped_lock lock(m_mutex);

		while (m_queue.empty())						//while the queue is empty
		{
			m_condition_variable.wait(lock);			//wait for the condition variable
		}


		T popped_value = std::move(m_queue.front());			// get the front value
		m_queue.pop();								// pop out the value
		return std::move(popped_value);							//return the value
	}

};

}//namespace

#endif