#ifndef __YUNI_NET_MESSAGE_API_METHOD_HXX__
# define __YUNI_NET_MESSAGE_API_METHOD_HXX__


namespace Yuni
{
namespace Net
{
namespace Messaging
{
namespace API
{

	inline const String& Method::name() const
	{
		return pName;
	}


	inline const String& Method::brief() const
	{
		return pBrief;
	}


	inline Method& Method::brief(const AnyString& text)
	{
		pBrief = text;
		return *this;
	}


	template<class StringT>
	inline Method& Method::option(const StringT& key, const AnyString& value)
	{
		pOptions[(pTmp = key)] = value;
		return *this;
	}


	template<class StringT>
	inline const String& Method::option(const StringT& key) const
	{
		return pOptions[(pTmp = key)];
	}




} // namespace API
} // namespace Messaging
} // namespace Net
} // namespace Yuni

#endif // __YUNI_NET_MESSAGE_API_METHOD_HXX__
