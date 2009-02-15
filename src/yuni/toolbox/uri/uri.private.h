#ifndef __YUNI_TOOLBOX_URI_PRIVATE_H__
# define __YUNI_TOOLBOX_URI_PRIVATE_H__

# include "../string.h"



namespace Yuni
{
namespace Private
{
namespace Uri
{


	/*!
	** \brief Carrier for informations about an URI
	*/
	class Informations
	{
	public:
		//! \name Constructors
		//@{
		
		Informations();
		Informations(const Informations& rhs);

		//@}

		void assign(const Informations& rhs);
		void clear();

		String toString() const;

		bool isEqualsTo(const Informations& rhs) const;

	public:
		String scheme;
		String user;
		String password;
		String server;
		sint32 port;
		String path;
		String query;
		String fragment;
		//! Were the informations of the URI valid during the last build
		bool isValid;

	}; // class Informations




} // namespace Uri	
} // namespace Private
} // namespace Yuni

#endif // __YUNI_TOOLBOX_URI_PRIVATE_H__
