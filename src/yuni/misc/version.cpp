
#include <yuni/misc/version.h>

namespace Yuni
{

    Version::Version()
        :pHi(0), pLo(0), pRevision(0), pAuthor(), pWebUrl()
    {}

    Version::Version(const Version& c)
        :pHi(c.pHi), pLo(c.pLo), pRevision(c.pRevision), pAuthor(c.pAuthor), pWebUrl(c.pWebUrl)
    {}

} // namespace Yuni
