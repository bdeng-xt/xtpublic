#pragma once
#ifndef XT_FIX_UTIL_H
#define XT_FIX_UTIL_H

/**
* \file FIXUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide fix utility functions.
*
* \description
*	This component provides fix functions for strings.
*/

#include <cstdint>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <algorithm>
#include <locale>
#include <cctype>
#include <vector>
#include <set>
#include "XTConfig.h"

namespace XT {

class XT_COMMON_API FIXUtil {
public:
	FIXUtil() {} // = delete;
	FIXUtil(const FIXUtil&) {} // = delete;
	FIXUtil(FIXUtil&&) {} // = delete;
	~FIXUtil() {} // = delete;

	FIXUtil& operator=(const FIXUtil&) { return *this; } // = delete;
	FIXUtil& operator=(FIXUtil&&) { return *this; } // = delete;

public:
	static bool hasFieldTag(int tag);
	static std::string getFieldNameForTag(int tag);

	static bool hasFieldName(const std::string& name);
	static int getTagForFieldName(const std::string& name);

	static std::vector<std::string> getFieldNamesStartsWith(const std::string& prefix);
	static std::vector<std::string> getFieldNamesEndsWith(const std::string& suffix);
	static std::vector<std::string> getFieldNamesContains(const std::string& substr);

	static bool hasMsgType(const std::string& msgtype);
	static std::string getNameForMsgType(const std::string& msgtype);

	static bool hasMsgName(const std::string& name);
	static std::string getMsgTypeForName(const std::string& name);

	static std::vector<std::string> getMsgNamesStartsWith(const std::string& prefix);
	static std::vector<std::string> getMsgNamesEndsWith(const std::string& suffix);
	static std::vector<std::string> getMsgNamesContains(const std::string& substr);

protected:
	static std::map<int, std::string> m_fieldTagToNameMap;
	static std::map<std::string, int> m_filedNameToTagMap;

	static std::map<std::string, std::string> m_msgTypeToNameMap;
	static std::map<std::string, std::string> m_msgNameToTypeMap;

	static std::map<int, std::string> getFieldTagToNameMap();
	static std::map<std::string, int> getFieldNameToTagMap();

	static std::map<std::string, std::string> getMsgTypeToNameMap();
	static std::map<std::string, std::string> getMsgNameToTypeMap();
    
};

}//namespace

#endif