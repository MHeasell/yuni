#include "variant.h"


namespace Yuni
{

	Variant::Variant() :
		pShareContent(false)
	{}


	Variant::Variant(const NullPtr&) :
		pShareContent(false)
	{}


	Variant::Variant(const char* rhs) :
		pData(new Private::Variant::Data<String>(rhs)),
		pShareContent(false)
	{
	}


	Variant::Variant(const Private::Variant::IDataHolder* rhs) :
		pData(const_cast<Private::Variant::IDataHolder*>(rhs)),
		pShareContent(false)
	{
	}


	Variant::Variant(const Variant& rhs) :
		pShareContent(false)
	{
		assign(rhs);
	}


	Variant::Variant(Private::Variant::IDataHolder* rhs) :
		pData(rhs),
		pShareContent(false)
	{
	}


	void Variant::assign(uint32 rhs)
	{
		if (pShareContent && !(!pData))
			pData->assign(rhs);
		else
			pData = new Private::Variant::Data<uint32>(rhs);
	}
	void Variant::assign(sint32 rhs)
	{
		if (pShareContent && !(!pData))
			pData->assign(rhs);
		else
			pData = new Private::Variant::Data<sint32>(rhs);
	}
	void Variant::assign(uint64 rhs)
	{
		if (pShareContent && !(!pData))
			pData->assign(rhs);
		else
			pData = new Private::Variant::Data<uint64>(rhs);
	}
	void Variant::assign(sint64 rhs)
	{
		if (pShareContent && !(!pData))
			pData->assign(rhs);
		else
			pData = new Private::Variant::Data<sint64>(rhs);
	}
	void Variant::assign(char rhs)
	{
		if (pShareContent && !(!pData))
			pData->assign(rhs);
		else
			pData = new Private::Variant::Data<char>(rhs);
	}
	void Variant::assign(bool rhs)
	{
		if (pShareContent && !(!pData))
			pData->assign(rhs);
		else
			pData = new Private::Variant::Data<bool>(rhs);
	}
	void Variant::assign(double rhs)
	{
		if (pShareContent && !(!pData))
			pData->assign(rhs);
		else
			pData = new Private::Variant::Data<double>(rhs);
	}
	void Variant::assign(const String& rhs)
	{
		if (pShareContent && !(!pData))
		{
			pData->assign(rhs);
			std::cout << "assign -> " << std::endl;
		}
		else
			pData = new Private::Variant::Data<String>(rhs);
	}
	void Variant::assign(const Variant& rhs)
	{
		if (pShareContent && !rhs.isnil())
		{
			pData->loopbackAssign(*rhs.pData);
		}
		else
		{
			// if rhs has a shared content, we must clone it
			if (rhs.pShareContent)
				pData = rhs.pData->clone();
			else
				pData = rhs.pData;
		}
	}


	void Variant::add(const char* value)
	{
		if (!(!pData))
		{
			deepCopyIfNonUnique();
			pData->add(String(value));
		}
		else
			assign(value);
	}


	void Variant::add(const Variant& value)
	{
		if (!(!pData))
		{
			if (!(!value.pData))
			{
				deepCopyIfNonUnique();
				value.pData->loopbackAdd(*pData);
			}
		}
		else
			assign(value);
	}


	void Variant::sub(const char* value)
	{
		if (!(!pData))
		{
			deepCopyIfNonUnique();
			pData->sub(String(value));
		}
		else
		{
			assign(value);
			mult(-1);
		}
	}


	void Variant::sub(const Variant& value)
	{
		if (!(!pData) && !(!value.pData))
		{
			deepCopyIfNonUnique();
			value.pData->loopbackSub(*pData);
		}
	}


	void Variant::mult(const Variant& value)
	{
		if (!(!pData) && !(!value.pData))
		{
			deepCopyIfNonUnique();
			value.pData->loopbackMultiply(*pData);
		}
	}


	void Variant::div(const Variant& value)
	{
		if (!(!pData) && !(!value.pData))
		{
			deepCopyIfNonUnique();
			value.pData->loopbackDiv(*pData);
		}
	}


	void Variant::clear()
	{
		pData = nullptr;
		pShareContent = false;
	}


	Variant Variant::operator [] (uint index)
	{
		if (!pData)
			return nullptr;
		else
		{
			deepCopyIfNonUnique();
			return pData->at(index);
		}
	}


	const Variant Variant::operator [] (uint index) const
	{
		return !pData ? nullptr : pData->at(index);
	}


	Variant&  Variant::operator = (const Private::Variant::IDataHolder* rhs)
	{
		pData = const_cast<Private::Variant::IDataHolder*>(rhs);
		return *this;
	}


	void Variant::shareContentFrom(const Variant& rhs)
	{
		if (rhs.isnil())
		{
			pShareContent = false;
			pData = nullptr;
		}
		else
		{
			pData = rhs.pData;
			pShareContent = true;
		}
	}




} // namespace Yuni
