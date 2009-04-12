#ifndef __YUNI_TOOLBOX_URI_URI_H__
# define __YUNI_TOOLBOX_URI_URI_H__

# include "../../yuni.h"
# include <limits.h>
# include <ostream>
# include "../../net/protocol.h"
# include "uri.private.h"
# include "../string.h"




namespace Yuni
{


	/*!
	** \brief Uniform resource Identifier
	**
	**
	** This implementation of URIs follows the RFC 3986
	** \see http://www.ietf.org/rfc/rfc3986.txt
	**
	** Here are some examples of URIs (extracted from the RFC itself)
	** \code
	** file:///etc/hosts
	** ftp://ftp.is.co.za/rfc/rfc1808.txt
	** http://www.ietf.org/rfc/rfc3986.txt
	** ldap://[2001:db8::7]/c=GB?objectClass?one
	** mailto:John.Doe@example.com
	** news:comp.infosystems.www.servers.unix
	** tel:+1-816-555-1212
	** telnet://192.0.2.16:80/
	** urn:oasis:names:specification:docbook:dtd:xml:4.1.2
	** \endcode
	**
	** Composition (extracted from the RFC too) :
	** \code
	**  foo://example.com:8042/over/there?name=ferret#nose
	**  \_/   \______________/\_________/ \_________/ \__/
	**   |           |            |            |        |
	** scheme     authority       path        query   fragment
	**   |   _____________________|__
	**  / \ /                        \
	**  urn:example:animal:ferret:nose
	** \endcode
	**
	**
	** Here is a typical way of how to use this class :
	** \code
	** Uri uri("http://www.example.org");
	** uri.defaultPathIfEmpty(); // Ensure the path is not empty
	** switch (uri.protocol())
	** {
	** 		case Net::Protocol::http  : ...; break; // Deals with the HTTP protocol
	** 		case Net::Protocol::ftp   : ...; break; // Deals with the FTP protocol
	** 		default: ...; // Unsupported protocol
	** }
	** \endcode
	**
	**
	** It is possible to modify only a part of the URI :
	** \code
	** // The original URI
	** Uri uri("http://www.example.org/?myquery=foo");
	**
	** uri.query("anotherquery=bar");
	** std::cout << uri << std::endl; // http://www.example.org/?anotherquery=bar
	**
	** uri.user("myuser");
	** std::cout << uri << std::endl; // http://myuser@www.example.org/?anotherquery=bar
	** \endcode
	**
	**
	**
	** \note An URL refers to a subset of URIs
	**
	** \note <b>Modifying an URI</b> : If any modification is brought to any part
	** of the URI, the returned value of the method `isValid()` should no longer
	** be used, because this variable is set when the URI is built from a simple
	** string.
	**
	**
	**
	** \note <b>Special scheme</b> : When the scheme `file` is used, the server
	** field should not be used (`file://foo/tmp` should lead to `/tmp`, but
	** `file:///foo/tmp` will lead to `/foo/tmp`).
	**
	**
	**
	** \note <b>Suffix reference</b> : The URI syntax is designed for unambiguous
	** reference to resources but traditional uses allow (for convenient reasons)
	** a suffix of the URI as a reference consisting of only the authority and path
	** portions of the URI, such as `www.libyuni.org` or `google`. This class does
	** not make any changes on the server name :
	** \code
	** Uri uri("google");
	** std::cout << uri.server() << std::endl; // `google`
	**
	** Uri uri2("www.libyuni.org");
	** std::cout << uri2.server() << std::endl; // `www.libyuni.org`
	**
	** Uri uri3("www.libyuni.org/downloads");
	** // Server: `www.libyuni.org`, path: `/downloads`
	** std::cout << "Server: `" << uri3.server() << "`, path: `" << uri3.path() << "`" << std::endl;
	** \endcode
	**
	**
	**
	** \note <b>IPv6</b> : According to the RFC, IPv6 addresses must be enclosed
	** in brackets (ex: `http://[2001:db8::7]`)
	**
	**
	**
	** \note <b>Dot segments Removal</b> : In the most cases, the special segments
	** `.` and `..` will be removed (`file:///path/./to/../somewhere` will give
	** `file:///path/somewhere`). However it can not be done for the begining of
	** relative paths (`file://../../relative/./path` will give
	** `file://../../relative/path`).
	**
	**
	** \bug This implementation does not handle at all escaped caracters
	*/
	class Uri
	{
	public:
		//! \name Constructors
		//@{

		/*!
		** \brief Default constructor
		*/
		Uri() {}

		/*!
		** \brief Constructor with a string, to directly construct the URI
		*/
		Uri(const String& s);

		/*!
		** \brief Copy constructor
		*/
		explicit Uri(const Uri& rhs);

		//@}


		//! \name Informations about the URI structure
		//@{

		/*!
		** \brief Clear all informations about the URI structure
		*/
		void clear() {pInfos.clear();}

		//! Scheme (lowercase)
		const String& scheme() const {return pInfos.scheme;}
		//! Set the scheme
		void scheme(const String& s) {pInfos.scheme = s;}
		void scheme(const Net::Protocol::Type& type) {pInfos.scheme = Net::Protocol::ToScheme(type);}

		//! Server
		const String& server() const {return pInfos.server;}
		//! Set the server
		void server(const String& s) {pInfos.server = s;}

		//! Port (equals to `INT_MIN` if none)
		int port() const {return pInfos.port;}
		//! Set the port value (only if strictly positive or equals to INT_MIN do disable it)
		void port(const int p) {if (p > 0 || p == INT_MIN) pInfos.port = p;}

		//! User
		const String& user() const {return pInfos.user;}
		//! Set the user
		void user(const String& s) {pInfos.user = s;}

		//! Password
		const String& password() const {return pInfos.password;}
		//! Set the password
		void password(const String& s) {pInfos.password = s;}

		//! Path
		const String& path() const {return pInfos.path;}
		//! Set the path
		void path(const String& s) {pInfos.path = s;}
		//! Set a default path (`/`) if there is no path
		void defaultPathIfEmpty() {if (pInfos.path.empty()) pInfos.path = "/";}

		//! Query
		const String& query() const {return pInfos.query;}
		//! Set the query
		void query(const String& s) {pInfos.query = s;}

		//! Fragment
		const String& fragment() const {return pInfos.fragment;}
		//! Set the fragment
		void fragment(const String& s) {pInfos.fragment = s;}

		/*!
		** \brief Get if the URI was valid during the last extract
		**
		** \note If any modification is brought to any part of the URI, the returned
		** value of this method should no longer be used, because this variable is set
		** when the URI is built from a simple string.
		*/
		bool isValid() const {return pInfos.isValid;}

		//@}


		//! \name Scheme
		//@{

		/*!
		** \brief Try to find out the protocol from the scheme
		*/
		Net::Protocol::Type protocol() const
		{return pInfos.isValid ? Net::Protocol::SchemeToType(pInfos.scheme): Net::Protocol::unknown;}


		/*!
		** \brief Convenient method to know if the URI is merely a file
		*/
		bool schemeIsFile() const
		{return (pInfos.scheme.empty() && !pInfos.path.empty()) || "file" == pInfos.scheme;}

		/*!
		** \brief Get if the scheme is `HTTP` or `HTTPS`
		*/
		bool schemeIsHTTP() const
		{return !pInfos.scheme.empty() && ("http" == pInfos.scheme || "https" == pInfos.scheme);}

		/*!
		** \brief Get if the scheme is `FTP`
		*/
		bool schemeIsFTP() const
		{return !pInfos.scheme.empty() && "ftp" == pInfos.scheme;}

		/*!
		** \brief Get if the scheme is `SSH`
		*/
		bool schemeIsSSH() const
		{return !pInfos.scheme.empty() && "ssh" == pInfos.scheme;}

		/*!
		** \brief Get if the scheme is `LDAP`
		*/
		bool schemeIsLDAP() const
		{return !pInfos.scheme.empty() && "ldap" == pInfos.scheme;}

		//@}


		//! \name Conversion
		//@{

		/*!
		** \brief Reconstruct the URI to a string
		*/
		String toString() const {return pInfos.toString();}

		/*!
		** \brief Print this URI to a stream output
		** \param out The stream output
		*/
		std::ostream& print(std::ostream& out) const {out << pInfos.toString();return out;}

		//@}


		//! \name Operators
		//@{

		//! The operator =
		Uri& operator = (const Uri& rhs)  {pInfos.assign(rhs.pInfos);return *this;}
		Uri& operator = (const String& rhs)  {extractURIFromString(rhs);return *this;}

		//! The operator ==
		bool operator == (const Uri& rhs) const {return pInfos.isEqualsTo(rhs.pInfos);}
		//! The operator !=
		bool operator != (const Uri& rhs) const {return !((*this) == rhs);}
		//! The operator ()
		String operator() () const {return pInfos.toString();}
		//@}


	private:
		/*!
		** \brief Build URI Informations from a string
		** \param raw The string
		*/
		void extractURIFromString(const String& raw);

	private:
		//! Structured Informations about the URI
		Private::Uri::Informations pInfos;

	}; // class Uri





} // namespace Yuni




//! \name Operator overload for stream printing
//@{
inline std::ostream& operator << (std::ostream& out, const Yuni::Uri& u)
{return u.print(out);}
//@}


#endif // __YUNI_TOOLBOX_URI_URI_H__
