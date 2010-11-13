#ifndef __YUNI_UI_DESKTOP_HXX__
# define __YUNI_UI_DESKTOP_HXX__


namespace Yuni
{
namespace UI
{

	inline Desktop::~Desktop()
	{
		destroyBoundEvents();
	}


	inline void Desktop::reconnect()
	{
		ThreadingPolicy::MutexLocker lock(*this);
		reconnectWL();
	}


	inline void Desktop::disconnect()
	{
		ThreadingPolicy::MutexLocker lock(*this);
		disconnectWL();
	}


	inline void Desktop::add(const Application::Ptr& app)
	{
		if (!(!app))
		{
			ThreadingPolicy::MutexLocker lock(*this);
			pApps[app->guid()] = app;
			reconnectOneApplicationWL(app);
		}
	}


	inline Desktop& Desktop::operator += (const Application::Ptr& app)
	{
		if (!(!app))
		{
			ThreadingPolicy::MutexLocker lock(*this);
			pApps[app->guid()] = app;
			reconnectOneApplicationWL(app);
		}
		return *this;
	}


	inline Desktop& Desktop::operator << (const Application::Ptr& app)
	{
		if (!(!app))
		{
			ThreadingPolicy::MutexLocker lock(*this);
			pApps[app->guid()] = app;
			reconnectOneApplicationWL(app);
		}
		return *this;
	}


	template<typename StringT>
	inline void Desktop::remove(const StringT& guid)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  InvalidTypeForBufferSize);

		ThreadingPolicy::MutexLocker lock(*this);
		pApps.erase(guid);
	}


	inline void Desktop::remove(const Application::Ptr& app)
	{
		if (!(!app))
		{
			ThreadingPolicy::MutexLocker lock(*this);
			pApps.erase(app->guid());
		}
	}


	template<typename StringT>
	inline Desktop& Desktop::operator -= (const StringT& guid)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  InvalidTypeForBufferSize);

		ThreadingPolicy::MutexLocker lock(*this);
		pApps.erase(guid);
		return *this;
	}


	inline Desktop& Desktop::operator -= (const Application::Ptr& app)
	{
		if (!(!app))
		{
			ThreadingPolicy::MutexLocker lock(*this);
			pApps.erase(app->guid());
		}
		return *this;
	}




} // namespace UI
} // namespace Yuni

#endif // __YUNI_UI_DESKTOP_HXX__
