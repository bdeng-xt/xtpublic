#pragma once
#ifndef XT_FIXTURE_H
#define XT_FIXTURE_H

/**
* \file Fixture.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a fixture class.
*
* \description
*	Designed for fixture.
*/

#include <cstdint>
#include <string>
#include <cstdlib>
#include <iostream>


#include "XTContext.h"
#include "XTConfig.h"

namespace XT
{

	//! Benchmark fixture
	/*!
		Provides interface to initialize and cleanup benchmarks.
	*/
	class Fixture
	{
	public:
		Fixture() noexcept = default;
		Fixture(const Fixture&) noexcept = default;
		Fixture(Fixture&&) noexcept = default;
		virtual ~Fixture() noexcept = default;

		Fixture& operator=(const Fixture&) noexcept = default;
		Fixture& operator=(Fixture&&) noexcept = default;

	protected:
		//! Initialize benchmark
		/*!
			This method is called before benchmark run method.

			\param context - Benchmark running context
		*/
		virtual void Initialize(Context& context) {}
		//! Cleanup benchmark
		/*!
			This method is called after benchmark run method.

			\param context - Benchmark running context
		*/
		virtual void Cleanup(Context& context) {}
	};

}//namespace

#endif