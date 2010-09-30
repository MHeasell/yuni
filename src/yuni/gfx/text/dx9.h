#ifndef __YUNI_GFX_TEXT_DX9_H__
# define __YUNI_GFX_TEXT_DX9_H__

# include "../../yuni.h"

# if defined(YUNI_WINDOWSYSTEM_MSW) && defined(YUNI_USE_DIRECTX)
#	include "../../core/system/windows.hdr.h"
#	include "../api/dx9.h"
#	include "./font.h"

namespace Yuni
{
namespace Gfx
{

	/*!
	** \brief MSWindows with DirectX9-specific implementation of a font
	*/
	class DX9Font: public AFont
	{
	public:
		DX9Font(LPDIRECT3DDEVICE9 device, const String& fontFace,
			unsigned int size, bool bold = false, bool italic = false);
		~DX9Font();

		//! Draw some text using this font
		virtual void drawText(const String& text, unsigned int left,
			unsigned int top, unsigned int right, unsigned int bottom);

	private:
		//! Actually create the font
		bool createFont();

	private:
		//! Windows font
		HFONT pFont;

		//! Has the font been initialized yet?
		bool pInitialized;

		//! DirectX device
		LPDIRECT3DDEVICE9 pDXDevice;

	}; // DX9Font

} // namespace Gfx
} // namespace Yuni

#endif // YUNI_WINDOWSYSTEM_MSW && YUNI_USE_DIRECTX

#endif // __YUNI_GFX_TEXT_DX9_H__

