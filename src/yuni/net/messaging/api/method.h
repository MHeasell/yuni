#ifndef __YUNI_NET_MESSAGE_API_METHOD_H__
# define __YUNI_NET_MESSAGE_API_METHOD_H__

# include "../../../yuni.h"
# include "fwd.h"
# include "../../../core/string.h"
# include "../../../core/dictionary.h"
# include "../../../core/bind.h"
# include "../message.h"


namespace Yuni
{
namespace Net
{
namespace Messaging
{
namespace API
{

	class YUNI_DECL Method final
	{
	public:
		//! Hash table
		typedef Dictionary<String, Method>::Hash  Hash;
		typedef Bind<void (Net::Messaging::Message&)>  Callback;

	public:
		/*!
		** \brief Get the name of the method
		*/
		const String& name() const;


		//! \name Brief
		//@{
		//! Get the brief
		const String& brief() const;
		//! Set the brief
		Method& brief(const AnyString& text);
		//@}


		//! \name Options
		//@{
		//! Set an option
		template<class StringT> Method& option(const StringT& key, const AnyString& value);
		template<class StringT> const String& option(const StringT& key) const;
		//@}


	public:
		/*!
		** \brief Callback to invoker
		*/
		Callback callback;


	private:
		//! Name of the method
		String pName;
		//! Brief
		String pBrief;
		//! Options
		mutable KeyValueStore pOptions;

		//! Temporary string
		mutable String pTmp;
		// Our friend !
		friend class Methods;

	}; // class Method




} // namespace API
} // namespace Messaging
} // namespace Net
} // namespace Yuni

# include "method.hxx"

#endif // __YUNI_NET_MESSAGE_API_METHOD_H__
