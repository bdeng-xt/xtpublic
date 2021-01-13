#pragma once
#ifndef XT_BINTREE_H
#define XT_BINTREE_H

/**
* \file XTBinTree.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for binary tree.
*
* \description
*	Designed for use for binary tree.
*/

#include <cassert>
#include <cstddef>
#include <functional>
#include <iterator>
#include <utility>

namespace XT
{

	template <class TContainer, typename T>
	class BinTreeIterator;
	template <class TContainer, typename T>
	class BinTreeConstIterator;
	template <class TContainer, typename T>
	class BinTreeReverseIterator;
	template <class TContainer, typename T>
	class BinTreeConstReverseIterator;

	//! Intrusive non balanced binary tree container
	/*!
		Binary trees are the good structures for associative searching. They  keep
		items in sort order, so each of item can be found in a short time.

		Not thread-safe.

		<b>Overview</b>\n
		In computer science, a binary search tree (BST) is a binary tree which has
		the following properties:
		\li Each node has a value.
		\li A total order is defined on these values.
		\li The left subtree of a node contains only values less than or equal  to
			the node's value.
		\li The right subtree of a node contains only values greater than or equal
			to the node's value.

		\image html BinTree.png "Binary tree"
		The major advantage of binary search trees is  that  the  related  sorting
		algorithms and search algorithms such as in-order traversal  can  be  very
		efficient.

		Binary search trees are a fundamental data  structure  used  to  construct
		more abstract data structures such as  sets,  multisets,  and  associative
		arrays.

		If a BST allows duplicate values, then it represents a multiset. This kind
		of tree uses non-strict inequalities. Everything in the left subtree of  a
		node is strictly less than the value of the node, but  everything  in  the
		right subtree is either greater than or equal to the value of the node.

		If a BST does not allow duplicate values, then the tree represents  a  set
		with unique values, like the mathematical  set.  Trees  without  duplicate
		values use strict inequalities, meaning that the left subtree  of  a  node
		only contains nodes with values that are less than the value of the  node,
		and the right subtree only contains values that are greater.

		The choice of storing equal values in the right subtree only is arbitrary;
		the left would work just as well. One can also permit non-strict  equality
		in both sides. This allows a tree containing many duplicate values  to  be
		balanced better, but it makes searching more complex.

		Most operations on a binary search tree take time directly proportional to
		the tree's height, so it is desirable to keep the height  small.  Ordinary
		binary search trees have the primary disadvantage  that  they  can  attain
		very large heights in rather ordinary situations, such as  when  the  keys
		are inserted in order. The result is a data structure similar to a  linked
		list, making all operations on the tree expensive. If we know all the data
		ahead of time, we can keep the height small on average by adding values in
		a random order, but we do not always have  this  luxury,  particularly  in
		online algorithms.

		Self-balancing   binary   trees   solve   this   problem   by   performing
		transformations on the tree (such as tree  rotations)  at  key  times,  in
		order to reduce the height. Although a certain overhead is involved, it is
		justified in the long run by drastically  decreasing  the  time  of  later
		operations.

		The height must always be at least the ceiling of log n, since  there  are
		at most 2k nodes on the kth level; a complete  or  full  binary  tree  has
		exactly this many levels.  Balanced  BSTs  are  not  always  so  precisely
		balanced, since it can be expensive to keep a tree at  minimum  height  at
		all times; instead, they keep the height within a constant factor of  this
		lower bound.

		Times for various operations in terms of number of nodes in the tree n:
		\li Lookup - O(log n)
		\li Insertion -  O(log n)
		\li Removal -  O(log n)
		\li In-order iteration over all elements - O(n)

		For some implementations these times are worst-case, while for others they
		are amortized.

		<b>Applications</b>\n
		Self-balancing binary search trees  can  be  used  in  a  natural  way  to
		construct associative arrays; key-value pairs are simply inserted with  an
		ordering based on the key alone. In  this  capacity,  self-balancing  BSTs
		have a number of advantages and disadvantages over their main  competitor,
		hash tables. Lookup is somewhat complicated in the case where the same key
		can be used multiple times.

		Many algorithms can exploit self-balancing BSTs  to  achieve  good  worst-
		case bounds with very little effort. For example, if binary tree  sort  is
		done with a BST, we have  a  very  simple-to-describe  yet  asymptotically
		optimal O(n log n) sorting  algorithm  (although  such  an  algorithm  has
		practical disadvantages  due  to  bad  cache  behavior).  Similarly,  many
		algorithms in computational geometry exploit variations on self- balancing
		BSTs to solve problems such as the line segment intersection  problem  and
		the point location problem efficiently.

		Self-balancing BSTs are a flexible data structure, in that  it's  easy  to
		extend them to efficiently record additional information  or  perform  new
		operations. For example, one can  record  the  number  of  nodes  in  each
		subtree having a certain property, allowing one to  count  the  number  of
		nodes in a certain key range with that property in O(log  n)  time.  These
		extensions can be used, for example, to optimize database queries or other
		list-processing algorithms.

		<b>References</b>\n
		\li Donald Knuth. The Art of Computer Programming, Volume 3:  Sorting  and
			Searching, Third Edition. Addison-Wesley,  1997.  ISBN  0-201-89685-0.
			Section 6.2.3: Balanced Trees, pp.458-481.

		<b>Taken from:</b>\n
		Binary search tree from Wikipedia, the free encyclopedia
		http://en.wikipedia.org/wiki/Binary_search_tree
	*/
	template <typename T, typename TCompare = std::less<T>>
	class BinTree
	{
	public:
		// Standard container type definitions
		typedef T value_type;
		typedef TCompare value_compare;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef BinTreeIterator<BinTree<T, TCompare>, T> iterator;
		typedef BinTreeConstIterator<BinTree<T, TCompare>, T> const_iterator;
		typedef BinTreeReverseIterator<BinTree<T, TCompare>, T> reverse_iterator;
		typedef BinTreeConstReverseIterator<BinTree<T, TCompare>, T> const_reverse_iterator;

		//! Binary tree node
		struct Node
		{
			T* parent;  //!< Pointer to the parent binary tree node
			T* left;    //!< Pointer to the left child binary tree node
			T* right;   //!< Pointer to the right child binary tree node

			Node() : parent(nullptr), left(nullptr), right(nullptr) {}
		};

		explicit BinTree(const TCompare& compare = TCompare()) noexcept : _compare(compare), _size(0), _root(nullptr) {}
		template <class InputIterator>
		BinTree(InputIterator first, InputIterator last, const TCompare& compare = TCompare()) noexcept;
		BinTree(const BinTree&) noexcept = default;
		BinTree(BinTree&&) noexcept = default;
		~BinTree() noexcept = default;

		BinTree& operator=(const BinTree&) noexcept = default;
		BinTree& operator=(BinTree&&) noexcept = default;

		//! Check if the binary tree is not empty
		explicit operator bool() const noexcept { return !empty(); }

		//! Is the binary tree empty?
		bool empty() const noexcept { return _root == nullptr; }

		//! Get the binary tree size
		size_t size() const noexcept { return _size; }

		//! Get the root binary tree item
		T* root() noexcept { return _root; }
		const T* root() const noexcept { return _root; }
		//! Get the lowest binary tree item
		T* lowest() noexcept;
		const T* lowest() const noexcept;
		//! Get the highest binary tree item
		T* highest() noexcept;
		const T* highest() const noexcept;

		//! Compare two items: if the first item is less than the second one?
		bool compare(const T& item1, const T& item2) const noexcept { return _compare(item1, item2); }

		//! Get the begin binary tree iterator
		iterator begin() noexcept;
		const_iterator begin() const noexcept;
		const_iterator cbegin() const noexcept;
		//! Get the end binary tree iterator
		iterator end() noexcept;
		const_iterator end() const noexcept;
		const_iterator cend() const noexcept;

		//! Get the reverse begin binary tree iterator
		reverse_iterator rbegin() noexcept;
		const_reverse_iterator rbegin() const noexcept;
		const_reverse_iterator crbegin() const noexcept;
		//! Get the reverse end binary tree iterator
		reverse_iterator rend() noexcept;
		const_reverse_iterator rend() const noexcept;
		const_reverse_iterator crend() const noexcept;

		//! Find the iterator which points to the first equal item in the binary tree or return end iterator
		iterator find(const T& item) noexcept;
		const_iterator find(const T& item) const noexcept;

		//! Find the iterator which points to the first item that not less than the given item in the binary tree or return end iterator
		iterator lower_bound(const T& item) noexcept;
		const_iterator lower_bound(const T& item) const noexcept;
		//! Find the iterator which points to the first item that greater than the given item in the binary tree or return end iterator
		iterator upper_bound(const T& item) noexcept;
		const_iterator upper_bound(const T& item) const noexcept;

		//! Insert a new item into the binary tree
		/*!
			\param item - Item to insert
			\return Pair with the iterator to the inserted item and success flag
		*/
		std::pair<iterator, bool> insert(T& item) noexcept;
		//! Insert a new item into the binary tree with a position hint
		/*!
			\param position - Iterator position to the inserted item
			\param item - Item to insert
			\return Pair with the iterator to the inserted item and success flag
		*/
		std::pair<iterator, bool> insert(const const_iterator& position, T& item) noexcept;

		//! Erase the given item from the binary tree
		/*!
			\param item - Item to erase
			\return Erased item
		*/
		T* erase(const T& item) noexcept;
		//! Erase the given item from the binary tree
		/*!
			\param it - Iterator to the erased item
			\return Erased item iterator
		*/
		iterator erase(const iterator& it) noexcept;

		//! Clear the binary tree
		void clear() noexcept;

		//! Swap two instances
		void swap(BinTree& bintree) noexcept;
		template <typename U, typename UCompare>
		friend void swap(BinTree<U, UCompare>& bintree1, BinTree<U, UCompare>& bintree2) noexcept;

	private:
		TCompare _compare;  // Binary tree node comparator
		size_t _size;       // Binary tree size
		T* _root;           // Binary tree root node

		const T* InternalLowest() const noexcept;
		const T* InternalHighest() const noexcept;
		const T* InternalFind(const T& item) const noexcept;
		const T* InternalLowerBound(const T& item) const noexcept;
		const T* InternalUpperBound(const T& item) const noexcept;
	};

	//! Intrusive binary tree iterator
	/*!
		Not thread-safe.
	*/
	template <class TContainer, typename T>
	class BinTreeIterator
	{
		friend BinTreeConstIterator<TContainer, T>;

	public:
		// Standard iterator type definitions
		typedef T value_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef std::bidirectional_iterator_tag iterator_category;

		BinTreeIterator() noexcept : _container(nullptr), _node(nullptr) {}
		explicit BinTreeIterator(TContainer* container, T* node) noexcept : _container(container), _node(node) {}
		BinTreeIterator(const BinTreeIterator& it) noexcept = default;
		BinTreeIterator(BinTreeIterator&& it) noexcept = default;
		~BinTreeIterator() noexcept = default;

		BinTreeIterator& operator=(const BinTreeIterator& it) noexcept = default;
		BinTreeIterator& operator=(BinTreeIterator&& it) noexcept = default;

		friend bool operator==(const BinTreeIterator& it1, const BinTreeIterator& it2) noexcept
		{
			return (it1._container == it2._container) && (it1._node == it2._node);
		}
		friend bool operator!=(const BinTreeIterator& it1, const BinTreeIterator& it2) noexcept
		{
			return (it1._container != it2._container) || (it1._node != it2._node);
		}

		BinTreeIterator& operator++() noexcept;
		BinTreeIterator operator++(int) noexcept;

		reference operator*() noexcept;
		pointer operator->() noexcept;

		//! Check if the iterator is valid
		explicit operator bool() const noexcept { return (_container != nullptr) && (_node != nullptr); }

		//! Compare two items: if the first item is less than the second one?
		bool compare(const T& item1, const T& item2) const noexcept { return (_container != nullptr) ? _container->compare(item1, item2) : false; }

		//! Swap two instances
		void swap(BinTreeIterator& it) noexcept;
		template <class UContainer, typename U>
		friend void swap(BinTreeIterator<UContainer, U>& it1, BinTreeIterator<UContainer, U>& it2) noexcept;

	private:
		TContainer* _container;
		T* _node;
	};

	//! Intrusive binary tree constant iterator
	/*!
		Not thread-safe.
	*/
	template <class TContainer, typename T>
	class BinTreeConstIterator
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
		typedef std::bidirectional_iterator_tag iterator_category;

		BinTreeConstIterator() noexcept : _container(nullptr), _node(nullptr) {}
		explicit BinTreeConstIterator(const TContainer* container, const T* node) noexcept : _container(container), _node(node) {}
		BinTreeConstIterator(const BinTreeIterator<TContainer, T>& it) noexcept : _container(it._container), _node(it._node) {}
		BinTreeConstIterator(const BinTreeConstIterator& it) noexcept = default;
		BinTreeConstIterator(BinTreeConstIterator&& it) noexcept = default;
		~BinTreeConstIterator() noexcept = default;

		BinTreeConstIterator& operator=(const BinTreeIterator<TContainer, T>& it) noexcept
		{
			_container = it._container; _node = it._node; return *this;
		}
		BinTreeConstIterator& operator=(const BinTreeConstIterator& it) noexcept = default;
		BinTreeConstIterator& operator=(BinTreeConstIterator&& it) noexcept = default;

		friend bool operator==(const BinTreeConstIterator& it1, const BinTreeConstIterator& it2) noexcept
		{
			return (it1._container == it2._container) && (it1._node == it2._node);
		}
		friend bool operator!=(const BinTreeConstIterator& it1, const BinTreeConstIterator& it2) noexcept
		{
			return (it1._container != it2._container) || (it1._node != it2._node);
		}

		BinTreeConstIterator& operator++() noexcept;
		BinTreeConstIterator operator++(int) noexcept;

		const_reference operator*() const noexcept;
		const_pointer operator->() const noexcept;

		//! Check if the iterator is valid
		explicit operator bool() const noexcept { return (_container != nullptr) && (_node != nullptr); }

		//! Compare two items: if the first item is less than the second one?
		bool compare(const T& item1, const T& item2) const noexcept { return (_container != nullptr) ? _container->compare(item1, item2) : false; }

		//! Swap two instances
		void swap(BinTreeConstIterator& it) noexcept;
		template <class UContainer, typename U>
		friend void swap(BinTreeConstIterator<UContainer, U>& it1, BinTreeConstIterator<UContainer, U>& it2) noexcept;

	private:
		const TContainer* _container;
		const T* _node;
	};

	//! Intrusive binary tree reverse iterator
	/*!
		Not thread-safe.
	*/
	template <class TContainer, typename T>
	class BinTreeReverseIterator
	{
		friend BinTreeConstReverseIterator<TContainer, T>;

	public:
		// Standard iterator type definitions
		typedef T value_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef std::bidirectional_iterator_tag iterator_category;

		BinTreeReverseIterator() noexcept : _container(nullptr), _node(nullptr) {}
		explicit BinTreeReverseIterator(TContainer* container, T* node) noexcept : _container(container), _node(node) {}
		BinTreeReverseIterator(const BinTreeReverseIterator& it) noexcept = default;
		BinTreeReverseIterator(BinTreeReverseIterator&& it) noexcept = default;
		~BinTreeReverseIterator() noexcept = default;

		BinTreeReverseIterator& operator=(const BinTreeReverseIterator& it) noexcept = default;
		BinTreeReverseIterator& operator=(BinTreeReverseIterator&& it) noexcept = default;

		friend bool operator==(const BinTreeReverseIterator& it1, const BinTreeReverseIterator& it2) noexcept
		{
			return (it1._container == it2._container) && (it1._node == it2._node);
		}
		friend bool operator!=(const BinTreeReverseIterator& it1, const BinTreeReverseIterator& it2) noexcept
		{
			return (it1._container != it2._container) || (it1._node != it2._node);
		}

		BinTreeReverseIterator& operator++() noexcept;
		BinTreeReverseIterator operator++(int) noexcept;

		reference operator*() noexcept;
		pointer operator->() noexcept;

		//! Check if the iterator is valid
		explicit operator bool() const noexcept { return (_container != nullptr) && (_node != nullptr); }

		//! Compare two items: if the first item is less than the second one?
		bool compare(const T& item1, const T& item2) const noexcept { return (_container != nullptr) ? _container->compare(item1, item2) : false; }

		//! Swap two instances
		void swap(BinTreeReverseIterator& it) noexcept;
		template <class UContainer, typename U>
		friend void swap(BinTreeReverseIterator<UContainer, U>& it1, BinTreeReverseIterator<UContainer, U>& it2) noexcept;

	private:
		TContainer* _container;
		T* _node;
	};

	//! Intrusive binary tree constant reverse iterator
	/*!
		Not thread-safe.
	*/
	template <class TContainer, typename T>
	class BinTreeConstReverseIterator
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
		typedef std::bidirectional_iterator_tag iterator_category;

		BinTreeConstReverseIterator() noexcept : _container(nullptr), _node(nullptr) {}
		explicit BinTreeConstReverseIterator(const TContainer* container, const T* node) noexcept : _container(container), _node(node) {}
		BinTreeConstReverseIterator(const BinTreeReverseIterator<TContainer, T>& it) noexcept : _container(it._container), _node(it._node) {}
		BinTreeConstReverseIterator(const BinTreeConstReverseIterator& it) noexcept = default;
		BinTreeConstReverseIterator(BinTreeConstReverseIterator&& it) noexcept = default;
		~BinTreeConstReverseIterator() noexcept = default;

		BinTreeConstReverseIterator& operator=(const BinTreeReverseIterator<TContainer, T>& it) noexcept
		{
			_container = it._container; _node = it._node; return *this;
		}
		BinTreeConstReverseIterator& operator=(const BinTreeConstReverseIterator& it) noexcept = default;
		BinTreeConstReverseIterator& operator=(BinTreeConstReverseIterator&& it) noexcept = default;

		friend bool operator==(const BinTreeConstReverseIterator& it1, const BinTreeConstReverseIterator& it2) noexcept
		{
			return (it1._container == it2._container) && (it1._node == it2._node);
		}
		friend bool operator!=(const BinTreeConstReverseIterator& it1, const BinTreeConstReverseIterator& it2) noexcept
		{
			return (it1._container != it2._container) || (it1._node != it2._node);
		}

		BinTreeConstReverseIterator& operator++() noexcept;
		BinTreeConstReverseIterator operator++(int) noexcept;

		const_reference operator*() const noexcept;
		const_pointer operator->() const noexcept;

		//! Check if the iterator is valid
		explicit operator bool() const noexcept { return (_container != nullptr) && (_node != nullptr); }

		//! Compare two items: if the first item is less than the second one?
		bool compare(const T& item1, const T& item2) const noexcept { return (_container != nullptr) ? _container->compare(item1, item2) : false; }

		//! Swap two instances
		void swap(BinTreeConstReverseIterator& it) noexcept;
		template <class UContainer, typename U>
		friend void swap(BinTreeConstReverseIterator<UContainer, U>& it1, BinTreeConstReverseIterator<UContainer, U>& it2) noexcept;

	private:
		const TContainer* _container;
		const T* _node;
	};
//////
	template <typename T, typename TCompare>
	template <class InputIterator>
	inline BinTree<T, TCompare>::BinTree(InputIterator first, InputIterator last, const TCompare& compare) noexcept
		: _compare(compare)
	{
		for (auto it = first; it != last; ++it)
			insert(*it);
	}

	template <typename T, typename TCompare>
	inline T* BinTree<T, TCompare>::lowest() noexcept
	{
		return (T*)InternalLowest();
	}

	template <typename T, typename TCompare>
	inline const T* BinTree<T, TCompare>::lowest() const noexcept
	{
		return InternalLowest();
	}

	template <typename T, typename TCompare>
	inline const T* BinTree<T, TCompare>::InternalLowest() const noexcept
	{
		const T* result = _root;
		if (result != nullptr)
			while (result->left != nullptr)
				result = result->left;
		return result;
	}

	template <typename T, typename TCompare>
	inline T* BinTree<T, TCompare>::highest() noexcept
	{
		return (T*)InternalHighest();
	}

	template <typename T, typename TCompare>
	inline const T* BinTree<T, TCompare>::highest() const noexcept
	{
		return InternalHighest();
	}

	template <typename T, typename TCompare>
	inline const T* BinTree<T, TCompare>::InternalHighest() const noexcept
	{
		const T* result = _root;
		if (result != nullptr)
			while (result->right != nullptr)
				result = result->right;
		return result;
	}

	template <typename T, typename TCompare>
	inline typename BinTree<T, TCompare>::iterator BinTree<T, TCompare>::begin() noexcept
	{
		return iterator(this, lowest());
	}

	template <typename T, typename TCompare>
	inline typename BinTree<T, TCompare>::const_iterator BinTree<T, TCompare>::begin() const noexcept
	{
		return const_iterator(this, lowest());
	}

	template <typename T, typename TCompare>
	inline typename BinTree<T, TCompare>::const_iterator BinTree<T, TCompare>::cbegin() const noexcept
	{
		return const_iterator(this, lowest());
	}

	template <typename T, typename TCompare>
	inline typename BinTree<T, TCompare>::iterator BinTree<T, TCompare>::end() noexcept
	{
		return iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTree<T, TCompare>::const_iterator BinTree<T, TCompare>::end() const noexcept
	{
		return const_iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTree<T, TCompare>::const_iterator BinTree<T, TCompare>::cend() const noexcept
	{
		return const_iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTree<T, TCompare>::reverse_iterator BinTree<T, TCompare>::rbegin() noexcept
	{
		return reverse_iterator(this, highest());
	}

	template <typename T, typename TCompare>
	inline typename BinTree<T, TCompare>::const_reverse_iterator BinTree<T, TCompare>::rbegin() const noexcept
	{
		return const_reverse_iterator(this, highest());
	}

	template <typename T, typename TCompare>
	inline typename BinTree<T, TCompare>::const_reverse_iterator BinTree<T, TCompare>::crbegin() const noexcept
	{
		return const_reverse_iterator(this, highest());
	}

	template <typename T, typename TCompare>
	inline typename BinTree<T, TCompare>::reverse_iterator BinTree<T, TCompare>::rend() noexcept
	{
		return reverse_iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTree<T, TCompare>::const_reverse_iterator BinTree<T, TCompare>::rend() const noexcept
	{
		return const_reverse_iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTree<T, TCompare>::const_reverse_iterator BinTree<T, TCompare>::crend() const noexcept
	{
		return const_reverse_iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTree<T, TCompare>::iterator BinTree<T, TCompare>::find(const T& item) noexcept
	{
		return iterator(this, (T*)InternalFind(item));
	}

	template <typename T, typename TCompare>
	inline typename BinTree<T, TCompare>::const_iterator BinTree<T, TCompare>::find(const T& item) const noexcept
	{
		return const_iterator(this, InternalFind(item));
	}

	template <typename T, typename TCompare>
	inline const T* BinTree<T, TCompare>::InternalFind(const T& item) const noexcept
	{
		// Perform the binary tree search from the root node
		const T* current = _root;

		while (current != nullptr)
		{
			// Move to the left subtree
			if (compare(item, *current))
			{
				current = current->left;
				continue;
			}

			// Move to the right subtree
			if (compare(*current, item))
			{
				current = current->right;
				continue;
			}

			// Found result node
			return current;
		}

		// Nothing was found...
		return nullptr;
	}

	template <typename T, typename TCompare>
	inline typename BinTree<T, TCompare>::iterator BinTree<T, TCompare>::lower_bound(const T& item) noexcept
	{
		return iterator(this, (T*)InternalLowerBound(item));
	}

	template <typename T, typename TCompare>
	inline typename BinTree<T, TCompare>::const_iterator BinTree<T, TCompare>::lower_bound(const T& item) const noexcept
	{
		return const_iterator(this, InternalLowerBound(item));
	}

	template <typename T, typename TCompare>
	inline const T* BinTree<T, TCompare>::InternalLowerBound(const T& item) const noexcept
	{
		// Perform the binary tree search from the root node
		const T* current = _root;
		const T* previous = nullptr;

		while (current != nullptr)
		{
			// Move to the left subtree
			if (compare(item, *current))
			{
				previous = current;
				current = current->left;
				continue;
			}

			// Move to the right subtree
			if (compare(*current, item))
			{
				current = current->right;
				continue;
			}

			// Found result node
			return current;
		}

		// Return the previous lower bound node if any met
		return previous;
	}

	template <typename T, typename TCompare>
	inline typename BinTree<T, TCompare>::iterator BinTree<T, TCompare>::upper_bound(const T& item) noexcept
	{
		return iterator(this, (T*)InternalUpperBound(item));
	}

	template <typename T, typename TCompare>
	inline typename BinTree<T, TCompare>::const_iterator BinTree<T, TCompare>::upper_bound(const T& item) const noexcept
	{
		return const_iterator(this, InternalUpperBound(item));
	}

	template <typename T, typename TCompare>
	inline const T* BinTree<T, TCompare>::InternalUpperBound(const T& item) const noexcept
	{
		// Perform the binary tree search from the root node
		const T* current = _root;
		const T* previous = nullptr;

		while (current != nullptr)
		{
			// Move to the left subtree
			if (compare(item, *current))
			{
				previous = current;
				current = current->left;
				continue;
			}

			// Move to the right subtree
			current = current->right;
		}

		// Return the previous upper bound node if any met
		return previous;
	}

	template <typename T, typename TCompare>
	inline std::pair<typename BinTree<T, TCompare>::iterator, bool> BinTree<T, TCompare>::insert(T& item) noexcept
	{
		return insert(const_iterator(this, _root), item);
	}

	template <typename T, typename TCompare>
	inline std::pair<typename BinTree<T, TCompare>::iterator, bool> BinTree<T, TCompare>::insert(const const_iterator& position, T& item) noexcept
	{
		// Perform the binary tree insert from the given node
		T* current = (T*)position.operator->();

		while (current != nullptr)
		{
			// Move to the left subtree
			if (compare(item, *current))
			{
				if (current->left != nullptr)
				{
					current = current->left;
					continue;
				}
				else
				{
					// Link a new item to the left leaf
					current->left = &item;
					break;
				}
			}

			// Move to the right subtree
			if (compare(*current, item))
			{
				if (current->right != nullptr)
				{
					current = current->right;
					continue;
				}
				else
				{
					// Link a new item to the right leaf
					current->right = &item;
					break;
				}
			}

			// Found duplicate node
			return std::make_pair(iterator(this, current), false);
		}

		item.parent = current;
		item.left = nullptr;
		item.right = nullptr;
		if (_root == nullptr)
			_root = &item;
		++_size;

		return std::make_pair(iterator(this, &item), true);
	}

	template <typename T, typename TCompare>
	inline T* BinTree<T, TCompare>::erase(const T& item) noexcept
	{
		return erase(find(item)).operator->();
	}

	template <typename T, typename TCompare>
	inline typename BinTree<T, TCompare>::iterator BinTree<T, TCompare>::erase(const iterator& it) noexcept
	{
		T* result = ((iterator&)it).operator->();
		if (result == nullptr)
			return end();

		T* parent = result->parent;
		T* left = result->left;
		T* right = result->right;

		// Binary tree node without left child
		if (left == nullptr)
		{
			// Link the parent node with a right child
			if (parent != nullptr)
			{
				if (parent->left == result)
					parent->left = right;
				else
					parent->right = right;
			}
			else
				_root = right;
			if (right != nullptr)
				right->parent = parent;
		}
		// Binary tree node without right child
		else if (right == nullptr)
		{
			// Link the parent node with a left child
			if (parent != nullptr)
			{
				if (parent->left == result)
					parent->left = left;
				else
					parent->right = left;
			}
			else
				_root = left;
			if (left != nullptr)
				left->parent = parent;
		}
		// Binary tree node with both left and right childs
		else
		{
			// Link the parent node with a left child
			if (parent != nullptr)
			{
				if (parent->left == result)
					parent->left = left;
				else
					parent->right = left;
			}
			else
				_root = left;
			left->parent = parent;

			// Find a new base node
			T* temp = left;
			while (temp->right != nullptr)
				temp = temp->right;
			temp->right = right;
			right->parent = temp;
		}

		result->parent = nullptr;
		result->left = nullptr;
		result->right = nullptr;
		--_size;
		return iterator(this, result);
	}

	template <typename T, typename TCompare>
	inline void BinTree<T, TCompare>::clear() noexcept
	{
		_size = 0;
		_root = nullptr;
	}

	template <typename T, typename TCompare>
	inline void BinTree<T, TCompare>::swap(BinTree& bintree) noexcept
	{
		using std::swap;
		swap(_compare, bintree._compare);
		swap(_size, bintree._size);
		swap(_root, bintree._root);
	}

	template <typename T, typename TCompare>
	inline void swap(BinTree<T, TCompare>& bintree1, BinTree<T, TCompare>& bintree2) noexcept
	{
		bintree1.swap(bintree2);
	}

	template <class TContainer, typename T>
	BinTreeIterator<TContainer, T>& BinTreeIterator<TContainer, T>::operator++() noexcept
	{
		if (_node != nullptr)
		{
			if (_node->right != nullptr)
			{
				_node = _node->right;
				while (_node->left != nullptr)
					_node = _node->left;
			}
			else
			{
				while ((_node->parent != nullptr) && compare(*_node->parent, *_node))
					_node = _node->parent;
				_node = _node->parent;
			}
		}
		return *this;
	}

	template <class TContainer, typename T>
	inline BinTreeIterator<TContainer, T> BinTreeIterator<TContainer, T>::operator++(int) noexcept
	{
		BinTreeIterator<TContainer, T> result(*this);
		operator++();
		return result;
	}

	template <class TContainer, typename T>
	typename BinTreeIterator<TContainer, T>::reference BinTreeIterator<TContainer, T>::operator*() noexcept
	{
		assert((_node != nullptr) && "Iterator must be valid!");

		return *_node;
	}

	template <class TContainer, typename T>
	typename BinTreeIterator<TContainer, T>::pointer BinTreeIterator<TContainer, T>::operator->() noexcept
	{
		return _node;
	}

	template <class TContainer, typename T>
	void BinTreeIterator<TContainer, T>::swap(BinTreeIterator& it) noexcept
	{
		using std::swap;
		swap(_container, it._container);
		swap(_node, it._node);
	}

	template <class TContainer, typename T>
	void swap(BinTreeIterator<TContainer, T>& it1, BinTreeIterator<TContainer, T>& it2) noexcept
	{
		it1.swap(it2);
	}

	template <class TContainer, typename T>
	BinTreeConstIterator<TContainer, T>& BinTreeConstIterator<TContainer, T>::operator++() noexcept
	{
		if (_node != nullptr)
		{
			if (_node->right != nullptr)
			{
				_node = _node->right;
				while (_node->left != nullptr)
					_node = _node->left;
			}
			else
			{
				while ((_node->parent != nullptr) && compare(*_node->parent, *_node))
					_node = _node->parent;
				_node = _node->parent;
			}
		}
		return *this;
	}

	template <class TContainer, typename T>
	inline BinTreeConstIterator<TContainer, T> BinTreeConstIterator<TContainer, T>::operator++(int) noexcept
	{
		BinTreeConstIterator<TContainer, T> result(*this);
		operator++();
		return result;
	}

	template <class TContainer, typename T>
	typename BinTreeConstIterator<TContainer, T>::const_reference BinTreeConstIterator<TContainer, T>::operator*() const noexcept
	{
		assert((_node != nullptr) && "Iterator must be valid!");

		return *_node;
	}

	template <class TContainer, typename T>
	typename BinTreeConstIterator<TContainer, T>::const_pointer BinTreeConstIterator<TContainer, T>::operator->() const noexcept
	{
		return _node;
	}

	template <class TContainer, typename T>
	void BinTreeConstIterator<TContainer, T>::swap(BinTreeConstIterator& it) noexcept
	{
		using std::swap;
		swap(_container, it._container);
		swap(_node, it._node);
	}

	template <class TContainer, typename T>
	void swap(BinTreeConstIterator<TContainer, T>& it1, BinTreeConstIterator<TContainer, T>& it2) noexcept
	{
		it1.swap(it2);
	}

	template <class TContainer, typename T>
	BinTreeReverseIterator<TContainer, T>& BinTreeReverseIterator<TContainer, T>::operator++() noexcept
	{
		if (_node != nullptr)
		{
			if (_node->left != nullptr)
			{
				_node = _node->left;
				while (_node->right != nullptr)
					_node = _node->right;
			}
			else
			{
				while ((_node->parent != nullptr) && compare(*_node, *_node->parent))
					_node = _node->parent;
				_node = _node->parent;
			}
		}
		return *this;
	}

	template <class TContainer, typename T>
	inline BinTreeReverseIterator<TContainer, T> BinTreeReverseIterator<TContainer, T>::operator++(int) noexcept
	{
		BinTreeReverseIterator<TContainer, T> result(*this);
		operator++();
		return result;
	}

	template <class TContainer, typename T>
	typename BinTreeReverseIterator<TContainer, T>::reference BinTreeReverseIterator<TContainer, T>::operator*() noexcept
	{
		assert((_node != nullptr) && "Iterator must be valid!");

		return *_node;
	}

	template <class TContainer, typename T>
	typename BinTreeReverseIterator<TContainer, T>::pointer BinTreeReverseIterator<TContainer, T>::operator->() noexcept
	{
		return _node;
	}

	template <class TContainer, typename T>
	void BinTreeReverseIterator<TContainer, T>::swap(BinTreeReverseIterator& it) noexcept
	{
		using std::swap;
		swap(_container, it._container);
		swap(_node, it._node);
	}

	template <class TContainer, typename T>
	void swap(BinTreeReverseIterator<TContainer, T>& it1, BinTreeReverseIterator<TContainer, T>& it2) noexcept
	{
		it1.swap(it2);
	}

	template <class TContainer, typename T>
	BinTreeConstReverseIterator<TContainer, T>& BinTreeConstReverseIterator<TContainer, T>::operator++() noexcept
	{
		if (_node != nullptr)
		{
			if (_node->left != nullptr)
			{
				_node = _node->left;
				while (_node->right != nullptr)
					_node = _node->right;
			}
			else
			{
				while ((_node->parent != nullptr) && compare(*_node, *_node->parent))
					_node = _node->parent;
				_node = _node->parent;
			}
		}
		return *this;
	}

	template <class TContainer, typename T>
	inline BinTreeConstReverseIterator<TContainer, T> BinTreeConstReverseIterator<TContainer, T>::operator++(int) noexcept
	{
		BinTreeConstReverseIterator<TContainer, T> result(*this);
		operator++();
		return result;
	}

	template <class TContainer, typename T>
	typename BinTreeConstReverseIterator<TContainer, T>::const_reference BinTreeConstReverseIterator<TContainer, T>::operator*() const noexcept
	{
		assert((_node != nullptr) && "Iterator must be valid!");

		return *_node;
	}

	template <class TContainer, typename T>
	typename BinTreeConstReverseIterator<TContainer, T>::const_pointer BinTreeConstReverseIterator<TContainer, T>::operator->() const noexcept
	{
		return _node;
	}

	template <class TContainer, typename T>
	void BinTreeConstReverseIterator<TContainer, T>::swap(BinTreeConstReverseIterator& it) noexcept
	{
		using std::swap;
		swap(_container, it._container);
		swap(_node, it._node);
	}

	template <class TContainer, typename T>
	void swap(BinTreeConstReverseIterator<TContainer, T>& it1, BinTreeConstReverseIterator<TContainer, T>& it2) noexcept
	{
		it1.swap(it2);
	}


}//namespace



#endif