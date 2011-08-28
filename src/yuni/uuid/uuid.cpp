
#include "uuid.h"
#ifndef YUNI_OS_WINDOWS
# include <uuid/uuid.h>
#else
#endif
#include <cassert>


namespace Yuni
{


	void UUID::generate()
	{
		assert(sizeof(StorageType) == 16 && "Invalid storage size for uuid");

		# ifndef YUNI_OS_WINDOWS
		assert(sizeof(uuid_t) == 16);
		uuid_generate(pValue);
		# else
		# endif
	}


	void UUID::writeToCString(char* cstring) const
	{
		assert(cstring && "invalid pointer");
		# ifndef YUNI_OS_WINDOWS
		uuid_unparse(pValue, cstring);
		# else
		# endif
	}


	bool UUID::initializeFromCString(const char* cstring)
	{
		# ifndef YUNI_OS_WINDOWS
		// Why uuid_parse takes a char* and not a const char* ??
		return !uuid_parse(const_cast<char*>(cstring), pValue);
		# else
		return false;
		# endif
	}


	bool UUID::null() const
	{
		for (unsigned int i = 0; i != 16; ++i)
		{
			if (pValue[i])
				return false;
		}
		return true;
	}


	UUID::UUID()
	{
		for (unsigned int i = 0; i != 16; ++i)
			pValue[0] = 0;
	}


	UUID::UUID(const UUID& rhs)
	{
		for (unsigned int i = 0; i != 16; ++i)
			pValue[i] = rhs.pValue[i];
	}


	void UUID::clear()
	{
		for (unsigned int i = 0; i != 16; ++i)
			pValue[0] = 0;
	}


	UUID& UUID::operator = (const UUID& rhs)
	{
		for (unsigned int i = 0; i != 16; ++i)
			pValue[i] = rhs.pValue[i];
		return *this;
	}



} // namespace Yuni



std::ostream& operator << (std::ostream& out, const Yuni::UUID& rhs)
{
	char cstring[37];
	Yuni::Private::UUID::Helper::WriteToCString(cstring, rhs);
	out.write(cstring, 36);
	return out;
}



