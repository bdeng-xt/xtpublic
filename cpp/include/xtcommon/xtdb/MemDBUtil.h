#pragma once
#ifndef XT_MEMDB_UTIL_H
#define XT_MEMDB_UTIL_H


#include <cstdint>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <algorithm>

#include "XTConfig.h"

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#else
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif


namespace XT
{

class XT_COMMON_API MemDBUtil {
public:
	MemDBUtil() {} // = delete;
	MemDBUtil(const MemDBUtil&) {} // = delete;
	//	MemDBUtil(MemDBUtil&&) {} // = delete;
	~MemDBUtil() {} // = delete;

	MemDBUtil& operator=(const MemDBUtil&) { return *this; } // = delete;
   //	MemDBUtil& operator=(MemDBUtil&&) { return *this; } // = delete;
															   //////

protected:
	static const int s_KB; ///< killo bytes
	static const int s_MB; ///< mega bytes
public:
	static int getKB();

	static int getMB();
public:
	/**
	* Murmur Hash 2
	* @param key content to be hashed
	* @param len length of key
	* @param seed
	* @return hash result
	*/
	static uint32_t hash_32(const unsigned char *key, int32_t length, uint32_t seed = 42);

	static uint32_t hash_str_32(const std::string &key, uint32_t seed = 42);

	static void color_print(std::string level, std::string log);

	static bool in_color_terminal();

	/**
	* load mmap buffer, return address of the file-mapped memory
	* whether to write has to be specified in "is_writing"
	* buffer memory is locked if not lazy
	* @return the address of mapped memory
	*/
	static uintptr_t load_mmap_buffer(const std::string &path, size_t size, bool is_writing = false, bool lazy = true);

	static bool release_mmap_buffer(uintptr_t address, size_t size, bool lazy);

//	void handle_os_signals(void *hero);

};


}//namespace

#endif