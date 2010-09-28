#ifndef __YUNI_GFX_WINDOW_DIRECTX_MSW_H__
# define __YUNI_GFX_WINDOW_DIRECTX_MSW_H__

# include "../../../yuni.h"

# if defined(YUNI_WINDOWSYSTEM_MSW) && defined(YUNI_USE_DIRECTX)
#	include "../../../core/system/windows.hdr.h"
#	include "../../api/dx9.h"
#   include "../../surface/surface3d.h"
#	include "msw.h"


namespace Yuni
{
namespace Gfx
{
namespace Window
{

	/*!
	** \brief Implementation of an MFC window that uses DirectX display
	*/
	class DirectXMSW: public IMSWindows, public Surface::ISurface3D
	{
	public:
		//! The Threading Policy
		typedef IMSWindows::ThreadingPolicy ThreadingPolicy;

	public:
		DirectXMSW(UI::Window::Ptr& source, unsigned int bitDepth, bool fullScreen)
			:IMSWindows(source, bitDepth, fullScreen),
			pDXObject(NULL), pDXDevice(NULL), pVSync(false) // Deactivate vsync by default
		{
			pWindowClassName = "DirectX";
		}

		virtual bool initialize();
		virtual void close();
		virtual void resize(float width, float height);
		virtual Surface::ISurface3D* surface() { return this; }

		//! Is vertical synchronization (VSync) active?
		virtual bool verticalSync() const;
		//! Activate / deactivate vertical synchronization (VSync)
		virtual bool verticalSync(bool activate);

	protected:
		/*!
		** \brief Refresh the window content if necessary
		**
		** \returns Always refresh in DirectX view
		*/
		virtual bool refresh() { return true; }
		virtual void blitWL() { pDXDevice->Present(NULL, NULL, pHWnd, NULL); }

		//! \name Overridden from ISurface3D
		//@{
		//! Set the default color for clearing the surface
		virtual void clearColor(const Color::RGB<uint8>& newColor);
		virtual void clearScreen();
		virtual void resetView();
		virtual void applyTranslation(const Vector3D<float>& translation);
		virtual void applyRotation(const Vector3D<float>& rotation);
		virtual void drawTriangles(const Mesh::TriangleList& triangles);
		virtual void testDraw();
		virtual void release();
		//@}

	private:
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

		//! Clear color
		Color::RGB<uint8> pClearColor;

	}; // class DirectxMSW




} // namespace Window
} // namespace Gfx
} // namespace Yuni


# endif // YUNI_WINDOWSYSTEM_MSW && YUNI_USE_DIRECTX

#endif // __YUNI_GFX_WINDOW_DIRECTX_MSW_H__
