#pragma once
#ifndef XT_BINTREE_AVL_H
#define XT_BINTREE_AVL_H

/**
* \file XTBinTreeAVL.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for avl binary tree.
*
* \description
*	Designed for use for avl binary tree.
*/

#include <cassert>
#include <string>
#include <sstream>
#include <ostream> 

#include "XTBinTree.h"

namespace XT
{

	//! Intrusive balanced AVL binary tree container
	/*!
		Not thread-safe.

		<b>Overview</b>\n
		In computer science, an AVL tree is a self-balancing binary  search  tree,
		and the first such data structure to be  invented.  In  an  AVL  tree  the
		heights of the two child subtrees of any  node  differ  by  at  most  one,
		therefore it  is  also  called  height-balanced.  Lookup,  insertion,  and
		deletion all take O(log n) time in  both  the  average  and  worst  cases.
		Additions and deletions may require the tree to be rebalanced  by  one  or
		more tree rotations.

		The AVL tree is named after its two  inventors,  G.M.  Adelson-Velsky  and
		E.M. Landis, who published it in their 1962 paper "An  algorithm  for  the
		organization of information."

		The balance factor of a node is the height of its right subtree minus  the
		height of its left subtree. A node with balance factor  1,  0,  or  -1  is
		considered balanced. A node with any other balance  factor  is  considered
		unbalanced and requires rebalancing the tree. The balance factor is either
		stored directly at each node or computed from the heights of the subtrees.

		While AVL trees are theoretically  quite  sound,  they  are  not  commonly
		implemented due  to  their  high  implementation  complexity  to  keep  it
		balanced,  making  development  less  effective  when  compared  to  self-
		correcting tree structures,  such  as  splay  trees  or  heaps.  They  do,
		however, perform better than e.g. red-black trees. They are widely used in
		academic settings as an instructional data structure.

		<b>Operations</b>\n
		The basic operations of an AVL tree generally  involve  carrying  out  the
		same algorithms as would be carried out on  an  unbalanced  binary  search
		tree, but preceded or followed by  one  or  more  of  the  so-called  "AVL
		rotations."

		<b>Insertion</b>\n
		Insertion into an AVL tree may be carried out by inserting the given value
		into the tree as if it were an unbalanced binary  search  tree,  and  then
		retracing one's steps toward the root, rotating about any nodes which have
		become unbalanced during the insertion (see tree rotation). Since at  most
		1.5 times lg n nodes are retraced on the journey back  to  the  root,  and
		each AVL rotation takes constant time,  the  insertion  process  in  total
		takes O(log n) time.

		<b>Deletion</b>\n
		Deletion from an AVL tree may be carried out by rotating the  node  to  be
		deleted down into a leaf  node,  and  then  pruning  off  that  leaf  node
		directly. Since at most log n nodes are rotated during the  rotation  into
		the leaf, and each AVL rotation takes constant time, the deletion  process
		in total takes O(log n) time.

		Practically, this is a large overhead and complex to  program.  Therefore,
		it's more common to implement a lazy deletion -- leave the deletion target
		in place, flag it as "deleted", and replace it with an  inserted  node  if
		they would occupy the same spot.

		<b>Lookup</b>\n
		Lookup in an AVL tree is performed exactly  as  in  an  unbalanced  binary
		search tree, and thus takes O(log n) time, since an  AVL  tree  is  always
		kept balanced. No special provisions need to  be  taken,  and  the  tree's
		structure is not modified by lookups. (This is in contrast to  splay  tree
		lookups, which do modify their tree's structure.)

		<b>Usage</b>\n
		AVL trees are  faster than Red-Black  trees when lookups are more frequent
		than inserts/deletes and comparisons are expensive.

		<b>References</b>\n
		\li G. Adelson-Velskii and E.M. Landis, "An algorithm for the organization
			of  information."  Doklady  Akademii  Nauk  SSSR,  146:263-266,   1962
			(Russian). English translation by  Myron  J.  Ricci  in  Soviet  Math.
			Doklady, 3:1259-1263, 1962.
		\li Donald Knuth. The Art of Computer Programming, Volume 3:  Sorting  and
			Searching, Third Edition. Addison-Wesley,  1997.  ISBN  0-201-89685-0.
			Pages 458-475 of section 6.2.3: Balanced Trees. Note that Knuth  calls
			AVL trees simply "balanced trees".

		<b>Taken from:</b>\n
		AVL tree from Wikipedia, the free encyclopedia
		http://en.wikipedia.org/wiki/AVL_tree
	*/
	template <typename T, typename TCompare = std::less<T>>
	class BinTreeAVL
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
		typedef BinTreeIterator<BinTreeAVL<T, TCompare>, T> iterator;
		typedef BinTreeConstIterator<BinTreeAVL<T, TCompare>, T> const_iterator;
		typedef BinTreeReverseIterator<BinTreeAVL<T, TCompare>, T> reverse_iterator;
		typedef BinTreeConstReverseIterator<BinTreeAVL<T, TCompare>, T> const_reverse_iterator;

		//! AVL binary tree node
		struct Node
		{
			T* parent;          //!< Pointer to the parent binary tree node
			T* left;            //!< Pointer to the left child binary tree node
			T* right;           //!< Pointer to the right child binary tree node
			char balance;       //!< Balance level (-1, 0, 1)

			Node() : parent(nullptr), left(nullptr), right(nullptr), balance(0) {}
		};

		explicit BinTreeAVL(const TCompare& compare = TCompare()) noexcept
			: _compare(compare),
			_size(0),
			_root(nullptr)
		{}
		template <class InputIterator>
		BinTreeAVL(InputIterator first, InputIterator last, const TCompare& compare = TCompare()) noexcept;
		BinTreeAVL(const BinTreeAVL&) noexcept = default;
		BinTreeAVL(BinTreeAVL&&) noexcept = default;
		~BinTreeAVL() noexcept = default;

		BinTreeAVL& operator=(const BinTreeAVL&) noexcept = default;
		BinTreeAVL& operator=(BinTreeAVL&&) noexcept = default;

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
		void swap(BinTreeAVL& bintree) noexcept;
		template <typename U, typename UCompare>
		friend void swap(BinTreeAVL<U, UCompare>& bintree1, BinTreeAVL<U, UCompare>& bintree2) noexcept;

	private:
		TCompare _compare;  // Binary tree compare
		size_t _size;       // Binary tree size
		T* _root;           // Binary tree root node

		const T* InternalLowest() const noexcept;
		const T* InternalHighest() const noexcept;
		const T* InternalFind(const T& item) const noexcept;
		const T* InternalLowerBound(const T& item) const noexcept;
		const T* InternalUpperBound(const T& item) const noexcept;

		static void RotateLeft(T* node);
		static void RotateRight(T* node);
		static void RotateLeftLeft(T* node);
		static void RotateRightRight(T* node);
		static void Unlink(T* node);
		static void Swap(T*& node1, T*& node2);
	};
	//////
	template <typename T, typename TCompare>
	template <class InputIterator>
	inline BinTreeAVL<T, TCompare>::BinTreeAVL(InputIterator first, InputIterator last, const TCompare& compare) noexcept
		: _compare(compare)
	{
		for (auto it = first; it != last; ++it)
			insert(*it);
	}

	template <typename T, typename TCompare>
	inline T* BinTreeAVL<T, TCompare>::lowest() noexcept
	{
		return (T*)InternalLowest();
	}

	template <typename T, typename TCompare>
	inline const T* BinTreeAVL<T, TCompare>::lowest() const noexcept
	{
		return InternalLowest();
	}

	template <typename T, typename TCompare>
	inline const T* BinTreeAVL<T, TCompare>::InternalLowest() const noexcept
	{
		const T* result = _root;
		if (result != nullptr)
			while (result->left != nullptr)
				result = result->left;
		return result;
	}

	template <typename T, typename TCompare>
	inline T* BinTreeAVL<T, TCompare>::highest() noexcept
	{
		return (T*)InternalHighest();
	}

	template <typename T, typename TCompare>
	inline const T* BinTreeAVL<T, TCompare>::highest() const noexcept
	{
		return InternalHighest();
	}

	template <typename T, typename TCompare>
	inline const T* BinTreeAVL<T, TCompare>::InternalHighest() const noexcept
	{
		const T* result = _root;
		if (result != nullptr)
			while (result->right != nullptr)
				result = result->right;
		return result;
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAVL<T, TCompare>::iterator BinTreeAVL<T, TCompare>::begin() noexcept
	{
		return iterator(this, lowest());
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAVL<T, TCompare>::const_iterator BinTreeAVL<T, TCompare>::begin() const noexcept
	{
		return const_iterator(this, lowest());
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAVL<T, TCompare>::const_iterator BinTreeAVL<T, TCompare>::cbegin() const noexcept
	{
		return const_iterator(this, lowest());
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAVL<T, TCompare>::iterator BinTreeAVL<T, TCompare>::end() noexcept
	{
		return iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAVL<T, TCompare>::const_iterator BinTreeAVL<T, TCompare>::end() const noexcept
	{
		return const_iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAVL<T, TCompare>::const_iterator BinTreeAVL<T, TCompare>::cend() const noexcept
	{
		return const_iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAVL<T, TCompare>::reverse_iterator BinTreeAVL<T, TCompare>::rbegin() noexcept
	{
		return reverse_iterator(this, highest());
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAVL<T, TCompare>::const_reverse_iterator BinTreeAVL<T, TCompare>::rbegin() const noexcept
	{
		return const_reverse_iterator(this, highest());
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAVL<T, TCompare>::const_reverse_iterator BinTreeAVL<T, TCompare>::crbegin() const noexcept
	{
		return const_reverse_iterator(this, highest());
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAVL<T, TCompare>::reverse_iterator BinTreeAVL<T, TCompare>::rend() noexcept
	{
		return reverse_iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAVL<T, TCompare>::const_reverse_iterator BinTreeAVL<T, TCompare>::rend() const noexcept
	{
		return const_reverse_iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAVL<T, TCompare>::const_reverse_iterator BinTreeAVL<T, TCompare>::crend() const noexcept
	{
		return const_reverse_iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAVL<T, TCompare>::iterator BinTreeAVL<T, TCompare>::find(const T& item) noexcept
	{
		return iterator(this, (T*)InternalFind(item));
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAVL<T, TCompare>::const_iterator BinTreeAVL<T, TCompare>::find(const T& item) const noexcept
	{
		return const_iterator(this, InternalFind(item));
	}

	template <typename T, typename TCompare>
	inline const T* BinTreeAVL<T, TCompare>::InternalFind(const T& item) const noexcept
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
	inline typename BinTreeAVL<T, TCompare>::iterator BinTreeAVL<T, TCompare>::lower_bound(const T& item) noexcept
	{
		return iterator(this, (T*)InternalLowerBound(item));
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAVL<T, TCompare>::const_iterator BinTreeAVL<T, TCompare>::lower_bound(const T& item) const noexcept
	{
		return const_iterator(this, InternalLowerBound(item));
	}

	template <typename T, typename TCompare>
	inline const T* BinTreeAVL<T, TCompare>::InternalLowerBound(const T& item) const noexcept
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
	inline typename BinTreeAVL<T, TCompare>::iterator BinTreeAVL<T, TCompare>::upper_bound(const T& item) noexcept
	{
		return iterator(this, (T*)InternalUpperBound(item));
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAVL<T, TCompare>::const_iterator BinTreeAVL<T, TCompare>::upper_bound(const T& item) const noexcept
	{
		return const_iterator(this, InternalUpperBound(item));
	}

	template <typename T, typename TCompare>
	inline const T* BinTreeAVL<T, TCompare>::InternalUpperBound(const T& item) const noexcept
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
	inline std::pair<typename BinTreeAVL<T, TCompare>::iterator, bool> BinTreeAVL<T, TCompare>::insert(T& item) noexcept
	{
		return insert(const_iterator(this, _root), item);
	}

	template <typename T, typename TCompare>
	inline std::pair<typename BinTreeAVL<T, TCompare>::iterator, bool> BinTreeAVL<T, TCompare>::insert(const const_iterator& position, T& item) noexcept
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

		// Balance the binary tree
		T* node = &item;
		node->balance = 0;
		while (node->parent != nullptr)
		{
			// Rule 1
			if (((node->parent != nullptr) && (node->parent->left == node)) && (node->parent->balance == 0))
			{
				node->parent->balance = -1;
				node = node->parent;
				continue;
			}
			if (((node->parent != nullptr) && (node->parent->right == node)) && (node->parent->balance == 0))
			{
				node->parent->balance = 1;
				node = node->parent;
				continue;
			}

			// Rule 2
			if (((node->parent != nullptr) && (node->parent->left == node)) && (node->parent->balance == 1))
			{
				node->parent->balance = 0;
				break;
			}
			if (((node->parent != nullptr) && (node->parent->right == node)) && (node->parent->balance == -1))
			{
				node->parent->balance = 0;
				break;
			}

			// Rule 3
			if (((node->parent != nullptr) && (node->parent->left == node)) && (node->parent->balance == -1))
			{
				if (node->balance == 1)
					RotateLeftLeft(node->parent);
				else
					RotateRight(node->parent);
				break;
			}
			if (((node->parent != nullptr) && (node->parent->right == node)) && (node->parent->balance == 1))
			{
				if (node->balance == -1)
					RotateRightRight(node->parent);
				else
					RotateLeft(node->parent);
				break;
			}
		}

		// Correct AVL balanced binary tree root
		while (_root->parent != nullptr)
			_root = _root->parent;

		return std::make_pair(iterator(this, &item), true);
	}

	template <typename T, typename TCompare>
	inline T* BinTreeAVL<T, TCompare>::erase(const T& item) noexcept
	{
		return erase(find(item)).operator->();
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAVL<T, TCompare>::iterator BinTreeAVL<T, TCompare>::erase(const iterator& it) noexcept
	{
		T* result = ((iterator&)it).operator->();
		if (result == nullptr)
			return end();

		T* node = result;
		T* start = nullptr;

		// If we want to delete the root item, we have to do some extra operation the preserve some pointers...
		if (node->parent == nullptr)
		{
			// The root is the only one node in the tree
			if ((node->left == nullptr) && (node->right == nullptr))
			{
				_root = nullptr;
				node = nullptr;
			}
		}

		// Removed node has no children
		if ((node != nullptr) && (node->left == nullptr) && (node->right == nullptr))
		{
			if (node->parent->left == node)
				node->parent->left = nullptr;
			else
				node->parent->right = nullptr;
			start = node->parent;
			node = nullptr;
		}

		// Removed node has only right son
		if ((node != nullptr) && (node->left == nullptr) && (node->right != nullptr))
		{
			T* a = node->right;
			if (node->parent == nullptr)
				_root = a;
			Swap(node, a);
			node->right = nullptr;
			start = node;
		}

		// Removed node has only left son
		if ((node != nullptr) && (node->left != nullptr) && (node->right == nullptr))
		{
			T* a = node->left;
			if (node->parent == nullptr)
				_root = a;
			Swap(node, a);
			node->left = nullptr;
			start = node;
		}

		// Removed node has both sons.
		if ((node != nullptr) && (node->left != nullptr) && (node->right != nullptr))
		{
			T* a = node->left;
			while (a->right != nullptr)
				a = a->right;
			T* b = a->left;

			if (node->parent == nullptr)
				_root = a;
			Swap(node, a);

			if (b != nullptr)
			{
				if (a->parent == nullptr)
					_root = b;
				Swap(a, b);
				a->left = nullptr;
				start = a;
			}
			else
			{
				if (a->parent->left == a)
					a->parent->left = nullptr;
				else
					a->parent->right = nullptr;
				start = a->parent;
			}
		}

		// Unlink the removed node
		if (start != nullptr)
			Unlink(start);

		// Correct AVL balanced binary tree root
		if (_root != nullptr)
		{
			while (_root->parent != nullptr)
				_root = _root->parent;
		}

		result->parent = nullptr;
		result->left = nullptr;
		result->right = nullptr;
		--_size;
		return iterator(this, result);
	}

	template <typename T, typename TCompare>
	inline void BinTreeAVL<T, TCompare>::RotateLeft(T* node)
	{
		if (node->right == nullptr)
			return;

		T* current = node->right;

		if (node->parent != nullptr)
		{
			if ((node->parent != nullptr) && (node->parent->left == node))
				node->parent->left = current;
			else
				node->parent->right = current;
			current->parent = node->parent;
		}
		else
			current->parent = nullptr;
		node->right = current->left;
		current->left = node;
		node->parent = current;
		if (node->right != nullptr)
			node->right->parent = node;

		if (current->balance == 0)
		{
			node->balance = 1;
			current->balance = -1;
		}
		else
		{
			node->balance = 0;
			current->balance = 0;
		}
	}

	template <typename T, typename TCompare>
	inline void BinTreeAVL<T, TCompare>::RotateRight(T* node)
	{
		if (node->left == nullptr)
			return;

		T* current = node->left;

		if (node->parent != nullptr)
		{
			if ((node->parent != nullptr) && (node->parent->left == node))
				node->parent->left = current;
			else
				node->parent->right = current;
			current->parent = node->parent;
		}
		else
			current->parent = nullptr;
		node->left = current->right;
		current->right = node;
		node->parent = current;
		if (node->left != nullptr)
			node->left->parent = node;

		if (current->balance == 0)
		{
			node->balance = -1;
			current->balance = 1;
		}
		else
		{
			node->balance = 0;
			current->balance = 0;
		}
	}

	template <typename T, typename TCompare>
	inline void BinTreeAVL<T, TCompare>::RotateLeftLeft(T* node)
	{
		if ((node->left == nullptr) || (node->left->right == nullptr))
			return;

		T* current = node->left;
		T* next = node->left->right;

		if (node->parent != nullptr)
		{
			if ((node->parent != nullptr) && (node->parent->left == node))
				node->parent->left = next;
			else
				node->parent->right = next;
		}
		current->right = next->left;
		node->left = next->right;
		next->left = current;
		next->right = node;
		next->parent = node->parent;
		node->parent = next;
		current->parent = next;
		if (current->right != nullptr)
			current->right->parent = current;
		if (node->left != nullptr)
			node->left->parent = node;

		switch (next->balance)
		{
		case -1:
			node->balance = 1;
			current->balance = 0;
			break;
		case 0:
			node->balance = 0;
			current->balance = 0;
			break;
		case 1:
			node->balance = 0;
			current->balance = -1;
			break;
		}
		next->balance = 0;
	}

	template <typename T, typename TCompare>
	inline void BinTreeAVL<T, TCompare>::RotateRightRight(T* node)
	{
		if ((node->right == nullptr) || (node->right->left == nullptr))
			return;

		T* current = node->right;
		T* next = node->right->left;

		if (node->parent != nullptr)
		{
			if ((node->parent != nullptr) && (node->parent->left == node))
				node->parent->left = next;
			else
				node->parent->right = next;
		}
		node->right = next->left;
		current->left = next->right;
		next->left = node;
		next->right = current;
		next->parent = node->parent;
		node->parent = next;
		current->parent = next;
		if (node->right != nullptr)
			node->right->parent = node;
		if (current->left != nullptr)
			current->left->parent = current;

		switch (next->balance)
		{
		case -1:
			node->balance = 0;
			current->balance = 1;
			break;
		case 0:
			node->balance = 0;
			current->balance = 0;
			break;
		case 1:
			node->balance = -1;
			current->balance = 0;
			break;
		}
		next->balance = 0;
	}

	template <typename T, typename TCompare>
	inline void BinTreeAVL<T, TCompare>::Unlink(T* node)
	{
		// Rule 1
		if ((node->balance == 0) && (node->left == nullptr))
		{
			node->balance = 1;
			return;
		}
		if ((node->balance == 0) && (node->right == nullptr))
		{
			node->balance = -1;
			return;
		}

		// Rule 2
		if ((node->balance == -1) && (node->left == nullptr))
			node->balance = 0;
		if ((node->balance == 1) && (node->right == nullptr))
			node->balance = 0;

		// Rule 3
		if ((node->balance == -1) && (node->right == nullptr))
		{
			if (node->left->balance == 1)
				RotateLeftLeft(node);
			else
				RotateRight(node);
			node = node->parent;
			if (node->balance == 1)
				return;
		}
		if ((node->balance == 1) && (node->left == nullptr))
		{
			if (node->right->balance == -1)
				RotateRightRight(node);
			else
				RotateLeft(node);
			node = node->parent;
			if (node->balance == -1)
				return;
		}

		while (node->parent != nullptr)
		{
			// Rule 1
			if (((node->parent != nullptr) && (node->parent->left == node)) && (node->parent->balance == 0))
			{
				node->parent->balance = 1;
				break;
			}
			if (((node->parent != nullptr) && (node->parent->right == node)) && (node->parent->balance == 0))
			{
				node->parent->balance = -1;
				break;
			}

			// Rule 2
			if (((node->parent != nullptr) && (node->parent->left == node)) && (node->parent->balance == -1))
			{
				node->parent->balance = 0;
				node = node->parent;
				continue;
			}
			if (((node->parent != nullptr) && (node->parent->right == node)) && (node->parent->balance == 1))
			{
				node->parent->balance = 0;
				node = node->parent;
				continue;
			}

			// Rule 3
			if (((node->parent != nullptr) && (node->parent->right == node)) && (node->parent->balance == -1))
			{
				if (node->parent->left->balance == 1)
					RotateLeftLeft(node->parent);
				else
					RotateRight(node->parent);
				node = node->parent->parent;
				if (node->balance == 1)
					return;
				continue;
			}
			if (((node->parent != nullptr) && (node->parent->left == node)) && (node->parent->balance == 1))
			{
				if (node->parent->right->balance == -1)
					RotateRightRight(node->parent);
				else
					RotateLeft(node->parent);
				node = node->parent->parent;
				if (node->balance == -1)
					return;
				continue;
			}

			// Never happens...
			break;
		}
	}

	template <typename T, typename TCompare>
	inline void BinTreeAVL<T, TCompare>::Swap(T*& node1, T*& node2)
	{
		T* first_parent = node1->parent;
		T* first_left = node1->left;
		T* first_right = node1->right;
		T* second_parent = node2->parent;
		T* second_left = node2->left;
		T* second_right = node2->right;
		bool first_is_left = ((first_parent != nullptr) && (first_parent->left == node1));
		bool second_is_left = ((second_parent != nullptr) && (second_parent->left == node2));

		// Update first node links
		if (first_parent != nullptr)
		{
			if (first_is_left)
				first_parent->left = node2;
			else
				first_parent->right = node2;
		}
		if (first_left != nullptr)
			first_left->parent = node2;
		if (first_right != nullptr)
			first_right->parent = node2;

		// Update second node links
		if (second_parent != nullptr)
		{
			if (second_is_left)
				second_parent->left = node1;
			else
				second_parent->right = node1;
		}
		if (second_left != nullptr)
			second_left->parent = node1;
		if (second_right != nullptr)
			second_right->parent = node1;

		// Swap node links
		std::swap(node1->parent, node2->parent);
		std::swap(node1->left, node2->left);
		std::swap(node1->right, node2->right);
		std::swap(node1->balance, node2->balance);

		// Swap nodes
		std::swap(node1, node2);
	}

	template <typename T, typename TCompare>
	inline void BinTreeAVL<T, TCompare>::clear() noexcept
	{
		_size = 0;
		_root = nullptr;
	}

	template <typename T, typename TCompare>
	inline void BinTreeAVL<T, TCompare>::swap(BinTreeAVL& bintree) noexcept
	{
		using std::swap;
		swap(_compare, bintree._compare);
		swap(_size, bintree._size);
		swap(_root, bintree._root);
	}

	template <typename T, typename TCompare>
	inline void swap(BinTreeAVL<T, TCompare>& bintree1, BinTreeAVL<T, TCompare>& bintree2) noexcept
	{
		bintree1.swap(bintree2);
	}

}//namespace



#endif