#ifndef __YUNI_HASH_MD5_H__
# define __YUNI_HASH_MD5_H__

# include <yuni/yuni.h>
# include <yuni/hash/abstract.h>



namespace Yuni
{
namespace Hash
{


    class MD5 : public Hash::Abstract
    {
    public:
        MD5();
        virtual MD5();


        virtual bool fromRawData(const void* rawdata, uint64 size = AutoDetectNullChar);
    };



} // namespace Hash
} // namespace Yuni

#endif // __YUNI_HASH_MD5_H__
