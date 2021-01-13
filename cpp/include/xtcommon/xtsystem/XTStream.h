#pragma once
#ifndef XT_STREAM_H
#define XT_STREAM_H

/**
* \file Stream.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide stream classes .
*
* \description
*	Designed for stream classes .
*/

#include <cstdint>
#include <string>
#include <iostream>
#include <fstream>
#include "zlib.h"

#include <memory>

#include "XTConfig.h"
 
#include "XTExceptions.h"
#include "XTReader.h"
#include "XTWriter.h"





namespace XT
{

	//! Write character stream manipulator
	class XT_COMMON_API WriteChar
	{
	public:
		explicit WriteChar(char ch) : _ch(ch) {}

		friend std::ostream& operator<<(std::ostream& stream, const WriteChar& writer)
		{
			return stream << '\'' << writer._ch << '\'';
		}
		friend std::wostream& operator<<(std::wostream& stream, const WriteChar& writer)
		{
			return stream << '\'' << writer._ch << '\'';
		}

	private:
		char _ch;
	};

	//! Write wide character stream manipulator
	class XT_COMMON_API WriteWChar
	{
	public:
		explicit WriteWChar(wchar_t ch) : _ch(ch) {}

		friend std::ostream& operator<<(std::ostream& stream, const WriteWChar& writer)
		{
			return stream << '\'' << writer._ch << '\'';
		}
		friend std::wostream& operator<<(std::wostream& stream, const WriteWChar& writer)
		{
			return stream << '\'' << writer._ch << '\'';
		}

	private:
		wchar_t _ch;
	};

	//! Write string stream manipulator
	class XT_COMMON_API WriteString
	{
	public:
		template <size_t N>
		explicit WriteString(const char(&str)[N]) : _str(str), _size(N) {}

		friend std::ostream& operator<<(std::ostream& stream, const WriteString& writer)
		{
			stream << '"';
			stream.write(writer._str, writer._size);
			stream << '"';
			return stream;
		}
		friend std::wostream& operator<<(std::wostream& stream, const WriteString& writer)
		{
			stream << '"';
			for (size_t i = 0; i < writer._size; ++i)
				stream << writer._str[i];
			stream << '"';
			return stream;
		}

	private:
		const char* _str;
		size_t _size;
	};

	//! Write wide string stream manipulator
	class XT_COMMON_API WriteWString
	{
	public:
		template <size_t N>
		explicit WriteWString(const wchar_t(&str)[N]) : _str(str), _size(N) {}

		friend std::ostream& operator<<(std::ostream& stream, const WriteWString& writer)
		{
			stream << '"';
			for (size_t i = 0; i < writer._size; ++i)
				stream << writer._str[i];
			stream << '"';
			return stream;
		}
		friend std::wostream& operator<<(std::wostream& stream, const WriteWString& writer)
		{
			stream << '"';
			stream.write(writer._str, writer._size);
			stream << '"';
			return stream;
		}

	private:
		const wchar_t* _str;
		size_t _size;
	};

//////
//! Standard input stream
/*!
	Thread-safe.
*/
	class XT_COMMON_API StdInput : public Reader
	{
	public:
		StdInput();
		StdInput(const StdInput&) = delete;
		StdInput(StdInput&& stream) = delete;
		virtual ~StdInput();

		StdInput& operator=(const StdInput&) = delete;
		StdInput& operator=(StdInput&& stream) = delete;

		//! Check if the stream is valid
		explicit operator bool() const noexcept { return IsValid(); }

		//! Get the native stream handler
		void* stream() const noexcept;

		//! Is stream valid?
		bool IsValid() const noexcept;

		//! Read a bytes buffer from the stream
		/*!
			\param buffer - Buffer to read
			\param size - Buffer size
			\return Count of read bytes
		*/
		size_t Read(void* buffer, size_t size) override;

		using Reader::ReadAllBytes;
		using Reader::ReadAllText;
		using Reader::ReadAllLines;

		//! Swap two instances
		void swap(StdInput& stream) noexcept;
		friend void swap(StdInput& stream1, StdInput& stream2) noexcept;

	private:
		class Impl;
		std::unique_ptr<Impl> _pimpl;
	};

	//! Standard output stream
	/*!
		Thread-safe.
	*/
	class XT_COMMON_API StdOutput : public Writer
	{
	public:
		StdOutput();
		StdOutput(const StdOutput&) = delete;
		StdOutput(StdOutput&& stream) = delete;
		virtual ~StdOutput();

		StdOutput& operator=(const StdOutput&) = delete;
		StdOutput& operator=(StdOutput&& stream) = delete;

		//! Check if the stream is valid
		explicit operator bool() const noexcept { return IsValid(); }

		//! Get the native stream handler
		void* stream() const noexcept;

		//! Is stream valid?
		bool IsValid() const noexcept;

		//! Write a byte buffer into the stream
		/*!
			\param buffer - Buffer to write
			\param size - Buffer size
			\return Count of written bytes
		*/
		size_t Write(const void* buffer, size_t size) override;

		using Writer::Write;

		//! Flush the stream
		void Flush() override;

		//! Swap two instances
		void swap(StdOutput& stream) noexcept;
		friend void swap(StdOutput& stream1, StdOutput& stream2) noexcept;

	private:
		class Impl;
		std::unique_ptr<Impl> _pimpl;
	};

	//! Standard error stream
	/*!
		Thread-safe.
	*/
	class XT_COMMON_API StdError : public Writer
	{
	public:
		StdError();
		StdError(const StdError&) = delete;
		StdError(StdError&& stream) = delete;
		virtual ~StdError();

		StdError& operator=(const StdError&) = delete;
		StdError& operator=(StdError&& stream) = delete;

		//! Check if the stream is valid
		explicit operator bool() const { return IsValid(); }

		//! Get the native stream handler
		void* stream() const noexcept;

		//! Is stream valid?
		bool IsValid() const noexcept;

		//! Write a byte buffer into the stream
		/*!
			\param buffer - Buffer to write
			\param size - Buffer size
			\return Count of written bytes
		*/
		size_t Write(const void* buffer, size_t size) override;

		using Writer::Write;

		//! Flush the stream
		void Flush() override;

		//! Swap two instances
		void swap(StdError& stream) noexcept;
		friend void swap(StdError& stream1, StdError& stream2) noexcept;

	private:
		class Impl;
		std::unique_ptr<Impl> _pimpl;
	};
//////
	inline void swap(StdInput& stream1, StdInput& stream2) noexcept
	{
		stream1.swap(stream2);
	}

	inline void swap(StdOutput& stream1, StdOutput& stream2) noexcept
	{
		stream1.swap(stream2);
	}

	inline void swap(StdError& stream1, StdError& stream2) noexcept
	{
		stream1.swap(stream2);
	}
//////
	class XT_COMMON_API gzstreambuf : public std::streambuf {
	private:
		static const int bufferSize = 47 + 256;    // size of data buff
		// totals 512 bytes under g++ for igzstream at the end.

		gzFile           file;               // file handle for compressed file
		char             buffer[bufferSize]; // data buffer
		char             opened;             // open/close state of stream
		int              mode;               // I/O mode

		int flush_buffer();
	public:
		gzstreambuf() : opened(0) {
			setp(buffer, buffer + (bufferSize - 1));
			setg(buffer + 4,     // beginning of putback area
				buffer + 4,     // read position
				buffer + 4);    // end position      
		  // ASSERT: both input & output capabilities will not be used together
		}
		int is_open() { return opened; }
		gzstreambuf* open(const char* name, int open_mode);
		gzstreambuf* close();
		~gzstreambuf() { close(); }

		virtual int     overflow(int c = EOF);
		virtual int     underflow();
		virtual int     sync();
	};

	class XT_COMMON_API gzstreambase : virtual public std::ios {
	protected:
		gzstreambuf buf;
	public:
		gzstreambase() { init(&buf); }
		gzstreambase(const char* name, int open_mode);
		~gzstreambase();
		void open(const char* name, int open_mode);
		void close();
		gzstreambuf* rdbuf() { return &buf; }
	};

	// ----------------------------------------------------------------------------
	// User classes. Use igzstream and ogzstream analogously to ifstream and
	// ofstream respectively. They read and write files based on the gz* 
	// function interface of the zlib. Files are compatible with gzip compression.
	// ----------------------------------------------------------------------------

	class XT_COMMON_API igzstream : public gzstreambase, public std::istream {
	public:
		igzstream() : std::istream(&buf) {}
		igzstream(const char* name, int open_mode = std::ios::in)
			: gzstreambase(name, open_mode), std::istream(&buf) {}
		gzstreambuf* rdbuf() { return gzstreambase::rdbuf(); }
		void open(const char* name, int open_mode = std::ios::in) {
			gzstreambase::open(name, open_mode);
		}
	};

	class XT_COMMON_API ogzstream : public gzstreambase, public std::ostream {
	public:
		ogzstream() : std::ostream(&buf) {}
		ogzstream(const char* name, int mode = std::ios::out)
			: gzstreambase(name, mode), std::ostream(&buf) {}
		gzstreambuf* rdbuf() { return gzstreambase::rdbuf(); }
		void open(const char* name, int open_mode = std::ios::out) {
			gzstreambase::open(name, open_mode);
		}
	};


}//namespace XT


#endif