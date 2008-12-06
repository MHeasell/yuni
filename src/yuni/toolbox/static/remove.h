#ifndef __YUNI_TOOLBOX_STATIC_REMOVE_H__
# define __YUNI_TOOLBOX_STATIC_REMOVE_H__


namespace Yuni
{
namespace Static
{

/*!
** \brief Remove some part about a single type
*/
namespace Remove
{

	//! \name Reference
	//@{
	//! Remove the reference of a type (* or &)
	template <typename T> struct Reference { typedef T Type; };
	template <typename T> struct Reference<T&> { typedef T Type; };
	template <typename T> struct Reference<T*> { typedef T Type; };
	template <typename T> struct Reference<const T*> { typedef const T Type; };
	template <typename T> struct Reference<const T&> { typedef const T Type; };
	//@}

	//! \name Const
	//@{
	//! Remove the "Const" part of a type
	template <typename T> struct Const { typedef T Type; };
	template <typename T> struct Const<const T> { typedef T Type; };
	//@}

	template <typename T> struct All
	{
		typedef typename Remove::Const<typename Remove::Reference<T>::Type>::Type Type;
	};


} // namespace Remove

} // namespace Static
} // namespaec Yuni



#endif // __YUNI_TOOLBOX_STATIC_REMOVE_H__
