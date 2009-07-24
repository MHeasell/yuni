#ifndef __YUNI_CORE_SYSTEM_NULLPTR_H__
# define __YUNI_CORE_SYSTEM_NULLPTR_H__


namespace Yuni
{

	/*!
	** \brief C++ Idioms/nullptr
	**
	** \see proposal (N2431)
	*/
	const class NullPtr
	{
	public:
		//! Convertible to any type of null non-member
		template<class T> operator T*() const
		{
			return 0;
		}

		/*!
		** \brief Any type of null member pointer
		** \note In gcc 4.1.1 compiler that does not recognize the comparison of
		** nullptr with point to member function.
		*/
		template<class C, class T> operator T C::*() const
		{
			return 0;
		}

	private:
		void operator&() const;  // Can't take address of nullptr

	} nullptr = {};





	//! Type for a default behavior / policy
	struct Default {};

	//! Absence Option
	struct None {};




} // namespace Yuni

#endif // __YUNI_CORE_SYSTEM_NULLPTR_H__
