#pragma once
#ifndef XT_SETTINGS_THREADS_H
#define XT_SETTINGS_THREADS_H

/**
* \file SettingsThreads.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a thread settings class.
*
* \description
*	Designed for thread settings.
*/

#include <cstdint>
#include <string>
#include <cstdlib>
#include <iostream>

#include "XTSettings.h"
#include "XTConfig.h"

namespace XT
{

	//! Threads benchmark settings
	/*!
		Constructs benchmark settings by providing count of operations and count of running threads.
	*/
	class SettingsThreads : public Settings
	{
	public:
		//! Initialize settings with the default benchmark duration (5 seconds)
		SettingsThreads() : Settings() {}
		//! Initialize settings with the given count of running threads
		/*!
			\param threads - Count of running threads
		*/
		SettingsThreads(int threads) : Settings() { Threads(threads); }
		//! Initialize settings with the given count of running threads and the given count of operations
		/*!
			\param threads - Count of running threads
			\param operations - Count of operations
		*/
		SettingsThreads(int threads, int64_t operations) : Settings(operations) { Threads(threads); }
		SettingsThreads(const Settings& settings) : Settings(settings) {}
		SettingsThreads(const SettingsThreads&) = default;
		SettingsThreads(Settings&& settings) noexcept : Settings(std::move(settings)) {}
		SettingsThreads(SettingsThreads&&) = default;
		~SettingsThreads() = default;

		SettingsThreads& operator=(const SettingsThreads&) = default;
		SettingsThreads& operator=(SettingsThreads&&) = default;
	};

}//namespace XT

#endif