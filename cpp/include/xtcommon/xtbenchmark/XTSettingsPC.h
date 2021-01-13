#pragma once
#ifndef XT_SETTINGS_PC_H
#define XT_SETTINGS_PC_H

/**
* \file SettingsPC.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a producer consumer settings class.
*
* \description
*	Designed for producer consumer settings.
*/

#include <cstdint>
#include <string>
#include <cstdlib>
#include <iostream>

#include "XTSettings.h"
#include "XTConfig.h"

namespace XT
{

	//! Producers/Consumers benchmark settings
	/*!
		Constructs benchmark settings by providing count of operations and count of producers/consumers.
	*/
	class SettingsPC : public Settings
	{
	public:
		//! Initialize settings with the default benchmark duration (5 seconds)
		SettingsPC() : Settings() {}
		//! Initialize settings with the given count of producers/consumers
		/*!
			\param producers - Count of producers
			\param consumers - Count of consumers
		*/
		SettingsPC(int producers, int consumers) : Settings() { PC(producers, consumers); }
		//! Initialize settings with the given count of producers/consumers and the given count of operations
		/*!
			\param producers - Count of producers
			\param consumers - Count of consumers
			\param operations - Count of operations
		*/
		SettingsPC(int producers, int consumers, int64_t operations) : Settings(operations) { PC(producers, consumers); }
		SettingsPC(const Settings& settings) : Settings(settings) {}
		SettingsPC(const SettingsPC&) = default;
		SettingsPC(Settings&& settings) noexcept : Settings(std::move(settings)) {}
		SettingsPC(SettingsPC&&)  = default;
		~SettingsPC() = default;

		SettingsPC& operator=(const SettingsPC&) = default;
		SettingsPC& operator=(SettingsPC&&) = default;
	};


}//namespace XT

#endif