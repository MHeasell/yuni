#ifndef __YUNI_CORE_MEMORY_BUFFER_MEMORY_BUFFER_HXX__
# define __YUNI_CORE_MEMORY_BUFFER_MEMORY_BUFFER_HXX__


namespace Yuni
{


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::MemoryBuffer()
	{}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::MemoryBuffer(const MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>& rhs)
		:AncestorType(rhs)
	{}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::MemoryBuffer(const U& rhs)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::valid, MemoryBuffer_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::Length<UType>::valid,  MemoryBuffer_InvalidTypeForBufferSize);

		Private::MemoryBufferImpl::Assign<MemoryBufferType, UType>::Do(*this, rhs);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::MemoryBuffer(const C* block, const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size blockSize)
	{
		AncestorType::assign(block, blockSize);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline void MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::assign(const U& u)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::valid, MemoryBuffer_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::Length<UType>::valid,  MemoryBuffer_InvalidTypeForBufferSize);

		Private::MemoryBufferImpl::Assign<MemoryBuffer, UType>::Do(*this, u);
		return *this;
	}

	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline void MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::append(const U& u)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::valid, MemoryBuffer_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::Length<UType>::valid,  MemoryBuffer_InvalidTypeForBufferSize);

		Private::MemoryBufferImpl::Append<MemoryBuffer, UType>::Do(*this, u);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline void MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::append(const U& u,
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size size)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::valid, MemoryBuffer_InvalidTypeForBuffer);

		AncestorType::append(Core::Traits::CString<UType>::Buffer(u), size);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline void MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::push_back(const U& u)
	{
		append(u);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline void MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::push_front(const U& u)
	{
		insert(0, u);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline void MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::prepend(const U& u)
	{
		insert(0, u);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline void MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::prepend(const U& u,
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size size)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;

		insert(0, Core::Traits::CString<UType>::Buffer(u), size);
	}





	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline void
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::assign(const C* buffer,
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size size)
	{
		AncestorType::assign(buffer, size);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline void
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::append(const C* buffer,
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size size)
	{
		AncestorType::append(buffer, size);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>&
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::clear()
	{
		AncestorType::clear();
		return *this;
	}



	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline void
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::reserve(
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size minCapacity)
	{
		AncestorType::reserve(minCapacity);
	}



	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline void
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::put(const C c)
	{
		AncestorType::put(c);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	void MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::fill(const U& pattern)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::Length<UType>::valid,  MemoryBuffer_InvalidTypeForBufferSize);

		if (AncestorType::size)
			Private::MemoryBufferImpl::Fill<MemoryBuffer, UType>::Do(AncestorType::data, AncestorType::size, pattern);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::find(const C buffer) const
	{
		for (Size i = 0; i != AncestorType::size; ++i)
		{
			if (buffer == AncestorType::data[i])
				return i;
		}
		return npos;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::indexOf(
		typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size offset,
		const C buffer) const
	{
		for (; offset < AncestorType::size; ++offset)
		{
			if (buffer == AncestorType::data[offset])
				return offset;
		}
		return npos;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline bool
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::startsWith(const C* buffer,
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size len) const
	{
		return (buffer && len && len <= AncestorType::size)
			? (0 == ::memcmp(AncestorType::data, buffer, len))
			: false;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline bool
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::startsWith(const U& u) const
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::valid, MemoryBuffer_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::Length<UType>::valid,  MemoryBuffer_InvalidTypeForBufferSize);

		return startsWith(Core::Traits::CString<UType>::Buffer(u), Core::Traits::Length<UType,Size>::Value(u));
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline bool
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::endsWith(const C* buffer,
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size len) const
	{
		return (buffer && len && len <= AncestorType::size)
			? (0 == ::memcmp(AncestorType::data + (AncestorType::size - len), buffer, len))
			: false;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline bool
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::endsWith(const U& u) const
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::valid, MemoryBuffer_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::Length<UType>::valid,  MemoryBuffer_InvalidTypeForBufferSize);

		return endsWith(Core::Traits::CString<UType>::Buffer(u), Core::Traits::Length<UType,Size>::Value(u));
	}




	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::find(const C* buffer,
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size len) const
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


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::indexOf(
		typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size offset,
		const C* buffer,
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size len) const
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



	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::find(const U& u) const
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::valid, MemoryBuffer_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::Length<UType>::valid,  MemoryBuffer_InvalidTypeForBufferSize);

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


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::indexOf(
		typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size offset,
		const U& u) const
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::valid, MemoryBuffer_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::Length<UType>::valid,  MemoryBuffer_InvalidTypeForBufferSize);

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


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::find_first_of(const U& u) const
	{
		// Find the substring
		return find(u);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline void
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::consume(
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size n)
	{
		erase(0, n);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	void
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::erase(
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size offset,
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size len)
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


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline C
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::at(
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size offset) const
	{
		return (offset < AncestorType::size) ? AncestorType::data[offset] : C();
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline const C&
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::operator [] (
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size offset) const
	{
		return AncestorType::data[offset];
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline C&
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::operator [] (
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size offset)
	{
		return AncestorType::data[offset];
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline bool
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::insert(
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size offset,
		const U& u)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::valid, MemoryBuffer_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::Length<UType>::valid,  MemoryBuffer_InvalidTypeForBufferSize);

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


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline bool
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::insert(
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size offset,
		const U& u,
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size size)
	{
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<typename Static::Remove::Const<U>::Type>::valid, MemoryBuffer_InvalidTypeForBuffer);

		return insert(offset, Core::Traits::CString<typename Static::Remove::Const<U>::Type>::Buffer(u), size);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	bool
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::insert(
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size offset,
		const C* buffer,
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size size)
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


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	bool
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::insert(
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size offset,
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


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	void
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::overwrite(
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size offset,
		const C* region,
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size size)
	{
		if (offset < AncestorType::size && size)
		{
			if (offset + size > AncestorType::size)
				(void)::memcpy(AncestorType::data + offset, region, sizeof(C) * AncestorType::size - offset);
			else
				(void)::memcpy(AncestorType::data + offset, region, sizeof(C) * size);
		}
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	void
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::overwrite(
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size offset,
		const U& u)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::valid, MemoryBuffer_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::Length<UType>::valid,  MemoryBuffer_InvalidTypeForBufferSize);

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




	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	void
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::truncate(const Size newSize)
	{
		if (newSize < AncestorType::size)
			AncestorType::size = newSize;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::size() const
	{
		return AncestorType::size;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::capacity() const
	{
		return AncestorType::capacity;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline const C*
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::data() const
	{
		return AncestorType::data;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline C*
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::data()
	{
		return AncestorType::data;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline const C*
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::c_str() const
	{
		return AncestorType::data;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline bool
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::empty() const
	{
		return (0 == AncestorType::size);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline bool
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::notEmpty() const
	{
		return (0 != AncestorType::size);
	}



	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline void
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::resize(
		typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size len)
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


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	void
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::trimRight(const C c)
	{
		while (AncestorType::size > 0 && AncestorType::data[AncestorType::size - 1] == c)
			--AncestorType::size;
		if (zeroTerminated)
			AncestorType::data[AncestorType::size] = C();
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	void
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::trimLeft(const C c)
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


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	void
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::trimRight(const U& u)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::valid, MemoryBuffer_InvalidTypeForBuffer);

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


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	void
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::trimLeft(const U& u)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<UType>::valid, MemoryBuffer_InvalidTypeForBuffer);

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


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	void
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::trim(const C c)
	{
		// It seems more interesting to trim from the end first, to reduce the size
		// of the buffer as soon as possible and to reduce the amount of data to move
		// if a region must be removed by trimLeft.
		trimRight(c);
		trimLeft(c);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	void
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::trim(const U& u)
	{
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Core::Traits::CString<typename Static::Remove::Const<U>::Type>::valid, MemoryBuffer_InvalidTypeForBuffer);

		// It seems more interesting to trim from the end first, to reduce the size
		// of the buffer as soon as possible and to reduce the amount of data to move
		// if a region must be removed by trimLeft.
		trimRight(u);
		trimLeft(u);
	}



	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::assignWithoutChecking(
		const C* block,
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size blockSize)
	{
		return AncestorType::assignWithoutChecking(block, blockSize);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::appendWithoutChecking(
		const C* block,
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size blockSize)
	{
		return AncestorType::appendWithoutChecking(block, blockSize);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::assignWithoutChecking(const C c)
	{
		return AncestorType::assignWithoutChecking(c);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::appendWithoutChecking(const C c)
	{
		return AncestorType::appendWithoutChecking(c);
	}



	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline bool
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::operator != (const U& rhs) const
	{
		return !(*this == rhs);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline bool
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::operator ! () const
	{
		return !AncestorType::size;
	}



	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>&
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::operator += (const U& rhs)
	{
		Private::MemoryBufferImpl::Append<MemoryBuffer, typename Static::Remove::Const<U>::Type>::Do(*this, rhs);
		return *this;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>&
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::operator << (const U& rhs)
	{
		Private::MemoryBufferImpl::Append<MemoryBuffer, typename Static::Remove::Const<U>::Type>::Do(*this, rhs);
		return *this;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>&
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::operator = (const MemoryBuffer& rhs)
	{
		Private::MemoryBufferImpl::Assign<MemoryBuffer, C>::Do(*this, rhs);
		return *this;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>&
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::operator = (const U& rhs)
	{
		Private::MemoryBufferImpl::Assign<MemoryBuffer, typename Static::Remove::Const<U>::Type>::Do(*this, rhs);
		return *this;
	}





} // namespace Yuni

#endif // __YUNI_CORE_MEMORY_BUFFER_MEMORY_BUFFER_HXX__
