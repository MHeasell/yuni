#ifndef __YUNI_GFX_RENDER_OPENGL_H__
# define __YUNI_GFX_RENDER_OPENGL_H__

# include "renderer.h"

namespace Yuni
{
namespace Gfx
{
namespace Render
{

	/*!
	** \brief OpenGL implementation of a renderer
	**
	** For the moment, this is a naive unoptimized implementation.
	*/
	class OpenGL: public ARenderer
	{
	protected:
		//! Initalize OpenGL
		virtual bool initialize();

		//! For GL, implementation does nothing
		virtual void release();

		//! Resize the viewport
		virtual void resize(unsigned int width, unsigned int height);

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

	}; // OpenGL

} // namespace Render
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_RENDER_OPENGL_H__
