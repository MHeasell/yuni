#ifdef __YUNI_UI_APPLICATION_HXX__
# define __YUNI_UI_APPLICATION_HXX__


namespace Yuni
{
namespace UI
{


	template<typename StringT, typename StringT2>
	inline Application::Application(const StringT& id, const StringT2& name)
		: pID(id), pName(name)
	{}


	inline const StaticString& Application::ID()
	{
		return pID;
	}


	inline const StaticString& Application::Name()
	{
		return pName;
	}


} // namespace UI
} // namespace Yuni

#endif // __YUNI_UI_APPLICATION_HXX__
