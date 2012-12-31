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

	/*!
	** \brief Schema for API methods
	**
	** A schema is some kink of namespace, where methods will belong
	*/
	class YUNI_DECL Schema final
	{
	public:
		//! The most suitable smart pointer
		typedef SmartPtr<Protocol> Ptr;
		//! Container for schemas
		typedef Dictionary<String, Schema>::Hash  Hash;


	public:
		//! Reduce the memory consumption as much as possible
		void shrinkMemory();

	public:
		//! All methods
		API::Methods methods;

	}; // class Protocol




} // namespace Messaging
} // namespace Net
} // namespace Yuni

# include "schema.hxx"

#endif // __YUNI_NET_MESSAGING_API_SCHEMA_H__
