#ifndef __YUNI_NET_MESSAGING_THREAD_CONTEXT_H__
# define __YUNI_NET_MESSAGING_THREAD_CONTEXT_H__

# include "../../yuni.h"
# include "../../core/smartptr.h"


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
	class YUNI_DECL ThreadContext final
	{
	public:
		//! The most suitable smart pointer
		typedef SmartPtr<Protocol> Ptr;


	public:
		/*!
		** \brief Default constructor
		*/
		ThreadContext();

		//! Clear all internal variables
		void clear();

	public:
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

	}; // class ThreadContext




} // namespace Messaging
} // namespace Net
} // namespace Yuni

# include "threadcontext.hxx"

#endif // __YUNI_NET_MESSAGING_THREAD_CONTEXT_H__
