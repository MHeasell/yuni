
namespace Yuni
{

	template<
		typename T,
		template <class> class ThreadingPolicy
		>
	void* SmallObject<T, ThreadingPolicy>::operator new (std::size_t size)
	{
		ThreadingModel::MutexLocker lock;
		return Core::SmallObjAllocator::Instance().allocate(size);
	}

	template<
		typename T,
		template <class> class ThreadingPolicy
		>
	void SmallObject<T, ThreadingPolicy>::operator delete (void* ptr, std::size_t size)
	{
		ThreadingModel::MutexLocker lock;
		Core::SmallObjAllocator::Instance().deallocate(ptr, size);
	}

	template<
		typename T,
		template <class> class ThreadingPolicy
		>
	void* SmallObject<T, ThreadingPolicy>::operator new[] (std::size_t size)
	{
		ThreadingModel::MutexLocker lock;
		return Core::SmallObjAllocator::Instance().allocate(size);
	}

	template<
		typename T,
		template <class> class ThreadingPolicy
		>
	void SmallObject<T, ThreadingPolicy>::operator delete[] (void* ptr, std::size_t size)
	{
		ThreadingModel::MutexLocker lock;
		Core::SmallObjAllocator::Instance().deallocate(ptr, size);
	}

} // Yuni
