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

	template<class T>
	struct InternalType
	{
		enum { value = Yuni::Variant::tNil };
	};

	template<> struct InternalType<bool>   { enum { value = Yuni::Variant::tBool }; };
	template<> struct InternalType<char>   { enum { value = Yuni::Variant::tChar }; };
	template<> struct InternalType<sint32> { enum { value = Yuni::Variant::tInt32 }; };
	template<> struct InternalType<sint64> { enum { value = Yuni::Variant::tInt64 }; };
	template<> struct InternalType<uint32> { enum { value = Yuni::Variant::tUInt32 }; };
	template<> struct InternalType<uint64> { enum { value = Yuni::Variant::tUInt64 }; };
	template<> struct InternalType<String> { enum { value = Yuni::Variant::tString }; };



	/*!
	** \brief Abstract container for variant data.
	*/
	class IDataHolder : public Yuni::Policy::SingleThreaded<IDataHolder>
	{
	public:
		//! Threading policy
		typedef Yuni::Policy::SingleThreaded<IDataHolder>  ThreadingPolicy;
		//! The most suitable smart pointer to this object
		typedef IDataHolderPtr  Ptr;
		//! Vector
		typedef std::vector<Ptr>  Vector;

	public:
		//! Constructor
		IDataHolder() {}

		//! Destructor
		virtual ~IDataHolder() {}

		//! Converts the data to the type T.
		template<class T> T to() const;
		//! Converts the data to the type T.
		template<class T> bool to(T& out) const;

		//! Internal data type
		virtual Yuni::Variant::InnerType type() const = 0;

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
		virtual void assignList(const IDataHolder::Vector&) = 0;
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
		virtual void addList(const IDataHolder::Vector&) = 0;
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

		//! is equals to uint32
		virtual bool isEquals(uint32 n) const = 0;
		//! is equals to sint32
		virtual bool isEquals(sint32 n) const = 0;
		//! is equals to uint64
		virtual bool isEquals(uint64 n) const = 0;
		//! is equals to sint64
		virtual bool isEquals(sint64 n) const = 0;
		//! is equals to double
		virtual bool isEquals(double n) const = 0;
		//! is equals to bool
		virtual bool isEquals(bool n) const = 0;
		//! is equals to char
		virtual bool isEquals(char n) const = 0;
		//! is equals to string
		virtual bool isEquals(const String& n) const = 0;

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
		//! is equal variant
		virtual bool loopbackIsEquals(IDataHolder& dataholder) const = 0;
		//@}


		//! \name Method invocation
		//@{
		//! Method invokation, with no parameter
		virtual IDataHolder* invoke(const String& name);
		//! Method invokation, with 1 parameter
		virtual IDataHolder* invoke(const String& name, IDataHolder* a1);
		//! Method invokation, with 2 parameters
		virtual IDataHolder* invoke(const String& name, IDataHolder* a1, IDataHolder* a2);
		//! Method invokation, with 3 parameters
		virtual IDataHolder* invoke(const String& name, IDataHolder* a1, IDataHolder* a2, IDataHolder* a3);
		//! Method invokation, with 4 parameters
		virtual IDataHolder* invoke(const String& name, IDataHolder* a1, IDataHolder* a2, IDataHolder* a3, IDataHolder* a4);
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
	** \brief Data Converter interface (Interface)
	*/
	class IDataConverter
	{
	public:
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
		virtual bool convertFrom(const IDataHolder::Vector& v) = 0;
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

	template<class T>
	struct Converter<IDataHolder::Ptr, T>
	{
		static bool Value(const IDataHolder::Ptr& /*from*/, T& /*to*/)
		{
			return false;
		}
	};

	template<>
	struct Converter<IDataHolder::Ptr, String>
	{
		static bool Value(const IDataHolder::Ptr& from, String& to)
		{
			if (!from)
				to += "(nil)";
			else
				to += from->to<String>();
			return true;
		}
	};

	template<class From>
	struct Converter<From, String>
	{
		static bool Value(const From& from, String& to)
		{
			to.append(from);
			return true;
		}
	};


	template<class TargetType>
	struct DataConverterEvent
	{
		static void ListBegin(TargetType&) {}
		static void ListSeparator(TargetType&) {}
		static void ListEnd(TargetType&) {}
	};

	template<>
	struct DataConverterEvent<String>
	{
		static void ListBegin(String& out) { out += '[';}
		static void ListSeparator(String& out) { out += ", ";}
		static void ListEnd(String& out) {out += ']';}
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
		{ return Converter<sint64,TargetType>::Value(v, result); }

		virtual bool convertFrom(uint64 v)
		{ return Converter<uint64, TargetType>::Value(v, result); }

		virtual bool convertFrom(double v)
		{ return Converter<double,TargetType>::Value(v, result); }

		virtual bool convertFrom(const String& v)
		{ result = v.to<TargetType>(); return true; }

		virtual bool convertFrom(const IDataHolder::Vector& v)
		{
			DataConverterEvent<TargetType>::ListBegin(result);
			switch (v.size())
			{
				case 0:
					break;
				case 1:
					Converter<IDataHolder::Ptr,TargetType>::Value(v[0], result);
					break;
				default:
					Converter<IDataHolder::Ptr,TargetType>::Value(v[0], result);
					for (uint i = 1; i != v.size(); ++i)
					{
						DataConverterEvent<TargetType>::ListSeparator(result);
						Converter<IDataHolder::Ptr,TargetType>::Value(v[i], result);
					}
					break;
			}
			DataConverterEvent<TargetType>::ListEnd(result);
			return true;
		}

	public:
		//! The conversion Result
		TargetType result;

	}; // class DataConverter





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

		virtual Yuni::Variant::InnerType type() const {return (Yuni::Variant::InnerType) InternalType<T>::value;}

		virtual void clear() { pValue = T(); }

		virtual void assignList(const IDataHolder::Vector&) {}
		virtual void assign(uint32 n) { pValue = (T) n; }
		virtual void assign(sint32 n) { pValue = (T) n; }
		virtual void assign(uint64 n) { pValue = (T) n; }
		virtual void assign(sint64 n) { pValue = (T) n; }
		virtual void assign(double n) { pValue = (T) n; }
		virtual void assign(const String& n) { pValue = n.to<T>(); }
		virtual void assign(bool n) { pValue = (T) n; }
		virtual void assign(char n) { pValue = (T) n; }

		virtual void addList(const IDataHolder::Vector&) {}
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
		virtual void mult(char n) { pValue *= (T) n; }
		virtual void mult(const String& n) { pValue *= n.to<T>(); }

		virtual void div(uint32 n) { pValue /= (T) n; }
		virtual void div(sint32 n) { pValue /= (T) n; }
		virtual void div(uint64 n) { pValue /= (T) n; }
		virtual void div(sint64 n) { pValue /= (T) n; }
		virtual void div(double n) { pValue /= (T) n; }
		virtual void div(bool) { /* do nothing*/ }
		virtual void div(char n) { pValue /= (T) n; }
		virtual void div(const String& n) { pValue /= n.to<T>(); }

		virtual bool isEquals(uint32 n) const {return Math::Equals(pValue, (T) n);}
		virtual bool isEquals(sint32 n) const {return Math::Equals(pValue, (T) n);}
		virtual bool isEquals(uint64 n) const {return Math::Equals(pValue, (T) n);}
		virtual bool isEquals(sint64 n) const {return Math::Equals(pValue, (T) n);}
		virtual bool isEquals(double n) const {return Math::Equals(pValue, (T) n);}
		virtual bool isEquals(bool n) const {return Math::Equals(pValue, (T) n);}
		virtual bool isEquals(char n) const {return Math::Equals(pValue, (T) n);}
		virtual bool isEquals(const String& n) const {return Math::Equals(pValue, n.to<T>());}

		virtual void loopbackAssign(IDataHolder& dataholder) const {dataholder.assign(pValue);}
		virtual void loopbackAdd(IDataHolder& dataholder) const {dataholder.add(pValue);}
		virtual void loopbackMultiply(IDataHolder& dataholder) const {dataholder.mult(pValue);}
		virtual void loopbackSub(IDataHolder& dataholder) const {dataholder.sub(pValue);}
		virtual void loopbackDiv(IDataHolder& dataholder) const {dataholder.div(pValue);}
		virtual bool loopbackIsEquals(IDataHolder& dataholder) const {return dataholder.isEquals(pValue);}

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

		virtual Yuni::Variant::InnerType type() const {return Yuni::Variant::tChar;}

		virtual void clear() { pValue = '\0'; }

		virtual void assignList(const IDataHolder::Vector&) {}
		virtual void assign(uint32 n) { pValue = (T) n; }
		virtual void assign(sint32 n) { pValue = (T) n; }
		virtual void assign(uint64 n) { pValue = (T) n; }
		virtual void assign(sint64 n) { pValue = (T) n; }
		virtual void assign(double n) { pValue = (T) n; }
		virtual void assign(const String& n) { pValue = n.to<T>(); }
		virtual void assign(bool n) { pValue = (T) n; }
		virtual void assign(char n) { pValue = (T) n; }

		virtual void addList(const IDataHolder::Vector&) {}
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

		virtual bool isEquals(uint32 n) const {return pValue == (T) n;}
		virtual bool isEquals(sint32 n) const {return pValue == (T) n;}
		virtual bool isEquals(uint64 n) const {return pValue == (T) n;}
		virtual bool isEquals(sint64 n) const {return pValue == (T) n;}
		virtual bool isEquals(double n) const {return Math::Equals(pValue, (T) n);}
		virtual bool isEquals(bool n) const {return pValue == (T) n;}
		virtual bool isEquals(char n) const {return pValue == (T) n;}
		virtual bool isEquals(const String& n) const {return n.size() == 1 and n[0] == pValue;}

		virtual void loopbackAssign(IDataHolder& dataholder) const {dataholder.assign((char)pValue);}
		virtual void loopbackAdd(IDataHolder& dataholder) const {dataholder.add((char)pValue);}
		virtual void loopbackMultiply(IDataHolder& dataholder) const {dataholder.mult((char)pValue);}
		virtual void loopbackSub(IDataHolder& dataholder) const {dataholder.sub((char)pValue);}
		virtual void loopbackDiv(IDataHolder& dataholder) const {dataholder.div((char)pValue);}
		virtual bool loopbackIsEquals(IDataHolder& dataholder) const {return dataholder.isEquals((char)pValue);};

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

		virtual Yuni::Variant::InnerType type() const {return Yuni::Variant::tBool;}

		virtual void clear() { pValue = false; }

		virtual void assignList(const IDataHolder::Vector&) {}
		virtual void assign(sint32 n) { pValue = (n != 0); }
		virtual void assign(uint32 n) { pValue = (n != 0); }
		virtual void assign(sint64 n) { pValue = (n != 0); }
		virtual void assign(uint64 n) { pValue = (n != 0); }
		virtual void assign(double n) { pValue = not Math::Zero(n); }
		virtual void assign(const String& n) { pValue = n.to<T>(); }
		virtual void assign(bool n) { pValue = n; }
		virtual void assign(char n) { pValue = (n != 0); }

		virtual void addList(const IDataHolder::Vector&) {}
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

		virtual void mult(uint32 n) { if (!n) pValue = false; }
		virtual void mult(sint32 n) { if (!n) pValue = false; }
		virtual void mult(uint64 n) { if (!n) pValue = false; }
		virtual void mult(sint64 n) { if (!n) pValue = false; }
		virtual void mult(double n) { if (Math::Zero(n)) pValue = false; }
		virtual void mult(bool) { /* do nothing*/ }
		virtual void mult(char n) { if (!n) pValue = false; }
		virtual void mult(const String& n) { if (!n.to<bool>()) pValue = false; }

		virtual void div(uint32) { }
		virtual void div(sint32) { }
		virtual void div(uint64) { }
		virtual void div(sint64) { }
		virtual void div(double) { }
		virtual void div(bool) { /* do nothing*/ }
		virtual void div(char) { }
		virtual void div(const String&) { }

		virtual bool isEquals(uint32 n) const {return pValue == (n != 0);}
		virtual bool isEquals(sint32 n) const {return pValue == (n != 0);}
		virtual bool isEquals(uint64 n) const {return pValue == (n != 0);}
		virtual bool isEquals(sint64 n) const {return pValue == (n != 0);}
		virtual bool isEquals(double n) const {return Math::Equals<double>((double)pValue, n);}
		virtual bool isEquals(bool n) const {return pValue == n;}
		virtual bool isEquals(char n) const {return pValue == (n != '\0');}
		virtual bool isEquals(const String& n) const {return pValue == n.to<T>();}

		virtual void loopbackAssign(IDataHolder& dataholder) const {dataholder.assign(pValue);}
		virtual void loopbackAdd(IDataHolder& dataholder) const {dataholder.add(pValue);}
		virtual void loopbackMultiply(IDataHolder& dataholder) const {dataholder.mult(pValue);}
		virtual void loopbackSub(IDataHolder& dataholder) const {dataholder.sub(pValue);}
		virtual void loopbackDiv(IDataHolder& dataholder) const {dataholder.div(pValue);}
		virtual bool loopbackIsEquals(IDataHolder& dataholder) const {return dataholder.isEquals(pValue);};

	private:
		//! The real data element.
		T pValue;

	}; // class Data






} // namespace Variant
} // namespace Private
} // namespace Yuni

#include "dataholder.hxx"

#endif /* !__YUNI_CORE_VARIANT_VARIANT_DATAHOLDER_H__ */
