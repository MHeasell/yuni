
#include "../../core/string.h"
#include "wgl.h"

#ifdef YUNI_WINDOWSYSTEM_MSW

namespace Yuni
{
namespace Gfx
{

	WGLFont::WGLFont(const String& fontFace, unsigned int size, bool bold, bool italic)
		: AFont(fontFace, size, bold, italic), pInitialized(false)
	{}

	WGLFont::~WGLFont()
	{
		if (pInitialized)
		{
			DeleteObject(pFont);
			glDeleteLists(pDisplayList, 96);
		}
	}

	void WGLFont::drawText(const String& text, unsigned int /*left*/, unsigned int /*top*/,
		unsigned int /*right*/, unsigned int /*bottom*/)
	{
		if (!pInitialized)
		{
			pInitialized = createFont();
			if (!pInitialized)
			{
				glDeleteLists(pDisplayList, 96);
				return;
			}
		}

		// Set color and position
		glColor3f(0.8f, 0.8f, 0.0f);
		glRasterPos2f(-2.0f, 0.0f);
		// Prevent our display list from affecting other display lists
		glPushAttrib(GL_LIST_BIT);
		glListBase(pDisplayList - 32);
		glCallLists(text.length(), GL_UNSIGNED_BYTE, Traits::CString<String>::Perform(text));
		glPopAttrib();
	}

	bool WGLFont::createFont()
	{
		pDisplayList = glGenLists(96);
		// Height is negative so as to choose character height, not cell height.
		// Use mostly default values, force antialiasing, prefer TrueType fonts.
		pFont = CreateFont(-(int)pSize, 0, 0, 0, pBold ? FW_BOLD : FW_NORMAL,
			pItalic, false, false, DEFAULT_CHARSET, OUT_TT_PRECIS,
			CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH,
			Traits::CString<String>::Perform(pFace));

		HDC hDC = wglGetCurrentDC();
		SelectObject(hDC, pFont);

		return wglUseFontBitmaps(hDC, 32, 96, pDisplayList) ? true : false;

		// This is the code for outline fonts. Outline fonts are drawn as real 3D polygons. They can also be drawn as wireframe.
	//	GLYPHMETRICSFLOAT gmf[96];
 	//	float depth = 0.0f; // Possible extrusion
 	//	return wglUseFontOutlines(hDC, 32, 96, pDisplayList, 0.0f, depth, WGL_FONT_POLYGONS, gmf);
	}

} // namespace Gfx
} // namespace Yuni

#endif // YUNI_WINDOWSYSTEM_MSW
