#pragma once
#ifndef XT_FILE_UTIL_H
#define XT_FILE_UTIL_H

/**
* \file FileUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide file directory utility functions.
*
* \description
*	This component provides utility functions for file and directory.
*/

#include <cstdint>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#define BOOST_SYSTEM_NO_LIB
#define BOOST_FILESYSTEM_NO_LIB
#include <boost/filesystem.hpp>

#include "XTConfig.h"
#include "StringMap.h"

namespace XT
{
class XT_COMMON_API FileUtil {
public:
	FileUtil() {} // = delete;
	FileUtil(const FileUtil&) {} // = delete;
//	FileUtil(TimeUtil&&) {} // = delete;
	~FileUtil() {} // = delete;

	FileUtil& operator=(const FileUtil&) { return *this; } // = delete;
//	FileUtil& operator=(FileUtil&&) { return *this; } // = delete;
	//////
public:

	/**
	* @name File
	*/
	///@{
	/**
	* @brief test if a file exists
	*
	* @param file name of file
	*
	* @return if file exists or not
	*/
	static bool existsFile(const std::string& filename);


	/**
	* @brief back up a file
	*
	* @param file name of file
	*
	* @return status
	*/
	static int bkupFile(const std::string& filename);

	/**
	* @brief back up a file
	*
	* @param file name of file
	* @param bkup file name
	*
	* @return status
	*/
	static int bkupFileTo(const std::string& filename, const std::string& bkupfile);


	/**
	* @brief find files by prefix name
	*
	* @param tgtPath as path
	* @param nameprefix as prefix
	*
	* @return vector of file names
	*/
	static std::vector<std::string> getFilesWithNameStartsWith(const std::string& tgtPath, const std::string& nameprefix);

	/**
	* @brief find files with substring in the name
	*
	* @param tgtPath as path
	* @param subname
	*
	* @return vector of file names
	*/
	static std::vector<std::string> getFilesWithNameContains(const std::string& tgtPath, const std::string& subname);

	/**
	* @brief parse logfile
	*
	* @param logfile
	* 
	* @return smp
	*/
	static StringMapPtr parseLogFile(const std::string& logfile);

	/**
	* @brief parse csvfile
	*
	* @param csvfile
	*
	* @return smp
	*/
	static StringMapPtr parseCsvFile(const std::string& csvfile);

	/**
	* @brief add dtstr to csv line
	*
	* @param csvfile
	* @param outfile
	*
	* @return number of lines
	*/
	static int addDTStrForCsvFile(const std::string& csvfile, const std::string& outfile, const std::string& separator=",", int tscolumn = 0,bool isnanots=false, int uniquecol=-1);


	/**
	* @brief create dir for intdate
	*
	* @param intdate
	*/
	static void createDirForIntDate(const std::string& datadir, int intdate);


	/**
	* @brief get dir for intdate
	*
	* @param intdate
	*/
	static std::string getDirForIntDate(const std::string& datadir, int intdate);

	/**
	* @brief get subdirs by pattern
	*
	* @directory
	* @pattern
	* @isrecursive
	*/
	static std::vector<std::string> getSubDirsByPattern(const std::string& directory, const std::string& pattern, bool isrecursive);
	///@}



};

}//namespace



#endif