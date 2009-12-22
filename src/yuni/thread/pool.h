#ifndef __YUNI_THREAD_POOL_H__
# define __YUNI_THREAD_POOL_H__


namespace Yuni
{
namespace Thread
{


	template<class T>
	class Pool
	{
	public:
		Pool();
		~Pool();

		void clear(unsigned int timeout = AThread::defaultTimeout);

		void resize(unsigned int n, unsigned int timeout = AThread::defaultTimeout);


		T* operator [] (unsigned int index) {return pThreads[index];}

	private:
		std::vector<T*> pThreads;
	};


} // namespace Thread
} // namespace Yuni

#endif // __YUNI_THREAD_POOL_H__
