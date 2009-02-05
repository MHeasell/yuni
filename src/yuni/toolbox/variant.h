#ifndef __YUNI_TOOLBOX_VARIANT_H__
#define __YUNI_TOOLBOX_VARIANT_H__

# include <iostream>
# include <stdexcept>
# include <typeinfo>
# include <algorithm>

# include "../yuni.h"


namespace Yuni
{
namespace Exceptions
{
	/*!
	** \brief Is thrown in case of bad cast from one type to another.
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

namespace Private
{
namespace Variant
{

	/*!
	** \brief Static function pointer table
	**
	** All the operations done on Variant storage objects are done via
	** the functions currently defined in pTable. Depending on the size of the object,
	** this member may use different approachs to store the data.
	** This function table defines the function pointers to the different operations.
	*/
	struct FunctionPtrTable
	{
		const std::type_info& (*type)();
		void (*staticDelete)(void**);
		void (*clone)(void* const*, void**);
		void (*move)(void* const*, void**);
	};

	/*!
	** \brief Static functions for small objects (smaller than a void *)
	**
	** The goal of this struct is to use pObject as a sort of union
	** to store object smaller than pointer size. Of course, this means that
	** bigger objects can be stored faster if you use 64-bit addresses.
	*/
	template <bool isSmall>
	struct Functions
	{
		template <typename T>
		struct Type
		{
			static const std::type_info& type()
			{
				return typeid(T);
			}

			static void staticDelete(void** object)
			{
				reinterpret_cast<T*>(object)->~T();
			}

			static void clone(void* const* source, void** dest)
			{
				new (dest) T(*reinterpret_cast<T const*>(source));
			}

			static void move(void* const* source, void** dest)
			{
				reinterpret_cast<T*>(dest)->~T();
				*reinterpret_cast<T*>(dest) = *reinterpret_cast<T const*>(source);
			}
		};
	};

	/*!
	** \brief Static functions implementations for big objects (larger than a void *)
	**
	** This implementation stores big objects as normal objects (ie. a pointer to an alloc'ed
	** object in pObject.)
	*/
	template <>
	struct Functions<false>
	{
		template <typename T>
		struct Type
		{
			static const std::type_info& type()
			{
				return typeid(T);
			}

			static void staticDelete(void** object)
			{
				delete(*reinterpret_cast<T**>(object));
			}

			static void clone(void* const* source, void** dest)
			{
				*dest = new T(**reinterpret_cast<T* const*>(source));
			}

			static void move(void* const* source, void** dest)
			{
				(*reinterpret_cast<T**>(dest))->~T();
				**reinterpret_cast<T**>(dest) = **reinterpret_cast<T* const*>(source);
			}
		};
	};

	/*!
	** \brief Structure providing function table for a type.
	**
	** This structure provides a function to get the appropriate function table for
	** a given type in an allegedly sexy way. (like Table<T>::get())
	*/
    template<typename T>
    struct Table
    {
		//! Equals true if the given type is smalled than a pointer.
		static const bool isSmall = sizeof(T) <= sizeof(void*);
      
		/*!
		** \brief Returns a pointer on a static function table
		**
		** The static function table depends on the type and its size.
		** One different function table will be instanciated by type.
		*/
	    static FunctionPtrTable * get()
	    {
		    static FunctionPtrTable staticTable =
			{
				Functions<isSmall>::template Type<T>::type,
				Functions<isSmall>::template Type<T>::staticDelete,
				Functions<isSmall>::template Type<T>::clone,
				Functions<isSmall>::template Type<T>::move
		    };

		    return &staticTable;
	    }
    };
    
	/*!
	** \brief Variant type for an empty Variant.
	*/
    struct Empty {
    };

} // namespace Variant
} // namespace Private

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
	** bool isDouble = v.is<double>();
	**
	** if (isDouble)
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
		Variant(const T& source)
		{
			pTable = Private::Variant::Table<T>::get();
			if (sizeof(T) <= sizeof(void*))
				new (&pObject) T(source);
			else
				pObject = new T(source);
		}

		//! Copy of an existing C string (less-than-ideal, but it works for now.)
		template <int S>
		Variant(char const (&source)[S])
		{
			pTable = Private::Variant::Table<std::string>::get();
			if (sizeof(std::string) <= sizeof(void*))
				new (&pObject) std::string(source);
			else
				pObject = new std::string(source);
		}

		//! Empty constructor
		Variant()
		{
			pTable = Private::Variant::Table<Private::Variant::Empty>::get();
			pObject = NULL;
		}

		//! Copy constructor
		Variant(const Variant& rhs)
		{
			pTable = Private::Variant::Table<Private::Variant::Empty>::get();
			assign(rhs);
		}

		//! Destructor
		~Variant()
		{
			pTable->staticDelete(&pObject);
		}

		//@}

		//! \name Alteration methods
		//@{

		/*!
		** \brief Assignment from another Variant
		** \param[in] rhs The Variant to assign from
		** \return This Variant
		*/
		Variant& assign(const Variant& rhs)
		{
			// Are we copying from the same type (using the same table) ?
			if (pTable == rhs.pTable)
			{ // If so, we can avoid reallocation
				pTable->move(&rhs.pObject, &pObject);
			}
			else
			{
				reset();
				rhs.pTable->clone(&rhs.pObject, &pObject);
				pTable = rhs.pTable;
			}
			return *this;
		}

		/*!
		** \brief Assignment from any object, with any storage type.
		** \param[in] rhs The object to assign from
		** \return This Variant
		*/
		template <typename T, typename U>
		Variant& assign(const T& rhs)
		{
			// Are we copying between the same type of variants ?
			Private::Variant::FunctionPtrTable* rhsTable = Private::Variant::Table<U>::get();

			if (pTable == rhsTable)
			{ // Yes, so we can avoid reallocating, and re-use memory.
				if (sizeof(U) <= sizeof(void*))
					// Create copy on-top of object pointer itself
					new (&pObject) U(rhs);
				else
					// Create copy on-top of the old version
					new (pObject) U(rhs);
			}
			else
			{ // No, this was not the same type.
				reset();
				if (sizeof(U) <= sizeof(void*))
				{
					// Create copy on-top of object pointer itself
					new (&pObject) U(rhs);
					// Update table pointer
					pTable = rhsTable;
				}
				else
				{
					pObject = new U(rhs);
					pTable = rhsTable;
				}
			}
			return *this;
		}

		/*!
		** \brief Specialized assign for simple types.
		*/
		template <typename T>
		Variant& assign(const T& rhs)
		{
			return assign<T, T>(rhs);
		}

		/*!
		** \brief Specialized assign for C Strings. Less than ideal.
		*/
		template <int S>
		Variant& assign(char const (&rhs)[S])
		{
			return assign<char const[S], std::string>(rhs);
		}

		/*!
		** \brief Assignment operator for convenience
		*/
		template <typename T>
		Variant& operator=(T const& rhs)
		{
			return assign(rhs);
		}

		/*!
		** \brief Swaps this variant with another
		*/
		Variant& swap(Variant& other)
		{
			std::swap(pTable, other.pTable);
			std::swap(pObject, other.pObject);
			return *this;
		}

		/*!
		** \brief Resets the Variant to an empty state.
		*/
		void reset()
		{
			if (empty())
				return ;

			pTable->staticDelete(&pObject);
			pTable = Private::Variant::Table<Private::Variant::Empty>::get();
			pObject = NULL;
		}

		//@}

		//! \name Information methods
		//@{

		/*!
		** \brief Returns the type_info of the held variable.
		**
		** Can be used to compare with typeid(MyType).
		*/
		const std::type_info& type() const
		{
			return pTable->type();
		}


		/*!
		** \brief Returns true if the object is of the specified type
		*/
		template <typename T>
		bool is() const
		{
			return type() == typeid(T);
		}


		/*!
		** \brief Checks if the variant has been assigned a value.
		** \return True if the variant contains no value.
		*/
		bool empty() const
		{
			return pTable == Private::Variant::Table<Private::Variant::Empty>::get();
		}



		//@}

		//! \name Retrieval methods
		//@{

		/*!
		** \brief Casts the Variant to the T type. Throws a Yuni::Exceptions::BadCast
		** if not possible.
		** \return A T object.
		*/
		template <typename T>
		const T& cast() const
		{
			if (type() != typeid(T))
				throw Exceptions::BadCast(type(), typeid(T));

			if (sizeof(T) <= sizeof(void*))
				return *reinterpret_cast<T const*>(&pObject);

			return *reinterpret_cast<T const*>(pObject);
		}

		//@}

	private:
		/*!
		** \brief Static function pointer table storage
		*/
		Private::Variant::FunctionPtrTable * pTable;

		/*!
		** \brief Object storage.
		*/
		void* pObject;
	};

} // namespace Yuni

#endif /* !__YUNI_TOOLBOX_VARIANT_H__ */


