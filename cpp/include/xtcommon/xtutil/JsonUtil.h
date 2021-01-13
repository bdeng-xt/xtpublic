#pragma once
#ifndef XT_JSON_UTIL_H
#define XT_JSON_UTIL_H

/**
* \file JsonUtil.h
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

#include "nlohmann_json.hpp"

namespace XT {

class XT_COMMON_API JsonUtil {
public:
	JsonUtil() {} // = delete;
	JsonUtil(const JsonUtil&) {} // = delete;
	JsonUtil(JsonUtil&&) {} // = delete;
	~JsonUtil() {} // = delete;

	JsonUtil& operator=(const JsonUtil&) { return *this; } // = delete;
	JsonUtil& operator=(JsonUtil&&) { return *this; } // = delete;

public:

	static bool isValidJsonStr(const std::string& s);
	static std::string getValueForKeyInJsonStr(const std::string& s, const std::string& key);
	static std::vector<std::string> getKeysForJsonStr(const std::string& s);
	static std::string removeKeysForJsonStr(const std::string& s, std::vector<std::string>& keys);

	static std::string keepKeysForJsonStr(const std::string& s, std::vector<std::string>& keep_keys);
    
};

}//namespace

#endif