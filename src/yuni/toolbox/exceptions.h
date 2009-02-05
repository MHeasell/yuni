#ifndef __YUNI_TOOLBOX_EXCEPTIONS_H__
#define __YUNI_TOOLBOX_EXCEPTIONS_H__

# include <stdexcept>
# include <typeinfo>

namespace Yuni
{

/*!
** \brief Exceptions thrown by the Yuni framework.
**
** We try to keep these to a minimum, but there's still cases where throwing
** an exception seems the cleanest way to handle certain cases.
*/
namespace Exceptions
{
	/*!
	** \brief Is thrown in case of impossible cast from one type to another.
	** \see Variant
	*/
	struct BadCast : public std::bad_cast
	{
		/*!
		** \brief Constructor
		*/
		BadCast(const std::type_info& src, const std::type_info& dest)
			: from(src.name()), to(dest.name())
		{ }

		/*!
		** \brief Description printed by libstdc++.
		*/
		virtual const char *what() const throw ()
		{
			return "Bad cast";
		}

		/*!
		** \brief Cast source
		*/
		const char* from;

		/*!
		** \brief Cast target
		*/
		const char* to;
	};
} // namespace Exceptions
} // namespace Yuni

#endif /* !__YUNI_TOOLBOX_EXCEPTIONS_H__ */


