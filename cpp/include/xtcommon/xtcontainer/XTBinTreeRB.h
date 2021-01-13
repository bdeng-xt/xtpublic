#pragma once
#ifndef XT_BINTREE_RB_H
#define XT_BINTREE_RB_H

/**
* \file XTBinTreeRB.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for red black binary tree.
*
* \description
*	Designed for use for red black binary tree.
*/

#include <cassert>
#include <string>
#include <sstream>
#include <ostream> 

#include "XTBinTree.h"

namespace XT
{

	//! Intrusive balanced Red-Black binary tree container
	/*!
		Not thread-safe.

		<b>Overview</b>\n
		A red-black tree is a type of self-balancing binary search  tree,  a  data
		structure  used  in  computer  science,  typically   used   to   implement
		associative arrays. The original structure was invented in 1972 by  Rudolf
		Bayer who called them "symmetric binary B-trees", but acquired its  modern
		name in a paper in 1978 by Leo J.  Guibas  and  Robert  Sedgewick.  It  is
		complex, but has good worst-case running time for its  operations  and  is
		efficient in practice: it can search, insert, and delete in O(log n) time,
		where n is the number of elements in the tree.

		<b>Background and terminology</b>\n
		A red-black tree is a special type of binary tree, which  is  a  structure
		used in computer science to organize pieces of comparable  data,  such  as
		numbers. Each piece of data is stored in a node. One of the  nodes  always
		functions as our starting place, and is not the child of any node; we call
		this the root node or root. It has up to two "children",  other  nodes  to
		which it connects. Each of these children can have up to two  children  of
		its own, and so on. The root node thus has a path  connecting  it  to  any
		other node in the tree.

		If a node has no children, we call it a leaf node, since intuitively it is
		at the periphery of the tree. A subtree is the portion of  the  tree  that
		can be reached from a certain  node,  considered  as  a  tree  itself.  In
		red-black trees, the leaves are assumed to be null, that is, they  do  not
		contain any data.

		As red-black  trees  are  also  binary  search  trees,  they  satisfy  the
		constraint that every node contains a value less  than  or  equal  to  all
		nodes in its right subtree, and greater than or equal to all nodes in  its
		left subtree. This makes it quick to search the tree for  a  given  value,
		and allows efficient in-order traversal of elements.

		<b>Uses and advantages.</b>\n
		Red-black trees, along with AVL trees, offer the best possible  worst-case
		guarantees for insertion time, deletion time, and search  time.  Not  only
		does this make  them  valuable  in  time-sensitive  applications  such  as
		real-time applications, but it makes  them  valuable  building  blocks  in
		other data structures which provide worst-case  guarantees;  for  example,
		many data structures used  in  computational  geometry  can  be  based  on
		red-black trees.

		Red-black trees are also particularly valuable in functional  programming,
		where they are one of the most common persistent data structures, used  to
		construct associative arrays and sets which can retain  previous  versions
		after mutations. The persistent version of red-black trees requires  O(log
		n) space for each insertion or deletion, in addition to time.

		Red-black trees are an isometry of 2-3-4 trees. In other words, for  every
		2-3-4 tree, there exists at least one red-black tree with data elements in
		the same order. The insertion and deletion operations on 2-3-4  trees  are
		also equivalent to color-flipping and rotations in red-black  trees.  This
		makes 2-3-4 trees an important tool for  understanding  the  logic  behind
		red-black trees,  and  this  is  why  many  introductory  algorithm  texts
		introduce 2-3-4 trees just before red-black trees, even though 2-3-4 trees
		are not often used in practice.

		<b>Properties</b>\n
		\image html BinTreeRB.png "Red-Black binary tree"
		A red-black tree is a binary search tree  where  each  node  has  a  color
		attribute, the value of which is either red or black. In addition  to  the
		ordinary  requirements  imposed  on  binary  search  trees,  we  make  the
		following additional requirements of any valid red-black tree:

		\li 1. A node is either red or black.
		\li 2. The root is black.
		\li 3. All leaves are black. (This includes the NIL children)
		\li 4. Both children of every red node are black.  (i.e.  Every  red  node
			   must have a black parent.)
		\li 5. All paths from any given node to its leaf nodes  contain  the  same
			   number of black nodes.

		These constraints enforce a critical property of red-black trees: that the
		longest possible path from the root to a leaf is no  more  than  twice  as
		long as the shortest possible path. The result is that the tree is roughly
		balanced. Since operations such as inserting, deleting, and finding values
		requires worst-case time proportional to the  height  of  the  tree,  this
		theoretical upper bound  on  the  height  allows  red-black  trees  to  be
		efficient in the worst-case, unlike ordinary binary search trees.

		To see why these properties guarantee this, it suffices to  note  that  no
		path can have two red nodes in a row, due  to  property  4.  The  shortest
		possible  path  has  all  black  nodes,  and  the  longest  possible  path
		alternates between red and black nodes. Since all maximal paths  have  the
		same number of black nodes, by property 5, this shows that no path is more
		than twice as long as any other path.

		In many presentations of tree data structures, it is possible for  a  node
		to have only one child, and leaf nodes contain data.  It  is  possible  to
		present red-black trees in this paradigm, but it changes  several  of  the
		properties and complicates  the  algorithms.  For  this  reason,  in  this
		article we use "nil leaves" or "null leaves", which contain  no  data  and
		merely serve to indicate where the tree ends, as shown above. These  nodes
		are often omitted  in  drawings,  resulting  in  a  tree  which  seems  to
		contradict the above principles, but which in fact does not. A consequence
		of this is that all internal (non-leaf) nodes have two children,  although
		one or more of those children may be a null leaf.

		Some explain a red-black tree as a binary search tree whose edges, instead
		of nodes, are colored in  red  or  black,  but  this  does  not  make  any
		difference. The color of a node in  our  terminology  corresponds  to  the
		color of the edge connecting the node to its parent, except that the  root
		node  is  always  black  in  our  terminology  (property  2)  whereas  the
		corresponding edge does not exist.

		<b>Operations</b>\n
		Read-only operations on a red-black  tree  require  no  modification  from
		those used for binary search trees, because  every  red-black  tree  is  a
		specialization of a simple binary  search  tree.  However,  the  immediate
		result of an  insertion  or  removal  may  violate  the  properties  of  a
		red-black tree. Restoring the red-black properties requires a small number
		(O(log n) or amortized O(1)) of color changes (which  are  very  quick  in
		practice) and no more than  three  tree  rotations  (two  for  insertion).
		Although insert and delete operations are complicated, their times  remain
		O(log n).

		<b>Proof of asymptotic bounds</b>\n

		A red black  tree  which  contains  n  internal  nodes  has  a  height  of
		O(log(n)).

		Definitions:

		\li h(v) = height of subtree rooted at node v
		\li bh(v) = the number of black nodes (not counting v if it is black) from
			v to any leaf in the subtree (called the black-height).

		<b>Lemma:</b> A subtree rooted at node v has at least 2bh(v) ? 1  internal
		nodes.

		Proof of Lemma (by induction height):

		Basis: h(v) = 0

		If v has a height of zero then it must be nil, therefore bh(v) = 0. So:

		\f$2^{bh(v)} - 1 = 20 - 1 = 1 - 1 = 0\f$

		Inductive Hypothesis: v such that  h(v)  =  k,  has  \f$2^{bh(v)}  -  1\f$
		internal nodes implies that v' such that h(v') = k+1 has  \f$2^{bh(v')}  -
		1\f$ internal nodes.

		Since v' has h(v') > 0 it is an internal node. As such it has two children
		which have a black-height of  either  bh(v')  or  bh(v')-1  (depending  on
		whether v' is red or black). By the inductive hypothesis each child has at
		least \f$2^{bh(v)} - 1 - 1\f$ internal nodes, so v' has:

		\f[2^{bh(v)} - 1 - 1 + 2^{bh(v')} - 1 - 1 + 1 = 2^{bh(v')} - 1\f]

		internal nodes.

		Using this lemma  we  can  now  show  that  the  height  of  the  tree  is
		logarithmic. Since at least half of the nodes on any path from the root to
		a leaf are black (property 4 of a red black tree), the  black-  height  of
		the root is at least \f$h(root) \over 2\f$. By the lemma we get:

		\f[n \geq 2^{{h(root) \over 2}} - 1 \leftrightarrow  \;  \log{(n+1)}  \geq
		{h(root) \over 2} \leftrightarrow \; h(root) \leq 2\log{(n+1)}\f]

		Therefore the height of the root is O(log(n)).

		<b>Usage</b>\n
		Reb-Black trees have as a first advantage that their performance is easier
		to  predict, making  them a good  data structure  for libraries. Reb-Black
		tree  win AVL trees  in cases when there are lots of inserts / deletes and
		comparisons  are  chap.  Reb-Black tree  will be faster because on average
		Reb-Black tree use less rotation.

		<b>References</b>\n
		\li Mathworld: Red-Black Tree
		\li San Diego State University: CS 660: Red-Black  tree  notes,  by  Roger
			Whitney
		\li Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford
			Stein. Introduction to  Algorithms,  Second  Edition.  MIT  Press  and
			McGraw-Hill, 2001. ISBN 0-262-03293-7 . Chapter 13:  Red-Black  Trees,
			pp.273-301.

		<b>Taken from:</b>\n
		Red-black tree from Wikipedia, the free encyclopedia
		http://en.wikipedia.org/wiki/Red-black_tree
	*/
	template <typename T, typename TCompare = std::less<T>>
	class BinTreeRB
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
		typedef BinTreeIterator<BinTreeRB<T, TCompare>, T> iterator;
		typedef BinTreeConstIterator<BinTreeRB<T, TCompare>, T> const_iterator;
		typedef BinTreeReverseIterator<BinTreeRB<T, TCompare>, T> reverse_iterator;
		typedef BinTreeConstReverseIterator<BinTreeRB<T, TCompare>, T> const_reverse_iterator;

		//! Red-Black binary tree node
		struct Node
		{
			T* parent;  //!< Pointer to the parent binary tree node
			T* left;    //!< Pointer to the left child binary tree node
			T* right;   //!< Pointer to the right child binary tree node
			bool rb;    //!< Red-Black flag

			Node() : parent(nullptr), left(nullptr), right(nullptr), rb(false) {}
		};

		explicit BinTreeRB(const TCompare& compare = TCompare()) noexcept
			: _compare(compare),
			_size(0),
			_root(nullptr)
		{}
		template <class InputIterator>
		BinTreeRB(InputIterator first, InputIterator last, const TCompare& compare = TCompare()) noexcept;
		BinTreeRB(const BinTreeRB&) noexcept = default;
		BinTreeRB(BinTreeRB&&) noexcept = default;
		~BinTreeRB() noexcept = default;

		BinTreeRB& operator=(const BinTreeRB&) noexcept = default;
		BinTreeRB& operator=(BinTreeRB&&) noexcept = default;

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
		void swap(BinTreeRB& bintree) noexcept;
		template <typename U, typename UCompare>
		friend void swap(BinTreeRB<U, UCompare>& bintree1, BinTreeRB<U, UCompare>& bintree2) noexcept;

	private:
		TCompare _compare;  // Binary tree compare
		size_t _size;       // Binary tree size
		T* _root;           // Binary tree root node

		const T* InternalLowest() const noexcept;
		const T* InternalHighest() const noexcept;
		const T* InternalFind(const T& item) const noexcept;
		const T* InternalLowerBound(const T& item) const noexcept;
		const T* InternalUpperBound(const T& item) const noexcept;

		void RotateLeft(T* node);
		void RotateRight(T* node);
		void Unlink(T* node, T* parent);
		static void Swap(T*& node1, T*& node2);
	};
//////
	template <typename T, typename TCompare>
	template <class InputIterator>
	inline BinTreeRB<T, TCompare>::BinTreeRB(InputIterator first, InputIterator last, const TCompare& compare) noexcept
		: _compare(compare)
	{
		for (auto it = first; it != last; ++it)
			insert(*it);
	}

	template <typename T, typename TCompare>
	inline T* BinTreeRB<T, TCompare>::lowest() noexcept
	{
		return (T*)InternalLowest();
	}

	template <typename T, typename TCompare>
	inline const T* BinTreeRB<T, TCompare>::lowest() const noexcept
	{
		return InternalLowest();
	}

	template <typename T, typename TCompare>
	inline const T* BinTreeRB<T, TCompare>::InternalLowest() const noexcept
	{
		const T* result = _root;
		if (result != nullptr)
			while (result->left != nullptr)
				result = result->left;
		return result;
	}

	template <typename T, typename TCompare>
	inline T* BinTreeRB<T, TCompare>::highest() noexcept
	{
		return (T*)InternalHighest();
	}

	template <typename T, typename TCompare>
	inline const T* BinTreeRB<T, TCompare>::highest() const noexcept
	{
		return InternalHighest();
	}

	template <typename T, typename TCompare>
	inline const T* BinTreeRB<T, TCompare>::InternalHighest() const noexcept
	{
		const T* result = _root;
		if (result != nullptr)
			while (result->right != nullptr)
				result = result->right;
		return result;
	}

	template <typename T, typename TCompare>
	inline typename BinTreeRB<T, TCompare>::iterator BinTreeRB<T, TCompare>::begin() noexcept
	{
		return iterator(this, lowest());
	}

	template <typename T, typename TCompare>
	inline typename BinTreeRB<T, TCompare>::const_iterator BinTreeRB<T, TCompare>::begin() const noexcept
	{
		return const_iterator(this, lowest());
	}

	template <typename T, typename TCompare>
	inline typename BinTreeRB<T, TCompare>::const_iterator BinTreeRB<T, TCompare>::cbegin() const noexcept
	{
		return const_iterator(this, lowest());
	}

	template <typename T, typename TCompare>
	inline typename BinTreeRB<T, TCompare>::iterator BinTreeRB<T, TCompare>::end() noexcept
	{
		return iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTreeRB<T, TCompare>::const_iterator BinTreeRB<T, TCompare>::end() const noexcept
	{
		return const_iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTreeRB<T, TCompare>::const_iterator BinTreeRB<T, TCompare>::cend() const noexcept
	{
		return const_iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTreeRB<T, TCompare>::reverse_iterator BinTreeRB<T, TCompare>::rbegin() noexcept
	{
		return reverse_iterator(this, highest());
	}

	template <typename T, typename TCompare>
	inline typename BinTreeRB<T, TCompare>::const_reverse_iterator BinTreeRB<T, TCompare>::rbegin() const noexcept
	{
		return const_reverse_iterator(this, highest());
	}

	template <typename T, typename TCompare>
	inline typename BinTreeRB<T, TCompare>::const_reverse_iterator BinTreeRB<T, TCompare>::crbegin() const noexcept
	{
		return const_reverse_iterator(this, highest());
	}

	template <typename T, typename TCompare>
	inline typename BinTreeRB<T, TCompare>::reverse_iterator BinTreeRB<T, TCompare>::rend() noexcept
	{
		return reverse_iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTreeRB<T, TCompare>::const_reverse_iterator BinTreeRB<T, TCompare>::rend() const noexcept
	{
		return const_reverse_iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTreeRB<T, TCompare>::const_reverse_iterator BinTreeRB<T, TCompare>::crend() const noexcept
	{
		return const_reverse_iterator(this, nullptr);
	}

	template <typename T, typename TCompare>
	inline typename BinTreeRB<T, TCompare>::iterator BinTreeRB<T, TCompare>::find(const T& item) noexcept
	{
		return iterator(this, (T*)InternalFind(item));
	}

	template <typename T, typename TCompare>
	inline typename BinTreeRB<T, TCompare>::const_iterator BinTreeRB<T, TCompare>::find(const T& item) const noexcept
	{
		return const_iterator(this, InternalFind(item));
	}

	template <typename T, typename TCompare>
	inline const T* BinTreeRB<T, TCompare>::InternalFind(const T& item) const noexcept
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
	inline typename BinTreeRB<T, TCompare>::iterator BinTreeRB<T, TCompare>::lower_bound(const T& item) noexcept
	{
		return iterator(this, (T*)InternalLowerBound(item));
	}

	template <typename T, typename TCompare>
	inline typename BinTreeRB<T, TCompare>::const_iterator BinTreeRB<T, TCompare>::lower_bound(const T& item) const noexcept
	{
		return const_iterator(this, InternalLowerBound(item));
	}

	template <typename T, typename TCompare>
	inline const T* BinTreeRB<T, TCompare>::InternalLowerBound(const T& item) const noexcept
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
	inline typename BinTreeRB<T, TCompare>::iterator BinTreeRB<T, TCompare>::upper_bound(const T& item) noexcept
	{
		return iterator(this, (T*)InternalUpperBound(item));
	}

	template <typename T, typename TCompare>
	inline typename BinTreeRB<T, TCompare>::const_iterator BinTreeRB<T, TCompare>::upper_bound(const T& item) const noexcept
	{
		return const_iterator(this, InternalUpperBound(item));
	}

	template <typename T, typename TCompare>
	inline const T* BinTreeRB<T, TCompare>::InternalUpperBound(const T& item) const noexcept
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
	inline std::pair<typename BinTreeRB<T, TCompare>::iterator, bool> BinTreeRB<T, TCompare>::insert(T& item) noexcept
	{
		return insert(const_iterator(this, _root), item);
	}

	template <typename T, typename TCompare>
	inline std::pair<typename BinTreeRB<T, TCompare>::iterator, bool> BinTreeRB<T, TCompare>::insert(const const_iterator& position, T& item) noexcept
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
		// Set red color for new red-black balanced binary tree node
		node->rb = true;
		// Check red-black properties
		while ((node->parent != nullptr) && node->parent->rb)
		{
			// We have a violation...
			if (node->parent == node->parent->parent->left)
			{
				T* uncle = node->parent->parent->right;
				if ((uncle != nullptr) && uncle->rb)
				{
					// Uncle is red
					node->parent->rb = false;
					uncle->rb = false;
					node->parent->parent->rb = true;
					node = node->parent->parent;
				}
				else
				{
					// Uncle is back
					if (node == node->parent->right)
					{
						// Make node a left child
						node = node->parent;
						RotateLeft(node);
					}

					// Recolor and rotate
					node->parent->rb = false;
					node->parent->parent->rb = true;
					RotateRight(node->parent->parent);
				}
			}
			else
			{
				// Mirror image of above code...
				T* uncle = node->parent->parent->left;
				if ((uncle != nullptr) && uncle->rb)
				{
					// Uncle is red
					node->parent->rb = false;
					uncle->rb = false;
					node->parent->parent->rb = true;
					node = node->parent->parent;
				}
				else
				{
					// Uncle is black
					if (node == node->parent->left)
					{
						node = node->parent;
						RotateRight(node);
					}

					// Recolor and rotate
					node->parent->rb = false;
					node->parent->parent->rb = true;
					RotateLeft(node->parent->parent);
				}
			}
		}
		_root->rb = false;

		return std::make_pair(iterator(this, &item), true);
	}

	template <typename T, typename TCompare>
	inline T* BinTreeRB<T, TCompare>::erase(const T& item) noexcept
	{
		return erase(find(item)).operator->();
	}

	template <typename T, typename TCompare>
	inline typename BinTreeRB<T, TCompare>::iterator BinTreeRB<T, TCompare>::erase(const iterator& it) noexcept
	{
		T* result = ((iterator&)it).operator->();
		if (result == nullptr)
			return end();

		T* x;
		T* y;
		T* node = result;

		if ((node->left == nullptr) || (node->right == nullptr))
		{
			// y has a nullptr node as a child
			y = node;
		}
		else
		{
			// Find tree successor with a nullptr node as a child
			y = node->right;
			while (y->left != nullptr)
				y = y->left;
		}

		// Swap two nodes
		if (y != node)
		{
			if (node->parent == nullptr)
				_root = y;
			Swap(node, y);
		}

		// x is y's only child
		if (y->left != nullptr)
			x = y->left;
		else
			x = y->right;

		// Remove y from the parent chain
		if (x != nullptr)
			x->parent = y->parent;
		if (y->parent != nullptr)
		{
			if (y == y->parent->left)
				y->parent->left = x;
			else
				y->parent->right = x;
		}
		else
			_root = x;

		// Unlink given node
		if (!y->rb)
			Unlink(x, y->parent);

		result->parent = nullptr;
		result->left = nullptr;
		result->right = nullptr;
		--_size;
		return iterator(this, result);
	}

	template <typename T, typename TCompare>
	inline void BinTreeRB<T, TCompare>::RotateLeft(T* node)
	{
		T* current = node->right;

		// Establish node->right link
		node->right = current->left;
		if (current->left != nullptr)
			current->left->parent = node;

		// Establish current->parent link
		current->parent = node->parent;
		if (node->parent != nullptr)
		{
			if (node == node->parent->left)
				node->parent->left = current;
			else
				node->parent->right = current;
		}
		else
			_root = current;

		// Link node and current
		current->left = node;
		node->parent = current;
	}

	template <typename T, typename TCompare>
	inline void BinTreeRB<T, TCompare>::RotateRight(T* node)
	{
		T* current = node->left;

		// Establish node->right link
		node->left = current->right;
		if (current->right != nullptr)
			current->right->parent = node;

		// Establish current->parent link
		current->parent = node->parent;
		if (node->parent != nullptr)
		{
			if (node == node->parent->right)
				node->parent->right = current;
			else
				node->parent->left = current;
		}
		else
			_root = current;

		// Link node and current
		current->right = node;
		node->parent = current;
	}

	template <typename T, typename TCompare>
	inline void BinTreeRB<T, TCompare>::Unlink(T* node, T* parent)
	{
		T* w;

		while ((parent != nullptr) && ((node == nullptr) || !node->rb))
		{
			if (node == parent->left)
			{
				w = parent->right;
				if ((w != nullptr) && w->rb)
				{
					w->rb = false;
					parent->rb = true;
					RotateLeft(parent);
					w = parent->right;
				}
				if (w == nullptr)
					break;
				if (((w->left == nullptr) || !w->left->rb) && ((w->right == nullptr) || !w->right->rb))
				{
					w->rb = true;
					node = parent;
					parent = parent->parent;
				}
				else
				{
					if ((w->right == nullptr) || !w->right->rb)
					{
						w->left->rb = false;
						w->rb = true;
						RotateRight(w);
						w = parent->right;
					}

					// Copy red-black color information
					if (parent->rb)
						w->rb = true;
					else
						w->rb = false;
					parent->rb = false;
					w->right->rb = false;
					RotateLeft(parent);
					node = _root;
					parent = nullptr;
				}
			}
			else
			{
				w = parent->left;
				if ((w != nullptr) && w->rb)
				{
					w->rb = false;
					parent->rb = true;
					RotateRight(parent);
					w = parent->left;
				}
				if (w == nullptr)
					break;
				if (((w->left == nullptr) || !w->left->rb) && ((w->right == nullptr) || !w->right->rb))
				{
					w->rb = true;
					node = parent;
					parent = parent->parent;
				}
				else
				{
					if ((w->left == nullptr) || !w->left->rb)
					{
						w->right->rb = false;
						w->rb = true;
						RotateLeft(w);
						w = parent->left;
					}

					// Copy red-black color information
					if (parent->rb)
						w->rb = true;
					else
						w->rb = false;
					parent->rb = false;
					w->left->rb = false;
					RotateRight(parent);
					node = _root;
					parent = nullptr;
				}
			}
		}

		if (node != nullptr)
			node->rb = false;
	}

	template <typename T, typename TCompare>
	inline void BinTreeRB<T, TCompare>::Swap(T*& node1, T*& node2)
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
	inline void BinTreeRB<T, TCompare>::clear() noexcept
	{
		_size = 0;
		_root = nullptr;
	}

	template <typename T, typename TCompare>
	inline void BinTreeRB<T, TCompare>::swap(BinTreeRB& bintree) noexcept
	{
		using std::swap;
		swap(_compare, bintree._compare);
		swap(_size, bintree._size);
		swap(_root, bintree._root);
	}

	template <typename T, typename TCompare>
	inline void swap(BinTreeRB<T, TCompare>& bintree1, BinTreeRB<T, TCompare>& bintree2) noexcept
	{
		bintree1.swap(bintree2);
	}

}//namespace XT

#endif