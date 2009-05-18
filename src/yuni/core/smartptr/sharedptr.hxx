#ifndef __YUNI_MISC_SHARED_POINTER_HXX__
# define __YUNI_MISC_SHARED_POINTER_HXX__


namespace Yuni
{

	template<class T>
	SharedPtr<T>& SharedPtr<T>::reset()
	{
		release();
		return *this;
	}


	template<class T>
	SharedPtr<T>& SharedPtr<T>::reset(const SharedPtr<T>& rhs)
	{
		if (this != &rhs)
		{
			release();
			acquire(rhs.counter);
		}
		return *this;
	}

	template<class T>
	void SharedPtr<T>::release()
	{
		// decrement the count, delete if it is equals to 0
		if (counter)
		{
			if (--counter->count == 0)
			{
				delete counter->ptr;
				delete counter;
			}
			counter = 0;
		}
	}




} // namespace Yuni

#endif // __YUNI_MISC_SHARED_POINTER_HXX__
