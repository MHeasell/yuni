
#include "directxmsw.h"
#include "factory.h"
#include "../../core/string.h"

#if defined(YUNI_WINDOWSYSTEM_MSW) && defined(YUNI_USE_DIRECTX)

namespace Yuni
{
namespace Gfx
{
namespace Window
{

	bool DirectXMSW::initialize()
	{
		if (!AMSWindows::initialize())
			return false;

		// Show the window
		ShowWindow(pHWnd, SW_SHOW);
		// Slightly higher priority
		SetForegroundWindow(pHWnd);
		// Sets keyboard focus to the window
		SetFocus(pHWnd);

		// TODO: This might very well be useless, check it
		resize(pWidth, pHeight);

		// Initialize our newly created DirectX window
		pDXObject = Direct3DCreate9(D3D_SDK_VERSION);
		if (pDXObject == NULL)
		{
			MessageBox(pHWnd, "DirectX Runtime library not installed!", "DirectX Init error", MB_OK);
			return false;
		}
		resetPresentationParameters();
		if (FAILED(pDXObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, pHWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING, &pDXPresentParams, &pDXDevice)))
		{
			if (FAILED(pDXObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF,
				pHWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&pDXPresentParams, &pDXDevice)))
			{
				MessageBox(pHWnd, "Failed to create the reference device!",
					"DirectX Init Error", MB_OK);
				release();
				close();
				return false;
			}
		}

		return true;
	}

	void DirectXMSW::resetPresentationParameters()
	{
		ZeroMemory(&pDXPresentParams, sizeof(pDXPresentParams));
		pDXPresentParams.Windowed = !pFullScreen;
		pDXPresentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
		pDXPresentParams.EnableAutoDepthStencil = true;
		pDXPresentParams.AutoDepthStencilFormat = D3DFMT_D16;
		// This controls whether to wait for vsync
		pDXPresentParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		pDXPresentParams.hDeviceWindow = pHWnd;
		pDXPresentParams.BackBufferCount = 1;
		pDXPresentParams.BackBufferWidth = pWidth;
		pDXPresentParams.BackBufferHeight = pHeight;
		pDXPresentParams.BackBufferFormat = D3DFMT_X8R8G8B8;
		// Antialias: D3DMULTISAMPLE_NONMASKABLE, D3DMULTISAMPLE_2_SAMPLES, ...
		pDXPresentParams.MultiSampleType = D3DMULTISAMPLE_NONE;

	}

	bool DirectXMSW::resetDevice()
	{
		if (FAILED(pDXDevice->Reset(&pDXPresentParams)))
		{
			MessageBox(pHWnd, "Device reset failed!", "DirectX Init Error", MB_OK);
			release();
			close();
			return false;
		}
		return true;
	}


	void DirectXMSW::close()
	{
		release();
		AMSWindows::close();
	}

	void DirectXMSW::release()
	{
		if (pDXDevice)
		{
			pDXDevice->Release();
			pDXDevice = NULL;
		}
		if (pDXObject)
		{
			pDXObject->Release();
			pDXObject = NULL;
		}
	}

	void DirectXMSW::resize(unsigned int width, unsigned int height)
	{
		//ADirectX::resizeAPI(width, height);
		AWindow::resize(width, height);
	}


	bool DirectXMSW::verticalSync() const
	{
		return pVSync;
	}

	bool DirectXMSW::verticalSync(bool active)
	{
		if (active == pVSync)
			return true;
		pDXPresentParams.PresentationInterval = active ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;
		return resetDevice();
	}

} // namespace Window
} // namespace Gfx3D
} // namespace Yuni

#endif // YUNI_WINDOWSYSTEM_MSW && YUNI_USE_DIRECTX
