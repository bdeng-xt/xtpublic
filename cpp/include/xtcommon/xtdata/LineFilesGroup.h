#pragma once
#ifndef XT_LINE_FILES_GROUP_H
#define XT_LINE_FILES_GROUP_H

/**
* \file LineFilesGroup.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a files group class .
*
* \description
*	Designed for a files group class.
*/

#include <cstdint>
#include <string>
#include <iostream> 
#include <fstream>

#include <memory>
#include <vector>
#include <map>
#include <unordered_map>

#include "XTConfig.h"
#include "XTStream.h"
#include "LineFiles.h"

namespace XT
{

class XT_COMMON_API LineFilesGroup
{

public:
	/**
	* @name Constructor and Initialization
	*/
	///@{
	/**
	* @brief constructor
	*/
	LineFilesGroup();

	/**
	* @brief default copy constructor
	*/
	LineFilesGroup(const LineFilesGroup& from) = default;

	/**
	* @brief default copy assignment
	*/
	LineFilesGroup& operator=(const LineFilesGroup& from) = default;

	/**
	* @brief destructor
	*/
	virtual ~LineFilesGroup();
	///@}

public:
	
	void addLineFiles(const std::string& name, const LineFilesPtr& linefiles);

	void init();

	bool hasNext();

	std::string& getLine();

	int64_t getLineTs();

	const std::string& getName();
protected:
	std::unordered_map<std::string, LineFilesPtr > m_lineFilesMap;
	std::unordered_map<std::string, int64_t> m_lineTsMap;
	std::unordered_map<std::string, std::string> m_lineMap;

	bool m_isInitialized;
	bool m_hasNext;

	std::string m_emptyString;
	int64_t m_lineTs;
	int m_lineCount;

	std::string m_nextName;
	int64_t m_nextLineTs;

	std::string m_line;
	std::string m_name;

protected:
	const std::string& getNextName();




};//class
typedef std::shared_ptr<LineFilesGroup> LineFilesGroupPtr;

}//namespace


#endif