#ifndef __YUNI_HASH_TABLE_H__
# define __YUNI_HASH_TABLE_H__

# include <yuni/yuni.h>
# include <yuni/string.h>
# include <ext/hash_fun.h>
# include <ext/hash_map>
# include <yuni/hash/key.h>


namespace Yuni
{
namespace Hash
{


    /*! \class Hash::Table
    **
    ** \brief Unique Associative container
    */
    template<class K, typename V>
    class Table
    {
    public:
        //! An iterator
        typedef typename __gnu_cxx::hash_map< K, V, __gnu_cxx::hash<K> >::iterator  iterator;
        //! A const iterator
        typedef typename __gnu_cxx::hash_map< K, V, __gnu_cxx::hash<K> >::const_iterator  const_iterator;

    public:
        //! \name Constructors & Destructor
        //@{
        //! Default constructor
        Table();
        //! Copy constructor
        Table(const Table& c);
        //! Destructor
        virtual ~Table();
        //@}

        /*!
        ** \brief Get if an entry exists
        **
        ** \param key The key to find
        ** \return True if the key exists, False otherwise
        */
        bool exists(const K& key) const {return pTable.find(key) != pTable.end();}

        /*!
        ** \brief Get/Set an entry
        **
        ** If the entry does not exist, it will be created
        **
        ** \param key The key to get/set
        ** \return The value of the key
        */
        V& operator[] (const K& key) {return pTable[key];}

        /*!
        ** \brief Find a key in the table
        **
        ** \param key The key to find
        ** \return The iterator pointing to the key, end() if not found
        */
        iterator find(const K& key) {return pTable.find(key);}
        const_iterator find(const K& key) const {return pTable.find(key);}

        /*!
        ** \brief Get the value of a key
        **
        ** \param key The key to find
        ** \param defvalue The default value if the key can not be found
        ** \return The value ofthe key, `defvalue` if the key could not be found
        */
        V& value(const K& key, const V& defvalue = V()) const;

        /*!
        ** \brief Get an iterator pointing to the beginning of the table
        */
        iterator begin() {return pTable.begin();}
        const_iterator begin() const {return pTable.begin();}

        /*!
        ** \brief Get an iterator pointing to the end of the table
        */
        iterator end() {return pTable.end();}
        const_iterator end() const {return pTable.end();}

        /*!
        ** \brief Clear the table
        */
        void clear();

        /*!
        ** \brief Erase a single key
        **
        ** \param key The key to find
        ** \return True if the key has been erased, False if not found
        */
        void erase(const K& key);

    private:
        //! The real hash map
        __gnu_cxx::hash_map< K, V, __gnu_cxx::hash<K> >  pTable;

    }; // class Hash::Table




} // namespace Hash
} // namespace Yuni


# include <yuni/hash/table.hxx>

#endif // __YUNI_HASH_TABLE_H__
