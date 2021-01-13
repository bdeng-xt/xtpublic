#pragma once
#ifndef XT_LINE_FILES_H
#define XT_LINE_FILES_H

/**
* \file LineFiles.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a files class .
*
* \description
*	Designed for a files class.
*/

#include <cstdint>
#include <string>
#include <iostream> 
#include <fstream>

#include <memory>
#include <vector>

#include "XTConfig.h"
#include "Util.h"
#include "StringUtil.h"
#include "TimeUtil.h"

#include "XTStream.h"

namespace XT
{

class XT_COMMON_API LineFiles
{
public:
	/**
	* @name Constructor and Initialization
	*/
	///@{
	/**
	* @brief constructor
	*/
	LineFiles();

	/**
	* @brief default copy constructor
	*/
	LineFiles(const LineFiles& from) = default;

	/**
	* @brief default copy assignment
	*/
	LineFiles& operator=(const LineFiles& from) = default;

	/**
	* @brief destructor
	*/
	virtual ~LineFiles();
	///@}

public:
	void addFile(const std::string& filename);

	void init();

	bool hasNext();

	std::string& getLine();

	int64_t getLineTs();

	void setLineTs(int64_t ts);

	int getTsType();

	void setTsType(int tstype);

protected:
	std::vector<std::string> m_files;
	int m_fileIdx;
	std::shared_ptr<std::istream> m_fileStream;

	bool m_isInitialized;
	bool m_hasNext;
	std::string m_line;
	int64_t m_lineTs;
	std::string m_emptyLine;

	int m_tsType;




};//class
typedef std::shared_ptr<LineFiles> LineFilesPtr;

}//namespace


#endif