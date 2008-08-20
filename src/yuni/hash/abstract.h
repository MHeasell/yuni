#ifndef __YUNI_HASH_ABSTRACT_H__
# define __YUNI_HASH_ABSTRACT_H__

# include <yuni/yuni.h>
# include <yuni/string.h>


namespace Yuni
{
namespace Hash
{

    class Abstract
    {
    public:
        Abstract();
        virtual ~Abstract();

        /*!
        ** \brief Reset the hash value
        */
        void reset() {pValue.clear();}

        /*!
        ** \brief Compute the hash from a string
        **
        ** \param s The string
        ** \return True if the operation has succeeded, False otherwise
        */
        bool fromString(const String& s) {return fromRawData(s.c_str(), s.size());}

        /*!
        ** \brief Compute the hash from raw data
        **
        ** \param rawdata The buffer
        ** \param size The size of the buffer. AutoDetectNullChar will make an autodetection of the length
        ** \return True if the operation has succeeded, False otherwise
        */
        virtual bool fromRawData(const void* rawdata, uint64 size = AutoDetectNullChar) = 0;

        /*!
        ** \brief Get the hash value
        */
        const String& value() const {return pValue;}
        //! Get the hash value
        const String& operator() () const {return pValue;}

        /*!
        ** \brief Compute the hash value from a string and returns it
        **
        ** \param s The string to compute
        ** \return The hash value
        */
        const String& operator[] (const String& s) {fromString(s);return pValue;}

    protected:
        //! The hash value
        String pValue;
    };


} // namespace Hash
} // namespace Yuni

#endif // __YUNI_HASH_ABSTRACT_H__
