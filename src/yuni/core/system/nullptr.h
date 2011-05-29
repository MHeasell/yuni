#ifndef __YUNI_CORE_SYSTEM_NULLPTR_H__
# define __YUNI_CORE_SYSTEM_NULLPTR_H__

# ifdef __cplusplus /* Only with a C++ Compiler */

# ifdef YUNI_HAS_NULLPTR
#	include <cstddef>
# endif



namespace Yuni
{

	# ifdef YUNI_HAS_NULLPTR

	typedef std::nullptr_t NullPtr;

	# else

	/*!
	** \brief C++ Idioms/nullptr
	**
	** \see proposal (N2431)
	*/
	const class NullPtr
	{
	public:
		/*! Convertible to any type of null non-member */
		template<class T> inline operator T*() const
		{
			return 0;
		}

		/*!
		** \brief Any type of null member pointer
		**
		** \note In gcc 4.1.1 compiler that does not recognize the comparison of
		** nullptr with point to member function.
		*/
		template<class C, class T> inline operator T C::*() const
		{
			return 0;
		}

		# if YUNI_OS_GCC_VERSION >= 40400
		template<class T> bool operator == (const T* rhs) const
		{
			return !rhs;
		}

		template<class T> bool operator != (const T* rhs) const
		{
			return (NULL != rhs);
		}
		# endif

	private:
		void operator&() const;  /* Can't take address of nullptr */

	} nullptr = {};


	# endif // nullptr support



} /* namespace Yuni */



# if YUNI_OS_GCC_VERSION >= 40400
template<class T>
inline bool operator == (const T* rhs, const Yuni::NullPtr&)
{
	return !rhs;
}

template<class T>
inline bool operator != (const T* rhs, const Yuni::NullPtr&)
{
	return static_cast<const T*>(NULL) != rhs;
}
# endif


# endif /* C++ Compiler */


#endif /* __YUNI_CORE_SYSTEM_NULLPTR_H__ */
