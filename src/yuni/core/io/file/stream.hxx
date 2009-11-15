#ifndef __YUNI_CORE_IO_FILE_STREAM_HXX__
# define __YUNI_CORE_IO_FILE_STREAM_HXX__


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


	inline Stream::~Stream()
	{
		if (pFd)
			(void)::fclose(pFd);
	}


	template<class C>
	inline bool Stream::open(const C& filename, const OpenMode::Type mode)
	{
		// Close the file if already opened
		if (pFd)
			(void)::fclose(pFd);
		# ifdef YUNI_OS_WINDOWS
		pFd = OpenFileOnWindows(Core::Traits::CString<typename Static::Remove::Const<C>::Type>::Buffer(filename), mode);
		# else
		pFd = ::fopen(Core::Traits::CString<typename Static::Remove::Const<C>::Type>::Buffer(filename), OpenMode::ToCString(mode));
		# endif
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


	inline bool Stream::purge()
	{
        # ifdef YUNI_OS_WINDOWS
        return false;
        # else
		return (0 == ::fpurge(pFd));
        # endif
	}


	inline char Stream::get()
	{
		return (char)::fgetc(pFd);
	}


	inline size_t Stream::read(char* buffer, const size_t size)
	{
		return ::fread(buffer, size, 1, pFd);
	}


	inline bool Stream::put(const char c)
	{
		return !::fputc((int) c, pFd);
	}


	inline size_t Stream::write(const char* buffer, const size_t size)
	{
		return ::fwrite(buffer, size, 1, pFd);
	}


	template<class C>
	inline size_t Stream::write(const C& buffer)
	{
		return ::fwrite(Core::Traits::CString<typename Static::Remove::Const<C>::Type>::Buffer(buffer),
			Core::Traits::Length<typename Static::Remove::Const<C>::Type>::Value(buffer), 1, pFd);
	}


	template<class C>
	inline size_t Stream::write(const C& buffer, const size_t size)
	{
		return ::fwrite(Core::Traits::CString<typename Static::Remove::Const<C>::Type>::Buffer(buffer),
			size, 1, pFd);
	}


	inline bool Stream::operator ! () const
	{
		return (NULL == pFd);
	}


	template<class C>
	Stream& Stream::operator += (const C& rhs)
	{
		(void)::fwrite(Core::Traits::CString<typename Static::Remove::Const<C>::Type>::Buffer(rhs),
			Core::Traits::Length<typename Static::Remove::Const<C>::Type>::Value(rhs), 1, pFd);
		return *this;
	}


	template<class C>
	Stream& Stream::operator << (const C& rhs)
	{
		(void)::fwrite(Core::Traits::CString<typename Static::Remove::Const<C>::Type>::Buffer(rhs),
			Core::Traits::Length<typename Static::Remove::Const<C>::Type>::Value(rhs), 1, pFd);
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
