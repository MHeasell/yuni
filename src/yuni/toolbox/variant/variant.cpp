#include <algorithm>
#include "variant.h"


namespace Yuni
{


	Variant::Variant()
	{
		pTable = Private::Variant::Table<Private::Variant::Empty>::get();
		pObject = NULL;
	}


	Variant::Variant(const Variant& rhs)
	{
		pTable = Private::Variant::Table<Private::Variant::Empty>::get();
		assign(rhs);
	}


	Variant::~Variant()
	{
		pTable->staticDelete(&pObject);
	}


	Variant& Variant::assign(const Variant& rhs)
	{
		// Are we copying from the same type (using the same table) ?
		if (pTable == rhs.pTable)
		{
			// If so, we can avoid reallocation
			pTable->move(&rhs.pObject, &pObject);
		}
		else
		{
			reset();
			rhs.pTable->clone(&rhs.pObject, &pObject);
			pTable = rhs.pTable;
		}
		return *this;
	}


	void Variant::Swap(Variant& one, Variant& other)
	{
		std::swap(one.pTable, other.pTable);
		std::swap(one.pObject, other.pObject);
	}


	void Variant::reset()
	{
		if (!this->empty())
		{
			pTable->staticDelete(&pObject);
			pTable = Private::Variant::Table<Private::Variant::Empty>::get();
			pObject = NULL;
		}
	}



} // namespace Yuni
