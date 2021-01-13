#pragma once
#ifndef XT_BINTREE_AA_H
#define XT_BINTREE_AA_H

/**
* \file XTBinTreeAA.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for AA binary tree.
*
* \description
*	Designed for use for AA binary tree.
*/

#include <cassert>
#include <string>
#include <sstream>
#include <ostream> 

#include "XTBinTree.h"

namespace XT
{

	//! Intrusive balanced A.Andersson binary tree container
	/*!
		Not thread-safe.

		<b>Overview</b>\n
		Andersson trees are simple and easy to implement  balanced  binary  search
		trees that are based on the foundations of red black trees.  Consequently,
		Andersson trees have similar performance and structuring properties as red
		black trees without the difficult implementation. Red black trees  are  an
		abstraction of the symmetric binary B-tree, which is a clever  abstraction
		of a B-tree of order 4.  Andersson  trees  are  a  simplification  of  the
		symmetric binary B-tree that use a B-tree of order  3  to  remove  several
		unpleasant cases in the implementation. If the last  two  sentences  meant
		absolutely nothing to you, that's okay. This background isn't necessary to
		understand Andersson trees or implement them well.  Andersson  trees  were
		introduced by Arne Andersson in his  paper  "Balanced  Search  Trees  Made
		Simple". They were further studied by a  few  people,  most  notably  Mark
		Allen Weiss, who discussed them briefly in his books  on  data  structures
		and algorithm analysis.

		Andersson trees are a very simple  alternative  to  the  more  traditional
		balanced binary search trees. The performance properties are very close to
		that of red black trees, and the effort required in implementing  them  is
		minimal for anyone who is comfortable writing basic binary search trees.

		<b>Performance</b>\n
		The performance of an AA tree is equivalent to the performance of  a  red-
		black tree. While an AA tree makes more rotations than a  red-black  tree,
		the simpler algorithms tend to be faster, and all of this balances out  to
		result in similar performance. A red-black tree is more consistent in  its
		performance than an AA tree, but an AA tree tends  to  be  flatter,  which
		results in slightly faster search times.

		<b>Usage</b>\n
		When comparisons are expensive but lookups are more frequent than updates,
		the  AA  tree  might win.  AA  tree  tends  to  be flatter,  which results
		in  slightly faster search times.

		<b>Taken from:</b>\n
		AA tree from Wikipedia, the free encyclopedia
		http://en.wikipedia.org/wiki/AA_tree
	*/
	template <typename T, typename TCompare = std::less<T>>
	class BinTreeAA
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
		typedef BinTreeIterator<BinTreeAA<T, TCompare>, T> iterator;
		typedef BinTreeConstIterator<BinTreeAA<T, TCompare>, T> const_iterator;
		typedef BinTreeReverseIterator<BinTreeAA<T, TCompare>, T> reverse_iterator;
		typedef BinTreeConstReverseIterator<BinTreeAA<T, TCompare>, T> const_reverse_iterator;

		//! A.Andersson binary tree node
		struct Node
		{
			T* parent;      //!< Pointer to the parent binary tree node
			T* left;        //!< Pointer to the left child binary tree node
			T* right;       //!< Pointer to the right child binary tree node
			size_t level;   //!< Balance level

			Node() : parent(nullptr), left(nullptr), right(nullptr), level(0) {}
		};

		explicit BinTreeAA(const TCompare& compare = TCompare()) noexcept
			: _compare(compare),
			_size(0),
			_root(nullptr)
		{}
		template <class InputIterator>
		BinTreeAA(InputIterator first, InputIterator last, const TCompare& compare = TCompare()) noexcept;
		BinTreeAA(const BinTreeAA&) noexcept = default;
		BinTreeAA(BinTreeAA&&) noexcept = default;
		~BinTreeAA() noexcept = default;

		BinTreeAA& operator=(const BinTreeAA&) noexcept = default;
		BinTreeAA& operator=(BinTreeAA&&) noexcept = default;

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
		void swap(BinTreeAA& bintree) noexcept;
		template <typename U, typename UCompare>
		friend void swap(BinTreeAA<U, UCompare>& bintree1, BinTreeAA<U, UCompare>& bintree2) noexcept;

	private:
		TCompare _compare;  // Binary tree compare
		size_t _size;       // Binary tree size
		T* _root;           // Binary tree root node

		const T* InternalLowest() const noexcept;
		const T* InternalHighest() const noexcept;
		const T* InternalFind(const T& item) const noexcept;
		const T* InternalLowerBound(const T& item) const noexcept;
		const T* InternalUpperBound(const T& item) const noexcept;

		//! Skew the binary tree node
		/*!
			Skew is a right rotation when an insertion or deletion creates a left
			red link.

			\param node - Skew node
		*/
		void Skew(T* node);
		//! Split the binary tree node.
		/*!
			Split is a conditional left rotation when an insertion or deletion
			creates two consecutive red links.

			\param node - Split node
			\return 'true' if the split operation completed successfully, 'false' if the split operation failed
		*/
		bool Split(T* node);
	};
//////
	template <typename T, typename TCompare>
	template <class InputIterator>
	inline BinTreeAA<T, TCompare>::BinTreeAA(InputIterator first, InputIterator last, const TCompare& compare) noexcept
		: _compare(compare)
	{
		for (auto it = first; it != last; ++it)
			insert(*it);
	}

	template <typename T, typename TCompare>
	inline T* BinTreeAA<T, TCompare>::lowest() noexcept
	{
		return (T*)InternalLowest();
	}

	template <typename T, typename TCompare>
	inline const T* BinTreeAA<T, TCompare>::lowest() const noexcept
	{
		return InternalLowest();
	}

	template <typename T, typename TCompare>
	inline const T* BinTreeAA<T, TCompare>::InternalLowest() const noexcept
	{
		const T* result = _root;
		if (result != nullptr)
			while (result->left != nullptr)
				result = result->left;
		return result;
	}

	template <typename T, typename TCompare>
	inline T* BinTreeAA<T, TCompare>::highest() noexcept
	{
		return (T*)InternalHighest();
	}

	template <typename T, typename TCompare>
	inline const T* BinTreeAA<T, TCompare>::highest() const noexcept
	{
		return InternalHighest();
	}

	template <typename T, typename TCompare>
	inline const T* BinTreeAA<T, TCompare>::InternalHighest() const noexcept
	{
		const T* result = _root;
		if (result != nullptr)
			while (result->right != nullptr)
				result = result->right;
		return result;
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAA<T, TCompare>::iterator BinTreeAA<T, TCompare>::begin() noexcept
	{
		return iterator(this, lowest());
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAA<T, TCompare>::const_iterator BinTreeAA<T, TCompare>::begin() const noexcept
	{
		return const_iterator(this, lowest());
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAA<T, TCompare>::const_iterator BinTreeAA<T, TCompare>::cbegin() const noexcept
	{
		return const_iterator(this, lowest());
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAA<T, TCompare>::iterator BinTreeAA<T, TCompare>::end() noexcept
	{
		return iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAA<T, TCompare>::const_iterator BinTreeAA<T, TCompare>::end() const noexcept
	{
		return const_iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAA<T, TCompare>::const_iterator BinTreeAA<T, TCompare>::cend() const noexcept
	{
		return const_iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAA<T, TCompare>::reverse_iterator BinTreeAA<T, TCompare>::rbegin() noexcept
	{
		return reverse_iterator(this, highest());
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAA<T, TCompare>::const_reverse_iterator BinTreeAA<T, TCompare>::rbegin() const noexcept
	{
		return const_reverse_iterator(this, highest());
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAA<T, TCompare>::const_reverse_iterator BinTreeAA<T, TCompare>::crbegin() const noexcept
	{
		return const_reverse_iterator(this, highest());
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAA<T, TCompare>::reverse_iterator BinTreeAA<T, TCompare>::rend() noexcept
	{
		return reverse_iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAA<T, TCompare>::const_reverse_iterator BinTreeAA<T, TCompare>::rend() const noexcept
	{
		return const_reverse_iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAA<T, TCompare>::const_reverse_iterator BinTreeAA<T, TCompare>::crend() const noexcept
	{
		return const_reverse_iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAA<T, TCompare>::iterator BinTreeAA<T, TCompare>::find(const T& item) noexcept
	{
		return iterator(this, (T*)InternalFind(item));
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAA<T, TCompare>::const_iterator BinTreeAA<T, TCompare>::find(const T& item) const noexcept
	{
		return const_iterator(this, InternalFind(item));
	}

	template <typename T, typename TCompare>
	inline const T* BinTreeAA<T, TCompare>::InternalFind(const T& item) const noexcept
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
	inline typename BinTreeAA<T, TCompare>::iterator BinTreeAA<T, TCompare>::lower_bound(const T& item) noexcept
	{
		return iterator(this, (T*)InternalLowerBound(item));
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAA<T, TCompare>::const_iterator BinTreeAA<T, TCompare>::lower_bound(const T& item) const noexcept
	{
		return const_iterator(this, InternalLowerBound(item));
	}

	template <typename T, typename TCompare>
	inline const T* BinTreeAA<T, TCompare>::InternalLowerBound(const T& item) const noexcept
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
	inline typename BinTreeAA<T, TCompare>::iterator BinTreeAA<T, TCompare>::upper_bound(const T& item) noexcept
	{
		return iterator(this, (T*)InternalUpperBound(item));
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAA<T, TCompare>::const_iterator BinTreeAA<T, TCompare>::upper_bound(const T& item) const noexcept
	{
		return const_iterator(this, InternalUpperBound(item));
	}

	template <typename T, typename TCompare>
	inline const T* BinTreeAA<T, TCompare>::InternalUpperBound(const T& item) const noexcept
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
	inline std::pair<typename BinTreeAA<T, TCompare>::iterator, bool> BinTreeAA<T, TCompare>::insert(T& item) noexcept
	{
		return insert(const_iterator(this, _root), item);
	}

	template <typename T, typename TCompare>
	inline std::pair<typename BinTreeAA<T, TCompare>::iterator, bool> BinTreeAA<T, TCompare>::insert(const const_iterator& position, T& item) noexcept
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
		node->level = 1;
		while (node->parent != nullptr)
		{
			node = node->parent;
			if (node->level != ((node->left != nullptr) ? node->left->level + 1 : 1))
			{
				Skew(node);
				if ((node->right == nullptr) || (node->level != node->right->level))
					node = node->parent;
			}

			if (!Split(node->parent))
				break;
		}

		return std::make_pair(iterator(this, &item), true);
	}

	template <typename T, typename TCompare>
	inline T* BinTreeAA<T, TCompare>::erase(const T& item) noexcept
	{
		return erase(find(item)).operator->();
	}

	template <typename T, typename TCompare>
	inline typename BinTreeAA<T, TCompare>::iterator BinTreeAA<T, TCompare>::erase(const iterator& it) noexcept
	{
		T* result = ((iterator&)it).operator->();
		if (result == nullptr)
			return end();

		T* node = result;
		T* temp;

		if (result->left != nullptr)
		{
			node = result->left;
			while (node->right != nullptr)
				node = node->right;
		}
		else if (result->right != nullptr)
			node = result->right;

		temp = ((node->parent == result) ? node : node->parent);
		if (node->parent != nullptr)
		{
			if (node->parent->left == node)
				node->parent->left = nullptr;
			else
				node->parent->right = nullptr;
		}
		else
			_root = nullptr;

		if (result != node)
		{
			if (result->parent != nullptr)
			{
				if (result->parent->left == result)
					result->parent->left = node;
				else
					result->parent->right = node;
			}
			else
				_root = node;

			node->parent = result->parent;
			if (result->left != nullptr)
				result->left->parent = node;
			node->left = result->left;
			if (result->right != nullptr)
				result->right->parent = node;
			node->right = result->right;

			// Copy levels
			node->level = result->level;
		}

		while (temp != nullptr)
		{
			if (temp->level > ((temp->left != nullptr) ? temp->left->level + 1 : 1))
			{
				temp->level = temp->level - 1;
				if (Split(temp))
				{
					if (Split(temp))
						Skew(temp->parent->parent);
					break;
				}
			}
			else if (temp->level <= ((temp->right != nullptr) ? temp->right->level + 1 : 1))
				break;
			else
			{
				Skew(temp);
				if (temp->level > temp->parent->level)
				{
					Skew(temp);
					Split(temp->parent->parent);
					break;
				}
				temp = temp->parent;
			}
			temp = temp->parent;
		}

		result->parent = nullptr;
		result->left = nullptr;
		result->right = nullptr;
		--_size;
		return iterator(this, result);
	}

	template <typename T, typename TCompare>
	inline void BinTreeAA<T, TCompare>::Skew(T* node)
	{
		if (node == nullptr)
			return;

		T* current = node->left;
		if (node->parent != nullptr)
		{
			if (node->parent->left == node)
				node->parent->left = current;
			else
				node->parent->right = current;
		}
		else
			_root = current;
		current->parent = node->parent;
		node->parent = current;

		node->left = current->right;
		if (node->left != nullptr)
			node->left->parent = node;
		current->right = node;

		if (node->left != nullptr)
			node->level = node->left->level + 1;
		else
			node->level = 1;
	}

	template <typename T, typename TCompare>
	inline bool BinTreeAA<T, TCompare>::Split(T* node)
	{
		if (node == nullptr)
			return false;

		T* current = node->right;
		if ((current != nullptr) && (current->right != nullptr) && (current->right->level == node->level))
		{
			if (node->parent != nullptr)
			{
				if (node->parent->left == node)
					node->parent->left = current;
				else
					node->parent->right = current;
			}
			else
				_root = current;
			current->parent = node->parent;
			node->parent = current;

			node->right = current->left;
			if (node->right != nullptr)
				node->right->parent = node;
			current->left = node;
			current->level = node->level + 1;
			return true;
		}

		return false;
	}

	template <typename T, typename TCompare>
	inline void BinTreeAA<T, TCompare>::clear() noexcept
	{
		_size = 0;
		_root = nullptr;
	}

	template <typename T, typename TCompare>
	inline void BinTreeAA<T, TCompare>::swap(BinTreeAA& bintree) noexcept
	{
		using std::swap;
		swap(_compare, bintree._compare);
		swap(_size, bintree._size);
		swap(_root, bintree._root);
	}

	template <typename T, typename TCompare>
	inline void swap(BinTreeAA<T, TCompare>& bintree1, BinTreeAA<T, TCompare>& bintree2) noexcept
	{
		bintree1.swap(bintree2);
	}

}//namespace XT



#endif