#ifndef __YUNI_CORE_FS_PATHS_HXX__
# define __YUNI_CORE_FS_PATHS_HXX__


namespace Yuni
{
namespace Core
{
namespace Paths
{


	template<int N>
	inline bool MakeDir(const StringBase<char,N>& p, unsigned int mode)
	{
		return MakeDir(p.c_str(), mode);
	}


	template<int N, int M>
	inline bool RecursiveCopy(const StringBase<char,N>& src, const StringBase<char,M>& dst)
	{
		return RecursiveCopy(src.c_str(), dst.c_str());
	}


	template<int N>
	inline bool RmDir(const StringBase<char,N>& p)
	{
		return RmDir(p.c_str());
	}


} // namespace Paths
} // namespace Core
} // namespace Yuni

#endif // __YUNI_CORE_FS_PATHS_H__
