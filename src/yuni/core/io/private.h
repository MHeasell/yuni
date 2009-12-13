#ifndef __YUNI_CORE_IO_PRIVATE_H__
# define __YUNI_CORE_IO_PRIVATE_H__


namespace Yuni
{
namespace Private
{
namespace IO
{
namespace FilesystemImpl
{

	bool ExistsUnixImpl(const char* p);
	bool ExistsWindowsImpl(const char* p, const size_t sizeHint);


	# ifdef YUNI_OS_WINDOWS

	bool IsFileWindowsImpl(const char* p, const size_t sizeHint);
	bool IsDirectoryWindowsImpl(const char* p, const size_t sizeHint);

	# else

	bool IsFileUnixImpl(const char* p);
	bool IsDirectoryUnixImpl(const char* p);

	# endif


	bool CopyFile(const char* from, const char* to);


	bool Size(const char* filename, uint64& value);
	uint64 Size(const char* filename);


} // namespace FilesystemImpl
} // namespace IO
} // namespace Private
} // namespace Yuni

#endif // __YUNI_CORE_IO_PRIVATE_H__
