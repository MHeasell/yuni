#ifndef __YUNI_GFX_SURFACE_OPENGL_H__
# define __YUNI_GFX_SURFACE_OPENGL_H__

# include "surface3d.h"

namespace Yuni
{
namespace Gfx
{
namespace Surface
{



	/*!
	** \brief An OpenGL surface
	**
	** For the moment, this is a naive unoptimized implementation.
	*/
	class OpenGL: public ISurface3D
	{
	protected:
		//! Initalize OpenGL
		virtual bool initialize();

		//! For GL, implementation does nothing
		virtual void release();

		//! Resize the viewport
		virtual void resize(float width, float height);

		//! Choose a color to clear the screen with
		virtual void clearColor(Color::RGB<uint8>& newColor);

		//! Clear the screen to black
		virtual void clearScreen();

		//! Reset the view matrices
		virtual void resetView();

		//! Apply view translation
		virtual void applyTranslation(const Vector3D<float>& translation);

		//! Apply view rotation
		virtual void applyRotation(const Vector3D<float>& rotation);

		//! Draw some triangles
		virtual void drawTriangles(const Mesh::TriangleList& triangles);

		//! TEMPORARY
		virtual void testDraw();

	}; // class OpenGL



} // namespace Surface
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_SURFACE_OPENGL_H__
