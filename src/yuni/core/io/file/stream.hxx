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
		if (Core::Traits::CString<typename Static::Remove::Const<U>::Type>::valid)
		{
			# ifdef YUNI_OS_WINDOWS
			pFd = OpenFileOnWindows(
				Core::Traits::CString<typename Static::Remove::Const<U>::Type>::Buffer(filename),
				mode);
			# else
			pFd = ::fopen(
				Core::Traits::CString<typename Static::Remove::Const<U>::Type>::Buffer(filename),
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
		if (Core::Traits::CString<typename Static::Remove::Const<U>::Type>::valid)
		{
			# ifdef YUNI_OS_WINDOWS
			pFd = OpenFileOnWindows(
				Core::Traits::CString<typename Static::Remove::Const<U>::Type>::Buffer(filename),
				mode);
			# else
			pFd = ::fopen(
				Core::Traits::CString<typename Static::Remove::Const<U>::Type>::Buffer(filename),
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
		if (Core::Traits::CString<typename Static::Remove::Const<U>::Type>::valid)
		{
			return ::fwrite(
				Core::Traits::CString<typename Static::Remove::Const<U>::Type>::Buffer(buffer),
				1,
				Core::Traits::Length<typename Static::Remove::Const<U>::Type>::Value(buffer), pFd);
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
		if (Core::Traits::CString<typename Static::Remove::Const<U>::Type>::valid)
		{
			return ::fwrite(
				Core::Traits::CString<typename Static::Remove::Const<U>::Type>::Buffer(buffer),
				1, size, pFd);
		}
		else
		{
			String translator;
			translator += buffer;
			return ::fwrite(translator.c_str(), 1, size < translator.size() ? size : translator.size(), pFd);
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
		if (Core::Traits::CString<typename Static::Remove::Const<U>::Type>::valid)
		{
			(void)::fwrite(
				Core::Traits::CString<typename Static::Remove::Const<U>::Type>::Buffer(u),
				1,
				Core::Traits::Length<typename Static::Remove::Const<U>::Type>::Value(u), pFd);
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
		if (Core::Traits::CString<typename Static::Remove::Const<U>::Type>::valid)
		{
			(void)::fwrite(
				Core::Traits::CString<typename Static::Remove::Const<U>::Type>::Buffer(u),
				1,
				Core::Traits::Length<typename Static::Remove::Const<U>::Type>::Value(u), pFd);
		}
		else
		{
			String translator;
			translator << u;
			(void)::fwrite(translator.c_str(), 1, translator.size(), pFd);
		}
		return *this;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline size_t
	Stream::read(MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>& buffer)
	{
		typedef MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>  MemoryBufferType;
		typedef typename MemoryBufferType::Type PODType;

		if (MemoryBufferType::zeroTerminated)
		{
			const size_t result = read(buffer.data(), sizeof(C) * buffer.size());
			((const PODType*) buffer.data())[result] = PODType();
			return result;
		}
		else
			return read(buffer.data(), sizeof(PODType) * buffer.size());
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline Stream&
	Stream::operator >> (MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>&  rhs)
	{
		typedef MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>  MemoryBufferType;
		typedef typename MemoryBufferType::Type PODType;

		(void) this->read(rhs.data(), sizeof(PODType) * rhs.size());
		return *this;
	}






} // namespace File
} // namespace IO
} // namespace Core
} // namespace Yuni

#endif // __YUNI_CORE_IO_FILE_STREAM_HXX__
