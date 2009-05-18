#ifndef __YUNI_HASH_DICTIONARY_H__
# define __YUNI_HASH_DICTIONARY_H__

# include "../../yuni.h"
# include "table.h"
# include "../string.h"



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
	class Dictionary : public Table<String, V, Policy::SingleThreaded>
	{
	public:
		//! Table
		typedef Table<String, V, Policy::SingleThreaded> TableType;
		//! An Iterator for the dictionary
		typedef typename TableType::iterator  iterator;
		//! A Const iterator for the dictionary
		typedef typename TableType::const_iterator  const_iterator;

	public:
		//! \name Constructors & Destructor
		//@{
		//! Default constructor
		Dictionary() : TableType() {}
		//! Copy constructor
		Dictionary(const Dictionary& c) : TableType(c) {}
		//! Destructor
		virtual ~Dictionary() {TableType::clear();}
		//@}

		/*!
		** \brief Get if an entry exists
		**
		** \param key The key to find
		** \return True if the key exists, False otherwise
		*/
		bool exists(const String& key) const {return TableType::exists(key);}
		/*!
		** \brief Get/Set an entry
		**
		** If the entry does not exist, it will be created
		**
		** \param key The key to get/set
		** \return The value of the key
		*/
		V& operator[] (const String& key) {return (*(static_cast < TableType* > (this)))[key];}

		/*!
		** \brief Find a key in the table
		**
		** \param key The key to find
		** \return The iterator pointing to the key, end() if not found
		*/
		iterator find(const String& key) {return TableType::find(key);}
		const_iterator find(const String& key) const {return TableType::find(key);}

		/*!
		** \brief Get the value of a key
		**
		** \param key The key to find
		** \param defvalue The default value if the key can not be found
		** \return The value ofthe key, `defvalue` if the key could not be found
		*/
		V value(const String& key, const V& defvalue = V()) {return TableType::value(key, defvalue);}

		/*!
		** \brief Get an iterator pointing to the beginning of the table
		*/
		iterator begin() {return TableType::begin();}
		//const_iterator begin() const {return TableType::begin();}

		/*!
		** \brief Get an iterator pointing to the end of the table
		*/
		iterator end() {return TableType::end();}
		//const_iterator end() const {return TableType::end();}

		/*!
		** \brief Clear the table
		*/
		void clear() {TableType::clear();}

		/*!
		** \brief Erase a single key
		**
		** \param key The key to find
		** \return True if the key has been erased, False if not found
		*/
		void erase(const String& key) {TableType::erase(key);}

		/*!
		** \brief Size of the dictionary
		*/
		int size() {return TableType::size();}

	}; // class Hash::Dictionary




} // namespace Hash
} // namespace Yuni


#endif // __YUNI_HASH_DICTIONARY_H__
