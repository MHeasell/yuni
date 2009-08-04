#ifndef __YUNI_CORE_ATOMIC_INT_HXX__
# define __YUNI_CORE_ATOMIC_INT_HXX__


namespace Yuni
{
namespace Atomic
{


	template<int Size, template<class> class TP>
	inline Int<Size,TP>::Int()
		:pValue()
	{}


	template<int Size, template<class> class TP>
	Int<Size,TP>::Int(const sint16 v)
		:pValue((ScalarType)v)
	{}

	template<int Size, template<class> class TP>
	inline Int<Size,TP>::Int(const sint32 v)
		:pValue((ScalarType)v)
	{}


	template<int Size, template<class> class TP>
	inline Int<Size,TP>::Int(const sint64 v)
		:pValue((ScalarType)v)
	{}




	template<int Size, template<class> class TP>
	inline Int<Size,TP>::Int(const Int<Size,TP>& v)
	{
		pValue = v;
	}

	template<int Size, template<class> class TP>
	template<int Size2, template<class> class TP2>
	inline Int<Size,TP>::Int(const Int<Size2,TP2>& v)
	{
		pValue = (ScalarType)v.pValue;
	}


	template<int Size, template<class> class TP>
	inline Int<Size,TP>::operator ScalarType () const
	{
		return pValue;
	}


	template<int Size, template<class> class TP>
	inline typename Int<Size,TP>::ScalarType Int<Size,TP>::operator ++ ()
	{
		return (threadSafe)
			? Private::AtomicImpl::Operator<Size,TP>::Increment(*this)
			: (++pValue);
	}


	template<int Size, template<class> class TP>
	inline typename Int<Size,TP>::ScalarType Int<Size,TP>::operator -- ()
	{
		return (threadSafe)
			? Private::AtomicImpl::Operator<Size,TP>::Decrement(*this)
			: (--pValue);
	}


	template<int Size, template<class> class TP>
	inline typename Int<Size,TP>::ScalarType Int<Size,TP>::operator ++ (int)
	{
		return (threadSafe)
			? Private::AtomicImpl::Operator<Size,TP>::Increment(*this) - 1
			: (pValue++);
	}


	template<int Size, template<class> class TP>
	inline typename Int<Size,TP>::ScalarType Int<Size,TP>::operator -- (int)
	{
		return (threadSafe)
			? Private::AtomicImpl::Operator<Size,TP>::Decrement(*this) + 1
			: (pValue--);
	}


	template<int Size, template<class> class TP>
	inline bool Int<Size,TP>::operator ! () const
	{
		return !pValue;
	}


	template<int Size, template<class> class TP>
	inline typename Int<Size,TP>::ScalarType Int<Size,TP>::operator = (const ScalarType v)
	{
		pValue = v;
		return *this;
	}




} // namespace Atomic
} // namespace Yuni

#endif // __YUNI_CORE_ATOMIC_INT_HXX__
