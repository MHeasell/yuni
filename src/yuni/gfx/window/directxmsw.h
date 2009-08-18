#ifndef __YUNI_GFX_WINDOW_DIRECTX_MSW_H__
# define __YUNI_GFX_WINDOW_DIRECTX_MSW_H__

# include "../../yuni.h"

# if defined(YUNI_WINDOWSYSTEM_MSW) && defined(YUNI_USE_DIRECTX)
#	include "../../core/system/windows.hdr.h"
#	include "../api/dx9.h"
#	include "../api/api.h"
#	include "msw.h"


namespace Yuni
{
namespace Gfx
{
namespace Window
{

	/*!
	** \brief Implementation of a MFC window that uses DirectX display
	*/
	class DirectXMSW: public AMSWindows, public Api::IGfxAPI
	{
	public:
		DirectXMSW(const String& title, unsigned int width, unsigned int height, unsigned int bitDepth, bool fullScreen)
			:AMSWindows(title, width, height, bitDepth, fullScreen),
			pDXObject(NULL), pDXDevice(NULL), pVSync(false) // Deactivate vsync by default
		{
			pWindowClassName = "DirectX";
		}

		virtual bool initialize();
		virtual void close();
		virtual void blit() { pDXDevice->Present(NULL, NULL, NULL, NULL); }
		virtual void resize(unsigned int width, unsigned int height);

		//! Is vertical synchronization (VSync) active?
		virtual bool verticalSync() const;
		//! Activate / deactivate vertical synchronization (VSync)
		virtual bool verticalSync(bool activate);

	private:
		void release();

		void resetPresentationParameters();

		bool resetDevice();

	private:
		//! DirectX object
		LPDIRECT3D9 pDXObject;

		//! DirectX device
		LPDIRECT3DDEVICE9 pDXDevice;

		//! DirectX Presentation parameters
		D3DPRESENT_PARAMETERS pDXPresentParams;

		//! Current status of the VSync
		bool pVSync;

	}; // class DirectxMSW




} // namespace Window
} // namespace Gfx
} // namespace Yuni


# endif // YUNI_WINDOWSYSTEM_MSW && YUNI_USE_DIRECTX

#endif // __YUNI_GFX_WINDOW_DIRECTX_MSW_H__
