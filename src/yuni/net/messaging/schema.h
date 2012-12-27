#ifndef __YUNI_NET_MESSAGING_API_SCHEMA_H__
# define __YUNI_NET_MESSAGING_API_SCHEMA_H__

# include "../../yuni.h"
# include "../../core/dictionary.h"


namespace Yuni
{
namespace Net
{
namespace Messaging
{

	class YUNI_DECL Schema final
	{
	public:
		//! The most suitable smart pointer
		typedef SmartPtr<Protocol> Ptr;
		//! Container for schemas
		typedef Dictionary<String, Schema>::Hash  Hash;

	public:
		//! All methods
		API::Methods methods;

	}; // class Protocol




} // namespace Messaging
} // namespace Net
} // namespace Yuni


#endif // __YUNI_NET_MESSAGING_API_SCHEMA_H__
