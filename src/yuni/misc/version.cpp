
#include <yuni/misc/version.h>

namespace Yuni
{


    void Version::InternalLib(Version& v)
    {
        v.hi(0);
        v.lo(1);
        v.revision(0);
        v.author("The Yuni Team");
        v.webUrl("http://www.libyuni.org");
    }


    Version::Version()
        :pHi(0), pLo(0), pRevision(0), pAuthor(), pWebUrl()
    {}

    Version::Version(const int h, const int l, const int r)
        :pHi(h), pLo(l), pRevision(r), pAuthor(), pWebUrl()
    {}


    Version::Version(const Version& c)
        :pHi(c.pHi), pLo(c.pLo), pRevision(c.pRevision), pAuthor(c.pAuthor), pWebUrl(c.pWebUrl)
    {}

    void Version::hi(const int h)
    {
        pHi = (h < 0) ? 0 : h;
    }

    void Version::lo(const int l)
    {
        pLo = (l < 0) ? 0 : l;
    }

    void Version::revision(const int r)
    {
        pRevision = (r < 0) ? 0 : r;
    }

    void Version::author(const String& s)
    {
        pAuthor = s;
    }

    void Version::webUrl(const String& s)
    {
        pWebUrl = s;
    }

    bool Version::isLessThan(const Version& rhs) const
    {
        if (pHi < rhs.pHi)
            return true;
        if (pHi == rhs.pHi)
        {
            if (pLo < rhs.pLo)
                return true;
            if (pLo == rhs.pLo)
                return pRevision < rhs.pRevision;
        }
        return false;
    }

    bool Version::isGreaterThan(const Version& rhs) const
    {
        if (pHi > rhs.pHi)
            return true;
        if (pHi == rhs.pHi)
        {
            if (pLo > rhs.pLo)
                return true;
            if (pLo == rhs.pLo)
                return pRevision > rhs.pRevision;
        }
        return false;
    }


    bool Version::isEqualTo(const Version& rhs) const
    {
        return (rhs.pHi == pHi) && (rhs.pLo == pLo) && (rhs.pRevision == pRevision);
    }


    String Version::toString() const
    {
        String r;
        r << pHi << "." << pLo;
        if (pRevision)
            r << " (r" << pRevision << ")";
        return r;
    }



} // namespace Yuni
