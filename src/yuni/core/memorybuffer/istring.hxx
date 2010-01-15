#ifndef __YUNI_CORE_MEMORY_BUFFER_ISTRING_HXX__
# define __YUNI_CORE_MEMORY_BUFFER_ISTRING_HXX__


namespace Yuni
{
namespace Core
{


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::IString()
	{}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::IString(const NullPtr&)
	{}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::IString(const NullPtr*)
	{}




	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::IString(const IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>& rhs)
		:AncestorType(rhs)
	{}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	inline IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::IString(const U& rhs)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::valid, IString_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::Length<UType>::valid,  IString_InvalidTypeForBufferSize);

		Private::IStringImpl::Assign<IStringType, UType>::Do(*this, rhs);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::IString(const C* block, const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size blockSize)
	{
		AncestorType::assign(block, blockSize);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	inline void IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::assign(const U& u)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;

		Private::IStringImpl::Assign<IString, UType>::Do(*this, u);
		return *this;
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	inline void IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::append(const U& u)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;

		Private::IStringImpl::Append<IString, UType>::Do(*this, u);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	inline void IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::append(const U& u,
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size size)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;

		AncestorType::append(Core::Traits::CString<UType>::Buffer(u), size);
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	inline void IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::write(const U& u,
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size size)
	{
		append(u, size);
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	inline void IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::push_back(const U& u)
	{
		append(u);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	inline void IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::push_front(const U& u)
	{
		insert(0, u);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	inline void IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::prepend(const U& u)
	{
		insert(0, u);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	inline void IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::prepend(const U& u,
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size size)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;

		insert(0, Core::Traits::CString<UType>::Buffer(u), size);
	}





	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline void
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::assign(const C* buffer,
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size size)
	{
		AncestorType::assign(buffer, size);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline void
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::append(const C* buffer,
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size size)
	{
		AncestorType::append(buffer, size);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>&
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::clear()
	{
		AncestorType::clear();
		return *this;
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline void
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::reserve(
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size minCapacity)
	{
		AncestorType::reserve(minCapacity);
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline void
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::put(const C c)
	{
		AncestorType::put(c);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	void IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::fill(const U& pattern)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::Length<UType>::valid,  IString_InvalidTypeForBufferSize);

		if (AncestorType::size)
			Private::IStringImpl::Fill<IString, UType>::Do(AncestorType::data, AncestorType::size, pattern);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::find(const C buffer) const
	{
		for (Size i = 0; i != AncestorType::size; ++i)
		{
			if (buffer == AncestorType::data[i])
				return i;
		}
		return npos;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::indexOf(
		typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size offset,
		const C buffer) const
	{
		for (; offset < AncestorType::size; ++offset)
		{
			if (buffer == AncestorType::data[offset])
				return offset;
		}
		return npos;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::startsWith(const C* buffer,
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size len) const
	{
		return (buffer && len && len <= AncestorType::size)
			? (0 == ::memcmp(AncestorType::data, buffer, len))
			: false;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	inline bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::startsWith(const U& u) const
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::valid, IString_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::Length<UType>::valid,  IString_InvalidTypeForBufferSize);

		return startsWith(Core::Traits::CString<UType>::Buffer(u),
			Core::Traits::Length<UType,Size>::Value(u));
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::endsWith(const C* buffer,
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size len) const
	{
		return (buffer && len && len <= AncestorType::size)
			? (0 == ::memcmp(AncestorType::data + (AncestorType::size - len), buffer, len))
			: false;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	inline bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::endsWith(const U& u) const
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::valid, IString_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::Length<UType>::valid,  IString_InvalidTypeForBufferSize);

		return endsWith(Core::Traits::CString<UType>::Buffer(u), Core::Traits::Length<UType,Size>::Value(u));
	}




	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::find(const C* buffer,
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size len) const
	{
		if (buffer && len && len <= AncestorType::size)
		{
			const Size end = AncestorType::size - len + 1;
			for (Size i = 0; i != end; ++i)
			{
				if (AncestorType::data[i] == *buffer)
				{
					if (!::memcmp(AncestorType::data + i, buffer, len))
						return i;
				}
			}
		}
		return npos;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::indexOf(
		typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size offset,
		const C* buffer,
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size len) const
	{
		if (buffer && len && len <= AncestorType::size)
		{
			const Size end = AncestorType::size - len + 1;
			for (; offset < end; ++offset)
			{
				if (AncestorType::data[offset] == *buffer)
				{
					if (!::memcmp(AncestorType::data + offset, buffer, len))
						return offset;
				}
			}
		}
		return npos;
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	inline typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::find(const U& u) const
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::valid, IString_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::Length<UType>::valid,  IString_InvalidTypeForBufferSize);

		// Find the substring
		if (Core::Traits::Length<UType,Size>::isFixed)
		{
			// We can make some optimisations when the length is known at compile compile time
			// This part of the code should not bring better performances but it should
			// prevent against bad uses of the API, like using a C* for looking for a single char.

			// The value to find is actually empty, npos will be the unique answer
			if (0 == Core::Traits::Length<UType,Size>::fixedLength)
				return npos;
			// The string is actually a single POD item
			if (1 == Core::Traits::Length<UType,Size>::fixedLength)
				return find(Core::Traits::CString<UType>::Buffer(u), 1);
			// Researching for the substring with a known length
			return find(Core::Traits::CString<UType>::Buffer(u), Core::Traits::Length<UType,Size>::fixedLength);
		}
		// A mere CString, with a known length at runtime only
		return find(Core::Traits::CString<UType>::Buffer(u), Core::Traits::Length<UType,Size>::Value(u));
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	inline typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::indexOf(
		typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size offset,
		const U& u) const
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::valid, IString_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::Length<UType>::valid,  IString_InvalidTypeForBufferSize);

		// Find the substring
		if (Core::Traits::Length<UType,Size>::isFixed)
		{
			// We can make some optimisations when the length is known at compile compile time
			// This part of the code should not bring better performances but it should
			// prevent against bad uses of the API, like using a C* for looking for a single char.

			// The value to find is actually empty, npos will be the unique answer
			if (0 == Core::Traits::Length<UType,Size>::fixedLength)
				return npos;
			// The string is actually a single POD item
			if (1 == Core::Traits::Length<UType,Size>::fixedLength)
				return indexOf(offset, Core::Traits::CString<UType>::Buffer(u), 1);
			// Researching for the substring with a known length
			return indexOf(offset, Core::Traits::CString<UType>::Buffer(u), Core::Traits::Length<UType,Size>::fixedLength);
		}
		// A mere CString, with a known length at runtime only
		return indexOf(offset, Core::Traits::CString<UType>::Buffer(u), Core::Traits::Length<UType,Size>::Value(u));
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	inline typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::find_first_of(const U& u) const
	{
		// Find the substring
		return find(u);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline void
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::consume(
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size n)
	{
		erase(0, n);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	inline U
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::to() const
	{
		return Yuni::Core::Extension::IString::To<typename Static::Remove::Const<U>::Type>::Perform(*this);
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	inline bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::to(U& out) const
	{
		return Yuni::Core::Extension::IString::To<typename Static::Remove::Const<U>::Type>::Perform(*this, out);
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	void
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::erase(
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size offset,
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size len)
	{
		// Only valid if the offset is strictly less than the current size
		if (offset < AncestorType::size && len)
		{
			// If the number of items to erase is greater than the current size
			// then all characters after 'offset' are dead
			if (offset + len > AncestorType::size)
				AncestorType::size = offset;
			else
			{
				// Actually we have to erase a part of the buffer
				(void)::memmove(AncestorType::data + sizeof(C) * (offset),
								AncestorType::data + sizeof(C) * (offset + len), sizeof(C) * (AncestorType::size - offset));
				// Reducing the buffer's size
				AncestorType::size -= len;
			}
			if (zeroTerminated)
				AncestorType::data[AncestorType::size] = C();
		}
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline C
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::at(
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size offset) const
	{
		return (offset < AncestorType::size) ? AncestorType::data[offset] : C();
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline const C&
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::operator [] (
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size offset) const
	{
		return AncestorType::data[offset];
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline C&
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::operator [] (
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size offset)
	{
		return AncestorType::data[offset];
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline const C&
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::operator [] (const int offset) const
	{
		return AncestorType::data[(unsigned int)offset];
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline C&
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::operator [] (const int offset)
	{
		return AncestorType::data[(unsigned int)offset];
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	inline bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::insert(
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size offset,
		const U& u)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::valid, IString_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::Length<UType>::valid,  IString_InvalidTypeForBufferSize);

		if (Core::Traits::Length<UType,Size>::isFixed)
		{
			// We can make some optimisations when the length is known at compile compile time
			// This part of the code should not bring better performances but it should
			// prevent against bad uses of the API, like using a C* for looking for a single char.

			// The value to find is actually empty, false will be the unique answer
			if (0 == Core::Traits::Length<UType,Size>::fixedLength)
				return false;
			// The string is actually a single POD item
			if (1 == Core::Traits::Length<UType,Size>::fixedLength)
				return insert(offset, Core::Traits::CString<UType>::Buffer(u), 1);
			// Researching for the substring with a known length
			return insert(offset, Core::Traits::CString<UType>::Buffer(u), Core::Traits::Length<UType,Size>::fixedLength);
		}

		return insert(offset, Core::Traits::CString<UType>::Buffer(u), Core::Traits::Length<UType,Size>::Value(u));
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	inline bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::insert(
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size offset,
		const U& u,
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size size)
	{
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<typename Static::Remove::Const<U>::Type>::valid, IString_InvalidTypeForBuffer);

		return insert(offset, Core::Traits::CString<typename Static::Remove::Const<U>::Type>::Buffer(u), size);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::insert(
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size offset,
		const C* buffer,
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size size)
	{
		if (size > 0)
		{
			if (offset == AncestorType::size)
			{
				append(buffer, size);
				return true;
			}
			else
			{
				// Checking the offset and the size of the given buffer
				if (offset < AncestorType::size)
				{
					AncestorType::insert(offset, buffer, size);
					return true;
				}
			}
		}
		return false;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::insert(
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size offset,
		const C c)
	{
		if (offset == AncestorType::size)
		{
			append(&c, 1);
			return true;
		}
		else
		{
			// Checking the offset and the size of the given buffer
			if (offset < AncestorType::size)
			{
				AncestorType::insert(offset, &c, 1);
				return true;
			}
		}
		return false;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	void
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::overwrite(
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size offset,
		const C* region,
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size size)
	{
		if (offset < AncestorType::size && size)
		{
			if (offset + size > AncestorType::size)
				(void)::memcpy(AncestorType::data + offset, region, sizeof(C) * AncestorType::size - offset);
			else
				(void)::memcpy(AncestorType::data + offset, region, sizeof(C) * size);
		}
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	void
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::overwrite(
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size offset,
		const U& u)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::valid, IString_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::Length<UType>::valid,  IString_InvalidTypeForBufferSize);

		// Find the substring
		if (Core::Traits::Length<UType,Size>::isFixed)
		{
			// We can make some optimisations when the length is known at compile compile time
			// This part of the code should not bring better performances but it should
			// prevent against bad uses of the API, like using a C* for looking for a single char.

			// The value to find is actually empty, nothing to do
			if (0 == Core::Traits::Length<UType,Size>::fixedLength)
				return;
			// The string is actually a single POD item
			if (1 == Core::Traits::Length<UType,Size>::fixedLength)
				return overwrite(offset, Core::Traits::CString<UType>::Buffer(u), 1);
			// Researching for the substring with a known length
			return overwrite(offset, Core::Traits::CString<UType>::Buffer(u), Core::Traits::Length<UType,Size>::fixedLength);
		}

		return overwrite(offset, Core::Traits::CString<UType>::Buffer(u), Core::Traits::Length<UType,Size>::Value(u));
	}




	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	void
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::truncate(const Size newSize)
	{
		if (newSize < AncestorType::size)
			AncestorType::size = newSize;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::size() const
	{
		return AncestorType::size;
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::length() const
	{
		return AncestorType::size;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline uint64
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::sizeInBytes() const
	{
		return AncestorType::size * sizeof(C);
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::capacity() const
	{
		return AncestorType::capacity;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline uint64
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::capacityInBytes() const
	{
		return AncestorType::capacity * sizeof(C);
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline const C*
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::data() const
	{
		return AncestorType::data;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline C*
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::data()
	{
		return AncestorType::data;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline const C*
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::c_str() const
	{
		return AncestorType::data;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::empty() const
	{
		return (0 == AncestorType::size);
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::null() const
	{
		return (NULL == AncestorType::data);
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::notEmpty() const
	{
		return (0 != AncestorType::size);
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline void
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::resize(
		typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size len)
	{
		if (AncestorType::expandable)
		{
			// Dynamic buffer
			AncestorType::reserve(len + AncestorType::zeroTerminated);
			AncestorType::size = len;
		}
		else
		{
			// Static buffer
			if (len <= AncestorType::capacity)
				AncestorType::size = len;
			else
				AncestorType::size = AncestorType::capacity;
		}
		// Zero-Terminated buffers
		if (zeroTerminated)
			AncestorType::data[AncestorType::size] = C();
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	void
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::trimRight(const C c)
	{
		while (AncestorType::size > 0 && AncestorType::data[AncestorType::size - 1] == c)
			--AncestorType::size;
		if (zeroTerminated)
			AncestorType::data[AncestorType::size] = C();
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	void
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::trimLeft(const C c)
	{
		if (AncestorType::size > 0)
		{
			Size offset = 0;
			while (offset < AncestorType::size && AncestorType::data[offset] == c)
				++offset;
			if (offset)
				erase(0, offset);
		}
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	void
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::trimRight(const U& u)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::valid, IString_InvalidTypeForBuffer);

		const C* ptr;
		while (AncestorType::size > 0)
		{
			ptr = Core::Traits::CString<UType>::Buffer(u);
			while (C() != *ptr)
			{
				if (*ptr == AncestorType::data[AncestorType::size - 1])
				{
					--AncestorType::size;
					break;
				}
				++ptr;
			}
			if (C() == *ptr)
				break;
		}
		if (zeroTerminated)
			AncestorType::data[AncestorType::size] = C();
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	void
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::trimLeft(const U& u)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::valid, IString_InvalidTypeForBuffer);

		const C* ptr;
		Size count = 0;
		while (count < AncestorType::size)
		{
			ptr = Core::Traits::CString<UType>::Buffer(u);
			while (C() != *ptr)
			{
				if (*ptr == AncestorType::data[count])
				{
					++count;
					break;
				}
				++ptr;
			}
			if (C() == *ptr)
				break;
		}
		if (count != 0)
			erase(0, count);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	void
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::trim(const C c)
	{
		// It seems more interesting to trim from the end first, to reduce the size
		// of the buffer as soon as possible and to reduce the amount of data to move
		// if a region must be removed by trimLeft.
		trimRight(c);
		trimLeft(c);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	void
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::trim(const U& u)
	{
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<typename Static::Remove::Const<U>::Type>::valid, IString_InvalidTypeForBuffer);

		// It seems more interesting to trim from the end first, to reduce the size
		// of the buffer as soon as possible and to reduce the amount of data to move
		// if a region must be removed by trimLeft.
		trimRight(u);
		trimLeft(u);
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::assignWithoutChecking(
		const C* block,
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size blockSize)
	{
		return AncestorType::assignWithoutChecking(block, blockSize);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::appendWithoutChecking(
		const C* block,
		const typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size blockSize)
	{
		return AncestorType::appendWithoutChecking(block, blockSize);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::assignWithoutChecking(const C c)
	{
		return AncestorType::assignWithoutChecking(c);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline typename IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::Size
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::appendWithoutChecking(const C c)
	{
		return AncestorType::appendWithoutChecking(c);
	}





	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class AnyStringT>
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>&
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::format(const AnyStringT& format, ...)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<AnyStringT>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::valid, IString_InvalidTypeForBuffer);
		// Assert, if the container is not zero-terminated
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::zeroTerminated, IString_FormatMustBeZeroTerminated);

		// Empty the buffer
		clear();
		// Dealing with the variadic arguments
		va_list parg;
		va_start(parg, format);
		vappendFormat(Core::Traits::CString<UType>::Buffer(format), parg);
		va_end(parg);
		return *this;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class AnyStringT>
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>&
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::appendFormat(const AnyStringT& format, ...)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<AnyStringT>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::valid, IString_InvalidTypeForBuffer);
		// Assert, if the container is not zero-terminated
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::zeroTerminated, IString_FormatMustBeZeroTerminated);

		// Dealing with the variadic arguments
		va_list parg;
		va_start(parg, format);
		vappendFormat(Core::Traits::CString<UType>::Buffer(format), parg);
		va_end(parg);
		return *this;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	void
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::vappendFormat(const char* format, va_list args)
	{
		// Nothing to do if the format is empty
		if (!format || '\0' == *format)
			return;

		// There is no way to know by advance the size occupied by the formatted
		// string
		// Instead of allocating a new temporary buffer, we will directly use
		// this buffer as much as possible.
		//
		// The returned size
		int i;

		if (expandable)
		{
			// Pre-Allocating a minimal amount of free space
			if (AncestorType::capacity - AncestorType::size < 10)
				AncestorType::reserve(AncestorType::size + chunkSize);
			while (true)
			{
				i = Private::IStringImpl::vnsprintf<C>(AncestorType::data + AncestorType::size,
					(AncestorType::capacity - AncestorType::size) * sizeof(C), format, args);
				if (i == -1)
				{
					AncestorType::reserve(AncestorType::capacity + chunkSize);
					continue;
				}
				else
				{
					if (i < 0)
						return;
				}
				AncestorType::size += (Size) i;
				if (zeroTerminated)
					AncestorType::data[AncestorType::size] = C();
			}
		}
		else
		{
			// In this case, the buffer can not be expanded
			// We will only try once
			if (AncestorType::capacity != AncestorType::size)
			{
				i = Private::IStringImpl::vnsprintf<C>(AncestorType::data + AncestorType::size,
					(AncestorType::capacity - AncestorType::size) * sizeof(C), format, args);
				if (i >= 0)
				{
					AncestorType::size += (Size) i;
					if (zeroTerminated)
						AncestorType::data[AncestorType::size] = C();
				}
			}
		}
	}










	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	inline bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::operator != (const U& rhs) const
	{
		return !(*this == rhs);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::operator ! () const
	{
		return !AncestorType::size;
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	inline IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>&
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::operator += (const U& rhs)
	{
		Private::IStringImpl::Append<IStringType, typename Static::Remove::Const<U>::Type>::Do(*this, rhs);
		return *this;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	inline IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>&
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::operator << (const U& rhs)
	{
		Private::IStringImpl::Append<IStringType, typename Static::Remove::Const<U>::Type>::Do(*this, rhs);
		return *this;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>&
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::operator = (const IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>& rhs)
	{
		Private::IStringImpl::Assign<IStringType, IStringType>::Do(*this, rhs);
		return *this;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<class U>
	inline IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>&
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::operator = (const U& rhs)
	{
		Private::IStringImpl::Assign<IStringType, typename Static::Remove::Const<U>::Type>::Do(*this, rhs);
		return *this;
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::operator < (const IString& rhs) const
	{
		return (!AncestorType::size || (AncestorType::size < rhs.size()
			&& ::memcmp(AncestorType::data, rhs.data(), AncestorType::size * sizeof(C)) <= 0));
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::operator > (const IString& rhs) const
	{
		return (AncestorType::size > rhs.size()
			&& ::memcmp(AncestorType::data, rhs.data(), rhs.size() * sizeof(C)) >= 0);
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::operator <= (const IString& rhs) const
	{
		return (!AncestorType::size || (AncestorType::size <= rhs.size()
			&& ::memcmp(AncestorType::data, rhs.data(), AncestorType::size * sizeof(C)) <= 0));
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::operator >= (const IString& rhs) const
	{
		return (AncestorType::size && AncestorType::size >= rhs.size()
			&& ::memcmp(AncestorType::data, rhs.data(), rhs.size() * sizeof(C)) >= 0);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::operator == (const C* rhs) const
	{
		// Assert, if the length of the given container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::Length<C>::valid,  IString_InvalidTypeForBufferSize);

		const Size cL = (rhs ? Core::Traits::Length<C,Size>::Value(rhs) : 0);
		return (AncestorType::size == cL && AncestorType::size != 0
			&& !::memcmp(AncestorType::data, rhs, AncestorType::size * sizeof(C)));
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::operator <= (const C* rhs) const
	{
		// Assert, if the length of the given container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::Length<C>::valid,  IString_InvalidTypeForBufferSize);

		const Size cL = (rhs ? Core::Traits::Length<C,Size>::Value(rhs) : 0);
		return (AncestorType::size <= cL && AncestorType::size != 0
			&& ::memcmp(AncestorType::data, rhs, AncestorType::size * sizeof(C)) <= 0);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::operator >= (const C* rhs) const
	{
		// Assert, if the length of the given container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::Length<C>::valid,  IString_InvalidTypeForBufferSize);

		const Size cL = (rhs ? Core::Traits::Length<C,Size>::Value(rhs) : 0);
		return (AncestorType::size >= cL && AncestorType::size != 0
			&& ::memcmp(AncestorType::data, rhs, AncestorType::size * sizeof(C)) >= 0);
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::operator < (const C* rhs) const
	{
		// Assert, if the length of the given container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::Length<C>::valid,  IString_InvalidTypeForBufferSize);

		const Size cL = (rhs ? Core::Traits::Length<C,Size>::Value(rhs) : 0);
		return (AncestorType::size < cL && AncestorType::size != 0
			&& ::memcmp(AncestorType::data, rhs, AncestorType::size * sizeof(C)) < 0);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::operator > (const C* rhs) const
	{
		// Assert, if the length of the given container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::Length<C>::valid,  IString_InvalidTypeForBufferSize);

		const Size cL = (rhs ? Core::Traits::Length<C,Size>::Value(rhs) : 0);
		return (AncestorType::size > cL && AncestorType::size != 0
			&& ::memcmp(AncestorType::data, rhs, AncestorType::size * sizeof(C)) > 0);
	}




	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	inline bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::operator == (const IString& rhs) const
	{
		return (AncestorType::size > 0 && AncestorType::size == rhs.size()
			&& !::memcmp(AncestorType::data, rhs.data(), AncestorType::size * sizeof(C)));
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	template<unsigned int C1, bool E1, bool Z1>
	inline bool
	IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>::operator == (const IString<C1, E1, Z1, C>& rhs) const
	{
		return (AncestorType::size == rhs.size()
			&& !::memcmp(AncestorType::data, rhs.data(), AncestorType::size * sizeof(C)));
	}





} // namespace Core
} // namespace Yuni

#endif // __YUNI_CORE_MEMORY_BUFFER_ISTRING_HXX__
