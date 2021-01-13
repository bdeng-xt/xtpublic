#pragma once
#ifndef XT_FUNCTION_H
#define XT_FUNCTION_H

/**
* \file Function.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a function class .
*
* \description
*	Designed for a function class.
*/

#include <cstdint>
#include <string>
#include <iostream> 

#include <functional>
#include <memory>

namespace XT
{

	//! Allocation free function stub
	template <class, size_t Capacity = 1024>
	class Function;

	//! Allocation free function
	/*!
		Allocation free function uses internal stack-based buffer to keep
		the closure. This allows to avoid slow heap allocation in function
		constructor as it performed in std::function implementation.

		Invocation overhead is similar to std::function implementation.
	*/
	template <class R, class... Args, size_t Capacity>
	class Function<R(Args...), Capacity>
	{
	public:
		Function() noexcept;
		Function(std::nullptr_t) noexcept;
		Function(const Function& function) noexcept;
		Function(Function&& function) noexcept;
		template <class TFunction>
		Function(TFunction&& function) noexcept;
		~Function() noexcept;

		Function& operator=(std::nullptr_t) noexcept;
		Function& operator=(const Function& function) noexcept;
		Function& operator=(Function&& function) noexcept;
		template <typename TFunction>
		Function& operator=(TFunction&& function) noexcept;
		template <typename TFunction>
		Function& operator=(std::reference_wrapper<TFunction> function) noexcept;

		//! Check if the function is valid
		explicit operator bool() const noexcept { return (_manager != nullptr); }

		//! Invoke the function
		R operator()(Args... args);

		//! Swap two instances
		void swap(Function& function) noexcept;
		template <class UR, class... UArgs, size_t UCapacity>
		friend void swap(Function<UR(UArgs...), UCapacity>& function1, Function<UR(UArgs...), UCapacity>& function2) noexcept;

	private:
		enum class Operation { Clone, Destroy };

		using Invoker = R(*)(void*, Args&&...);
		using Manager = void(*)(void*, void*, Operation);
		using Storage = typename std::aligned_storage<Capacity - sizeof(Invoker) - sizeof(Manager), 8>::type;

		Storage _data;
		Invoker _invoker;
		Manager _manager;

		template <typename TFunction>
		static R Invoke(void* data, Args&&... args) noexcept;

		template <typename TFunction>
		static void Manage(void* dst, void* src, Operation op) noexcept;
	};
/////

	template <class R, class... Args, size_t Capacity>
	inline Function<R(Args...), Capacity>::Function() noexcept
		: _invoker(nullptr),
		_manager(nullptr)
	{
	}

	template <class R, class... Args, size_t Capacity>
	inline Function<R(Args...), Capacity>::Function(std::nullptr_t) noexcept
		: Function<R(Args...), Capacity>()
	{
	}

	template <class R, class... Args, size_t Capacity>
	inline Function<R(Args...), Capacity>::Function(const Function& function) noexcept
		: Function<R(Args...), Capacity>()
	{
		if (function)
		{
			function._manager(&_data, &function._data, Operation::Clone);
			_invoker = function._invoker;
			_manager = function._manager;
		}
	}

	template <class R, class... Args, size_t Capacity>
	inline Function<R(Args...), Capacity>::Function(Function&& function) noexcept
		: Function<R(Args...), Capacity>()
	{
		function.swap(*this);
	}

	template <class R, class... Args, size_t Capacity>
	template <class TFunction>
	inline Function<R(Args...), Capacity>::Function(TFunction&& function) noexcept
		: Function<R(Args...), Capacity>()
	{
		using function_type = typename std::decay<TFunction>::type;
		static_assert(alignof(function_type) <= alignof(Storage), "Invalid function storage alignment!");
		static_assert(sizeof(function_type) <= sizeof(Storage), "Function storage too small!");
		new (&_data) function_type(std::forward<TFunction>(function));
		_invoker = &Invoke<function_type>;
		_manager = &Manage<function_type>;
	}

	template <class R, class... Args, size_t Capacity>
	inline Function<R(Args...), Capacity>::~Function() noexcept
	{
		if (_manager)
			_manager(&_data, nullptr, Operation::Destroy);
	}

	template <class R, class... Args, size_t Capacity>
	inline Function<R(Args...), Capacity>& Function<R(Args...), Capacity>::operator=(std::nullptr_t) noexcept
	{
		if (_manager)
		{
			_manager(&_data, nullptr, Operation::Destroy);
			_manager = nullptr;
			_invoker = nullptr;
		}
		return *this;
	}

	template <class R, class... Args, size_t Capacity>
	inline Function<R(Args...), Capacity>& Function<R(Args...), Capacity>::operator=(const Function& function) noexcept
	{
		Function(function).swap(*this);
		return *this;
	}

	template <class R, class... Args, size_t Capacity>
	inline Function<R(Args...), Capacity>& Function<R(Args...), Capacity>::operator=(Function&& function) noexcept
	{
		Function(std::move(function)).swap(*this);
		return *this;
	}

	template <class R, class... Args, size_t Capacity>
	template <typename TFunction>
	inline Function<R(Args...), Capacity>& Function<R(Args...), Capacity>::operator=(TFunction&& function) noexcept
	{
		Function(std::forward<TFunction>(function)).swap(*this);
		return *this;
	}

	template <class R, class... Args, size_t Capacity>
	template <typename TFunction>
	inline Function<R(Args...), Capacity>& Function<R(Args...), Capacity>::operator=(std::reference_wrapper<TFunction> function) noexcept
	{
		Function(function).swap(*this);
		return *this;
	}

	template <class R, class... Args, size_t Capacity>
	inline R Function<R(Args...), Capacity>::operator()(Args... args)
	{
		if (!_invoker)
			throw std::bad_function_call();

		return _invoker(&_data, std::forward<Args>(args)...);
	}

	template <class R, class... Args, size_t Capacity>
	template <typename TFunction>
	inline R Function<R(Args...), Capacity>::Invoke(void* data, Args&&... args) noexcept
	{
		TFunction& function = *static_cast<TFunction*>(data);
		return function(std::forward<Args>(args)...);
	}

	template <class R, class... Args, size_t Capacity>
	template <typename TFunction>
	inline void Function<R(Args...), Capacity>::Manage(void* dst, void* src, Operation op) noexcept
	{
		switch (op)
		{
		case Operation::Clone:
			new (dst) TFunction(*static_cast<TFunction*>(src));
			break;
		case Operation::Destroy:
			static_cast<TFunction*>(dst)->~TFunction();
			break;
		}
	}

	template <class R, class... Args, size_t Capacity>
	inline void Function<R(Args...), Capacity>::swap(Function& function) noexcept
	{
		using std::swap;
		swap(_data, function._data);
		swap(_manager, function._manager);
		swap(_invoker, function._invoker);
	}

	template <class R, class... Args, size_t Capacity>
	void swap(Function<R(Args...), Capacity>& function1, Function<R(Args...), Capacity>& function2) noexcept
	{
		function1.swap(function2);
	}

////////////

}//namespace

#endif