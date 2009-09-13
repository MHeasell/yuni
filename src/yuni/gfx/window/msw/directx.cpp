
#include "../msw/directx.h"
#include "../../../core/string.h"

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

	void DirectXMSW::clearScreen()
	{
		pDXDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	}

	void DirectXMSW::resetView()
	{}

	void DirectXMSW::applyTranslation(const Vector3D<float>& translation)
	{}

	void DirectXMSW::applyRotation(const Vector3D<float>& rotation)
	{}

	void DirectXMSW::drawTriangles(const Mesh::TriangleList& triangles)
	{}

	void DirectXMSW::testDraw()
	{
		struct Vertex
		{
			float x;
			float y;
			float z;
			DWORD color;
		};
		Vertex vertices[] =
			{
				// Top
				{ 1.0f, 1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 0.0, 1.0, 0.0, 1.0 ) },
				{-1.0f, 1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 0.0, 1.0, 0.0, 1.0 ) },
				{-1.0f, 1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 0.0, 1.0, 0.0, 1.0 ) },
				{ 1.0f, 1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 0.0, 1.0, 0.0, 1.0 ) },

				// Bottom
				{ 1.0f,-1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 1.0, 0.5, 0.0, 1.0 ) },
				{-1.0f,-1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 1.0, 0.5, 0.0, 1.0 ) },
				{-1.0f,-1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 1.0, 0.5, 0.0, 1.0 ) },
				{ 1.0f,-1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 1.0, 0.5, 0.0, 1.0 ) },

				// Front
				{ 1.0f, 1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 1.0, 0.0, 0.0, 1.0 ) },
				{-1.0f, 1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 1.0, 0.0, 0.0, 1.0 ) },
				{-1.0f,-1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 1.0, 0.0, 0.0, 1.0 ) },
				{ 1.0f,-1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 1.0, 0.0, 0.0, 1.0 ) },

				// Back
				{-1.0f, 1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 1.0, 1.0, 0.0, 1.0 ) },
				{ 1.0f, 1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 1.0, 1.0, 0.0, 1.0 ) },
				{ 1.0f,-1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 1.0, 1.0, 0.0, 1.0 ) },
				{-1.0f,-1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 1.0, 1.0, 0.0, 1.0 ) },

				// Right
				{ 1.0f, 1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 1.0, 0.0, 1.0, 1.0 ) },
				{ 1.0f, 1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 1.0, 0.0, 1.0, 1.0 ) },
				{ 1.0f,-1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 1.0, 0.0, 1.0, 1.0 ) },
				{ 1.0f,-1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 1.0, 0.0, 1.0, 1.0 ) },

				// Left
				{-1.0f, 1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 0.0, 1.0, 1.0, 1.0 ) },
				{-1.0f, 1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 0.0, 1.0, 1.0, 1.0 ) },
				{-1.0f,-1.0f,-1.0f,  D3DCOLOR_COLORVALUE( 0.0, 1.0, 1.0, 1.0 ) },
				{-1.0f,-1.0f, 1.0f,  D3DCOLOR_COLORVALUE( 0.0, 1.0, 1.0, 1.0 ) }
			};
		static LPDIRECT3DVERTEXBUFFER9 vertexBuffer = NULL;
		if (NULL == vertexBuffer)
		{
			pDXDevice->CreateVertexBuffer(24 * sizeof(Vertex), 0, D3DFVF_XYZ | D3DFVF_DIFFUSE,
				D3DPOOL_DEFAULT, &vertexBuffer, NULL);

			Vertex* verticesPointer = NULL;
			vertexBuffer->Lock(0, sizeof(vertices), (void**)&verticesPointer, 0);
			memcpy(verticesPointer, vertices, sizeof(vertices));
			vertexBuffer->Unlock();
		}
		pDXDevice->BeginScene();
		pDXDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));
		pDXDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
		pDXDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 24);
		pDXDevice->EndScene();
	}

} // namespace Window
} // namespace Gfx3D
} // namespace Yuni

#endif // YUNI_WINDOWSYSTEM_MSW && YUNI_USE_DIRECTX
