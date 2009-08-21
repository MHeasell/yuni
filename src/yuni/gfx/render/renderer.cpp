
# include <algorithm>
# include "renderer.h"

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
		applyRotation(Vector3D<float>(rotQuad * 1.0f, rotQuad * 0.5f, rotQuad * 0.25f));
		testDraw();
		rotQuad += 0.1f;
		////// End Test Draw

		// All objects
		const Gfx::Scene::Objects& objects = scene.objects();

		// Foreach object
		const Gfx::Scene::Objects::const_iterator endObj = objects.end();
		for (Gfx::Scene::Objects::const_iterator it = objects.begin(); it != endObj; ++it)
		{
			// The skeleton
			const Gfx::Skeleton::Ptr& skel = it->second->skeleton();

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
