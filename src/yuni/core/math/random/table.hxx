#ifndef __YUNI_TOOLBOX_MATH_RANDOM_TABLE_HXX__
# define __YUNI_TOOLBOX_MATH_RANDOM_TABLE_HXX__



namespace Yuni
{
namespace Math
{
namespace Random
{


	template<class D, unsigned int TableSize, bool Cyclic, template<class> class TP>
	inline Table<D,TableSize,Cyclic,TP>::Table()
		:D(), pPos(0)
	{}


	template<class D, unsigned int TableSize, bool Cyclic, template<class> class TP>
	inline Table<D,TableSize,Cyclic,TP>::~Table()
	{}


	template<class D, unsigned int TableSize, bool Cyclic, template<class> class TP>
	inline void
	Table<D,TableSize,Cyclic,TP>::reset()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		static_cast<D*>(this)->reset();
		fillWL();
	}


	template<class D, unsigned int TableSize, bool Cyclic, template<class> class TP>
	inline void
	Table<D,TableSize,Cyclic,TP>::fill()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		fillWL();
	}

	template<class D, unsigned int TableSize, bool Cyclic, template<class> class TP>
	void
	Table<D,TableSize,Cyclic,TP>::fillWL()
	{
		// Regenerate all items in the cache
		for (unsigned int i = 0; i != TableSize; ++i)
			pCache[i] = static_cast<D*>(this)->next();
		// The index must be reset to `TableSize - 1`, in order to be
		// equals to the next call to `next()`
		// See `next()` for more informations.
		pPos = TableSize - 1;
	}


	template<class D, unsigned int TableSize, bool Cyclic, template<class> class TP>
	inline unsigned int
	Table<D,TableSize,Cyclic,TP>::size()
	{
		return TableSize;
	}




	template<class D, unsigned int TableSize, bool Cyclic, template<class> class TP>
	inline const typename Table<D,TableSize,Cyclic,TP>::Value
	Table<D,TableSize,Cyclic,TP>::next()
	{
		// Lock
		typename ThreadingPolicy::MutexLocker locker(*this);

		// In order to keep the best performances, we have to avoid post increments
		// and temporary variables.
		// A way to achieve this is to use a pre-increment and a simple test
		// for the index, then to directly return the result.
		// The bad side-effect of this method is that `pPos` must be initialized to
		// `TableSize - 1` if we want to use the first random number (at index 0).
		if (TableSize == ++pPos)
		{
			if (Cyclic) // constant-expression
				pPos = 0;
			else
				fillWL();
		}
		return pCache[pPos];
	}



	template<class D, unsigned int TableSize, bool Cyclic, template<class> class TP>
	template<class U>
	inline Table<D,TableSize,Cyclic,TP>&
	Table<D,TableSize,Cyclic,TP>::operator >> (U& u)
	{
		u = next();
		return *this;
	}


	template<class D, unsigned int TableSize, bool Cyclic, template<class> class TP>
	inline const typename Table<D,TableSize,Cyclic,TP>::Value
	Table<D,TableSize,Cyclic,TP>::operator () ()
	{
		return next();
	}




} // namespace Random
} // namespace Math
} // namespace Yuni

#endif // __YUNI_TOOLBOX_MATH_RANDOM_TABLE_HXX__
