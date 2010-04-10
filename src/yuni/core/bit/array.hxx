#ifndef __YUNI_CORE_BIT_BIT_ARRAY_HXX__
# define __YUNI_CORE_BIT_BIT_ARRAY_HXX__


namespace Yuni
{
namespace Core
{
namespace Bit
{

	inline Array::Array()
		:pCount(0)
	{}

	inline Array::Array(unsigned int n)
	{
		resize(n);
		unset();
	}

	inline Array::Array(unsigned int n, bool value)
	{
		resize(n);
		reset(value);
	}


	inline void Array::unset()
	{
		(void)::memset(pBuffer.data(), 0, pBuffer.sizeInBytes());
	}



	inline void Array::reset()
	{
		(void)::memset(pBuffer.data(), 0, pBuffer.sizeInBytes());
	}


	inline void Array::reset(bool value)
	{
		(void)::memset(pBuffer.data(), (value ? 0xFF : 0), pBuffer.sizeInBytes());
	}


	inline void Array::set(unsigned int i)
	{
		YUNI_BIT_SET(pBuffer.data(), i);
	}


	inline bool Array::get(unsigned int i) const
	{
		return YUNI_BIT_GET(pBuffer.data(), i);
	}


	inline bool Array::test(unsigned int i) const
	{
		return YUNI_BIT_GET(pBuffer.data(), i);
	}


	inline void Array::set(unsigned int i, bool value)
	{
		if (value)
			YUNI_BIT_SET(pBuffer.data(), i);
		else
			YUNI_BIT_UNSET(pBuffer.data(), i);
	}


	inline void Array::unset(unsigned int i)
	{
		YUNI_BIT_UNSET(pBuffer.data(), i);
	}


	inline void Array::reserve(unsigned int n)
	{
		pBuffer.reserve((n >> 3) + 1);
	}


	inline void Array::truncate(unsigned int n)
	{
		pBuffer.truncate(((pCount = n) >> 3) + 1);
	}


	inline void Array::resize(unsigned int n)
	{
		pBuffer.resize(((pCount = n) >> 3) + 1);
	}


	inline unsigned int Array::sizeInBytes() const
	{
		return pBuffer.sizeInBytes();
	}

	inline unsigned int Array::size() const
	{
		return pCount;
	}

	inline unsigned int Array::count() const
	{
		return pCount;
	}

	inline const char* Array::c_str() const
	{
		return pBuffer.c_str();
	}

	inline const char* Array::data() const
	{
		return pBuffer.data();
	}

	inline char* Array::data()
	{
		return pBuffer.data();
	}


	template<class AnyStringT>
	inline void Array::loadFromBuffer(const AnyStringT& u)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<AnyStringT>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, BitArray_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::Length<UType>::valid,  BitArray_InvalidTypeForBufferSize);

		if (Traits::Length<UType,Size>::isFixed)
		{
			// We can make some optimisations when the length is known at compile compile time
			// This part of the code should not bring better performances but it should
			// prevent against bad uses of the API, like using a C* for looking for a single char.

			// The value to find is actually empty, nothing to do
			if (0 == Traits::Length<UType,Size>::fixedLength)
			{
				pBuffer.clear();
				pCount = 0;
				return;
			}
		}
		pBuffer.assign(Traits::CString<UType>::Buffer(u), (pCount = Traits::Length<UType,Size>::Value(u)));
	}


	template<class AnyStringT>
	inline void Array::loadFromBuffer(const AnyStringT& u, unsigned int size)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<AnyStringT>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, BitArray_InvalidTypeForBuffer);

		pBuffer.assign(Traits::CString<UType>::Buffer(u), (pCount = size));
	}


	template<class AnyBufferT>
	inline void Array::saveToBuffer(AnyBufferT& u)
	{
		if (pCount)
			u.assign(pBuffer.c_str(), pBuffer.sizeInBytes());
		else
			u.clear();
	}


	inline Array& Array::operator = (const Array& rhs)
	{
		pBuffer = rhs.pBuffer;
		pCount = rhs.pCount;
		return *this;
	}


	template<class AnyStringT> inline Array& Array::operator = (const AnyStringT& rhs)
	{
		loadFromBuffer(rhs);
		return *this;
	}


	inline Array& Array::operator = (const NullPtr&)
	{
		pBuffer.clear();
		pCount = 0;
		return *this;
	}


	inline Array& Array::operator = (const NullPtr*)
	{
		pBuffer.clear();
		pCount = 0;
		return *this;
	}


	template<class U>
	inline void Array::print(U& out) const
	{
		for (unsigned int i = 0; i != pCount; ++i)
			out.put((YUNI_BIT_GET(pBuffer.data(), i)) ? '1' : '0');
	}


	template<bool ValueT>
	unsigned int Array::find(unsigned int offset) const
	{
		for (unsigned int i = (offset >> 3); i < pBuffer.size(); ++i)
		{
			if ((unsigned char)(pBuffer[i]) != (ValueT ? 0 : 0xFF))
			{
				unsigned char c = pBuffer[i];
				unsigned int result = 0;
				while ((bool) (YUNI_BIT_GET(&c, result)) != ValueT)
					++result;
				return result + (i << 3);
			}
		}
		return npos;
	}




} // namespace Bit
} // namespace Core
} // namespace Yuni

#endif // __YUNI_CORE_BIT_BIT_ARRAY_HXX__
