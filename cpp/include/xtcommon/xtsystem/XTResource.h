#pragma once
#ifndef XT_RESOURCE_H
#define XT_RESOURCE_H

/**
* \file XTResource.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide template functions for resource.
*
* \description
*	Designed for resource functions.
*/

#include <memory>
#include <functional>
#include "XTConfig.h"

#if defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
#include <dirent.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#if defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

namespace XT
{

#if defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)

	void XT_close_dir(DIR* d);
 
	void XT_close_file(FILE* f);
 
#elif defined(_WIN32) || defined(_WIN64)
 
	void XT_COMMON_API XT_close_dir(HANDLE d);

	void XT_COMMON_API XT_close_file(FILE* f);

#endif

//! Resource smart cleaner pattern
/*!
    Resource smart cleaner pattern allows to create unique smart pointer with
    a given resource and cleaner delegate which is used to automatic resource
    clean when it goes out of scope.

    Thread-safe.

    Example:
    \code{.cpp}
    int test()
    {
        // Create a file resource
        auto file = XT::resource(fopen("test", "rb"), [](FILE* file) { fclose(file); });

        // Work with the file resource
        int result = fgetc(file.get());

        // File resource will be cleaned automatically when we go out of scope
        return result;
    }
    \endcode

    \param handle - Resource handle
    \param cleaner - Cleaner function
*/
template <typename T, typename TCleaner>
//auto resource(T handle, TCleaner cleaner)
std::unique_ptr<typename std::remove_pointer<T>::type, TCleaner> resource(T handle, TCleaner cleaner)
{
    return std::unique_ptr<typename std::remove_pointer<T>::type, TCleaner>(handle, cleaner);
}

//! Resource smart cleaner pattern (void* specialization)
/*!
    \param handle - Resource handle
    \param cleaner - Cleaner function
*/
template <typename TCleaner>
//auto resource(void* handle, TCleaner cleaner)
std::unique_ptr<void, TCleaner> resource(void* handle, TCleaner cleaner)
{
    return std::unique_ptr<void, TCleaner>(handle, cleaner);
}

//! Resource smart cleaner pattern for empty resource handle
/*!
    \param cleaner - Cleaner function
*/
template <typename TCleaner>
//auto resource(TCleaner cleaner)
std::unique_ptr<void, TCleaner> resource(TCleaner cleaner)
{
    return std::unique_ptr<void, TCleaner>(&cleaner, cleaner);
}    

template <typename T>
using deleted_unique_ptr = std::unique_ptr<T, std::function<void(T*)> >;

}//namespace


#endif
