#ifndef __YUNI_CORE_VERSION_HXX__
# define __YUNI_CORE_VERSION_HXX__


namespace Yuni
{

	inline Version::Version()
		:hi(0), lo(0), revision(0)
	{}


	inline Version::Version(const int h, const int l)
		:hi(h), lo(l), revision(0)
	{}


	inline Version::Version(const int h, const int l, const int r)
		:hi(h), lo(l), revision(r)
	{}


	inline bool Version::isEqualTo(const Version& rhs) const
	{
		return (rhs.hi == hi) && (rhs.lo == lo) && (rhs.revision == revision);
	}


	inline bool Version::operator <  (const Version& rhs) const
	{
		return isLessThan(rhs);
	}

	inline bool Version::operator <= (const Version& rhs) const
	{
		return isEqualTo(rhs) || isLessThan(rhs);
	}

	inline bool Version::operator >  (const Version& rhs) const
	{
		return isGreaterThan(rhs);
	}

	inline bool Version::operator >= (const Version& rhs) const
	{
		return isEqualTo(rhs) || isGreaterThan(rhs);
	}

	inline bool Version::operator == (const Version& rhs) const
	{
		return isEqualTo(rhs);
	}

	inline bool Version::operator != (const Version& rhs) const
	{
		return !isEqualTo(rhs);
	}



} // namespace Yuni

#endif // __YUNI_CORE_VERSION_HXX__
