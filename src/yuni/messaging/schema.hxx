#ifndef __YUNI_MESSAGING_API_SCHEMA_HXX__
# define __YUNI_MESSAGING_API_SCHEMA_HXX__


namespace Yuni
{
namespace Messaging
{

	inline void Schema::shrinkMemory()
	{
		methods.shrinkMemory();
	}




} // namespace Messaging
} // namespace Yuni

#endif // __YUNI_MESSAGING_API_SCHEMA_HXX__
