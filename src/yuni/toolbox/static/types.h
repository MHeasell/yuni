#ifndef __YUNI_TOOLBOX_STATIC_TYPES_H__
# define __YUNI_TOOLBOX_STATIC_TYPES_H__

# include "../../yuni.h"


namespace Yuni
{
namespace Static
{
namespace Type
{

	//! \name Fundamental types
	//@{
	/*!
	** \brief Get if a type is fundamental
	*/
	template <typename T> struct IsFundamental
	{
		// Default to No
		enum { Yes = 0, No = 1 };
	};
	//@}


	//! \name Compound types
	//@{
	/*!
	** \brief Determine the compound type
	*/
	template <typename T>
	struct Compound
	{
		enum { IsPointer = 0, IsReference = 0, IsArray = 0, IsPtrMember = 0 };
		typedef T BaseType;
	};
	//@}


	//! \name Comparison
	//@{
	template<typename T, typename U>
	struct AreEqual
	{
		// Two types are not equal by default
		enum { Yes = 0, No = 1 };
	};
	//@}








	//! \name Overloads
	//@{

	// Those types are fundamental for sure
	//
	template <> struct IsFundamental<void> {enum{Yes = 1, No = 0}};
	template <> struct IsFundamental<bool> {enum{Yes = 1, No = 0}};
	template <> struct IsFundamental<char> {enum{Yes = 1, No = 0}};
	template <> struct IsFundamental<unsigned char> {enum{Yes = 1, No = 0}};
	template <> struct IsFundamental<signed char> {enum{Yes = 1, No = 0}};
	template <> struct IsFundamental<wchar_t> {enum{Yes = 1, No = 0}};
	template <> struct IsFundamental<float> {enum{Yes = 1, No = 0}};
	template <> struct IsFundamental<double> {enum{Yes = 1, No = 0}};
	template <> struct IsFundamental<long double> {enum{Yes = 1, No = 0}};
	// Signed int
	template <> struct IsFundamental<sint8> {enum{Yes = 1, No = 0}};
	template <> struct IsFundamental<sint16> {enum{Yes = 1, No = 0}};
	template <> struct IsFundamental<sint32> {enum{Yes = 1, No = 0}};
	template <> struct IsFundamental<sint64> {enum{Yes = 1, No = 0}};
	// Unsigned int
	template <> struct IsFundamental<uint8> {enum{Yes = 1, No = 0}};
	template <> struct IsFundamental<uint16> {enum{Yes = 1, No = 0}};
	template <> struct IsFundamental<uint32> {enum{Yes = 1, No = 0}};
	template <> struct IsFundamental<uint64> {enum{Yes = 1, No = 0}};



	// Specialization for references
	template <typename T>
	struct Compound<T&>
	{
		enum { IsPointer = 0, IsReference = 1, IsArray = 0, IsPtrMember = 0 };
		typedef typename Compound<T>::BaseType BaseType;
	};

	// Specialization for pointers
	template <typename T>
	struct Compound<T*>
	{
		enum { IsPointer = 1, IsReference = 0, IsArray = 0, IsPtrMember = 0 };
		typedef typename Compound<T>::BaseType BaseType;
	};

	// Specialization for empty arrays
	template <typename T>
	struct Compound<T[]>
	{
		enum { IsPointer = 0, IsReference = 0, IsArray = 1, IsPtrMember = 0 };
		typedef typename Compound<T>::BaseType BaseType;
	};

	// Specialization for arrays
	template <typename T, size_t N>
	struct Compound<T[N]>
	{
		enum { IsPointer = 0, IsReference = 0, IsArray = 1, IsPtrMember = 0 };
		typedef typename Compound<T>::BaseType BaseType;
	};

	// Specialization for pointer-to members
	template <typename T, typename C>
	struct Compound<T C::*>
	{
		enum { IsPointer = 0, IsReference = 0, IsArray = 0, IsPtrMember = 1 };
		typedef typename Compound<T>::BaseType BaseType;
	};


	
	template<typename W>
	struct AreEqual<W, W>
	{
		enum { Yes = 1, No = 0 };
	};

	//@} // Overloads


} // namespace Type
} // namespace Static
} // namespace Yuni


#endif // __YUNI_TOOLBOX_STATIC_TYPES_H__
