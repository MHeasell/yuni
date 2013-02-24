
#include "query.h"


namespace Yuni
{
namespace DBI
{


	Query& Query::parameter(uint index, const AnyString& value)
	{
		return *this;
	}


	Query& Query::variable(const AnyString& name, const AnyString& value)
	{
		return *this;
	}


	bool Query::perform()
	{
		return false;
	}


	Cursor Query::execute()
	{
		return Cursor();
	}





} // namespace DBI
} // namespace Yuni
