#pragma once
#ifndef XT_MRSW_MAP_H
#define XT_MRSW_MAP_H

/**
* \file mrsw_map.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  multiple readers single writer map.
*
* \description
*	Designed for customized thread safe map for multiple readers and single writer.
*/

#include <string>
#include <map>
#include <queue>

#include <mutex>

#include <boost/thread.hpp>		 
#include <boost/bind.hpp>		 
#include <boost/any.hpp>	 

#include <boost/thread/shared_mutex.hpp>

namespace XT
{

///thread safe queue
template<typename K, typename V>
class mrsw_map
{

protected:
	mutable boost::shared_mutex m_mutex;
	std::map<K, V> m_data;

public:

	mrsw_map()
	{}

	~mrsw_map()
	{
	}
	
	
	/// Checks if the map is empty
	bool empty() const
	{
		boost::shared_lock<boost::shared_mutex> rlock(m_mutex);
		return m_data.empty();
	}

	/// Returns item count in the map
	size_t size() const
	{
		boost::shared_lock<boost::shared_mutex> rlock(m_mutex);
		return m_data.size();
	}

	size_t max_size() const
	{
		boost::shared_lock<boost::shared_mutex> rlock(m_mutex);
		return m_data.max_size();
	}
	
	/// Checks whether the map contains \p key
	/**
	The function searches the item with key equal to \p key
	and returns \p true if it is found, and \p false otherwise.

	The function applies RCU lock internally.
	*/
 
	bool contains(K const& key)
	{
		boost::shared_lock<boost::shared_mutex> rlock(m_mutex);
		auto it = m_data.find(key);
		return it != m_data.end();
	}

	/// Inserts new node
 
	void insert(const K & key, const V & val)
	{
		boost::lock_guard<boost::shared_mutex> wlock(m_mutex);  //std::lock_guard<boost::shared_mutex> wlock(m_mutex);
		m_data[key] = val;
	}
 
	V& operator[](const K& k)
	{
		boost::lock_guard<boost::shared_mutex> wlock(m_mutex);  //std::lock_guard<boost::shared_mutex> wlock(m_mutex);
		return m_data[k];
	
	}

 
	V getValue(const K& k)
	{
		boost::shared_lock<boost::shared_mutex> rlock(m_mutex);

		return m_data.find(k) == m_data.end() ? V() : V(m_data[k]);
 
	}

	/// Delete \p key from the map
 
	size_t erase(K const& key)
	{
		boost::lock_guard<boost::shared_mutex> wlock(m_mutex);  //std::lock_guard<boost::shared_mutex> wlock(m_mutex);
		return m_data.erase(key);
	}

	/// Clears the map
	void clear()
	{
		boost::lock_guard<boost::shared_mutex> wlock(m_mutex);  //std::lock_guard<boost::shared_mutex> wlock(m_mutex);
		m_data.clear();
	}

	/////////////////////////
 
	void popValuesWithKeysBetween(std::vector<V>& vector, const K& lower, const K& upper)
	{
		boost::shared_lock<boost::shared_mutex> rlock(m_mutex);
		vector.clear();
		if (m_data.size() == 0 || upper<lower) 
		{
			return;
		}

		if (m_data.begin()->first > upper || m_data.rbegin()->first < lower )
		{
			return;
		}

		auto itlow = m_data.lower_bound(lower);
		auto itup = m_data.upper_bound(upper);

		for (auto it = itlow; it != itup; ++it)
		{
			vector.push_back(it->second);
		}
	}

 
	void popKeysWithKeysBetween(std::vector<K>& vector, const K& lower, const K& upper)
	{
		boost::shared_lock<boost::shared_mutex> rlock(m_mutex);
		vector.clear();
		if (m_data.size() == 0 || upper<lower)
		{
			return;
		}

		if (m_data.begin()->first > upper || m_data.rbegin()->first < lower)
		{
			return;
		}

		auto itlow = m_data.lower_bound(lower);
		auto itup = m_data.upper_bound(upper);

		for (auto it = itlow; it != itup; ++it)
		{
			vector.push_back(it->first);
		}
	}

 
	std::string getValuesCsvStrWithKeysBetween( const K& lower, const K& upper)
	{
		boost::shared_lock<boost::shared_mutex> rlock(m_mutex);
		std::stringstream ssresult;
		if (m_data.size() == 0 || upper<lower)
		{
			return "";
		}

		if (m_data.begin()->first > upper || m_data.rbegin()->first < lower)
		{
			return "";
		}

		auto itlow = m_data.lower_bound(lower);
		auto itup = m_data.upper_bound(upper);

		int count = 0;
		for (auto it = itlow; it != itup; ++it)
		{
			if (count > 0) { ssresult << ","; }
			ssresult << it->second;

			++count;
		}

		return ssresult.str();
	}

 
	std::string getKeysCsvStrWithKeysBetween(const K& lower, const K& upper)
	{
		boost::shared_lock<boost::shared_mutex> rlock(m_mutex);
		std::stringstream ssresult;
		if (m_data.size() == 0 || upper<lower)
		{
			return "";
		}

		if (m_data.begin()->first > upper || m_data.rbegin()->first < lower)
		{
			return "";
		}

		auto itlow = m_data.lower_bound(lower);
		auto itup = m_data.upper_bound(upper);

		int count = 0;
		for (auto it = itlow; it != itup; ++it)
		{
			if (count > 0) { ssresult << ","; }
			ssresult << it->first;

			++count;
		}

		return ssresult.str();
	}



};//class


}//namepsace XT



#endif