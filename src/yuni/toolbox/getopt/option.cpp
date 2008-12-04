#include "option.h"



namespace Yuni
{
namespace ToolBox
{
namespace GetOpt
{


	AOption::AOption(const char sOpt, const String& lOpt, bool ndValue, const String& comm)
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
			return "--" + pLongName;
		return "-" + pShortName;
	}



} // namespace GetOpt
} // namespace ToolBox
} // namespace GetOpt


