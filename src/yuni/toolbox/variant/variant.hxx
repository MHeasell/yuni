#ifndef __YUNI_TOOLBOX_VARIANT_VARIANT_HXX__
#define __YUNI_TOOLBOX_VARIANT_VARIANT_HXX__

namespace Yuni
{

	template <typename T>
	Variant::Variant(const T& source)
	{
		pTable = Private::Variant::Table<T>::get();
		if (sizeof(T) <= sizeof(void*))
			new (&pObject) T(source);
		else
			pObject = new T(source);
	}

	template <typename T, typename U>
	Variant& Variant::assign(const T& rhs)
	{
		// Are we copying between the same type of variants ?
		Private::Variant::FunctionPtrTable* rhsTable = Private::Variant::Table<U>::get();

		if (pTable == rhsTable)
		{ // Yes, so we can avoid reallocating, and re-use memory.
			// Destruct our current object
			pTable->staticDelete(&pObject);
			if (sizeof(U) <= sizeof(void*))
				// Create copy on-top of object pointer itself
				new (&pObject) U(rhs);
			else
				// Create copy on-top of the old version
				new (pObject) U(rhs);
		}
		else
		{ // No, this was not the same type.
			reset();
			if (sizeof(U) <= sizeof(void*))
			{
				// Create copy on-top of object pointer itself
				new (&pObject) U(rhs);
				// Update table pointer
				pTable = rhsTable;
			}
			else
			{
				pObject = new U(rhs);
				pTable = rhsTable;
			}
		}
		return *this;
	}

	template <typename T>
	const T& Variant::to() const
	{
		if (type() != typeid(T))
			throw Exceptions::BadCast(type(), typeid(T));

		if (sizeof(T) <= sizeof(void*))
			return *reinterpret_cast<T const*>(&pObject);

		return *reinterpret_cast<T const*>(pObject);
	}

	template <typename T>
	void Variant::initFromCString(T source)
	{
		pTable = Private::Variant::Table<String>::get();
		if (sizeof(String) <= sizeof(void*))
			new (&pObject) String(source);
		else
			pObject = new String(source);
	}

}

#endif /* !__YUNI_TOOLBOX_VARIANT_VARIANT_HXX__ */


