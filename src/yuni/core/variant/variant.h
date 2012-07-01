#ifndef __YUNI_CORE_VARIANT_VARIANT_H__
# define __YUNI_CORE_VARIANT_VARIANT_H__

# include "../../yuni.h"
# include "../string.h"
# include "../static/remove.h"
# include "dataholder/dataholder.h"
# include "dataholder/string.h"



namespace Yuni
{

	/*!
	** \brief Variant type implementation.
	**
	** This is an implementation of Variants that handles
	** a limited range of types (classical ones), but that
	** can make automagic conversions between them, if such
	** a conversion is possible.
	**
	** It differs from Any, which can handle almost any type
	** (with the notable exception of arrays), but cannot
	** automatically convert from a type to another.
	**
	** How to use:
	** \code
	** Variant v = 12;
	**
	** std::cout << v.to<float>() << std::endl;
	** std::cout << v.to<String>() << std::endl;
	** \endcode
	**
	** \ingroup Core
	*/
	class YUNI_DECL Variant
	{
	public:
		template<class T>
		struct New
		{
			//! Instanciate a new variant
			static Variant Instance();
			//! Instanciate a new variant with array support
			static Variant Array();
		};

	public:
		//! \name Constructors
		//@{
		//! Constructs an empty Variant
		Variant();
		//! Constructs a copy of an existing Variant.
		Variant(const Variant& rhs);
		//! Constructs from a string
		Variant(const char* rhs);
		//! Constructs a Variant based on an existing variable of simple type.
		template<class T> Variant(const T& rhs);
		//! Constructs from a dataholder
		Variant(const Private::Variant::IDataHolder* rhs);
		//! Constructs from a dataholder
		Variant(Private::Variant::IDataHolder* rhs);
		//! Constructor from nullptr
		Variant(const NullPtr&);

		//! Destructor
		~Variant() {}
		//@}


		//! \name Alteration methods
		//@{
		//! Assignment from an existing Variant
		void assign(const Variant& rhs);
		//! Assignment from standard type (uint32)
		void assign(uint32 rhs);
		//! Assignment from standard type (sint32)
		void assign(sint32 rhs);
		//! Assignment from standard type (uint64)
		void assign(uint64 rhs);
		//! Assignment from standard type (sint64)
		void assign(sint64 rhs);
		//! Assignment from standard type (char)
		void assign(char rhs);
		//! Assignment from standard type (bool)
		void assign(bool rhs);
		//! Assignment from standard type (double)
		void assign(double rhs);
		//! Assignment from standard type (string)
		void assign(const String& rhs);
		//! Assignment from standard type (string)
		void assign(const char* rhs);

		//! operator + (variant)
		void add(const Variant& value);
		//! operator add (string)
		void add(const char* value);
		//! operator +
		template<class T> void add(const T& value);

		//! operator * (variant)
		void sub(const Variant& value);
		//! operator * (string)
		void sub(const char* value);
		//! operator *
		template<class T> void sub(const T& value);

		//! operator + (variant)
		void div(const Variant& value);
		//! operator add (string)
		void div(const char* value);
		//! operator +
		template<class T> void div(const T& value);

		//! operator * (variant)
		void mult(const Variant& value);
		//! operator * (string)
		void mult(const char* value);
		//! operator *
		template<class T> void mult(const T& value);

		//! Resets the Variant to an empty one.
		void clear();

		/*!
		** \brief Share content with another variant
		*/
		void shareContentFrom(const Variant& rhs);
		/*!
		** \brief Revoke reference sharing
		*/
		void shareContentFrom(const NullPtr&);
		//@}


		//! \name Method invocation
		//@{
		/*!
		** \brief Invoke method
		*/
		Variant invoke(const String& methodname);
		//@}


		//! \name Information methods
		//@{
		//! Returns true if the Variant is empty.
		bool empty() const;
		//! Get if empty
		bool isnil() const;
		//@}


		//! \name Operator overloads
		//@{
		//! operator =
		Variant&  operator = (const Variant& rhs);
		//! operator =
		template<class T> Variant&  operator = (const T& rhs);
		//! operator =
		Variant&  operator = (const Private::Variant::IDataHolder* rhs);
		//! operator =
		Variant&  operator = (Private::Variant::IDataHolder* rhs);
		//! operator nullptr
		Variant&  operator = (const NullPtr&);
		//! operator +=
		template<class T> Variant& operator += (const T& rhs);
		//! operator -=
		template<class T> Variant& operator -= (const T& rhs);
		//! operator *=
		template<class T> Variant& operator *= (const T& rhs);
		//! operator /=
		template<class T> Variant& operator /= (const T& rhs);
		//! operator []
		Variant operator [] (uint index);
		const Variant operator [] (uint index) const;
		//@}


		//! \name Retrieval methods
		//@{
		template<class T> T to() const;
		//@}


	private:
		//! Perform a deep copy if the pointer is non unique
		void deepCopyIfNonUnique();

	private:
		//! Pointer to storage object
		Private::Variant::IDataHolder::Ptr pData;
		//! Flag to know if the content is currently shared
		bool pShareContent;

	}; // class Variant






} // namespace Yuni

# include "variant.hxx"

#endif // __YUNI_CORE_VARIANT_VARIANT_H__
