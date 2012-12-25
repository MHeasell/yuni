#ifndef __YUNI_NET_MESSAGE_API_METHOD_H__
# define __YUNI_NET_MESSAGE_API_METHOD_H__

# include "../../../yuni.h"
# include "fwd.h"
# include "../../../core/string.h"
# include "../../../core/dictionary.h"


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
		typedef Dictionary<String, Method>::Hash  MethodDictionary;

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
		//@}


	private:
		//! Name of the method
		String pName;
		//! Brief
		String pBrief;
		//! Options
		Dictionary<String,String>::Hash pOptions;

		//! Temporary string
		String pTmp;
		// Our friend !
		friend class Methods;

	}; // class Method




} // namespace API
} // namespace Messaging
} // namespace Net
} // namespace Yuni

# include "method.hxx"

#endif // __YUNI_NET_MESSAGE_API_METHOD_H__
