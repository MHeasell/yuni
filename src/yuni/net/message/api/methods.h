#ifndef __YUNI_NET_MESSAGING_API_METHODS_H__
# define __YUNI_NET_MESSAGING_API_METHODS_H__

# include "../../../yuni.h"
# include "fwd.h"
# include "method.h"


namespace Yuni
{
namespace Net
{
namespace Messaging
{
namespace API
{

	//! All methods
	class Methods final
	{
	public:
		/*!
		 ** \brief Add a new method
		 */
		Method& add(const AnyString& name);

		/*!
		** \brief Remove all methods
		*/
		void clear();

	private:
		//! methods
		Method::MethodDictionary pMethods;

	}; // class Methods




} // namespace API
} // namespace Messaging
} // namespace Net
} // namespace Yuni

# include "methods.hxx"

#endif // __YUNI_NET_MESSAGING_API_METHODS_H__
