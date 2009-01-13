
#include "script.h"

namespace Yuni
{
namespace Script
{

	AScript::AScript()
	{
		// Nothing to do here for now.
	}

	AScript::~AScript()
	{
		// Nothing to do here for now.
	}

	bool AScript::run()
	{
		return call(NULL, "main");
	}

} // namespace Script
} // namespace Yuni
