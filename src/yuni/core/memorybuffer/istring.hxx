#ifndef __YUNI_CORE_MEMORY_BUFFER_ISTRING_HXX__
# define __YUNI_CORE_MEMORY_BUFFER_ISTRING_HXX__

#include <ctype.h>


namespace Yuni
{


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::CustomString()
	{}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::CustomString(const NullPtr&)
	{}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::CustomString(const NullPtr*)
	{}




	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::CustomString(const CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>& rhs)
		:AncestorType(rhs)
	{}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::CustomString(const U& rhs)
	{
		// The given type, without its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, CustomString_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::Length<UType>::valid,  CustomString_InvalidTypeForBufferSize);

		Yuni::Core::Extension::CustomString::Assign<CustomStringType, UType>::Do(*this, rhs);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::CustomString(const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* block,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size blockSize)
	{
		AncestorType::assign(block, blockSize);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline void CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::assign(const U& u)
	{
		// The given type, without its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;

		Yuni::Core::Extension::CustomString::Assign<CustomString, UType>::Do(*this, u);
		return *this;
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline void CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::append(const U& u)
	{
		// The given type, without its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;

		Core::Extension::CustomString::Append<CustomString, UType>::Do(*this, u);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline void CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::append(const U& u,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size size)
	{
		// The given type, without its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;

		AncestorType::append(Traits::CString<UType>::Buffer(u), size);
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline void CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::write(const U& u,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size size)
	{
		append(u, size);
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline void CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::push_back(const U& u)
	{
		append(u);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline void CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::push_front(const U& u)
	{
		insert(0, u);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline void CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::prepend(const U& u)
	{
		insert(0, u);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline void CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::prepend(const U& u,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size size)
	{
		// The given type, without its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;

		insert(0, Traits::CString<UType>::Buffer(u), size);
	}





	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::assign(const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* buffer,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size size)
	{
		AncestorType::assign(buffer, size);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::append(const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* buffer,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size size)
	{
		AncestorType::append(buffer, size);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>&
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::clear()
	{
		AncestorType::clear();
		return *this;
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::reserve(
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size minCapacity)
	{
		AncestorType::reserve(minCapacity);
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::put(const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char c)
	{
		AncestorType::put(c);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	void CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::fill(const U& pattern)
	{
		// The given type, without its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::Length<UType>::valid,  CustomString_InvalidTypeForBufferSize);

		if (AncestorType::size)
			Yuni::Core::Extension::CustomString::Fill<CustomString, UType>::Do(AncestorType::data, AncestorType::size, pattern);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::find(const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char buffer) const
	{
		for (Size i = 0; i != AncestorType::size; ++i)
		{
			if (buffer == AncestorType::data[i])
				return i;
		}
		return npos;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::indexOf(
		typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char buffer) const
	{
		for (; offset < AncestorType::size; ++offset)
		{
			if (buffer == AncestorType::data[offset])
				return offset;
		}
		return npos;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::startsWith(const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* buffer,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size len) const
	{
		return (buffer && len && len <= AncestorType::size)
			? (0 == ::memcmp(AncestorType::data, buffer, len))
			: false;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::startsWith(const U& u) const
	{
		// The given type, without its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, CustomString_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::Length<UType>::valid,  CustomString_InvalidTypeForBufferSize);

		return startsWith(Traits::CString<UType>::Buffer(u),
			Traits::Length<UType,Size>::Value(u));
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::endsWith(const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* buffer,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size len) const
	{
		return (buffer && len && len <= AncestorType::size)
			? (0 == ::memcmp(AncestorType::data + (AncestorType::size - len), buffer, len))
			: false;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::endsWith(const U& u) const
	{
		// The given type, without its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, CustomString_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::Length<UType>::valid,  CustomString_InvalidTypeForBufferSize);

		return endsWith(Traits::CString<UType>::Buffer(u), Traits::Length<UType,Size>::Value(u));
	}




	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::find(const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* buffer,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size len) const
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


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::indexOf(
		typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* buffer,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size len) const
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



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::find(const U& u) const
	{
		// The given type, without its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, CustomString_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::Length<UType>::valid,  CustomString_InvalidTypeForBufferSize);

		// Find the substring
		if (Traits::Length<UType,Size>::isFixed)
		{
			// We can make some optimisations when the length is known at compile compile time
			// This part of the code should not bring better performances but it should
			// prevent against bad uses of the API, like using a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* for looking for a single char.

			// The value to find is actually empty, npos will be the unique answer
			if (0 == Traits::Length<UType,Size>::fixedLength)
				return npos;
			// The string is actually a single POD item
			if (1 == Traits::Length<UType,Size>::fixedLength)
				return find(Traits::CString<UType>::Buffer(u), 1);
			// Researching for the substring with a known length
			return find(Traits::CString<UType>::Buffer(u), Traits::Length<UType,Size>::fixedLength);
		}
		// A mere CString, with a known length at runtime only
		return find(Traits::CString<UType>::Buffer(u), Traits::Length<UType,Size>::Value(u));
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::indexOf(
		typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset,
		const U& u) const
	{
		// The given type, without its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, CustomString_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::Length<UType>::valid,  CustomString_InvalidTypeForBufferSize);

		// Find the substring
		if (Traits::Length<UType,Size>::isFixed)
		{
			// We can make some optimisations when the length is known at compile compile time
			// This part of the code should not bring better performances but it should
			// prevent against bad uses of the API, like using a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* for looking for a single char.

			// The value to find is actually empty, npos will be the unique answer
			if (0 == Traits::Length<UType,Size>::fixedLength)
				return npos;
			// The string is actually a single POD item
			if (1 == Traits::Length<UType,Size>::fixedLength)
				return indexOf(offset, Traits::CString<UType>::Buffer(u), 1);
			// Researching for the substring with a known length
			return indexOf(offset, Traits::CString<UType>::Buffer(u), Traits::Length<UType,Size>::fixedLength);
		}
		// A mere CString, with a known length at runtime only
		return indexOf(offset, Traits::CString<UType>::Buffer(u), Traits::Length<UType,Size>::Value(u));
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::find_first_of(const U& u) const
	{
		// Find the substring
		return find(u);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::consume(
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size n)
	{
		erase(0, n);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline U
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::to() const
	{
		return Yuni::Core::Extension::CustomString::Into<typename Static::Remove::Const<U>::Type>::Perform(*this);
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::to(U& out) const
	{
		return Yuni::Core::Extension::CustomString::Into<typename Static::Remove::Const<U>::Type>::Perform(*this, out);
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::erase(
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size len)
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
				(void)::memmove(AncestorType::data + sizeof(Char) * (offset),
								AncestorType::data + sizeof(Char) * (offset + len), sizeof(Char) * (AncestorType::size - offset));
				// Reducing the buffer's size
				AncestorType::size -= len;
			}
			if (zeroTerminated)
				AncestorType::data[AncestorType::size] = Char();
		}
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::at(
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset) const
	{
		return (offset < AncestorType::size) ? AncestorType::data[offset] : Char();
	}




	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::insert(
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset, const U& u)
	{
		// The given type, without its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, CustomString_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::Length<UType>::valid,  CustomString_InvalidTypeForBufferSize);

		if (Traits::Length<UType,Size>::isFixed)
		{
			// We can make some optimisations when the length is known at compile compile time
			// This part of the code should not bring better performances but it should
			// prevent against bad uses of the API, like using a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* for looking for a single char.

			// The value to find is actually empty, false will be the unique answer
			if (0 == Traits::Length<UType,Size>::fixedLength)
				return false;
			// The string is actually a single POD item
			if (1 == Traits::Length<UType,Size>::fixedLength)
				return insert(offset, Traits::CString<UType>::Buffer(u), 1);
			// Researching for the substring with a known length
			return insert(offset, Traits::CString<UType>::Buffer(u), Traits::Length<UType,Size>::fixedLength);
		}

		return insert(offset, Traits::CString<UType>::Buffer(u), Traits::Length<UType,Size>::Value(u));
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::insert(
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset,
		const U& u,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size size)
	{
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<typename Static::Remove::Const<U>::Type>::valid, CustomString_InvalidTypeForBuffer);

		return insert(offset, Traits::CString<typename Static::Remove::Const<U>::Type>::Buffer(u), size);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::insert(
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* buffer,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size size)
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


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::insert(
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset, const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char c)
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


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::overwrite(
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* region,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size size)
	{
		if (offset < AncestorType::size && size)
		{
			if (offset + size > AncestorType::size)
				(void)::memcpy(AncestorType::data + offset, region, sizeof(Char) * AncestorType::size - offset);
			else
				(void)::memcpy(AncestorType::data + offset, region, sizeof(Char) * size);
		}
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::overwrite(
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset, const U& u)
	{
		// The given type, without its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, CustomString_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::Length<UType>::valid,  CustomString_InvalidTypeForBufferSize);

		// Find the substring
		if (Traits::Length<UType,Size>::isFixed)
		{
			// We can make some optimisations when the length is known at compile compile time
			// This part of the code should not bring better performances but it should
			// prevent against bad uses of the API, like using a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* for looking for a single char.

			// The value to find is actually empty, nothing to do
			if (0 == Traits::Length<UType,Size>::fixedLength)
				return;
			// The string is actually a single POD item
			if (1 == Traits::Length<UType,Size>::fixedLength)
				return overwrite(offset, Traits::CString<UType>::Buffer(u), 1);
			// Researching for the substring with a known length
			return overwrite(offset, Traits::CString<UType>::Buffer(u), Traits::Length<UType,Size>::fixedLength);
		}

		return overwrite(offset, Traits::CString<UType>::Buffer(u), Traits::Length<UType,Size>::Value(u));
	}




	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::truncate(const Size newSize)
	{
		if (newSize < AncestorType::size)
			AncestorType::size = newSize;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::size() const
	{
		return AncestorType::size;
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::length() const
	{
		return AncestorType::size;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline uint64
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::sizeInBytes() const
	{
		return AncestorType::size * sizeof(Char);
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::capacity() const
	{
		return AncestorType::capacity;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline uint64
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::capacityInBytes() const
	{
		return AncestorType::capacity * sizeof(Char);
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char*
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::data() const
	{
		return AncestorType::data;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char*
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::data()
	{
		return AncestorType::data;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char*
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::c_str() const
	{
		return AncestorType::data;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::empty() const
	{
		return (0 == AncestorType::size);
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::null() const
	{
		return (NULL == AncestorType::data);
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::notEmpty() const
	{
		return (0 != AncestorType::size);
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::resize(
		typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size len)
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
			AncestorType::data[AncestorType::size] = Char();
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::trimRight(const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char c)
	{
		while (AncestorType::size > 0 && AncestorType::data[AncestorType::size - 1] == c)
			--AncestorType::size;
		if (zeroTerminated)
			AncestorType::data[AncestorType::size] = Char();
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::trimLeft(const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char c)
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


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::trimRight(const U& u)
	{
		// The given type, without its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, CustomString_InvalidTypeForBuffer);

		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* ptr;
		while (AncestorType::size > 0)
		{
			ptr = Traits::CString<UType>::Buffer(u);
			while (Char() != *ptr)
			{
				if (*ptr == AncestorType::data[AncestorType::size - 1])
				{
					--AncestorType::size;
					break;
				}
				++ptr;
			}
			if (Char() == *ptr)
				break;
		}
		if (zeroTerminated)
			AncestorType::data[AncestorType::size] = Char();
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::trimLeft(const U& u)
	{
		// The given type, without its const identifier
		typedef typename Static::Remove::Const<U>::Type UType;
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, CustomString_InvalidTypeForBuffer);

		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* ptr;
		Size count = 0;
		while (count < AncestorType::size)
		{
			ptr = Traits::CString<UType>::Buffer(u);
			while (Char() != *ptr)
			{
				if (*ptr == AncestorType::data[count])
				{
					++count;
					break;
				}
				++ptr;
			}
			if (Char() == *ptr)
				break;
		}
		if (count != 0)
			erase(0, count);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::trim(const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char c)
	{
		// It seems more interesting to trim from the end first, to reduce the size
		// of the buffer as soon as possible and to reduce the amount of data to move
		// if a region must be removed by trimLeft.
		trimRight(c);
		trimLeft(c);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::trim(const U& u)
	{
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<typename Static::Remove::Const<U>::Type>::valid, CustomString_InvalidTypeForBuffer);

		// It seems more interesting to trim from the end first, to reduce the size
		// of the buffer as soon as possible and to reduce the amount of data to move
		// if a region must be removed by trimLeft.
		trimRight(u);
		trimLeft(u);
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::assignWithoutChecking(
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* block,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size blockSize)
	{
		return AncestorType::assignWithoutChecking(block, blockSize);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::appendWithoutChecking(
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* block,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size blockSize)
	{
		return AncestorType::appendWithoutChecking(block, blockSize);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::assignWithoutChecking(const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char c)
	{
		return AncestorType::assignWithoutChecking(c);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::appendWithoutChecking(const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char c)
	{
		return AncestorType::appendWithoutChecking(c);
	}





	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class AnyStringT>
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>&
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::format(const AnyStringT& format, ...)
	{
		// The given type, without its const identifier
		typedef typename Static::Remove::Const<AnyStringT>::Type UType;
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, CustomString_InvalidTypeForBuffer);
		// Assert, if the container is not zero-terminated
		YUNI_STATIC_ASSERT(Traits::CString<UType>::zeroTerminated, CustomString_FormatMustBeZeroTerminated);

		// Empty the buffer
		clear();
		// Dealing with the variadic arguments
		va_list parg;
		va_start(parg, format);
		vappendFormat(Traits::CString<UType>::Buffer(format), parg);
		va_end(parg);
		return *this;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class AnyStringT>
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>&
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::appendFormat(const AnyStringT& format, ...)
	{
		// The given type, without its const identifier
		typedef typename Static::Remove::Const<AnyStringT>::Type UType;
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, CustomString_InvalidTypeForBuffer);
		// Assert, if the container is not zero-terminated
		YUNI_STATIC_ASSERT(Traits::CString<UType>::zeroTerminated, CustomString_FormatMustBeZeroTerminated);

		// Dealing with the variadic arguments
		va_list parg;
		va_start(parg, format);
		vappendFormat(Traits::CString<UType>::Buffer(format), parg);
		va_end(parg);
		return *this;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::vappendFormat(const char* format, va_list args)
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
				i = Private::CustomStringImpl::vnsprintf<Char>(AncestorType::data + AncestorType::size,
					(AncestorType::capacity - AncestorType::size) * sizeof(Char), format, args);
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
					AncestorType::data[AncestorType::size] = Char();
			}
		}
		else
		{
			// In this case, the buffer can not be expanded
			// We will only try once
			if (AncestorType::capacity != AncestorType::size)
			{
				i = Private::CustomStringImpl::vnsprintf<Char>(AncestorType::data + AncestorType::size,
					(AncestorType::capacity - AncestorType::size) * sizeof(Char), format, args);
				if (i >= 0)
				{
					AncestorType::size += (Size) i;
					if (zeroTerminated)
						AncestorType::data[AncestorType::size] = Char();
				}
			}
		}
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>&
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::toLower()
	{
		for (Size i = 0; i < AncestorType::size; ++i)
			AncestorType::data[i] = (Char) tolower(AncestorType::data[i]);
		return *this;
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>&
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::toUpper()
	{
		for (Size i = 0; i < AncestorType::size; ++i)
			AncestorType::data[i] = (Char) toupper(AncestorType::data[i]);
		return *this;
	}






	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char &
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator [] (
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset) const
	{
		return AncestorType::data[offset];
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char &
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator [] (
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset)
	{
		return AncestorType::data[offset];
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char &
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator [] (const int offset) const
	{
		return AncestorType::data[(unsigned int)offset];
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char &
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator [] (const int offset)
	{
		return AncestorType::data[(unsigned int)offset];
	}




	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator != (const U& rhs) const
	{
		return !(*this == rhs);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator ! () const
	{
		return !AncestorType::size;
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>&
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator += (const U& rhs)
	{
		Core::Extension::CustomString::Append<CustomStringType, typename Static::Remove::Const<U>::Type>::Do(*this, rhs);
		return *this;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>&
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator << (const U& rhs)
	{
		Core::Extension::CustomString::Append<CustomStringType, typename Static::Remove::Const<U>::Type>::Do(*this, rhs);
		return *this;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>&
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator = (const CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>& rhs)
	{
		Yuni::Core::Extension::CustomString::Assign<CustomStringType, CustomStringType>::Do(*this, rhs);
		return *this;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>&
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator = (const U& rhs)
	{
		Yuni::Core::Extension::CustomString::Assign<CustomStringType, typename Static::Remove::Const<U>::Type>::Do(*this, rhs);
		return *this;
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class AnyStringT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator < (const AnyStringT& rhs) const
	{
		// The given type, without its const identifier
		typedef typename Static::Remove::Const<AnyStringT>::Type UType;
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, CustomString_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::Length<UType>::valid,  CustomString_InvalidTypeForBufferSize);

		const Size rhsLength = Traits::Length<UType,Size>::Value(rhs);
		return ((AncestorType::size != rhsLength)
			? ::strncmp(AncestorType::data, Traits::CString<UType>::Buffer(rhs),
				(AncestorType::size < rhsLength ? AncestorType::size : rhsLength) * sizeof(Char)) <= 0
			: ::strncmp(AncestorType::data, Traits::CString<UType>::Buffer(rhs), AncestorType::size) < 0);
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class AnyStringT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator > (const AnyStringT& rhs) const
	{
		// The given type, without its const identifier
		typedef typename Static::Remove::Const<AnyStringT>::Type UType;
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, CustomString_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::Length<UType>::valid,  CustomString_InvalidTypeForBufferSize);

		const Size rhsLength = Traits::Length<UType,Size>::Value(rhs);
		return ((AncestorType::size != rhsLength)
			? ::strncmp(AncestorType::data, Traits::CString<UType>::Buffer(rhs),
				(AncestorType::size < rhsLength ? AncestorType::size : rhsLength) * sizeof(Char)) >= 0
			: ::strncmp(AncestorType::data, Traits::CString<UType>::Buffer(rhs), AncestorType::size) > 0);
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class AnyStringT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator <= (const AnyStringT& rhs) const
	{
		// The given type, without its const identifier
		typedef typename Static::Remove::Const<AnyStringT>::Type UType;
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, CustomString_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::Length<UType>::valid,  CustomString_InvalidTypeForBufferSize);

		const Size rhsLength = Traits::Length<UType,Size>::Value(rhs);
		return ::strncmp(AncestorType::data, Traits::CString<UType>::Buffer(rhs),
			(AncestorType::size < rhsLength ? AncestorType::size : rhsLength) * sizeof(Char)) <= 0;
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class AnyStringT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator >= (const AnyStringT& rhs) const
	{
		// The given type, without its const identifier
		typedef typename Static::Remove::Const<AnyStringT>::Type UType;
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, CustomString_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::Length<UType>::valid,  CustomString_InvalidTypeForBufferSize);

		const Size rhsLength = Traits::Length<UType,Size>::Value(rhs);
		return ::strncmp(AncestorType::data, Traits::CString<UType>::Buffer(rhs),
			(AncestorType::size < rhsLength ? AncestorType::size : rhsLength) * sizeof(Char)) >= 0;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class AnyStringT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator == (const AnyStringT& rhs) const
	{
		// The given type, without its const identifier
		typedef typename Static::Remove::Const<AnyStringT>::Type UType;
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, CustomString_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::Length<UType>::valid,  CustomString_InvalidTypeForBufferSize);

		return (AncestorType::size && AncestorType::size == Traits::Length<UType,Size>::Value(rhs)) &&
			!::strncmp(AncestorType::data, Traits::CString<UType>::Buffer(rhs), (AncestorType::size) * sizeof(Char));
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator == (const CustomString& rhs) const
	{
		return (AncestorType::size && AncestorType::size == rhs.size()
			&& !::strncmp(AncestorType::data, rhs.data(), AncestorType::size * sizeof(Char)));
	}






} // namespace Yuni

#endif // __YUNI_CORE_MEMORY_BUFFER_ISTRING_HXX__
