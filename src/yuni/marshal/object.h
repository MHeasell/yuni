#ifndef __YUNI_MARSHAL_OBJECT_H__
# define __YUNI_MARSHAL_OBJECT_H__

# include "../yuni.h"
# include "../core/string.h"
# include <vector>
# include "../core/dictionary.h"


namespace Yuni
{
namespace Marshal
{

	/*!
	** \brief Base object for data serialization
	**
	** This class is a Variant-like structure, but less scalable and faster
	** for small data types.
	** Additionally, this class remains a POD type (no smart pointer or C++ advanced techniques)
	** for being used with malloc / calloc.
	*/
	struct Object final
	{
	public:
		//! Internal type
		enum Type
		{
			//! Nil object
			otNil = 0,
			//! Boolean
			otBool,
			//! Integer
			otInteger,
			//! Double,
			otDouble,
			//! String
			otString,
			//! Array
			otArray,
			//! Dictionary
			otDictionary
		};


		//! Array of object
		typedef std::vector<Object>  InternalArray;
		//! Object mapping
		typedef Dictionary<String, Object>::Hash  InternalTable;

		// \internal for some reasons, the compiler requires to have this type public
		// (does not compile otherwise in object.cpp)
		union InternalDatatype
		{
			//! Value as integer
			sint64 integer;
			//! Value as bool
			bool boolean;
			//! Decimal
			double decimal;
			//! String
			String* string;
			//! Array
			InternalArray* array;
			//! Dictionary
			InternalTable* dictionary;
			//! Largest possible type
			void* biggest;
		};

	public:
		//! \name Constructors & Destructor
		//@{
		Object();
		//! Copy constructor
		Object(const Object& rhs);
		//! Constructor for internal operations
		Object(Type type, InternalDatatype value);
		//! Destructor
		~Object();
		//@}

		//! \name Clean
		//@{
		//! Clear internal variable
		void clear();
		//@}


		//! \name Assign
		//@{
		//! Copy operator
		void assign(const Object& rhs);
		//! assign boolean
		void assign(bool boolean);
		//! assign double
		void assign(double decimal);
		//! assign int
		void assign(int integer);
		//! assign int64
		void assign(sint64 integer);
		//! assign string
		void assign(const AnyString& string);
		//@}


		//! \name Append
		//@{
		//! Append an object
		void append(const Object& rhs);

		//! see append()
		template<class T> void push_back(const T& value);
		//@}


		//! \name Informations about internal data
		//@{
		//! Get the internal type
		Type type() const;

		/*!
		** \brief Get the number of item
		**
		** \return The number of items if an array or a dictionary, 0 if nil, 1 otherwise
		*/
		uint size() const;

		/*!
		** \brief Swap the content of two object
		*/
		void swap(Object& second);
		//@}


		//! \name Import & Export
		//@{
		/*!
		** \brief Dump the content into a JSON structure
		*/
		void toJSON(Clob& out) const;
		//@}


		//! \name Operators
		//@{
		//! Copy operator
		Object& operator = (const Object& rhs);
		//! assign something else
		template<class T> Object& operator = (const T& value);
		//! append
		template<class T> Object& operator += (const T& value);
		//! read/write the value of a given key
		Object& operator [] (const String& key);
		//@}


	private:
		void valueToJSON(Clob& out, uint depth) const;

	private:
		//! Internal data type
		Type pType;
		//! Internal value
		InternalDatatype pValue;

	}; // class Object





} // namespace Marshal
} // namespace Yuni

# include "object.hxx"

#endif // __YUNI_MARSHAL_OBJECT_H__
