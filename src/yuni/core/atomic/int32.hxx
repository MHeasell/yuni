#ifndef __YUNI_CORE_ATOMIC_INT32_HXX__
# define __YUNI_CORE_ATOMIC_INT32_HXX__



namespace Yuni
{
namespace Atomic
{


	inline Int32::Int32()
		:pValue(0)
	{}


	inline Int32::Int32(const int n)
		:pValue((sint32)n)
	{}


	inline Int32::Int32(const Int32& rhs)
		:pValue(rhs.pValue)
	{}


	inline void Int32::increment()
	{
		# if defined(YUNI_OS_WIN32)
		::InterlockedIncrement((LPLONG)&pValue);
		# elif defined(YUNI_OS_OSX)
		::OSAtomicIncrement32(&pValue);
		# else
		add(1);
		# endif
	}

	inline void Int32::decrement()
	{
		# if defined(YUNI_OS_WIN32)
		::InterlockedDecrement((LPLONG)&pValue);
		# elif defined(YUNI_OS_OSX)
		::OSAtomicDecrement32(&pValue);
		# else
		unsigned char nz;
		asm volatile ("lock; decl %1;\n\t"
			"setnz %%al"
			: "=a" (nz)
			: "m" (pValue)
			: "memory", "cc");
		# endif
	}


	inline int Int32::value() const
	{
		return pValue;
	}



	inline void Int32::add(const int x)
	{
		# if defined(YUNI_OS_WIN32)
		::InterlockedExchangeAdd((LPLONG)&pValue, x);
		# elif defined(YUNI_OS_OSX)
		::OSAtomicAdd32(x, &pValue);
		# else
		int old;
		asm volatile ("lock; xaddl %0,%1"
			: "=r"(old), "=m"(pValue) /* outputs */
			: "0"(x), "m"(pValue)   /* inputs */
			: "memory", "cc");
		# endif
	}

	inline void Int32::sub(const int x)
	{
		add(-(sint32)x);
	}


	inline Int32& Int32::operator ++ ()
	{
		increment();
		return *this;
	}

	inline Int32& Int32::operator -- ()
	{
		decrement();
		return *this;
	}

	inline Int32 Int32::operator ++ (const int)
	{
		Int32 copy(*this);
		increment();
		return copy;
	}


	inline Int32 Int32::operator -- (const int)
	{
		Int32 copy(*this);
		decrement();
		return copy;
	}


	inline Int32& Int32::operator += (const int x)
	{
		add((sint32)x);
		return *this;
	}


	inline Int32& Int32::operator -= (const int x)
	{
		add(-(sint32)x);
		return *this;
	}


	inline void Int32::set(const int x)
	{
		pValue = (sint32)x;
	}

	inline void Int32::set(const Int32& rhs)
	{
		pValue = rhs.pValue;
	}




	inline Int32& Int32::operator = (const int x)
	{
		pValue = (sint32)x;
		return *this;
	}


	inline Int32& Int32::operator = (const Int32& rhs)
	{
		pValue = rhs.pValue;
		return *this;
	}




} // namespace Atomic
} // namespace Yuni


#endif // __YUNI_CORE_ATOMIC_INT32_HXX__
