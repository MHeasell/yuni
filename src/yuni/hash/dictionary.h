#ifndef __YUNI_HASH_DICTIONARY_H__
# define __YUNI_HASH_DICTIONARY_H__

# include <yuni/yuni.h>
# include <yuni/hash/table.h>
# include <yuni/string.h>
# include <yuni/misc/static.h>



namespace Yuni
{
namespace Hash
{


	/*! \class Dictionary
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
	**
	** \internal Do not forget to broadcast changes into Hash::Table as well
	*/
	template<typename V, int Options = optNone>
	class Dictionary : public Table<String, V, false>
	{
	public:
		typedef typename Table<String, V, false> ::iterator  iterator;
		typedef typename Table<String, V, false> ::const_iterator  const_iterator;

	public:
		//! \name Constructors & Destructor
		//@{
		//! Default constructor
		Dictionary() : Table<String, V, false>() {}
		//! Copy constructor
		Dictionary(const Dictionary& c) : Table<String, V, false>(c) {}
		//! Destructor
		virtual ~Dictionary() {Table<String, V, false>::clear();}
		//@}

		/*!
		** \brief Get if an entry exists
		**
		** \param key The key to find
		** \return True if the key exists, False otherwise
		*/
		bool exists(const String& key) const {return Table<String, V, false>::exists(key);}
		/*!
		** \brief Get/Set an entry
		**
		** If the entry does not exist, it will be created
		**
		** \param key The key to get/set
		** \return The value of the key
		*/
		V& operator[] (const String& key) {return (*(static_cast < Table<String, V, false > * > (this)))[key];}

		/*!
		** \brief Find a key in the table
		**
		** \param key The key to find
		** \return The iterator pointing to the key, end() if not found
		*/
		iterator find(const String& key) {return Table<String, V, false>::find(key);}
		const_iterator find(const String& key) const {return Table<String, V, false>::find(key);}

		/*!
		** \brief Get the value of a key
		**
		** \param key The key to find
		** \param defvalue The default value if the key can not be found
		** \return The value ofthe key, `defvalue` if the key could not be found
		*/
		V value(const String& key, const V& defvalue = V()) const {return Table<String, V, false>::value(key, defvalue);}

		/*!
		** \brief Get an iterator pointing to the beginning of the table
		*/
		iterator begin() {return Table<String, V, false>::begin();}
		const_iterator begin() const {return Table<String, V, false>::begin();}

		/*!
		** \brief Get an iterator pointing to the end of the table
		*/
		iterator end() {return Table<String, V, false>::end();}
		const_iterator end() const {return Table<String, V, false>::end();}

		/*!
		** \brief Clear the table
		*/
		void clear() {Table<String, V, false>::clear();}

		/*!
		** \brief Erase a single key
		**
		** \param key The key to find
		** \return True if the key has been erased, False if not found
		*/
		void erase(const String& key) {Table<String, V, false>::erase(key);}

	}; // class Hash::Dictionary




} // namespace Hash
} // namespace Yuni


#endif // __YUNI_HASH_DICTIONARY_H__

