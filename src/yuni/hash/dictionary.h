#ifndef __YUNI_HASH_DICTIONARY_H__
# define __YUNI_HASH_DICTIONARY_H__

# include <yuni/yuni.h>
# include <yuni/hash/table.h>
# include <yuni/string.h>


namespace Yuni
{
namespace Hash
{


    /*! \class Hash::Dictionary
    **
    ** \brief Associative container where the key is merely a string
    **
    ** \code
    ** Yuni::Hash::Dictionary<int> months;
    **
    ** months["january"] = 31;
    ** months["february"] = 28;
    ** months["march"] = 31;
    ** months["april"] = 30;
    ** months["may"] = 31;
    ** months["june"] = 30;
    ** months["july"] = 31;
    ** months["august"] = 31;
    ** months["september"] = 30;
    ** months["october"] = 31;
    ** months["november"] = 30;
    ** months["december"] = 31;
    **
    ** std::cout << "september -> " << months["september"] << std::endl;
    ** std::cout << "december  -> " << months["december"] << std::endl;
    ** \endcode
    */
    template<typename V>
    class Dictionary : public Table<String, V>
    {
    public:
        //! \name Constructors & Destructor
        //@{
        //! Default constructor
        Dictionary() : Table<String, V>() {}
        //! Copy constructor
        Dictionary(const Dictionary& c) : Table<String, V>(c) {}
        //! Destructor
        virtual ~Dictionary() {Table<String, V>::clear();}
        //@}

    }; // class Hash::Dictionary


    template<>
    class Dictionary<String> : public Table<String, String>
    {
    public:
        //! \name Constructors & Destructor
        //@{
        //! Default constructor
        Dictionary() : Table<String, String>() {}
        //! Copy constructor
        Dictionary(const Dictionary& c) : Table<String, String>(c) {}
        //! Destructor
        virtual ~Dictionary() {Table<String, String>::clear();}
        //@}

        //! Read the value of a key as a string
        String toString(const String& key, const String& defvalue = "") const;

        //! Read the value of a key as a string
        bool toBool(const String& key, const bool defvalue = false) const;

        //! Read the value of a key as a string
        float toFloat(const String& key, const float defvalue = 0.0f) const;
        //! Read the value of a key as a string
        double toDouble(const String& key, const double defvalue = 0.0f) const;


        //! Read the value of a key as a signed int 8 bits
        sint8 toInt8(const String& key, const sint8 defvalue = 0) const;
        //! Read the value of a key as a signed int 16 bits
        sint16 toInt16(const String& key, const sint16 defvalue = 0) const;
        //! Read the value of a key as a signed int 32 bits
        sint32 toInt32(const String& key, const sint32 defvalue = 0) const;
        //! Read the value of a key as a signed int 64 bits
        sint64 toInt64(const String& key, const sint64 defvalue = 0) const;
        //! Read the value of a key as a unsigned int 8 bits
        uint8 toUInt8(const String& key, const uint8 defvalue = 0) const;
        //! Read the value of a key as a unsigned int 16 bits
        uint16 toUInt16(const String& key, const uint16 defvalue = 0) const;
        //! Read the value of a key as a unsigned int 32 bits
        uint32 toUInt32(const String& key, const uint32 defvalue = 0) const;
        //! Read the value of a key as a unsigned int 64 bits
        uint64 toUInt64(const String& key, const uint64 defvalue = 0) const;

    }; // class Hash::Dictionary<String>


} // namespace Hash
} // namespace Yuni


# include <yuni/hash/dictionary.hxx>

#endif // __YUNI_HASH_DICTIONARY_H__

