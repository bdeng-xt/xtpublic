#pragma once
#ifndef XT_PIPE_H
#define XT_PIPE_H

/**
* \file Pipe.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide read write pipe .
*
* \description
*	Designed for read-write pipe .
*/

#include <cstdint>
#include <string>

#include <memory>

#include "XTConfig.h"
#include "XTReader.h"
#include "XTWriter.h"
#include "XTExceptions.h"


namespace XT
{

	//! Pipe
	/*!
		A pipe is a section of shared memory that processes use for communication.  The
		process that creates a pipe is the pipe server. A process that  connects  to  a
		pipe is a pipe client. One process writes information to  the  pipe,  then  the
		other process reads the information from the pipe. This overview describes  how
		to create, manage, and use pipes.

		Not thread-safe.
	*/
	class XT_COMMON_API Pipe : public Reader, public Writer
	{
	public:
		Pipe();
		Pipe(const Pipe&) = delete;
		Pipe(Pipe&& pipe) = delete;
		virtual ~Pipe();

		Pipe& operator=(const Pipe&) = delete;
		Pipe& operator=(Pipe&& pipe) = delete;

		//! Get the native read endpoint handler
		void* reader() const noexcept;
		//! Get the native write endpoint handler
		void* writer() const noexcept;

		//! Is pipe opened for reading or writing?
		bool IsPipeOpened() const noexcept;
		//! Is pipe opened for reading?
		bool IsPipeReadOpened() const noexcept;
		//! Is pipe opened for writing?
		bool IsPipeWriteOpened() const noexcept;

		//! Read a bytes buffer from the pipe
		/*!
			If the pipe is not opened for reading the method will raise
			a system exception!

			\param buffer - Buffer to read
			\param size - Buffer size
			\return Count of read bytes
		*/
		size_t Read(void* buffer, size_t size) override;

		using Reader::ReadAllBytes;
		using Reader::ReadAllText;
		using Reader::ReadAllLines;

		//! Write a byte buffer into the pipe
		/*!
			If the pipe is not opened for writing the method will raise
			a system exception!

			\param buffer - Buffer to write
			\param size - Buffer size
			\return Count of written bytes
		*/
		size_t Write(const void* buffer, size_t size) override;

		using Writer::Write;

		//! Close the read pipe endpoint
		void CloseRead();
		//! Close the write pipe endpoint
		void CloseWrite();

		//! Close all pipe endpoints
		void Close();

		//! Swap two instances
		void swap(Pipe& pipe) noexcept;
		friend void swap(Pipe& pipe1, Pipe& pipe2) noexcept;

	private:
		class Impl;
		std::unique_ptr<Impl> _pimpl;
	};
////
	inline void swap(Pipe& pipe1, Pipe& pipe2) noexcept
	{
		pipe1.swap(pipe2);
	}



}//namespace


#endif