#pragma once
#ifndef XT_PB_UTIL_H
#define XT_PB_UTIL_H

/**
* \file PBUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a manager class for all protobuf utilities.
*
* \description
*	Designed for managing all protobuf utilities.
*/

#include <cstdint>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>

#ifdef WIN32
#include <io.h>
#endif

#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

#include <google/protobuf/stubs/common.h>

#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
#include <google/protobuf/text_format.h>

#include <google/protobuf/util/json_util.h>

//#include <protobuf_3.7.1/src/google/protobuf/message_lite.h>
//#include <protobuf_3.7.1/src/google/>

#include "StringMap.h"
#include "StringUtil.h"
#include "LogUtil.h"

#include "XTConfig.h"

namespace XT
{

class XT_COMMON_API PBInputFile
{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	PBInputFile();

	/**
	* @brief constructor
	*
	* @param filename
	*/
	PBInputFile(const std::string& filename);

	/**
	* @brief copy constructor
	*/
	PBInputFile(const PBInputFile& from);

	/**
	* @brief copy assignment
	*/
	PBInputFile& operator=(const PBInputFile& from);

	/**
	* @brief destructor
	*/
	virtual ~PBInputFile();

	///@}

	/**
	* @brief get filename
	*
	* @return filename
	*/
	const std::string& getFilename();

	/**
	* @brief get fd
	*
	* @return fd
	*/
	int getFd();

	/**
	* @brief get input stream
	*
	* @return input stream
	*/
	google::protobuf::io::ZeroCopyInputStream* getInputStream();

protected:
	std::string m_filename;///< filename
	int m_fd; ///< fd
	google::protobuf::io::ZeroCopyInputStream * m_inputStream; ///< input stream

};//class XT_COMMON_API PBInputFile
typedef ::boost::shared_ptr<PBInputFile> PBInputFilePtr;


class XT_COMMON_API PBOutputFile
{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	PBOutputFile();

	/**
	* @brief constructor
	*
	* @param filename
	*/
	PBOutputFile(const std::string& filename);

	/**
	* @brief copy constructor
	*/
	PBOutputFile(const PBOutputFile& from);

	/**
	* @brief copy assignment
	*/
	PBOutputFile& operator=(const PBOutputFile& from);

	/**
	* @brief destructor
	*/
	virtual ~PBOutputFile();

	///@}

	/**
	* @brief flush
	*/
	void flush();
	
	/**
	* @brief get filename
	*
	* @return filename
	*/
	const std::string& getFilename();

	/**
	* @brief get fd
	*
	* @return fd
	*/
	int getFd();

	/**
	* @brief get output stream
	*
	* @return output stream
	*/
	google::protobuf::io::ZeroCopyOutputStream* getOutputStream();

protected:
	std::string m_filename; ///< filename
	int m_fd; ///< fd
	google::protobuf::io::ZeroCopyOutputStream * m_outputStream; ///< output stream

};//class XT_COMMON_API PBOutputFile
typedef ::boost::shared_ptr<PBOutputFile> PBOutputFilePtr;


//////////////////////////////////////////
class XT_COMMON_API PBUtil
{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	PBUtil() {}

	/**
	* @brief copy constructor
	*/
	PBUtil(const PBUtil& from) {} // = delete;

	/**
	* @brief copy assignment
	*/
	PBUtil& operator=(const PBUtil& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~PBUtil() {}

	///@}
public:
	/**
	* @brief get string of message
	*
	* @param m as message
	*/
	static std::string getStr(const google::protobuf::Message& m);
	
	/**
	* @brief get protobuf string of message
	*
	* @param m as message
	*
	* @return protobuf string
	*/
	static std::string getPBStr(const google::protobuf::Message& m);
	/**
	* @brief parse protobuf string for message
	*
	* @param s as protobuf string
	* @param m as message
	*
	* @return if it is parsed successfully
	*/
	static bool parseFromPBStr(const std::string& s, google::protobuf::Message& m);

	/**
	* @brief get json string of message
	*
	* @param m as message
	*
	* @return json string
	*/
	static std::string getJsonStr(const google::protobuf::Message& m);
	/**
	* @brief parse json string for message
	*
	* @param s as json string
	* @param m as message
	*
	* @return if it is parsed successfully
	*/
	static bool parseFromJsonStr(const std::string& s, google::protobuf::Message& m);

	/**
	* @brief get csv string of message
	*
	* @param m as message
	*
	* @return csv string
	*/
	static std::string getCsvStr(const google::protobuf::Message& m, const std::string& sep="|");

	/**
	* @brief parse csv string for message
	*
	* @param s as csv string
	* @param m as message
	*
	* @return if it is parsed successfully
	*/
	static bool parseFromCsvStr(const std::string& s, google::protobuf::Message& m, const std::string& sep="|", int skipcols=0);

	/**
	* @brief get csv string of message
	*
	* @param m as message
	*
	* @return plain csv string
	*/
	static std::string getPlainCsvStr(const google::protobuf::Message& m, const std::string& sep = "|");

	/**
	* @brief parse csv string for message
	*
	* @param s as csv string
	* @param m as message
	*
	* @return if it is parsed successfully
	*/
	static bool parseFromPlainCsvStr(const std::string& s, google::protobuf::Message& m, const std::string& sep = "|", int skipcols = 0);

	/**
	* @brief parse from StringMapPtr
	*
	* @param smp
	* @param message
	*
	*/
	static bool parseFromStringMapPtr(const StringMapPtr& smp, google::protobuf::Message& m);

	/**
	* @brief update from StringMapPtr
	*
	* @param smp
	* @param message
	*
	*/
	static void updateFromStringMapPtr(const StringMapPtr& smp, google::protobuf::Message& m);

	/**
	* @brief get stringmapptr
	*
	* @param message
	*
	* @return smp
	*/
	static StringMapPtr getStringMapPtr(const google::protobuf::Message& m);

//////////////////////////////
protected:
	/**
	* @brief write delimited message to output stream
	*
	* @param message
	* @param rawOutput
	*
	*/
	static bool writeDelimitedTo(
		const google::protobuf::MessageLite& message,
		google::protobuf::io::ZeroCopyOutputStream* rawOutput);

	/**
	* @brief read delimited message from input stream
	*
	* @param rawInput
	* @param message
	*
	*/
	static bool readDelimitedFrom(
		google::protobuf::io::ZeroCopyInputStream* rawInput,
		google::protobuf::MessageLite* message);


///////////////////////////
public:
	/**
	* @brief write message to file
	*
	* @param message
	* @param filename
	*/
	static bool writeToFile(const google::protobuf::MessageLite& message, const std::string& filename);

	/**
	* @brief read message from file
	*
	* @param filename
	* @param message
	*/
	static bool readFromFile(const std::string& filename, google::protobuf::MessageLite& message);

	/**
	* @brief write message to file
	*
	* @param message
	* @param pboutputfile
	*/
	static bool writeDelimitedToPBOutputFile(const google::protobuf::MessageLite& message, boost::shared_ptr<PBOutputFile>& pboutputfile);

	/**
	* @brief read message from file
	*
	* @param message
	* @param pbinputfile
	*/
	static bool readDelimitedFromPBInputFile(google::protobuf::MessageLite& message, boost::shared_ptr<PBInputFile>& pbinputfile);

};//class

}//namespace

#endif
