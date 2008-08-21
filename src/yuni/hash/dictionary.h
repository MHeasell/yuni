#ifndef __YUNI_HASH_DICTIONARY_H__
# define __YUNI_HASH_DICTIONARY_H__

# include <yuni/yuni.h>
# include <yuni/hash/table.h>


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



} // namespace Hash
} // namespace Yuni

#endif // __YUNI_HASH_DICTIONARY_H__

