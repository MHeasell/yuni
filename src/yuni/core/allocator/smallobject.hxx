#ifndef __YUNI_CORE_ALLOCATOR_SMALLOBJECT_HXX__
# define __YUNI_CORE_ALLOCATOR_SMALLOBJECT_HXX__


namespace Yuni
{

	template<typename T, template <class> class TP>
	inline void*
	SmallObject<T, TP>::operator new (std::size_t size)
	{
		typename ThreadingPolicy::MutexLocker locker;
		return Core::SmallObjAllocator::Instance().allocate(size);
	}


	template<typename T, template <class> class TP>
	inline void
	SmallObject<T, TP>::operator delete (void* ptr, std::size_t size)
	{
		typename ThreadingPolicy::MutexLocker locker;
		Core::SmallObjAllocator::Instance().deallocate(ptr, size);
	}


	template<typename T, template <class> class TP>
	inline void*
	SmallObject<T, TP>::operator new[] (std::size_t size)
	{
		typename ThreadingPolicy::MutexLocker locker;
		return Core::SmallObjAllocator::Instance().allocate(size);
	}


	template<typename T, template <class> class TP>
	inline void
	SmallObject<T, TP>::operator delete[] (void* ptr, std::size_t size)
	{
		typename ThreadingPolicy::MutexLocker locker;
		Core::SmallObjAllocator::Instance().deallocate(ptr, size);
	}



} // namespace Yuni

#endif // __YUNI_CORE_ALLOCATOR_SMALLOBJECT_HXX__
