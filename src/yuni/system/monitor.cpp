
#include <yuni/system/screen.h>
#ifdef YUNI_OS_WINDOWS
#  ifndef WIN32_LEAN_AND_MEAN
#	 define WIN32_LEAN_AND_MEAN
#  endif
#  include <windows.h>
#endif // ifdef YUNI_OS_WINDOWS



namespace Yuni
{
namespace System
{

	namespace
	{

		#ifdef YUNI_OS_WINDOWS
		void getScreenResolutionWindows(Resolution& r)
		{
			r.width  = (uint16) GetSystemMetrics(SM_CXVIRTUALSCREEN);
			r.height = (uint16) GetSystemMetrics(SM_CYVIRTUALSCREEN);
		}
		#endif

	} // anonymous namespace

	Screen::Screen()
	{
		getCurrentResolution(pScreenResolution);
	}

	Screen::~Screen()
	{}


	void Screen::getCurrentResolution(Resolution& r)
	{
		#ifdef YUNI_OS_WINDOWS
		getScreenResolutionWindows(r);
		#endif
	}

} // namespace System
} // namespace Yuni


