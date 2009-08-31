#ifndef __YUNI_THREADS_PRIVATE_ABSTRACT_HXX__
# define __YUNI_THREADS_PRIVATE_ABSTRACT_HXX__


namespace Yuni
{
namespace Threads
{
namespace Private
{


	inline bool AThreadModel::isRunning() const
	{
		return pIsRunning;
	}


	inline String AThreadModel::name()
	{
		return String("<Unknown>");
	}

/*
	template<class T>
	T* AThreadModel::CreateAndStart(const bool f)
	{
		T* t = new T();
		if (f)
			t->freeOnTerminate(f);
		t->start();
		return t;
	}
*/



} // namespace Private
} // namespace Threads
} // namespace Yuni

#endif // __YUNI_THREADS_PRIVATE_ABSTRACT_HXX__
