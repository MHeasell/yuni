
#include "window.h"

#ifdef YUNI_OS_MAC
	// TODO: Write window creation for Cocoa. For the moment it does nothing
#	include "cocoa/opengl.h"
#else
#	ifdef YUNI_OS_WINDOWS
#		include "msw/opengl.h"
#		include "msw/directx.h"
#		include "msw/cairo.h"
#   else
#		ifdef YUNI_OS_UNIX
#			include "x11/opengl.h"
#		else
#			error No window creation available for your platform!
#		endif
#	endif
#endif



namespace Yuni
{
namespace Gfx
{
namespace Window
{

	IWindow* Create(UI::Window::Ptr& source, const Device::Ptr& device)
	{
		Yuni::Device::Display::Resolution::Ptr res = device->resolution();
		IWindow* wnd = NULL;
		switch (device->type())
		{
			# if defined(YUNI_WINDOWSYSTEM_MSW) && defined(YUNI_USE_DIRECTX)
			// No management of DirectX8 for the moment, use DirectX 9
			case Device::DirectX8:
			case Device::DirectX9:
				{
					wnd = new DirectXMSW(source, res->bitPerPixel(), device->fullscreen());
					break;
				}
			# endif

			case Device::OpenGL:
				{
					# ifdef YUNI_WINDOWSYSTEM_MSW
					wnd = new OpenGLMSW(source, res->bitPerPixel(), device->fullscreen());
					# endif
					# ifdef YUNI_WINDOWSYSTEM_X11
					wnd = new OpenGLX11(source, res->bitPerPixel(), device->fullscreen());
					# endif
					# ifdef YUNI_OS_MAC
					wnd = new OpenGLCocoa(source, res->bitPerPixel(), device->fullscreen());
					# endif
					break;
				}

			case Device::Cairo:
				{
					# ifdef YUNI_WINDOWSYSTEM_MSW
					wnd = new CairoMSW(source, res->bitPerPixel(), device->fullscreen());
					# endif
					# ifdef YUNI_WINDOWSYSTEM_X11
					//wnd = new CairoX11(source, res->bitPerPixel(), device->fullscreen());
					# endif
					# ifdef YUNI_OS_MAC
					//wnd = new CairoCocoa(title, res->width(), res->height(), res->bitPerPixel(), device->fullscreen());
					# endif
					break;
				}

			// For the moment, fail if asked for a null renderer or a software renderer
			default:
				return NULL;
		}

		if (wnd && !wnd->initialize())
		{
			wnd->close();
			delete wnd;
			return NULL;
		}
		return wnd;
	}




} // namespace Window
} // namespace Gfx
} // namespace Yuni
