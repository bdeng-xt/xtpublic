#pragma once
#ifndef XT_DIRECTORY_H
#define XT_DIRECTORY_H

/**
* \file Directory.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a directory class .
*
* \description
*	Designed for a directory class.
*/

#include <cstdint>
#include <string>
#include <iostream> 
#include <memory>

#include "XTPath.h"
#include "XTFile.h"
#include "XTSymlink.h"

#include "XTConfig.h"

namespace XT
{

	//! Filesystem directory iterator
	/*!
		Filesystem directory iterator is used to iterate through directory
		content (directories, files, symlinks).

		No sort order is guarantied!

		Not thread-safe.
	*/
	class XT_COMMON_API DirectoryIterator
	{
		friend class Directory;

	public:
		// Standard constant iterator type definitions
		typedef std::ptrdiff_t difference_type;
		typedef Path value_type;
		typedef const Path& reference;
		typedef const Path* pointer;
		typedef std::forward_iterator_tag iterator_category;

		DirectoryIterator();
		DirectoryIterator(DirectoryIterator& it);
		DirectoryIterator(DirectoryIterator&& it) noexcept;
		~DirectoryIterator();

		DirectoryIterator& operator=(DirectoryIterator& it);
		DirectoryIterator& operator=(DirectoryIterator&& it) noexcept;

		friend bool operator==(const DirectoryIterator& it1, const DirectoryIterator& it2) noexcept;
		friend bool operator!=(const DirectoryIterator& it1, const DirectoryIterator& it2) noexcept;

		DirectoryIterator& operator++();
		DirectoryIterator operator++(int);

		const Path& operator*() const noexcept;
		const Path* operator->() const noexcept;

		//! Swap two instances
		void swap(DirectoryIterator& it) noexcept;
		friend void swap(DirectoryIterator& it1, DirectoryIterator& it2) noexcept;

	private:
		class Impl;
		class SimpleImpl;
		class RecurseImpl;
		std::unique_ptr<Impl> _pimpl;
		Path _current;

		DirectoryIterator(const Path& current);
		DirectoryIterator(const Path& parent, bool recurse);
	};//class DirectoryIterator

////
	inline bool operator==(const DirectoryIterator& it1, const DirectoryIterator& it2) noexcept
	{
		return it1._current == it2._current;
	}

	inline bool operator!=(const DirectoryIterator& it1, const DirectoryIterator& it2) noexcept
	{
		return it1._current != it2._current;
	}

	inline const Path& DirectoryIterator::operator*() const noexcept
	{
		return _current;
	}

	inline const Path* DirectoryIterator::operator->() const noexcept
	{
		return &_current;
	}

	inline void DirectoryIterator::swap(DirectoryIterator& it) noexcept
	{
		using std::swap;
		_pimpl.swap(it._pimpl);
	}

	inline void swap(DirectoryIterator& it1, DirectoryIterator& it2) noexcept
	{
		it1.swap(it2);
	}

////////
//! Filesystem directory
/*!
	Filesystem directory wraps directory management operations (create,
	remove, iterate).

	Not thread-safe.
*/
	class XT_COMMON_API Directory : public Path
	{
	public:
		//! Default directory attributes (Normal)
		static const Flags<FileAttributes> DEFAULT_ATTRIBUTES;
		//! Default directory permissions (IRUSR | IWUSR | IXUSR | IRGRP | IXGRP | IROTH | IXOTH)
		static const Flags<FilePermissions> DEFAULT_PERMISSIONS;

		//! Initialize directory with an empty path
		Directory() : Path() {}
		//! Initialize directory with a given path
		/*!
			\param path - Directory path
		*/
		Directory(const Path& path) : Path(path) {}
		Directory(const Directory&) = default;
		Directory(Directory&&) = default;
		~Directory() = default;

		Directory& operator=(const Path& path)
		{
			Assign(path); return *this;
		}
		Directory& operator=(const Directory&) = default;
		Directory& operator=(Directory&&) = default;

		//! Check if the directory exist
		explicit operator bool() const noexcept { return IsDirectoryExists(); }

		//! Is the directory exists?
		bool IsDirectoryExists() const;
		//! Is the directory empty?
		bool IsDirectoryEmpty() const;

		//! Get the directory begin iterator
		DirectoryIterator begin() const;
		//! Get the directory end iterator
		DirectoryIterator end() const;

		//! Get the directory recursive begin iterator
		DirectoryIterator rbegin() const;
		//! Get the directory recursive end iterator
		DirectoryIterator rend() const;

		//! Get all entries (directories, files, symbolic links) in the current directory
		/*!
			\param pattern - Regular expression pattern (default is "")
			\return Entries collection
		*/
		std::vector<Path> GetEntries(const std::string& pattern = "");
		//! Recursively get all entries (directories, files, symbolic links) in the current directory
		/*!
			\param pattern - Regular expression pattern (default is "")
			\return Entries collection
		*/
		std::vector<Path> GetEntriesRecurse(const std::string& pattern = "");

		//! Get all directories (including symbolic link directories) in the current directory
		/*!
			\param pattern - Regular expression pattern (default is "")
			\return Directories collection
		*/
		std::vector<Directory> GetDirectories(const std::string& pattern = "");
		//! Recursively get all directories (including symbolic link directories) in the current directory
		/*!
			\param pattern - Regular expression pattern (default is "")
			\return Directories collection
		*/
		std::vector<Directory> GetDirectoriesRecurse(const std::string& pattern = "");

		//! Get all files (including symbolic link files) in the current directory
		/*!
			\param pattern - Regular expression pattern (default is "")
			\return Files collection
		*/
		std::vector<File> GetFiles(const std::string& pattern = "");
		//! Recursively get all files (including symbolic link files) in the current directory
		/*!
			\param pattern - Regular expression pattern (default is "")
			\return Files collection
		*/
		std::vector<File> GetFilesRecurse(const std::string& pattern = "");

		//! Get all symbolic links (including symbolic link directories) in the current directory
		/*!
			\param pattern - Regular expression pattern (default is "")
			\return Symbolic links collection
		*/
		std::vector<Symlink> GetSymlinks(const std::string& pattern = "");
		//! Recursively get all symbolic links (including symbolic link directories) in the current directory
		/*!
			\param pattern - Regular expression pattern (default is "")
			\return Symbolic links collection
		*/
		std::vector<Symlink> GetSymlinksRecurse(const std::string& pattern = "");

		//! Create directory from the given path
		/*!
			\param path - Directory path
			\param attributes - Directory attributes (default is Directory::DEFAULT_ATTRIBUTES)
			\param permissions - Directory permissions (default is Directory::DEFAULT_PERMISSIONS)
			\return Created directory
		*/
		static Directory Create(const Path& path, const Flags<FileAttributes>& attributes = Directory::DEFAULT_ATTRIBUTES, const Flags<FilePermissions>& permissions = Directory::DEFAULT_PERMISSIONS);
		//! Create full directory tree of the given path
		/*!
			\param path - Directory path
			\param attributes - Directory attributes (default is Directory::DEFAULT_ATTRIBUTES)
			\param permissions - Directory permissions (default is Directory::DEFAULT_PERMISSIONS)
			\return Created full directory tree
		*/
		static Directory CreateTree(const Path& path, const Flags<FileAttributes>& attributes = Directory::DEFAULT_ATTRIBUTES, const Flags<FilePermissions>& permissions = Directory::DEFAULT_PERMISSIONS);

		//! Swap two instances
		void swap(Directory& directory) noexcept;
		friend void swap(Directory& directory1, Directory& directory2) noexcept;
	};

	inline void Directory::swap(Directory& directory) noexcept
	{
		using std::swap;
		Path::swap(directory);
	}

	inline void swap(Directory& directory1, Directory& directory2) noexcept
	{
		directory1.swap(directory2);
	}

}//namespace


#endif
