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

	inline Method::Method() :
		pCallback(nullptr)
	{}


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


	inline Method& Method::invoke(Callback callback)
	{
		pCallback = callback;
		return *this;
	}


	inline Method::Callback Method::invoke() const
	{
		return pCallback;
	}


	inline Method& Method::option(const AnyString& key, const AnyString& value)
	{
		pOptions[(pTmp = key)] = value;
		return *this;
	}


	inline const String& Method::option(const AnyString& key) const
	{
		return pOptions[(pTmp = key)];
	}


	inline const Method::Parameter::Hash& Method::params() const
	{
		return pParams;
	}




} // namespace API
} // namespace Messaging
} // namespace Net
} // namespace Yuni

#endif // __YUNI_NET_MESSAGE_API_METHOD_HXX__
