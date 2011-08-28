
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
		uuid_generate(pValue.cstring);
		# else
		# endif
	}


	void UUID::writeToCString(char* cstring) const
	{
		assert(cstring && "invalid pointer");
		# ifndef YUNI_OS_WINDOWS
		uuid_unparse(pValue.cstring, cstring);
		# else
		# endif
	}


	bool UUID::initializeFromCString(const char* cstring)
	{
		# ifndef YUNI_OS_WINDOWS
		// Why uuid_parse takes a char* and not a const char* ??
		return !uuid_parse(const_cast<char*>(cstring), pValue.cstring);
		# else
		return false;
		# endif
	}



	bool UUID::null() const
	{
		return !pValue.n32[0] && !pValue.n32[1] && !pValue.n32[2] && !pValue.n32[3];
	}

	
	void UUID::clear()
	{
		pValue.n32[0] = 0;
		pValue.n32[1] = 0;
		pValue.n32[2] = 0;
		pValue.n32[3] = 0;
	}


	UUID::UUID()
	{
		pValue.n32[0] = 0;
		pValue.n32[1] = 0;
		pValue.n32[2] = 0;
		pValue.n32[3] = 0;
	}


	UUID::UUID(const UUID& rhs)
	{
		pValue.n32[0] = rhs.pValue.n32[0];
		pValue.n32[1] = rhs.pValue.n32[1];
		pValue.n32[2] = rhs.pValue.n32[2];
		pValue.n32[3] = rhs.pValue.n32[3];
	}


	UUID::UUID(Flag flag)
	{
		switch (flag)
		{
			case fGenerate: generate(); break;
			case fNull: clear(); break;
		}
	}



	UUID& UUID::operator = (const UUID& rhs)
	{
		pValue.n32[0] = rhs.pValue.n32[0];
		pValue.n32[1] = rhs.pValue.n32[1];
		pValue.n32[2] = rhs.pValue.n32[2];
		pValue.n32[3] = rhs.pValue.n32[3];
		return *this;
	}


	bool UUID::operator == (const UUID& rhs) const
	{
		return (pValue.n32[0] == rhs.pValue.n32[0])
			&& (pValue.n32[1] == rhs.pValue.n32[1])
			&& (pValue.n32[2] == rhs.pValue.n32[2])
			&& (pValue.n32[3] == rhs.pValue.n32[3]);
	}


	bool UUID::operator != (const UUID& rhs) const
	{
		return (pValue.n32[0] != rhs.pValue.n32[0])
			|| (pValue.n32[1] != rhs.pValue.n32[1])
			|| (pValue.n32[2] != rhs.pValue.n32[2])
			|| (pValue.n32[3] != rhs.pValue.n32[3]);
	}


	bool UUID::operator < (const UUID& rhs) const
	{
		return pValue.n32[3] < rhs.pValue.n32[3]
			&& pValue.n32[2] < rhs.pValue.n32[2]
			&& pValue.n32[1] < rhs.pValue.n32[1]
			&& pValue.n32[0] < rhs.pValue.n32[0];
	}



} // namespace Yuni



std::ostream& operator << (std::ostream& out, const Yuni::UUID& rhs)
{
	char cstring[37];
	Yuni::Private::UUID::Helper::WriteToCString(cstring, rhs);
	out.write(cstring, 36);
	return out;
}



