#ifndef __YUNI_CORE_VARIANT_VARIANT_DATAHOLDER_H__
# define __YUNI_CORE_VARIANT_VARIANT_DATAHOLDER_H__

# include <sstream>
# include "../../static/types.h"
# include "../../math/math.h"


namespace Yuni
{
namespace Private
{
namespace Variant
{

	/*!
	** \brief Data Converter interface (Interface)
	*/
	struct IDataConverter
	{
		//! Destructor
		virtual ~IDataConverter()
		{}

		//! \name From- converters for base types
		//@{
		virtual bool convertFrom(char v) = 0;
		virtual bool convertFrom(bool v) = 0;
		virtual bool convertFrom(sint32 v) = 0;
		virtual bool convertFrom(uint32 v) = 0;
		virtual bool convertFrom(sint64 v) = 0;
		virtual bool convertFrom(uint64 v) = 0;
		virtual bool convertFrom(double v) = 0;
		virtual bool convertFrom(const String& v) = 0;
		//@}

	}; // class IDataConverter



	/*!
	** \brief The real convertor structure.
	*/
	template<class From, class To>
	struct Converter
	{
		static bool Value(const From& from, To& to)
		{
			to = static_cast<To>(from);
			return true;
		}
	};

	// Specialization to avoid warning from Visual Studio (C4800)
	template<class From>
	struct Converter<From, bool>
	{
		static bool Value(const From& from, bool& to)
		{
			to = Math::Equals(From(), from);
			return true;
		}
	};


	/*!
	** \brief Concrete DataConverter implementation
	*/
	template<class TargetType>
	struct DataConverter : public IDataConverter
	{
	public:
		DataConverter() : result()
		{}

		virtual bool convertFrom(bool v)
		{ return Converter<bool,TargetType>::Value(v, result); }

		virtual bool convertFrom(char v)
		{ return Converter<char,TargetType>::Value(v, result); }

		virtual bool convertFrom(sint32 v)
		{ return Converter<sint32,TargetType>::Value(v, result); }

		virtual bool convertFrom(uint32 v)
		{ return Converter<uint32, TargetType>::Value(v, result); }

		virtual bool convertFrom(sint64 v)
		{ return Converter<sint32,TargetType>::Value(v, result); }

		virtual bool convertFrom(uint64 v)
		{ return Converter<uint32, TargetType>::Value(v, result); }

		virtual bool convertFrom(double v)
		{ return Converter<double,TargetType>::Value(v, result); }

		virtual bool convertFrom(const String& v)
		{ result = v.to<TargetType>(); return true; }

	public:
		//! The conversion Result
		TargetType result;

	}; // class DataConverter



	/*!
	** \brief Abstract container for variant data.
	*/
	class IDataHolder : public Yuni::Policy::SingleThreaded<IDataHolder>
	{
	public:
		//! Threading policy
		typedef Yuni::Policy::SingleThreaded<IDataHolder>  ThreadingPolicy;
		//! The most suitable smart pointer to this object
		typedef Yuni::SmartPtr<IDataHolder, Yuni::Policy::Ownership::COMReferenceCounted>  Ptr;

	public:
		//! Constructor
		IDataHolder() {}

		//! Destructor
		virtual ~IDataHolder() {}

		//! Converts the data to the type T.
		template<class T> T to() const;

		/*!
		** \brief Clear the inner content
		*/
		virtual void clear() = 0;

		/*!
		** \brief Clones the enclosed data
		** \returns A pointer on the new instance
		*/
		virtual IDataHolder* clone() const = 0;


		//! \name Operators
		//@{
		//! operator []
		virtual IDataHolder* at(uint /*index*/) {return nullptr;}
		//! operator [] const
		virtual const IDataHolder* at(uint /*index*/) const {return nullptr;}

		//! assign uint32
		virtual void assign(uint32 n) = 0;
		//! assign sint32
		virtual void assign(sint32 n) = 0;
		//! assign uint64
		virtual void assign(uint64 n) = 0;
		//! assign sint64
		virtual void assign(sint64 n) = 0;
		//! assign double
		virtual void assign(double n) = 0;
		//! assign string
		virtual void assign(const String& n) = 0;
		//! assign bool
		virtual void assign(bool n) = 0;
		//! assign char
		virtual void assign(char n) = 0;

		//! add uint32
		virtual void add(uint32 n) = 0;
		//! add sint32
		virtual void add(sint32 n) = 0;
		//! add uint64
		virtual void add(uint64 n) = 0;
		//! add sint64
		virtual void add(sint64 n) = 0;
		//! add double
		virtual void add(double n) = 0;
		//! add string
		virtual void add(const String& n) = 0;
		//! add bool
		virtual void add(bool n) = 0;
		//! add char
		virtual void add(char n) = 0;

		//! sub uint32
		virtual void sub(uint32 n) = 0;
		//! sub sint32
		virtual void sub(sint32 n) = 0;
		//! sub uint64
		virtual void sub(uint64 n) = 0;
		//! sub sint64
		virtual void sub(sint64 n) = 0;
		//! sub double
		virtual void sub(double n) = 0;
		//! sub string
		virtual void sub(const String& n) = 0;
		//! sub bool
		virtual void sub(bool n) = 0;
		//! sub char
		virtual void sub(char n) = 0;

		//! mult uint32
		virtual void mult(uint32 n) = 0;
		//! mult sint32
		virtual void mult(sint32 n) = 0;
		//! mult uint64
		virtual void mult(uint64 n) = 0;
		//! mult sint64
		virtual void mult(sint64 n) = 0;
		//! mult double
		virtual void mult(double n) = 0;
		//! mult bool
		virtual void mult(bool n) = 0;
		//! mult char
		virtual void mult(char n) = 0;
		//! mult string
		virtual void mult(const String& n) = 0;

		//! div uint32
		virtual void div(uint32 n) = 0;
		//! div sint32
		virtual void div(sint32 n) = 0;
		//! div uint64
		virtual void div(uint64 n) = 0;
		//! div sint64
		virtual void div(sint64 n) = 0;
		//! div double
		virtual void div(double n) = 0;
		//! div bool
		virtual void div(bool n) = 0;
		//! div char
		virtual void div(char n) = 0;
		//! div string
		virtual void div(const String& n) = 0;

		//! add variant
		virtual void loopbackAssign(IDataHolder& dataholder) const = 0;
		//! add variant
		virtual void loopbackAdd(IDataHolder& dataholder) const = 0;
		//! mult variant
		virtual void loopbackMultiply(IDataHolder& dataholder) const = 0;
		//! sub variant
		virtual void loopbackSub(IDataHolder& dataholder) const = 0;
		//! div variant
		virtual void loopbackDiv(IDataHolder& dataholder) const = 0;
		//@}


		//! \name Method invocation
		//@{
		//! Method invokation, with no parameter
		virtual IDataHolder* invoke(const String& /*name*/);
		//! Method invokation, with 1 parameter
		virtual IDataHolder* invoke(const String& /*name*/, IDataHolder* /*a1*/);
		//! Method invokation, with 2 parameters
		virtual IDataHolder* invoke(const String& /*name*/, IDataHolder* /*a1*/, IDataHolder* /*a2*/);
		//! Method invokation, with 3 parameters
		virtual IDataHolder* invoke(const String& /*name*/, IDataHolder* /*a1*/, IDataHolder* /*a2*/, IDataHolder* /*a3*/);
		//! Method invokation, with 4 parameters
		virtual IDataHolder* invoke(const String& /*name*/, IDataHolder* /*a1*/, IDataHolder* /*a2*/, IDataHolder* /*a3*/, IDataHolder* /*a4*/);
		//@}


		//! \name Pointer management
		//@{
		//! Increment the internal reference counter
		void addRef() const;
		//! Decrement the internal reference counter
		void release() const;
		//! Get if the object is an unique reference
		bool unique() const;
		//@}

	protected:
		/*!
		** \brief Runs the conversion using the specified converter.
		** The result of the conversion can be retrieved from
		** the converter itself.
		** \param[in] A reference on an instancied DataConverter<DestinationType>.
		*/
		virtual bool convertUsing(IDataConverter& cvtr) const = 0;

	private:
		mutable Yuni::Atomic::Int<> pRefCount;

	}; // class IDataHolder




	/*!
	** \brief Concrete variant data container
	**
	** This is templated with the real data type.
	*/
	template<class T>
	class Data : public IDataHolder
	{
	public:
		//! Constructor from the variable type
		explicit Data(const T& src) :
			pValue(src)
		{}

		//! Destructor
		virtual ~Data() {}

	protected:
		virtual bool convertUsing(IDataConverter& cvtr) const
		{ return cvtr.convertFrom(pValue); }

		virtual IDataHolder* clone() const
		{ return new Data<T>(pValue); }

		virtual void clear() { pValue = T(); }

		virtual void assign(uint32 n) { pValue = (T) n; }
		virtual void assign(sint32 n) { pValue = (T) n; }
		virtual void assign(uint64 n) { pValue = (T) n; }
		virtual void assign(sint64 n) { pValue = (T) n; }
		virtual void assign(double n) { pValue = (T) n; }
		virtual void assign(const String& n) { pValue = n.to<T>(); }
		virtual void assign(bool n) { pValue = (T) n; }
		virtual void assign(char n) { pValue = (T) n; }

		virtual void add(uint32 n) { pValue += (T) n; }
		virtual void add(sint32 n) { pValue += (T) n; }
		virtual void add(uint64 n) { pValue += (T) n; }
		virtual void add(sint64 n) { pValue += (T) n; }
		virtual void add(double n) { pValue += (T) n; }
		virtual void add(const String& n) { pValue += n.to<T>(); }
		virtual void add(bool n) { pValue += (T) n; }
		virtual void add(char n) { pValue += (T) n; }

		virtual void sub(uint32 n) { pValue -= (T) n; }
		virtual void sub(sint32 n) { pValue -= (T) n; }
		virtual void sub(uint64 n) { pValue -= (T) n; }
		virtual void sub(sint64 n) { pValue -= (T) n; }
		virtual void sub(double n) { pValue -= (T) n; }
		virtual void sub(const String& n) { pValue -= n.to<T>(); }
		virtual void sub(bool n) { pValue -= (T) n; }
		virtual void sub(char n) { pValue -= (T) n; }

		virtual void mult(uint32 n) { pValue *= (T) n; }
		virtual void mult(sint32 n) { pValue *= (T) n; }
		virtual void mult(uint64 n) { pValue *= (T) n; }
		virtual void mult(sint64 n) { pValue *= (T) n; }
		virtual void mult(double n) { pValue *= (T) n; }
		virtual void mult(bool) { /* do nothing*/ }
		virtual void mult(char n) { pValue *= (int)n; }
		virtual void mult(const String& n) { pValue *= n.to<T>(); }

		virtual void div(uint32 n) { pValue /= (T) n; }
		virtual void div(sint32 n) { pValue /= (T) n; }
		virtual void div(uint64 n) { pValue /= (T) n; }
		virtual void div(sint64 n) { pValue /= (T) n; }
		virtual void div(double n) { pValue /= (T) n; }
		virtual void div(bool) { /* do nothing*/ }
		virtual void div(char n) { pValue /= (int)n; }
		virtual void div(const String& n) { pValue /= n.to<T>(); }

		virtual void loopbackAssign(IDataHolder& dataholder) const {dataholder.assign(pValue);}
		virtual void loopbackAdd(IDataHolder& dataholder) const {dataholder.add(pValue);}
		virtual void loopbackMultiply(IDataHolder& dataholder) const {dataholder.mult(pValue);}
		virtual void loopbackSub(IDataHolder& dataholder) const {dataholder.sub(pValue);}
		virtual void loopbackDiv(IDataHolder& dataholder) const {dataholder.div(pValue);}

	private:
		//! The real data element.
		T pValue;

	}; // class Data



	/*!
	** \brief Concrete variant data container (char)
	*/
	template<>
	class Data<char> : public IDataHolder
	{
	public:
		typedef int T;

	public:
		//! Constructor from the variable type
		explicit Data(char src) :
			pValue(src)
		{}

		//! Destructor
		virtual ~Data() {}

	protected:
		virtual bool convertUsing(IDataConverter& cvtr) const
		{ return cvtr.convertFrom(pValue); }

		virtual IDataHolder* clone() const
		{ return new Data<T>(pValue); }

		virtual void clear() { pValue = '\0'; }

		virtual void assign(uint32 n) { pValue = (T) n; }
		virtual void assign(sint32 n) { pValue = (T) n; }
		virtual void assign(uint64 n) { pValue = (T) n; }
		virtual void assign(sint64 n) { pValue = (T) n; }
		virtual void assign(double n) { pValue = (T) n; }
		virtual void assign(const String& n) { pValue = n.to<T>(); }
		virtual void assign(bool n) { pValue = (T) n; }
		virtual void assign(char n) { pValue = (T) n; }

		virtual void add(uint32 n) { pValue += (T) n; }
		virtual void add(sint32 n) { pValue += (T) n; }
		virtual void add(uint64 n) { pValue += (T) n; }
		virtual void add(sint64 n) { pValue += (T) n; }
		virtual void add(double n) { pValue += (T) n; }
		virtual void add(const String& n) { pValue += n.to<T>(); }
		virtual void add(bool n) { pValue += (T) n; }
		virtual void add(char n) { pValue += (T) n; }

		virtual void sub(uint32 n) { pValue -= (T) n; }
		virtual void sub(sint32 n) { pValue -= (T) n; }
		virtual void sub(uint64 n) { pValue -= (T) n; }
		virtual void sub(sint64 n) { pValue -= (T) n; }
		virtual void sub(double n) { pValue -= (T) n; }
		virtual void sub(const String& n) { pValue -= n.to<T>(); }
		virtual void sub(bool n) { pValue -= (T) n; }
		virtual void sub(char n) { pValue -= (T) n; }

		virtual void mult(uint32 n) { pValue *= (T) n; }
		virtual void mult(sint32 n) { pValue *= (T) n; }
		virtual void mult(uint64 n) { pValue *= (T) n; }
		virtual void mult(sint64 n) { pValue *= (T) n; }
		virtual void mult(double n) { pValue *= (T) n; }
		virtual void mult(bool) { /* do nothing*/ }
		virtual void mult(char n) { pValue *= (int)n; }
		virtual void mult(const String& n) { pValue *= n.to<T>(); }

		virtual void div(uint32 n) { pValue /= (T) n; }
		virtual void div(sint32 n) { pValue /= (T) n; }
		virtual void div(uint64 n) { pValue /= (T) n; }
		virtual void div(sint64 n) { pValue /= (T) n; }
		virtual void div(double n) { pValue /= (T) n; }
		virtual void div(bool) { /* do nothing*/ }
		virtual void div(char n) { pValue /= (int)n; }
		virtual void div(const String& n) { pValue /= n.to<T>(); }

		virtual void loopbackAssign(IDataHolder& dataholder) const {dataholder.assign((char)pValue);}
		virtual void loopbackAdd(IDataHolder& dataholder) const {dataholder.add((char)pValue);}
		virtual void loopbackMultiply(IDataHolder& dataholder) const {dataholder.mult((char)pValue);}
		virtual void loopbackSub(IDataHolder& dataholder) const {dataholder.sub((char)pValue);}
		virtual void loopbackDiv(IDataHolder& dataholder) const {dataholder.div((char)pValue);}

	private:
		//! The real data element.
		T pValue;

	}; // class Data


	/*!
	** \brief Concrete variant data container (bool)
	*/
	template<>
	class Data<bool> : public IDataHolder
	{
	public:
		typedef bool T;

	public:
		//! Constructor from the variable type
		explicit Data(bool src) :
			pValue(src)
		{}

		//! Destructor
		virtual ~Data() {}

	protected:
		virtual bool convertUsing(IDataConverter& cvtr) const
		{ return cvtr.convertFrom(pValue); }

		virtual IDataHolder* clone() const
		{ return new Data<T>(pValue); }

		virtual void clear() { pValue = false; }

		virtual void assign(sint32 n) { pValue = (n); }
		virtual void assign(uint32 n) { pValue = (n); }
		virtual void assign(sint64 n) { pValue = (n); }
		virtual void assign(uint64 n) { pValue = (n); }
		virtual void assign(double n) { pValue = not Math::Zero(n); }
		virtual void assign(const String& n) { pValue = n.to<T>(); }
		virtual void assign(bool n) { pValue = n; }
		virtual void assign(char n) { pValue = n; }

		virtual void add(sint32 n) { if (n) pValue = true; }
		virtual void add(uint32 n) { if (n) pValue = true; }
		virtual void add(sint64 n) { if (n) pValue = true; }
		virtual void add(uint64 n) { if (n) pValue = true; }
		virtual void add(double n) { if (not Math::Zero(n)) pValue = true; }
		virtual void add(const String& n) { if (n.to<T>()) pValue = true; }
		virtual void add(bool n) { if (n) pValue = true; }
		virtual void add(char n) { if (n) pValue = true; }

		virtual void sub(sint32 n) { if (n) pValue = false; }
		virtual void sub(uint32 n) { if (n) pValue = false; }
		virtual void sub(sint64 n) { if (n) pValue = false; }
		virtual void sub(uint64 n) { if (n) pValue = false; }
		virtual void sub(double n) { if (not Math::Zero(n)) pValue = false; }
		virtual void sub(const String& n) { if (n.to<T>()) pValue = false; }
		virtual void sub(bool n) { if (n) pValue = false; }
		virtual void sub(char n) { if (n) pValue = false; }

		virtual void mult(uint32 n) { pValue *= (T) n; }
		virtual void mult(sint32 n) { pValue *= (T) n; }
		virtual void mult(uint64 n) { pValue *= (T) n; }
		virtual void mult(sint64 n) { pValue *= (T) n; }
		virtual void mult(double n) { pValue *= (int) n; }
		virtual void mult(bool) { /* do nothing*/ }
		virtual void mult(char n) { pValue *= (int)n; }
		virtual void mult(const String& n) { pValue *= n.to<T>(); }

		virtual void div(uint32 n) { pValue /= (T) n; }
		virtual void div(sint32 n) { pValue /= (T) n; }
		virtual void div(uint64 n) { pValue /= (T) n; }
		virtual void div(sint64 n) { pValue /= (T) n; }
		virtual void div(double n) { pValue /= (int) n; }
		virtual void div(bool) { /* do nothing*/ }
		virtual void div(char n) { pValue /= (int)n; }
		virtual void div(const String& n) { pValue /= n.to<T>(); }

		virtual void loopbackAssign(IDataHolder& dataholder) const {dataholder.assign(pValue);}
		virtual void loopbackAdd(IDataHolder& dataholder) const {dataholder.add(pValue);}
		virtual void loopbackMultiply(IDataHolder& dataholder) const {dataholder.mult(pValue);}
		virtual void loopbackSub(IDataHolder& dataholder) const {dataholder.sub(pValue);}
		virtual void loopbackDiv(IDataHolder& dataholder) const {dataholder.div(pValue);}

	private:
		//! The real data element.
		T pValue;

	}; // class Data






} // namespace Variant
} // namespace Private
} // namespace Yuni

#include "dataholder.hxx"

#endif /* !__YUNI_CORE_VARIANT_VARIANT_DATAHOLDER_H__ */
