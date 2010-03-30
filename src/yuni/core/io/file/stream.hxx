#ifndef __YUNI_CORE_IO_FILE_STREAM_HXX__
# define __YUNI_CORE_IO_FILE_STREAM_HXX__

# include "../../string.h"


namespace Yuni
{
namespace Core
{
namespace IO
{
namespace File
{


	inline Stream::Stream()
		:pFd(NULL)
	{
		// Do nothing
	}


	template<class U>
	inline Stream::Stream(const U& filename, const int mode)
	{
		if (Traits::CString<typename Static::Remove::Const<U>::Type>::valid)
		{
			# ifdef YUNI_OS_WINDOWS
			pFd = OpenFileOnWindows(
				Traits::CString<typename Static::Remove::Const<U>::Type>::Buffer(filename),
				mode);
			# else
			pFd = ::fopen(
				Traits::CString<typename Static::Remove::Const<U>::Type>::Buffer(filename),
				OpenMode::ToCString(mode));
			# endif
		}
		else
			pFd = NULL;
	}


	inline Stream::~Stream()
	{
		if (pFd)
			(void)::fclose(pFd);
	}


	template<class U>
	inline bool Stream::open(const U& filename, const int mode)
	{
		// Close the file if already opened
		if (pFd)
			(void)::fclose(pFd);
		if (Traits::CString<typename Static::Remove::Const<U>::Type>::valid)
		{
			# ifdef YUNI_OS_WINDOWS
			pFd = OpenFileOnWindows(
				Traits::CString<typename Static::Remove::Const<U>::Type>::Buffer(filename),
				mode);
			# else
			pFd = ::fopen(
				Traits::CString<typename Static::Remove::Const<U>::Type>::Buffer(filename),
				OpenMode::ToCString(mode));
			# endif
		}
		else
			pFd = NULL;
		return (NULL != pFd);
	}


	inline bool Stream::opened() const
	{
		return (NULL != pFd);
	}


	inline bool Stream::eof() const
	{
		return ::feof(pFd);
	}

	inline ssize_t Stream::tell() const
	{
		return (ssize_t)::ftell(pFd);
	}



	inline bool Stream::seekFromBeginning(ssize_t offset)
	{
		return (0 == ::fseek(pFd, offset, SEEK_SET));
	}


	inline bool Stream::seekFromEndOfFile(ssize_t offset)
	{
		return (0 == ::fseek(pFd, offset, SEEK_END));
	}


	inline bool Stream::seekMove(ssize_t offset)
	{
		return (0 == ::fseek(pFd, offset, SEEK_CUR));
	}


	inline bool Stream::flush()
	{
		return (0 == ::fflush(pFd));
	}


	inline char Stream::get()
	{
		return (char)::fgetc(pFd);
	}

	inline bool Stream::gets(char* buffer, size_t maxSize)
	{
		return (NULL != fgets(buffer, maxSize, pFd));
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline bool
	Stream::gets(CustomString<ChunkSizeT, ExpandableT,ZeroTerminatedT>& buffer)
	{
		// The buffer must be reserved to its full capacity just before
		// Assuming we have a mere Yuni::String, the internal may be null.
		buffer.reserve(buffer.capacity());
		// Read data from the file
		const bool ret = (NULL != ::fgets((char*)buffer.data(), buffer.capacity(), pFd));
		// We may have read less than expected. So we have to resize the string
		// to perform maintenance (about the internal size and the final zero)
		buffer.resize(::strlen(buffer.c_str()) / sizeof(typename CustomString<ChunkSizeT, ExpandableT,ZeroTerminatedT>::Char));
		return ret;
	}


	inline size_t Stream::read(char* buffer, const size_t size)
	{
		return ::fread(buffer, 1, size, pFd);
	}


	inline bool Stream::put(const char c)
	{
		return (0 == ::fputc((int) c, pFd));
	}


	inline size_t Stream::write(const char* buffer, const size_t size)
	{
		return ::fwrite(buffer, 1, size, pFd);
	}


	template<class U>
	inline size_t Stream::write(const U& buffer)
	{
		if (Traits::CString<typename Static::Remove::Const<U>::Type>::valid)
		{
			return ::fwrite(
				Traits::CString<typename Static::Remove::Const<U>::Type>::Buffer(buffer),
				1,
				Traits::Length<typename Static::Remove::Const<U>::Type>::Value(buffer), pFd);
		}
		else
		{
			String translator;
			translator += buffer;
			return ::fwrite(translator.c_str(), 1, translator.size(), pFd);
		}
	}


	template<class U>
	inline size_t Stream::write(const U& buffer, const size_t size)
	{
		if (Traits::CString<typename Static::Remove::Const<U>::Type>::valid)
		{
			return ::fwrite(
				(const void*) Traits::CString<typename Static::Remove::Const<U>::Type>::Buffer(buffer),
				1, size, pFd);
		}
		else
		{
			String translator;
			translator += buffer;
			return ::fwrite((const void*) translator.c_str(), 1, ((size < translator.size()) ? size : translator.size()), pFd);
		}
	}


	inline bool Stream::operator ! () const
	{
		return (NULL == pFd);
	}


	inline Stream& Stream::operator += (const char c)
	{
		(void)::fputc((int) c, pFd);
		return *this;
	}


	inline Stream& Stream::operator << (const char c)
	{
		(void)::fputc((int) c, pFd);
		return *this;
	}


	template<class U>
	inline Stream& Stream::operator += (const U& u)
	{
		if (Traits::CString<typename Static::Remove::Const<U>::Type>::valid)
		{
			(void)::fwrite(
				Traits::CString<typename Static::Remove::Const<U>::Type>::Buffer(u),
				1,
				Traits::Length<typename Static::Remove::Const<U>::Type>::Value(u), pFd);
		}
		else
		{
			String translator;
			translator += u;
			(void)::fwrite(translator.c_str(), 1, translator.size(), pFd);
		}
		return *this;
	}


	template<class U>
	inline Stream& Stream::operator << (const U& u)
	{
		if (Traits::CString<typename Static::Remove::Const<U>::Type>::valid)
		{
			(void)::fwrite(
				Traits::CString<typename Static::Remove::Const<U>::Type>::Buffer(u),
				1,
				Traits::Length<typename Static::Remove::Const<U>::Type>::Value(u), pFd);
		}
		else
		{
			String translator;
			translator << u;
			(void)::fwrite(translator.c_str(), 1, translator.size(), pFd);
		}
		return *this;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline size_t
	Stream::read(CustomString<ChunkSizeT, ExpandableT,ZeroTerminatedT>& buffer)
	{
		// Assert to prevent SegV
		assert(buffer.capacity() != 0 && "When reading a file, the buffer must have reserved some space");

		typedef typename CustomString<ChunkSizeT, ExpandableT,ZeroTerminatedT>::Char C;
		// Reading the file
		const size_t result = ::fread(buffer.data(), 1, sizeof(C) * buffer.size(), pFd);
		// Setting the good size, because we may have read less than asked
		if (result < buffer.size())
			buffer.truncate(result);
		// Making sure that the buffer is zero-terminated if required
		if (buffer.zeroTerminated)
			*((C*)(buffer.data() + buffer.size())) = C();
		return result;
	}


	template<class C, int ChunkSizeT>
	inline size_t
	Stream::read(StringBase<C, ChunkSizeT>& buffer)
	{
		// Assert to prevent SegV
		assert(buffer.capacity() != 0 && "When reading a file, the buffer must have reserved some space");

		// Reading the file
		const size_t result = ::fread(buffer.data(), 1, sizeof(C) * buffer.size(), pFd);
		// Setting the good size, because we may have read less than asked
		if (result < buffer.size())
			buffer.truncate(result);
		// Making sure that the buffer is zero-terminated if required
		*((C*)(buffer.data() + buffer.size())) = C();
		return result;
	}



	template<class U>
	inline Stream& Stream::operator >> (U&  rhs)
	{
		(void)read(rhs);
		return *this;
	}






} // namespace File
} // namespace IO
} // namespace Core
} // namespace Yuni

#endif // __YUNI_CORE_IO_FILE_STREAM_HXX__
