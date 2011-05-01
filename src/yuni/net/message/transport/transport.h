#ifndef __YUNI_NET_MESSAGE_TRANSPORT_TRANSPORT_H__
# define __YUNI_NET_MESSAGE_TRANSPORT_TRANSPORT_H__

# include "../../../yuni.h"
# include "layer.h"
# include "../../../core/string.h"


namespace Yuni
{
namespace Net
{
namespace Message
{
namespace Transport
{


	class ITransport
	{
	public:
		//! The most suitable smart pointer for the class
		typedef SmartPtr<ITransport>  Ptr;

	public:
		ITransport()
		{
		}

		virtual ~ITransport()
		{
		}

	}; // class Transport




} // namespace Transport
} // namespace Server
} // namespace Net
} // namespace Yuni

#endif // __YUNI_NET_MESSAGE_TRANSPORT_TRANSPORT_H__
