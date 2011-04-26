#ifndef __YUNI_NET_ERROR_H__
# define __YUNI_NET_ERROR_H__

# include "../yuni.h"


namespace Yuni
{
namespace Net
{

	/*!
	** \brief Errors that can be returned by routines in the 'Yuni::Net' module
	*/
	enum Error
	{
		//! No error
		errNone = 0,
		//! The port is invalid (range [1..65535])
		errInvalidPort,
		//! The address is invalid
		errInvalidHostAddress,
		//! The given address already exists in the list
		errDupplicatedAddress,
		//! The message is over the dynamic value `messageMaxSize`
		errMessageMaxSize,
		//! The maximum number of errors
		errMax
	};




} // namespace Net
} // namespace Yuni

#endif // __YUNI_NET_NET_H__
