#ifndef __YUNI_TOOLBOX_EXCEPTIONS_BAD_CAST_H__
# define __YUNI_TOOLBOX_EXCEPTIONS_BAD_CAST_H__

# include <stdexcept>
# include <typeinfo>



namespace Yuni
{
namespace Exceptions
{


	/*!
	** \brief Is thrown in case of impossible cast from one type to another.
	** \ingroup Exceptions
	**
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




#endif // __YUNI_TOOLBOX_EXCEPTIONS_BAD_CAST_H__
