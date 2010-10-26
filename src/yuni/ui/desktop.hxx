#ifndef __YUNI_UI_DESKTOP_HXX__
# define __YUNI_UI_DESKTOP_HXX__


namespace Yuni
{
namespace UI
{

	inline Desktop::Desktop()
	{}


	inline Desktop::~Desktop()
	{}


	inline void updateComponentWL(const IComponent::ID& componentID) const
	{
	}


	inline void Desktop::add(Application::Ptr& app)
	{
		if (!(!app))
			pApps[app->guid()] = app;
	}


	inline Desktop& Desktop::operator += (Application::Ptr& app)
	{
		if (!(!app))
			pApps[app->guid()] = app;
		return *this;
	}


	inline Desktop& Desktop::operator << (Application::Ptr& app)
	{
		if (!(!app))
			pApps[app->guid()] = app;
		return *this;
	}


	template<typename StringT>
	inline void Desktop::remove(const StringT& guid)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  InvalidTypeForBufferSize);

		pApps.erase(guid);
	}


	inline void Desktop::remove(Application::Ptr& app)
	{
		if (!(!app))
			pApps.erase(app->guid());
	}


	template<typename StringT>
	inline Desktop& Desktop::operator -= (const StringT& guid)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  InvalidTypeForBufferSize);

		pApps.erase(guid);
		return *this;
	}


	inline Desktop& Desktop::operator -= (Application::Ptr& app)
	{
		if (!(!app))
			pApps.erase(app->guid());
		return *this;
	}




} // namespace UI
} // namespace Yuni

#endif // __YUNI_UI_DESKTOP_HXX__
