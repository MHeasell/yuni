#ifndef __YUNI_HASH_ABSTRACT_H__
# define __YUNI_HASH_ABSTRACT_H__

# include <yuni/yuni.h>
# include <yuni/string.h>


namespace Yuni
{

/*!
** \brief Tools which use hashing mechanisms
*/
namespace Hash
{

/*!
** \brief Checksums
*/
namespace Checksum
{



	class Abstract
	{
	public:
		//! \name Constructor & Destructor
		//@{
		//! Default constructor
		Abstract();
		//! Destructor
		virtual ~Abstract();
		//@}

		/*!
		** \brief Reset the hash value
		*/
		void reset() {pValue.clear();}

		/*!
		** \brief Compute the hash from a string
		**
		** \param s The string
		** \return The hash value 
		*/
		const String& fromString(const String& s) {return fromRawData(s.c_str(), s.size());}

		/*!
		** \brief Compute the hash from raw data
		**
		** \param rawdata The buffer
		** \param size The size of the buffer. AutoDetectNullChar will make an autodetection of the length
		** \return The hash value 
		*/
		virtual const String& fromRawData(const void* rawdata, uint64 size = AutoDetectNullChar) = 0;

		/*!
		** \brief Compute the hash of a given file
		**
		** \param filename The filename to analyze
		** \return The hash value 
		*/
		virtual const String& fromFile(const String& filename) = 0;

		/*!
		** \brief Get the last hash value
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

	}; // class Hash::Abstract



} // namespace Checksum
} // namespace Hash
} // namespace Yuni

#endif // __YUNI_HASH_ABSTRACT_H__
