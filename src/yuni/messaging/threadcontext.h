#ifndef __YUNI_MESSAGING_THREAD_CONTEXT_H__
# define __YUNI_MESSAGING_THREAD_CONTEXT_H__

# include "../yuni.h"
# include "../core/smartptr.h"


namespace Yuni
{
namespace Messaging
{

	/*!
	** \brief Schema for API methods
	**
	** A schema is some kink of namespace, where methods will belong
	*/
	class YUNI_DECL Context final
	{
	public:
		//! The most suitable smart pointer
		typedef SmartPtr<Protocol> Ptr;


	public:
		/*!
		** \brief Default constructor
		*/
		Context();

		//! Clear all internal variables
		void clear();

		//! Reduce memory usage by internal variables if necessary,
		// usefull for some memory-hungry apps
		void autoshrink();


	public:
		//! Parameters
		KeyValueStore params;
		//! User data pointer
		void* userdata;

		//! String preallocated for various usage (text with small size, < 6Ko)
		// to reduce memory usage, the internal memory of this variable will automatically
		// be wipe out if using more than 6KiB
		String text;
		//! Clob for various uses (text from medium to large size)
		// to reduce memory usage, the internal memory of this variable will automatically
		// be wipe out if using more than 5MiB
		Clob clob;

		//! Name of the method invoked
		AnyString method;
		//! Schema of the method invoked
		AnyString schema;

		//! Http status
		uint httpStatus;

		//! Remote port of the current connection
		uint remotePort;

		//! Buffer reused by transports for generating a response
		// However, it can be safely used by the method invoked
		Clob buffer;


	private:
		template<uint MaxSize, class StringT> void AutoShrink(StringT& variable);

	}; // class ThreadContext





} // namespace Messaging
} // namespace Yuni

# include "threadcontext.hxx"

#endif // __YUNI_MESSAGING_THREAD_CONTEXT_H__
