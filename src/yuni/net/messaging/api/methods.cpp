
#include "methods.h"


namespace Yuni
{
namespace Net
{
namespace Messaging
{
namespace API
{

	Method& Methods::add(const AnyString& name)
	{
		// reference to the method object
		Method& method = pMethods[name];
		method.pName = name;
		return method;
	}





} // namespace API
} // namespace Messaging
} // namespace Net
} // namespace Yuni


