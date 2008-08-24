#ifndef __YUNI_HASH_KEY_H__
# define __YUNI_HASH_KEY_H__

# include <yuni/yuni.h>
# include <yuni/string.h>
# include <yuni/hash/std.hashmap.h>



namespace Yuni
{
namespace Hash
{


    class Key
    {
    public:
        //! Default Constructor
        Key() : pID(0) {}
        //! Constructor with a given unique ID
        Key(const size_t i) : pID(i) {}

        /*!
        ** \brief Get the unique ID
        */
        const size_t uid() const {return pID;}

    protected:
        size_t pID;

    }; // class Hash::Key


} // namespace Hash
} // namespace Yuni



# ifdef YUNI_OS_GNU_HASH_MAP
namespace __gnu_cxx
# else
namespace stdext
# endif
{

    template<>
    class hash<Yuni::Hash::Key>
    {
    public:
        size_t operator()(const Yuni::Hash::Key& __s) const
        { return __s.uid(); }
    };


    template <>
    class hash<Yuni::String>
    {
    public:
        size_t operator()(const Yuni::String& str) const
        {
            hash<char const *> h;
            return (h(str.c_str()));
        }
    };

} // namespace YuniSTLExt


#endif // __YUNI_HASH_KEY_H__
