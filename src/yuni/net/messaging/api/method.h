#ifndef __YUNI_NET_MESSAGE_API_METHOD_H__
# define __YUNI_NET_MESSAGE_API_METHOD_H__

# include "../../../yuni.h"
# include "fwd.h"
# include "../../../core/string.h"
# include "../../../core/dictionary.h"
# include "../../../core/bind.h"
# include "../message.h"
# include "../threadcontext.h"


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
		/*!
		** \brief Callback when a method is invoked
		**
		** C-Style callbacks are used for performance reasons. std::function or
		** Yuni::Bind should not be used. Anyway, using thread-context related data
		** should be encouraged instead of shared data between all treads.
		*/
		typedef void (* Callback) (Net::Messaging::ThreadContext&, Net::Messaging::Message&);

		class Parameter
		{
		public:
			typedef Dictionary<String,Parameter>::Hash  Hash;
		public:
			//! Name of the parameter
			String name;
			//! Brief
			String brief;
			//! Default value
			String defvalue;
		};

	public:
		//! \name Constructor & Destructor
		//@{
		//! Default constructor
		Method();
		//@}

		//! \name General informations about the method
		//@{
		/*!
		** \brief Get the name of the method
		*/
		const String& name() const;

		//! Get the brief
		const String& brief() const;
		//! Set the brief
		Method& brief(const AnyString& text);
		//@}

		//! \name Parameters
		//@{
		//! Add a parameter
		Method& param(const AnyString& name, const AnyString& brief);
		//! Add a parameter, with a default value
		Method& param(const AnyString& name, const AnyString& brief, const AnyString& defvalue);
		//! Get all parameters
		const Parameter::Hash& params() const;
		//@}

		//! \name Options
		//@{
		//! Set an option
		Method& option(const AnyString& key, const AnyString& value);
		const String& option(const AnyString& key) const;
		//@}

		//! \name Callback invoker
		//@{
		/*!
		** \brief Set the callback to invoke when the method is invocated
		**
		** The method will not be used by transports if a callback
		** is not provided.
		*/
		Method& invoke(Callback callback);
		//! Get the callback
		Callback invoke() const;
		//@}

		//! \name Memory
		//@{
		//! Reduce the memory consumption as much as possible
		void shrinkMemory();
		//@}


	private:
		//! Name of the method
		String pName;
		//! Brief
		String pBrief;
		//! Options
		mutable KeyValueStore pOptions;
		//! Parameters
		Parameter::Hash pParams;
		//! Callback to invoke
		Callback pCallback;

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
