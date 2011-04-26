#ifndef __YUNI_NET_SERVER_SERVER_HXX__
# define __YUNI_NET_SERVER_SERVER_HXX__


namespace Yuni
{
namespace Net
{
namespace Server
{


	template<class ImplT>
	inline unsigned int IServerTmpl<ImplT>::messageMaxSize() const
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		return pMessageMaxSize;
	}


	template<class ImplT>
	inline bool IServerTmpl<ImplT>::messageMaxSize(unsigned int size)
	{
		if (!size)
			return false;
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			pMessageMaxSize = size;
		}
		return true;
	}


	template<class ImplT>
	template<class StringT>
	bool IServerTmpl<ImplT>::listen(const StringT& address, const Port& port)
	{
		if (!port.valid())
			return errInvalidPort;

		// The address
		HostAddressPort adr;
		adr.address = address;
		adr.port = port;
		if (!adr.address)
			return errInvalidHostAddress;

		// Adding the new address
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			if (!pAddresses.insert(adr).second)
				return errDupplicatedAddress;
		}
		return errNone;
	}


	template<class ImplT>
	inline void IServerTmpl<ImplT>::clear()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		pAddresses.clear();
	}


	template<class ImplT>
	template<class StringT>
	inline Error
	IServerTmpl<ImplT>::sendAll(const StringT& buffer)
	{
		const unsigned int len = Traits::Length<StringT, unsigned int>::Value(buffer);
		const char* const cstr = Traits::CString<StringT>::Perform(buffer);
		return sendAll(cstr, len);
	}


	template<class ImplT>
	inline Error
	IServerTmpl<ImplT>::sendAll(const char* const buffer, unsigned int length)
	{
		if (!len)
			return errNone;
		if (len < pMessageMaxSize)
		{
			return errNone;
		}
		return errMessageMaxSize;
	}


	template<class ImplT>
	inline Error
	IServerTmpl<ImplT>::start()
	{
		Error err;

		{
			// Locking
			typename ThreadingPolicy::MutexLocker locker(*this);

			// Checking if not already running
			if (pRunning)
				return errNone;

			// Broadcasting the event `onStarting`
			{
				const Error canStart = errNone;
				// Starting !
				onStarting(canStart);
				if (canStart != errNone)
					return canStart;
			}

			// Ok, attempt to start the server from the real implementation
			err = ImplementationType::start();

			// Initializing the internal variable `pRunning` before going further
			pRunning = (err == errNone);

			// The mutex will be unlocked at this point
			// It is important that this mutex is unlocked before calling sub events
			// (to avoid deadlock)
		}
		if (err == errNone)
		{
			// Great ! The server is working !
			onStarted();
			return errNone;
		}

		// An error has occured
		return err;
	}






} // namespace Server
} // namespace Net
} // namespace Yuni

#endif // __YUNI_NET_SERVER_SERVER_HXX__
