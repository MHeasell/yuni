#ifndef __YUNI_CORE_IO_FILE_STREAM_H__
# define __YUNI_CORE_IO_FILE_STREAM_H__

# include "../../../yuni.h"
# include <stdio.h>
# include "../../static/assert.h"
# include "../../traits/cstring.h"
# include "../../traits/length.h"
# include "../../static/remove.h"
# include "openmode.h"



namespace Yuni
{
namespace Core
{
namespace IO
{
namespace File
{

	/*!
	** \brief Seek origin
	*/
	enum SeekOrigin
	{
		//! From the begining of the stream
		seekOriginBegin,
		//! From the current position in the stream
		seekOriginCurrent,
		//! From the end of the stream
		seekOriginEnd,
	};




	/*!
	** \brief A low-level implementation for reading and writing files
	**
	** \internal This implementation is most of the time a C++ wrapper over the standard
	**   routines 'fopen', 'fclose'... The implementation is a bit different on Windows
	**   because 'fopen' only handles ansi filenames.
	*/
	class Stream
	{
	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		Stream();
		/*!
		** \brief Copy constructor (not allowed, it will fail at compile time)
		*/
		Stream(const Stream& rhs);
		/*!
		** \brief Open a file
		*/
		template<class C> Stream(const C& filename, const OpenMode::Type mode = OpenMode::read);
		/*!
		** \brief Destructor
		**
		** The file will be closed if opened
		*/
		~Stream();
		//@}


		//! \name Open / Close a file
		//@{
		/*!
		** \brief Open a file
		**
		** \param filename Any string reprensenting an UTF8 relative or absolute filename
		** \param mode The open mode to use
		** \return True if the operation succeeded, false otherwise
		*/
		template<class C> bool open(const C& filename, const OpenMode::Type mode = OpenMode::read);

		/*!
		** \brief Close the file if opened
		*/
		bool close();
		//@}


		//! \name Stream
		//@{
		/*!
		** \brief Get if a file is currently opened
		*/
		bool opened() const;

		/*!
		** \brief Get if the end-of-file has been reached
		*/
		bool eof() const;

		/*!
		** \brief Set the position in the stream
		**
		** \param offset A relative offset
		** \param origin Origin of the offset
		** \return True if the operation succeeded, false otherwise
		*/
		bool seek(ssize_t offset, SeekOrigin origin = seekOriginCurrent);

		/*!
		** \brief Set the position indicator associated with the currently opened file from the beginning of the file
		**
		** \param offset A relative offset
		** \return True if the operation succeeded, False otherwise
		*/
		bool seekFromBeginning(ssize_t offset);

		/*!
		** \brief Set the position indicator associated with the currently opened file from the end of the file
		**
		** \param offset A relative offset
		** \return True if the operation succeeded, False otherwise
		*/
		bool seekFromEndOfFile(ssize_t offset);

		/*!
		** \brief Move the position indicator from the current position in the stream
		**
		** \param offset A relative offset
		** \return True if the operation succeeded, False otherwise
		*/
		bool seekMove(ssize_t offset);

		/*!
		** \brief Flush the last I/O operations
		**
		** \return True if the operation succeeded, False otherwise
		*/
		bool flush();

		/*!
		** \brief Purge (erases any input or output buffered in the stream)
		*/
		bool purge();
		//@}


		//! \name Read
		//@{
		/*!
		** \brief Read a single char
		*/
		char get();

		/*!
		** \brief Read a buffer
		**
		** \param buffer A raw buffer where to store the data which will be read from the file
		** \param size Size (in bytes) of the data to read (and size of the buffer)
		** \return The number of bytes that have been read
		*/
		size_t read(char* buffer, const size_t size);

		/*!
		** \brief Read data into a MemoryBuffer
		**
		** 'buffer.size() * sizeof(C)' bytes will be read from the stream and store
		** into the given buffer.
		** Use the method 'buffer.resize()' to change the buffer size.
		**
		** \param buffer An arbitrary buffer
		** \return The number of bytes that have been read
		*/
		template<class C, unsigned int CSizeT, bool ZeroT, bool ExpT>
		size_t read(MemoryBuffer<C,CSizeT,ZeroT,ExpT>&  buffer);
		//@}


		//! \name Write
		//@{
		/*!
		** \brief Write a chr to the stream
		*/
		bool put(const char c);

		/*!
		** \brief Write a raw buffer
		**
		** \param buffer An arbitrary buffer
		** \param size Size of the buffer to write
		** \return The number of bytes that have been written
		*/
		size_t write(const char* buffer, const size_t size);

		/*!
		** \brief Write any arbitrary buffer
		**
		** \param buffer An arbitrary buffer (const char*, String, MemoryBuffer)
		** \return The number of bytes that have been written
		*/
		template<class C> size_t write(const C& buffer);

		/*!
		** \brief Write any arbitrary buffer
		**
		** \param buffer An arbitrary buffer (const char*, String, MemoryBuffer)
		** \param size Size of the buffer to write
		** \return The number of bytes that have been written
		*/
		template<class C> size_t write(const C& buffer, const size_t size);
		//@}


		//! \name Operators
		//@{
		//! True if the stream if not opened
		bool operator ! () const;
		//! operator += (write)
		template<class C> Stream& operator += (const C& rhs);
		//! operator << (write)
		template<class C> Stream& operator << (const C& rhs);

		//! Operator >> (read)
		template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
		Stream& operator >> (MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>& rhs);
		//@}

	private:
		# ifdef YUNI_OS_WINDOWS
		//! UTF8 Implementation as replacement of the routine 'fopen' on Windows
		static FILE* OpenFileOnWindows(const char* filename, const OpenMode::Type mode);
		# endif

	private:
		//! A FILE pointer
		FILE* pFd;

	}; // class Stream




} // namespace File
} // namespace IO
} // namespace Core
} // namespace Yuni

# include "stream.hxx"

#endif // __YUNI_CORE_IO_FILE_STREAM_H__
