
#include "dx9.h"

#if defined(YUNI_WINDOWSYSTEM_MSW) && defined(YUNI_USE_DIRECTX)

namespace Yuni
{
namespace Gfx
{

	DX9Font::DX9Font(LPDIRECT3DDEVICE9 device, const String& fontFace,
		unsigned int size, bool bold, bool italic)
		: AFont(fontFace, size, bold, italic), pInitialized(false),
		  pDXDevice(device)
	{}


	DX9Font::~DX9Font()
	{}


	void DX9Font::drawText(const String& text, unsigned int left,
		unsigned int top, unsigned int right, unsigned int bottom)
	{
		if (!pInitialized)
			; // Do init
		// Draw
	}


} // namespace Gfx
} // namespace Yuni
