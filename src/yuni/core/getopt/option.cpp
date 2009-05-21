
#include "option.h"



namespace Yuni
{
namespace Core
{
namespace GetOpt
{


	AOption::AOption(const String::Char sOpt, const String& lOpt, bool ndValue, const String& comm)
		:pShortName(sOpt), pLongName(lOpt),
		pModified(false),
		pNeedValue(ndValue), pComments(comm)
	{}


	AOption::AOption(const AOption& c)
		:pShortName(c.pShortName), pLongName(c.pLongName),
		pModified(c.pModified),
		pNeedValue(c.pNeedValue), pComments(c.pComments)
	{}



	void AOption::reset()
	{
		pModified = false;
	}


	String AOption::fullNameForHelp()
	{
		String s;
		if (' ' != pShortName)
		{
			s += "-";
			s += pShortName;
			if (!pLongName.empty())
				s += ", ";
			else
			{
				if (pNeedValue)
					s += " <VALUE>";
			}
		}
		else
		{
			if (!pLongName.empty())
				s += "    ";
		}
		if (!pLongName.empty())
		{
			s += "--";
			s += pLongName;
			if (pNeedValue)
				s += "=<VALUE>";
		}
		return s;
	}


	String AOption::bestSuitableName()
	{
		if (!pLongName.empty())
			return String("--") << pLongName;
		return String('-') << pShortName;
	}



} // namespace GetOpt
} // namespace Core
} // namespace GetOpt


