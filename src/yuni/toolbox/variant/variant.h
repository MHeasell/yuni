#ifndef __YUNI_TOOLBOX_VARIANT_VARIANT_H__
#define __YUNI_TOOLBOX_VARIANT_VARIANT_H__

# include "../../yuni.h"
# include "../exceptions.h"
# include "../string.h"
# include "variant.private.h"

namespace Yuni
{

	/*!
	** \brief Classic Variant type implementation.
	**
	** This is a relatively classic, yet (i hope) fast implementation of
	** a Variant type.
	**
	** How to use:
	** \code
	**
	** Variant v(3.14);
	**
	** if (v.is<double>())
	**   // Be sure to check the type before, otherwise Variant will throw an exception.
	**   std::cout << v.cast<double>();
	**
	** \endcode
	*/
	class Variant
	{
	public:

		//! \name Constructors
		//@{

		//! Copy of an existing variable
		template <typename T>
		Variant(const T& source);

		//! Copy of an existing const C string
		Variant(const char* source)
		{ initFromCString(source); }

		//! Copy of an existing const C wide string
		Variant(const wchar_t* source)
		{ initFromCString(source); }

		//! Copy of an existing const C string
		Variant(char* source)
		{ initFromCString(source); }

		//! Copy of an existing const C wide string
		Variant(wchar_t* source)
		{ initFromCString(source); }

		//! Empty constructor
		Variant();

		//! Copy constructor
		Variant(const Variant& rhs);

		//! Destructor
		~Variant();


		//@}

		//! \name Alteration methods
		//@{

		/*!
		** \brief Assignment from another Variant
		** \param[in] rhs The Variant to assign from
		** \return This Variant
		*/
		Variant& assign(const Variant& rhs);

		/*!
		** \brief Assignment from any object, with any storage type.
		** \param[in] rhs The object to assign from
		** \return This Variant
		*/
		template <typename T, typename U>
		Variant& assign(const T& rhs);

		/*!
		** \brief Specialized assign for simple types.
		*/
		template <typename T>
		Variant& assign(const T& rhs)
		{ return assign<T, T>(rhs); }

		/*!
		** \brief Specialized assign for C Strings.
		*/
		Variant& assign(const char* rhs)
		{ return assign<const char*, String>(rhs); }

		/*!
		** \brief Specialized assign for C Wide Strings.
		*/
		Variant& assign(const wchar_t* rhs)
		{ return assign<const wchar_t*, String>(rhs); }

		/*!
		** \brief Assignment operator for convenience
		*/
		template <typename T>
		Variant& operator=(T const& rhs)
		{ return assign(rhs); }

		/*!
		** \brief Swaps a variant with another
		** \param[in][out] one Variant 1
		** \param[in][out] other Variant 2
		*/
		static void swap(Variant& one, Variant& other);

		/*!
		** \brief Resets the Variant to an empty state.
		*/
		void reset();

		//@}

		//! \name Information methods
		//@{

		/*!
		** \brief Returns the type_info of the held variable.
		**
		** Can be used to compare with typeid(MyType).
		*/
		const std::type_info& type() const
		{ return pTable->type(); }


		/*!
		** \brief Returns true if the object is of the specified type
		*/
		template <typename T>
		bool is() const
		{ return type() == typeid(T); }


		/*!
		** \brief Checks if the variant has been assigned a value.
		** \return True if the variant contains no value.
		*/
		bool empty() const
		{ return pTable == Private::Variant::Table<Private::Variant::Empty>::get(); }

		//@}

		//! \name Retrieval methods
		//@{

		/*!
		** \brief Casts the Variant to the T type. Throws a Yuni::Exceptions::BadCast
		** if not possible.
		** \return A T object.
		*/
		template <typename T>
		const T& to() const;

		//@}

	private:

		//! Special initializer for C Strings copys
		template <typename T>
		void initFromCString(T source);

	private:
		//! Static function pointer table storage
		Private::Variant::FunctionPtrTable * pTable;

		//! Object storage.
		void* pObject;
	};

} // namespace Yuni

# include "variant.hxx"

#endif /* !__YUNI_TOOLBOX_VARIANT_H__ */


