#ifndef __YUNI_NET_MESSAGING_PROTOCOL_H__
# define __YUNI_NET_MESSAGING_PROTOCOL_H__

# include "api/fwd.h"
# include "api/methods.h"


namespace Yuni
{
namespace Net
{
namespace Messaging
{

	class Protocol final
	{
	public:
		//! The most suitable smart pointer
		typedef SmartPtr<Protocol> Ptr;

	public:
		//! All methods
		API::Methods methods;

	}; // class Protocol





} // namespace Messaging
} // namespace Net
} // namespace Yuni

#endif // __YUNI_NET_MESSAGING_PROTOCOL_H__
