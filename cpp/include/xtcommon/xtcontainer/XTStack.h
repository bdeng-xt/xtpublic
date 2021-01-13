#pragma once
#ifndef XT_STACK_H
#define XT_STACK_H

/**
* \file XTStack.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for stack.
*
* \description
*	Designed for use for stack.
*/

#include <cassert>
#include <string>
#include <sstream>
#include <ostream> 
#include <cstddef>


namespace XT
{

	template <typename T>
	class StackIterator;
	template <typename T>
	class StackConstIterator;

	//! Intrusive stack container
	/*!
		Stack  represents  container  with  LIFO  (last  in  -  first  out)  stock
		algorithm. For example, you insert item A into stack. Then you insert item
		B into stack. There is an item B on the top of the stack.  After  removing
		item B, there will be an item A on the top of the stack.

		\code
		  Top-<--- Insert here
		   |
		+-----+         +-----+         +-----+         +-----+
		|     |    Next |     |    Next |     |    Next |     |    Next
		|  1  |-------->|  2  |-------->|  3  |-------->|  4  |--------> NULL
		|     |         |     |         |     |         |     |
		+-----+         +-----+         +-----+         +-----+
		   |
		   +-->--- Remove from here
		\endcode

		Not thread-safe.

		<b>Overview</b>\n
		\image html Stack.png "Stack"
		In computer science, a stack is a temporary abstract data  type  and  data
		structure based on the principle of Last In First Out (LIFO).  Stacks  are
		used extensively at every level of a modern computer system. For  example,
		a modern PC uses stacks at the architecture level, which are used  to  run
		an operating system. The operating system also uses stacks, which are used
		to run a Java Virtual Machine, which  is  stack  oriented,  and  the  Java
		language itself has a class called "Stack",  which  can  be  used  by  the
		programmer. The stack is ubiquitous.

		A stack-based computer system is one  that  stores  temporary  information
		primarily in stacks, rather than hardware CPU registers (a  register-based
		computer system).

		<b>Abstract data type</b>\n
		As an abstract data type, the stack is a  container  (data  structure)  of
		nodes and has two basic operations: push and pop. Push adds a  given  node
		to the top of the stack leaving previous  nodes  below.  Pop  removes  and
		returns the current top node of the stack. A frequently used  metaphor  is
		the idea of a stack of plates in a spring loaded cafeteria stack. In  such
		a stack, only the top plate is visible and accessible  to  the  user,  all
		other plates remain hidden. As new plates are  added  (pushed),  each  new
		plate becomes the top of the stack, and hides each plate below. As  plates
		are removed (popped) from the stack, they can be used,  and  second  plate
		becomes the top of the stack. Two important principles are illustrated  by
		this metaphor, the Last In First Out principle is one. The second is  that
		the contents of the stack are hidden. Only the top plate is visible, so to
		see what is on the third plate, the first and second plates will  have  to
		be removed.

		<b>Other Operations</b>\n
		In modern computer languages, the stack is usually implemented  with  more
		operations than just "push" and "pop". The length of a stack can often  be
		returned as a parameter. Another helper  operation  peek  can  return  the
		current top node of the stack without removing it from the stack.

		<b>Implementation</b>\n
		A typical storage requirement for a stack  of  n  elements  is  O(n).  The
		typical time requirement of O(1) operations is also easy to  satisfy  with
		an dynamic array or (singly) linked list implementation.

		<b>History</b>\n
		The stack method of expression evaluation  was  first  proposed  by  early
		German computer scientist F.L.  Bauer,  who  received  the  IEEE  Computer
		Society Pioneer Award in 1988 for his work on Computer Stacks.

		<b>References</b>\n
		\li Donald Knuth. The Art of Computer Programming, Volume  1:  Fundamental
			Algorithms, Third Edition. Addison-Wesley, 1997.  ISBN  0-201-89683-4.
			Section 2.2.1: Stacks, Queues, and Deques, pp. 238-243.
		\li Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford
			Stein. Introduction to  Algorithms,  Second  Edition.  MIT  Press  and
			McGraw-Hill,  2001.  ISBN  0-262-03293-7.  Section  10.1:  Stacks  and
			queues, pp.200-204.

		<b>Taken from:</b>\n
		Stack (data structure) from Wikipedia, the free encyclopedia
		http://en.wikipedia.org/wiki/Stack_%28data_structure%29
	*/
	template <typename T>
	class Stack
	{
	public:
		// Standard container type definitions
		typedef T value_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef StackIterator<T> iterator;
		typedef StackConstIterator<T> const_iterator;

		//! Stack node
		struct Node
		{
			T* next;    //!< Pointer to the next stack node

			Node() : next(nullptr) {}
		};

		Stack() noexcept : _size(0), _top(nullptr) {}
		template <class InputIterator>
		Stack(InputIterator first, InputIterator last) noexcept;
		Stack(const Stack&) noexcept = default;
		Stack(Stack&&) noexcept = default;
		~Stack() noexcept = default;

		Stack& operator=(const Stack&) noexcept = default;
		Stack& operator=(Stack&&) noexcept = default;

		//! Check if the stack is not empty
		explicit operator bool() const noexcept { return !empty(); }

		//! Is the stack empty?
		bool empty() const noexcept { return _top == nullptr; }

		//! Get the stack size
		size_t size() const noexcept { return _size; }

		//! Get the top stack item
		T* top() noexcept { return _top; }
		const T* top() const noexcept { return _top; }

		//! Get the begin stack iterator
		iterator begin() noexcept;
		const_iterator begin() const noexcept;
		const_iterator cbegin() const noexcept;
		//! Get the end stack iterator
		iterator end() noexcept;
		const_iterator end() const noexcept;
		const_iterator cend() const noexcept;

		//! Push a new item into the top of the stack
		/*!
			\param item - Pushed item
		*/
		void push(T& item) noexcept;

		//! Pop the item from the top of the stack
		/*!
			\return The top item popped from the stack
		*/
		T* pop() noexcept;

		//! Reverse the stack
		void reverse() noexcept;

		//! Clear the stack
		void clear() noexcept;

		//! Swap two instances
		void swap(Stack& stack) noexcept;
		template <typename U>
		friend void swap(Stack<U>& stack1, Stack<U>& stack2) noexcept;

	private:
		size_t _size;   // Stack size
		T* _top;        // Stack top node
	};

	//! Intrusive stack iterator
	/*!
		Not thread-safe.
	*/
	template <typename T>
	class StackIterator
	{
		friend StackConstIterator<T>;

	public:
		// Standard iterator type definitions
		typedef T value_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef std::forward_iterator_tag iterator_category;

		StackIterator() noexcept : _node(nullptr) {}
		explicit StackIterator(T* node) noexcept : _node(node) {}
		StackIterator(const StackIterator& it) noexcept = default;
		StackIterator(StackIterator&& it) noexcept = default;
		~StackIterator() noexcept = default;

		StackIterator& operator=(const StackIterator& it) noexcept = default;
		StackIterator& operator=(StackIterator&& it) noexcept = default;

		friend bool operator==(const StackIterator& it1, const StackIterator& it2) noexcept
		{
			return it1._node == it2._node;
		}
		friend bool operator!=(const StackIterator& it1, const StackIterator& it2) noexcept
		{
			return it1._node != it2._node;
		}

		StackIterator& operator++() noexcept;
		StackIterator operator++(int) noexcept;

		reference operator*() noexcept;
		pointer operator->() noexcept;

		//! Check if the iterator is valid
		explicit operator bool() const noexcept { return _node != nullptr; }

		//! Swap two instances
		void swap(StackIterator& it) noexcept;
		template <typename U>
		friend void swap(StackIterator<U>& it1, StackIterator<U>& it2) noexcept;

	private:
		T* _node;
	};

	//! Intrusive stack constant iterator
	/*!
		Not thread-safe.
	*/
	template <typename T>
	class StackConstIterator
	{
	public:
		// Standard iterator type definitions
		typedef T value_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef std::forward_iterator_tag iterator_category;

		StackConstIterator() noexcept : _node(nullptr) {}
		explicit StackConstIterator(const T* node) noexcept : _node(node) {}
		StackConstIterator(const StackIterator<T>& it) noexcept : _node(it._node) {}
		StackConstIterator(const StackConstIterator& it) noexcept = default;
		StackConstIterator(StackConstIterator&& it) noexcept = default;
		~StackConstIterator() noexcept = default;

		StackConstIterator& operator=(const StackIterator<T>& it) noexcept
		{
			_node = it._node; return *this;
		}
		StackConstIterator& operator=(const StackConstIterator& it) noexcept = default;
		StackConstIterator& operator=(StackConstIterator&& it) noexcept = default;

		friend bool operator==(const StackConstIterator& it1, const StackConstIterator& it2) noexcept
		{
			return it1._node == it2._node;
		}
		friend bool operator!=(const StackConstIterator& it1, const StackConstIterator& it2) noexcept
		{
			return it1._node != it2._node;
		}

		StackConstIterator& operator++() noexcept;
		StackConstIterator operator++(int) noexcept;

		const_reference operator*() const noexcept;
		const_pointer operator->() const noexcept;

		//! Check if the iterator is valid
		explicit operator bool() const noexcept { return _node != nullptr; }

		//! Swap two instances
		void swap(StackConstIterator& it) noexcept;
		template <typename U>
		friend void swap(StackConstIterator<U>& it1, StackConstIterator<U>& it2) noexcept;

	private:
		const T* _node;
	};
	//////
	template <typename T>
	template <class InputIterator>
	inline Stack<T>::Stack(InputIterator first, InputIterator last) noexcept
	{
		for (auto it = first; it != last; ++it)
			push(*it);
	}

	template <typename T>
	inline typename Stack<T>::iterator Stack<T>::begin() noexcept
	{
		return iterator(top());
	}

	template <typename T>
	inline typename Stack<T>::const_iterator Stack<T>::begin() const noexcept
	{
		return const_iterator(top());
	}

	template <typename T>
	inline typename Stack<T>::const_iterator Stack<T>::cbegin() const noexcept
	{
		return const_iterator(top());
	}

	template <typename T>
	inline typename Stack<T>::iterator Stack<T>::end() noexcept
	{
		return iterator(nullptr);
	}

	template <typename T>
	inline typename Stack<T>::const_iterator Stack<T>::end() const noexcept
	{
		return const_iterator(nullptr);
	}

	template <typename T>
	inline typename Stack<T>::const_iterator Stack<T>::cend() const noexcept
	{
		return const_iterator(nullptr);
	}

	template <typename T>
	inline void Stack<T>::push(T& item) noexcept
	{
		item.next = _top;
		_top = &item;
		++_size;
	}

	template <typename T>
	inline T* Stack<T>::pop() noexcept
	{
		if (_top == nullptr)
			return nullptr;

		T* result = _top;
		_top = result->next;
		result->next = nullptr;
		--_size;
		return result;
	}

	template <typename T>
	inline void Stack<T>::reverse() noexcept
	{
		T* current = _top;
		T* prev = nullptr;
		T* next = nullptr;

		while (current != nullptr)
		{
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}
		_top = prev;
	}

	template <typename T>
	inline void Stack<T>::clear() noexcept
	{
		_size = 0;
		_top = nullptr;
	}

	template <typename T>
	inline void Stack<T>::swap(Stack& stack) noexcept
	{
		using std::swap;
		swap(_size, stack._size);
		swap(_top, stack._top);
	}

	template <typename T>
	inline void swap(Stack<T>& stack1, Stack<T>& stack2) noexcept
	{
		stack1.swap(stack2);
	}

	template <typename T>
	StackIterator<T>& StackIterator<T>::operator++() noexcept
	{
		if (_node != nullptr)
			_node = _node->next;
		return *this;
	}

	template <typename T>
	inline StackIterator<T> StackIterator<T>::operator++(int) noexcept
	{
		StackIterator<T> result(*this);
		operator++();
		return result;
	}

	template <typename T>
	typename StackIterator<T>::reference StackIterator<T>::operator*() noexcept
	{
		assert((_node != nullptr) && "Iterator must be valid!");

		return *_node;
	}

	template <typename T>
	typename StackIterator<T>::pointer StackIterator<T>::operator->() noexcept
	{
		return _node;
	}

	template <typename T>
	void StackIterator<T>::swap(StackIterator& it) noexcept
	{
		using std::swap;
		swap(_node, it._node);
	}

	template <typename T>
	void swap(StackIterator<T>& it1, StackIterator<T>& it2) noexcept
	{
		it1.swap(it2);
	}

	template <typename T>
	StackConstIterator<T>& StackConstIterator<T>::operator++() noexcept
	{
		if (_node != nullptr)
			_node = _node->next;
		return *this;
	}

	template <typename T>
	inline StackConstIterator<T> StackConstIterator<T>::operator++(int) noexcept
	{
		StackConstIterator<T> result(*this);
		operator++();
		return result;
	}

	template <typename T>
	typename StackConstIterator<T>::const_reference StackConstIterator<T>::operator*() const noexcept
	{
		assert((_node != nullptr) && "Iterator must be valid!");

		return *_node;
	}

	template <typename T>
	typename StackConstIterator<T>::const_pointer StackConstIterator<T>::operator->() const noexcept
	{
		return _node;
	}

	template <typename T>
	void StackConstIterator<T>::swap(StackConstIterator& it) noexcept
	{
		using std::swap;
		swap(_node, it._node);
	}

	template <typename T>
	void swap(StackConstIterator<T>& it1, StackConstIterator<T>& it2) noexcept
	{
		it1.swap(it2);
	}


}//namespace XT




#endif