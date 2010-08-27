#ifndef __YUNI_GFX_SURFACE_ASURFACE3D_H__
# define __YUNI_GFX_SURFACE_ASURFACE3D_H__

# include "surface.h"

namespace Yuni
{
namespace Gfx
{
namespace Surface
{

	/*!
	** \brief A 3D surface can be drawn on using a scene tree and a camera
	**
	** It keeps track of render time, FPS count, and can keep
	** implementation-dependent mesh representations to speed things up.
	**
	** This is also a way to define a common interface to OpenGL and DirectX.
	*/
	class ASurface3D: public ASurface
	{
	public:
		typedef SmartPtr<ASurface3D> Ptr;

	protected:
		/*!
		** \brief Main constructor
		*/
		ASurface3D() : pPaused(false) {}

	public:
		//! \brief Virtual destructor
		virtual ~ASurface3D() {}

	private:
		//! Private copy constructor
		ASurface3D(const ASurface3D&);

	public:

		//! Pause / Unpause rendering
		virtual void pause(bool inPause) { pPaused = inPause; }

	protected:
		//! Draw one frame to backbuffer
		void drawFrame(const Yuni::Gfx::Scene& scene);

		//! Reset the view matrices
		virtual void resetView() = 0;

		//! Apply view translation
		virtual void applyTranslation(const Vector3D<float>& translation) = 0;

		//! Apply view rotation
		virtual void applyRotation(const Vector3D<float>& rotation) = 0;

		//! Draw some triangles
		virtual void drawTriangles(const Mesh::TriangleList& triangles) = 0;

		//! TEMPORARY
		virtual void testDraw() = 0;

	protected:
		//! Is the rendering paused ?
		bool pPaused;

		//! 3D scene associated with this surface
		Scene::Ptr pScene;

	}; // ASurface3D




} // namespace Surface
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_SURFACE_ASURFACE3D_H__
