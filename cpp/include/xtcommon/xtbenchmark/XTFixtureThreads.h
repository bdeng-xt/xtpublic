#pragma once
#ifndef XT_FIXTURE_THREADS_H
#define XT_FIXTURE_THREADS_H

/**
* \file FixtureThreads.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a thread benchmark fixture class.
*
* \description
*	Designed for thread benchmark fixture.
*/

#include <cstdint>
#include <string>
#include <cstdlib>
#include <iostream>


#include "XTContextThreads.h"
#include "XTConfig.h"

namespace XT
{

	//! Threads benchmark fixture
	/*!
		Provides interface to initialize and cleanup threads benchmarks.
	*/
	class FixtureThreads
	{
	public:
		FixtureThreads() noexcept = default;
		FixtureThreads(const FixtureThreads&) noexcept = default;
		FixtureThreads(FixtureThreads&&) noexcept = default;
		virtual ~FixtureThreads() noexcept = default;

		FixtureThreads& operator=(const FixtureThreads&) noexcept = default;
		FixtureThreads& operator=(FixtureThreads&&) noexcept = default;

	protected:
		//! Initialize benchmark
		/*!
			This method is called before benchmark run method.

			\param context - Benchmark running context
		*/
		virtual void Initialize(ContextThreads& context) {}
		//! Cleanup benchmark
		/*!
			This method is called after benchmark run method.

			\param context - Benchmark running context
		*/
		virtual void Cleanup(ContextThreads& context) {}

		//! Initialize thread
		/*!
			This method is called to initialize benchmark thread.

			\param context - Thread running context
		*/
		virtual void InitializeThread(ContextThreads& context) {}
		//! Cleanup thread
		/*!
			This method is called to cleanup benchmark thread.

			\param context - Thread running context
		*/
		virtual void CleanupThread(ContextThreads& context) {}
	};

}//namespace XT


#endif