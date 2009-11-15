#ifndef __YUNI_CORE_FS_FILES_HXX__
# define __YUNI_CORE_FS_FILES_HXX__

# include "../../traits/cstring.h"
# include "../../traits/length.h"
# include "../../static/remove.h"


namespace Yuni
{
namespace Core
{
namespace IO
{
namespace File
{


	template<class C>
	inline bool Exists(const C& p)
	{
		# ifdef YUNI_OS_WINDOWS
		return Private::IO::FilesystemImpl::IsFileWindowsImpl(
			Core::Traits::CString<typename Static::Remove::Const<C>::Type>::Buffer(p), Core::Traits::Length<C>::Value(p));
		# else
		return Private::IO::FilesystemImpl::IsFileUnixImpl(
			Core::Traits::CString<typename Static::Remove::Const<C>::Type>::Buffer(p));
		# endif
	}


	template<int N>
	inline bool Load(String::Vector& out, const StringBase<char,N>& filename, const bool emptyListBefore,
		const uint32 sizeLimit)
	{
		return Load(out, filename.c_str(), emptyListBefore, sizeLimit);
	}

	template<int N>
	inline bool Load(String::List& out, const StringBase<char,N>& filename, const bool emptyListBefore,
		const uint32 sizeLimit)
	{
		return Load(out, filename.c_str(), emptyListBefore, sizeLimit);
	}


	template<class C>
	bool CreateEmptyFile(const C& filename)
	{
		Core::IO::File::Stream file(filename, OpenMode::write | OpenMode::truncate);
		return file.opened();
	}


	template<class C1, class C2>
	bool SetContent(const C1& filename, const C2& content)
	{
		Core::IO::File::Stream file(filename, OpenMode::write | OpenMode::truncate);
		if (file.opened())
		{
			file += content;
			return true;
		}
		return false;
	}


	template<class C1, class C2>
	bool AppendContent(const C1& filename, const C2& content)
	{
		Core::IO::File::Stream file(filename, OpenMode::write | OpenMode::append);
		if (file.opened())
		{
			file += content;
			return true;
		}
		return false;
	}





} // namespace File
} // namespace IO
} // namespace Core
} // namespace Yuni

#endif // __YUNI_CORE_FS_FILES_H__
