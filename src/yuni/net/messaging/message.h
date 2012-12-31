#ifndef __YUNI_NET_MESSAGING_MESSAGE_H__
# define __YUNI_NET_MESSAGING_MESSAGE_H__

# include "../../yuni.h"
# include "../../core/dictionary.h"


namespace Yuni
{
namespace Net
{
namespace Messaging
{

	class Message final
	{
	public:
		Message() :
			httpStatus(200)
		{}

	public:
		// returned message
		Clob body;
		// HTTP Error
		uint httpStatus;
		// parameters
		KeyValueStore params;
		// Name of the method invoked
		AnyString method;
		// Schema
		AnyString schema;
		//! Method request (GET, POST, DELETE, PUT)
		AnyString httpMethod;

		//! Temporary string for computing container access (to avoid memory reallocation)
		String key;

	}; // class Message




} // namespace Messaging
} // namespace Net
} // namespace Yuni

#endif // __YUNI_NET_MESSAGING_MESSAGE_H__
