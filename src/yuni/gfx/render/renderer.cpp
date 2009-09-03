
#include <algorithm>
#include "renderer.h"
#include "../text/label.h"
#include "../text/wgl.h"

namespace Yuni
{
namespace Gfx
{
namespace Render
{

	void ARenderer::drawFrame(const Yuni::Gfx::Scene& scene)
	{
		if (pPaused)
			return;

		pCounter.addFrames(1);

		// Clear the screen to a unique color
		clearScreen();

		////// Test Draw
		static float rotQuad = 0.1f;

		resetView();
		applyTranslation(Vector3D<float>(0.0f, 0.0f, -7.0f));
		//applyRotation(Vector3D<float>(rotQuad * 1.0f, rotQuad * 0.5f, rotQuad * 0.25f));
		testDraw();
		resetView();
		applyTranslation(Vector3D<float>(0.0f, 0.0f, -4.0f));
		#ifdef YUNI_WINDOWSYSTEM_MSW
		wchar_t* wideText = _wcsdup(L"Font display test: kanji XX, kana XXXX!");
		// FIXME: This code fails on wcstombs_s, special characters are not managed properly. What to do?
		// TEN
		//wideText[25] = ('\x59' << 8) | '\x29';
		// CHI
		//wideText[26] = ('\x57' << 8) | '\x30';
		// SU
		//wideText[34] = ('\x30' << 8) | '\x59';
		// GO
		//wideText[35] = ('\x30' << 8) | '\x54';
		// I
		//wideText[36] = ('\x30' << 8) | '\x44';
		// I
		//wideText[37] = ('\x30' << 8) | '\x44';

		Label label(AFont::Ptr(new WGLFont("Arial", 45)), wideText, 50, 50);
		label.draw();
		delete[] wideText;
		#endif // YUNI_WINDOWSYSTEM_MSW
		rotQuad += 0.1f;
		////// End Test Draw

		// All objects
		const Gfx::Scene::Objects& objects = scene.objects();

		// Foreach object
		const Gfx::Scene::Objects::const_iterator endObj = objects.end();
		for (Gfx::Scene::Objects::const_iterator it = objects.begin(); it != endObj; ++it)
		{
			// The skeleton
			Gfx::Skeleton::Ptr skel = it->second->skeleton();

			// Reset matrices used for view: translation and rotation
			resetView();

			// Translation
			applyTranslation(skel->position());

			// Rotation
			applyRotation(skel->rotation());

			// Foreach triangle
			drawTriangles(skel->mesh()->triangles());

		} // foreach object
	}




} // namespace Render
} // namespace Gfx3D
} // namespace Yuni
