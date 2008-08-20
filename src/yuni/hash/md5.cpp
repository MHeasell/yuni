
#include <yuni/hash/md5.h>


namespace Yuni
{
namespace Hash
{

    MD5::MD5()
        :Hash::Abstract()
    {}

    MD5::~MD5()
    {}


    bool MD5::fromRawData(const void* rawdata, uint64 size)
    {
        pValue.clear();
        if (NULL == rawdata)
            return true;
        if (AutoDetectNullChar == size)
            size = strlen((const char*) rawdata);
        if (0 == size)
            return true;
        return true;
    }

} // namespace Hash
} // namespace Yuni


