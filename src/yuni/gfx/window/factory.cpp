
#include "factory.h"

# ifdef YUNI_OS_MAC
	// TODO: Write window creation for Cocoa. For the moment it does nothing
	#	include "openglcocoa.h"
# else
# 	ifdef YUNI_OS_WINDOWS
#		include "openglmsw.h"
#		include "directxmsw.h"
#   else
#		ifdef YUNI_OS_UNIX
#			include "openglx11.h"
#		else
#			error No window creation available for your platform!
#		endif
# 	endif
# endif



namespace Yuni
{
namespace Gfx
{
namespace Window
{


	AWindow* Factory::CreateGLWindow(const String& title, unsigned int width,
		unsigned int height, unsigned int bits, bool fullScreen)
	{
# ifdef YUNI_WINDOWSYSTEM_MSW
		AWindow* wnd = new OpenGLMSW(title, width, height, bits, fullScreen);
# endif
# ifdef YUNI_WINDOWSYSTEM_X11
		AWindow* wnd = new OpenGLX11(title, width, height, bits, fullScreen);
# endif
# ifdef YUNI_OS_MAC
		AWindow* wnd = new OpenGLCocoa(title, width, height, bits, fullScreen);
# endif

		if (!wnd->initialize())
		{
			wnd->close();
			delete wnd;
			return NULL;
		}
		return wnd;
	}

# if defined(YUNI_WINDOWSYSTEM_MSW) && defined(YUNI_USE_DIRECTX)
	AWindow* Factory::CreateDX9Window(const String& title, unsigned int width,
		unsigned int height, unsigned int bits, bool fullScreen)
	{
		AWindow* wnd = new DirectXMSW(title, width, height, bits, fullScreen);
		if (!wnd->initialize())
		{
			wnd->close();
			delete wnd;
			return NULL;
		}
		return wnd;
	}
# endif


} // namespace Window
} // namespace Gfx
} // namespace Yuni
