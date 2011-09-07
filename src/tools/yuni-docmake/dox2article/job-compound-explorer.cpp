
#include "job-compound-explorer.h"
#include "../logs.h"
#include <yuni/core/system/suspend.h>


namespace Yuni
{
namespace Edalene
{
namespace Dox2Article
{
namespace Job
{


	void CompoundExplorer::Dispatch()
	{
		typedef Compound::Map::iterator iterator;

		logs.info() << "reading class/namespace members";

		// Namespaces
		{
			const iterator end = allSymbols[Compound::kdNamespace].end();
			for (iterator i = allSymbols[Compound::kdNamespace].begin(); i != end; ++i)
			{
				Compound::Ptr& compound = i->second;
				queueService += new CompoundExplorer(compound);
			}
		}
		// Classes
		{
			const iterator end = allSymbols[Compound::kdClass].end();
			for (iterator i = allSymbols[Compound::kdClass].begin(); i != end; ++i)
			{
				Compound::Ptr& compound = i->second;
				queueService += new CompoundExplorer(compound);
			}
		}


		queueService.wait();
		while (!QueueServiceIsEmpty())
			Yuni::SuspendMilliSeconds(200);
	}






	CompoundExplorer::CompoundExplorer(const Compound::Ptr& compound) :
		pCompound(compound)
	{
	}


	CompoundExplorer::~CompoundExplorer()
	{
	}


	void CompoundExplorer::onExecute()
	{
		if (!pCompound)
			return;

		Compound& compound = *pCompound;
		if (!compound.refid)
			return;
	}





} // namespace Job
} // namespace Dox2Article
} // namespace Edalene
} // namespace Yuni

