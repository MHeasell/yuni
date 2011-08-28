#ifndef __YUNI_UUID_UUID_HXX__
# define __YUNI_UUID_UUID_HXX__


namespace Yuni
{

	template<class StringT>
	inline UUID::UUID(const StringT& string)
	{
		if (!assign(string))
			clear();
	}

	inline bool UUID::operator ! () const
	{
		return null();
	}


	template<class StringT>
	bool UUID::assign(const StringT& string)
	{
		YUNI_STATIC_ASSERT(Extension::IntoCString<StringT>::valid, InvalidString);
		const char* cstr = Traits::CString<StringT>::Perform(string);
		const unsigned int length = Traits::Length<StringT,unsigned int>::Value(string);

		if (length >= 36)
		{
			if (Extension::IntoCString<StringT>::zeroTerminated)
			{
				if (initializeFromCString(cstr))
					return true;
			}
			else
			{
				char buffer[37];
				for (unsigned int i = 0; i != 36; ++i)
					buffer[i] = cstr[i];
				buffer[36] = '\0';
				if (initializeFromCString(buffer))
					return true;
			}
		}
		return false;
	}


	template<class StringT>
	inline UUID& UUID::operator = (const StringT& string)
	{
		if (!assign(string))
			clear();
		return *this;
	}


} // namespace Yuni


namespace Yuni
{
namespace Private
{
namespace UUID
{

	class Helper
	{
	public:
		static void WriteToCString(char* cstr, const Yuni::UUID& uuid)
		{
			uuid.writeToCString(cstr);
		}
	};


} // namespace UUID
} // namespace Private
} // namespace Yuni

namespace Yuni
{
namespace Extension
{
namespace CustomString
{

	template<class CustomStringT>
	class Append<CustomStringT, Yuni::UUID>
	{
	public:
		static void Perform(CustomStringT& s, const Yuni::UUID& rhs)
		{
			const unsigned int currentLength = s.size();
			s.resize(s.size() + 37); // 36 + 1 zero-terminated
			Yuni::Private::UUID::Helper::WriteToCString((char*)s.data() + currentLength, rhs);
			s.removeLast();
		}
	};


	template<>
	class Into<Yuni::UUID>
	{
	public:
		typedef Yuni::UUID TargetType;
		enum { valid = 1 };

		template<class StringT> static bool Perform(const StringT& s, TargetType& out)
		{
			return out.assign(s);
		}

		template<class StringT> static TargetType Perform(const StringT& s)
		{
			return TargetType(s);
		}


	};

		
} // namespace CustomString
} // namespace Extension
} // namespace Yuni



// ostream
std::ostream& operator << (std::ostream& out, const Yuni::UUID& rhs);


#endif // __YUNI_UUID_UUID_HXX__
