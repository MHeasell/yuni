#ifndef __YUNI_TOOLBOX_STRING_STRING_HXX__
# define __YUNI_TOOLBOX_STRING_STRING_HXX__


namespace Yuni
{


	template<template<class,class> class U, class Type, class Alloc>
	void String::append(const U<Type,Alloc>& list, const String& sep, const unsigned int max)
	{
		unsigned int count = 0;
		typename U<Type,Alloc>::const_iterator end = list.end();
		for (typename U<Type,Alloc>::const_iterator i = list.begin(); i != end && count < max; ++i)
		{
			if (count)
				this->append(sep);
			*this << *i;
			++count;
		}
	}
	

	template<template<class,class> class U, class Type, class Alloc>
	void String::append(const U<Type,Alloc>& list, const String& sep, const String& enclosure, const unsigned int max)
	{
		unsigned int count = 0;
		typename U<Type,Alloc>::const_iterator end = list.end();
		for (typename U<Type,Alloc>::const_iterator i = list.begin(); i != end && count < max; ++i)
		{
			if (count)
				this->append(sep);
			*this << enclosure << *i << enclosure;
			++count;
		}
	}
	



	template<typename U>
	U String::to() const
	{
		YUNI_STATIC_ASSERT(false, ThisTypeIsNotImplemented);
	}

	template<typename U>
	void String::to(U&) const
	{
		YUNI_STATIC_ASSERT(false, ThisTypeIsNotImplemented);
	}

	template<> inline bool String::to<bool>() const {return this->toBool();}
	template<> inline float String::to<float>() const {return this->toFloat();}
	template<> inline double String::to<double>() const {return this->toDouble();}
	template<> inline sint8  String::to<sint8>() const {return this->toInt8();}
	template<> inline sint16 String::to<sint16>() const {return this->toInt16();}
	template<> inline sint32 String::to<sint32>() const {return this->toInt32();}
	template<> inline sint64 String::to<sint64>() const {return this->toInt64();}
	template<> inline uint8  String::to<uint8>() const {return this->toUInt8();}
	template<> inline uint16 String::to<uint16>() const {return this->toUInt16();}
	template<> inline uint32 String::to<uint32>() const {return this->toUInt32();}
	template<> inline uint64 String::to<uint64>() const {return this->toUInt64();}
	template<> inline String String::to<String>() const {return *this;}

	template<> inline void String::to<bool>(bool& u) const {u = this->toBool();}
	template<> inline void String::to<float>(float& u) const {u = this->toFloat();}
	template<> inline void String::to<double>(double& u) const {u = this->toDouble();}
	template<> inline void String::to<sint8>(sint8& u) const {u = this->toInt8();}
	template<> inline void String::to<sint16>(sint16& u) const {u = this->toInt16();}
	template<> inline void String::to<sint32>(sint32& u) const {u = this->toInt32();}
	template<> inline void String::to<sint64>(sint64& u) const {u = this->toInt64();}
	template<> inline void String::to<uint8>(uint8& u) const {u = this->toUInt8();}
	template<> inline void String::to<uint16>(uint16& u) const {u = this->toUInt16();}
	template<> inline void String::to<uint32>(uint32& u) const {u = this->toUInt32();}
	template<> inline void String::to<uint64>(uint64& u) const {u = this->toUInt64();}
	template<> inline void String::to<String>(String& u) const {u = *this;}




	template<template<class,class> class U, class Type, class Alloc>
	const String&
	String::split(U<Type,Alloc>& out, const String& sep, const bool emptyBefore) const
	{
		// Empty the container
		if (emptyBefore)
			out.clear();
		// String empty
		if (!this->empty())
		{
			String::Index indx = 0;
			while (true)
			{
				const String::Index newIndx = this->find_first_of(sep, indx);
				const String::Size len = newIndx - indx;
				if (len)
				{
					const String segment(*this, indx, len);
					if (!segment.empty())
						out.push_back(segment.to<Type>());
				}
				if (String::npos == newIndx)
					return *this;
				indx = newIndx + 1;
			}
		}
		return *this;
	}




} // namespace Yuni




//! \name Operator overload for stream printing
//@{

template<template<class,class> class U, class Type, class Alloc>
inline std::ostream& operator << (std::ostream& out, const U<Type,Alloc>& list)
{
	bool notFirst = false;
	typename U<Type,Alloc>::const_iterator end = list.end();
	for (typename U<Type,Alloc>::const_iterator i = list.begin(); i != end; ++i)
	{
		if (notFirst)
			out << ", ";
		else
			notFirst = true;
		out << *i;
	}
	return out;
}

//@}


#endif // __YUNI_TOOLBOX_STRING_STRING_HXX__
