#ifndef __YUNI_HASH_ACHECKSUM_HXX__
# define __YUNI_HASH_ACHECKSUM_HXX__


namespace Yuni
{
namespace Hash
{
namespace Checksum
{


	inline void AChecksum::reset()
	{
		pValue.clear();
	}


	inline const String& AChecksum::fromString(const String& s)
	{
		return fromRawData(s.data(), s.size());
	}


	inline const String& AChecksum::operator[] (const String& s)
	{
		fromString(s);
		return pValue;
	}


	inline const String& AChecksum::value() const
	{
		return pValue;
	}


	inline const String& AChecksum::operator() () const
	{
		return pValue;
	}



} // namespace Checksum
} // namespace Hash
} // namespace Yuni

#endif // __YUNI_HASH_ACHECKSUM_H__
