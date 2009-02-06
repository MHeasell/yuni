#ifndef __YUNI_MISC_VERSION_H__
# define __YUNI_MISC_VERSION_H__

# include "../string.h"



namespace Yuni
{


	/*!
	** \brief Provides version informations
	** \ingroup Toolbox
	*/
	class Version
	{
	public:
		/*!
		** \brief Get the version of the Yuni Library
		*/
		void InternalLib(Version& v);

	public:
		//! \name Constructor
		//@{
		//! Default constructor
		Version();
		//! Constructor with a given version
		Version(const int h, const int l, const int r = 0);
		//! Copy constructor
		Version(const Version& c);
		//@}

		int hi() const {return pHi;}
		void hi(const int h); 

		int lo() const {return pLo;}
		void lo(const int l);

		int revision() const {return pRevision;}
		void revision(const int r);

		const String& author() const {return pAuthor;}
		void author(const String& s);

		const String& webUrl() const {return pWebUrl;}
		void webUrl(const String& s);

		/*!
		** \brief Get the version in an human-readable string
		*/
		String toString() const;


		/*!
		** \brief Check if this version is less than another one
		*/
		bool isLessThan(const Version& rhs) const;
		/*!
		** \brief Check if this version is equal to another one
		*/
		bool isEqualTo(const Version& rhs) const;
		/*!
		** \brief Check if this version is greater than another one
		*/
		bool isGreaterThan(const Version& rhs) const;


		//! \name Operators
		//@{
		//! The operator <
		bool operator <  (const Version& rhs) const {return isLessThan(rhs);}
		//! The operator <=
		bool operator <= (const Version& rhs) const {return isEqualTo(rhs) || isLessThan(rhs);}
		//! The operator >
		bool operator >  (const Version& rhs) const {return isGreaterThan(rhs);}
		//! The operator <=
		bool operator >= (const Version& rhs) const {return isEqualTo(rhs) || isGreaterThan(rhs);}

		//! The operator ==
		bool operator == (const Version& rhs) const {return isEqualTo(rhs);}
		//! The operator !=
		bool operator != (const Version& rhs) const {return !isEqualTo(rhs);}
		//@}

	private:
		//! The hi version
		int pHi;
		//! The lo version
		int pLo;
		//! The revision
		int pRevision;
		//! The author
		String pAuthor;
		//! The Web address
		String pWebUrl;

	}; // class Version


} // namespace Yuni

#endif // __YUNI_MISC_VERSION_H__
