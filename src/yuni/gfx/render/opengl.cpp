
# include <algorithm>
# include "../api/gl.h"
# include "opengl.h"

namespace Yuni
{
namespace Gfx
{
namespace Render
{

	bool OpenGL::initialize()
	{
		// Enable Smooth Shading
		glShadeModel(GL_SMOOTH);
		// Black Background
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		// Depth Buffer Setup
		glClearDepth(1.0f);
		// Enables Depth Testing
		glEnable(GL_DEPTH_TEST);
		// The type of depth testing to do
		glDepthFunc(GL_LEQUAL);
		// Really nice perspective calculations
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		// Flush
		glFlush();
		return true;
	}

	void OpenGL::release()
	{}

	void OpenGL::resize(unsigned int width, unsigned int height)
	{
		// Prevent A Divide By Zero
		if (0 == height)
			height = 1;

		// Reset The Current Viewport
		glViewport(0, 0, width, height);

		// Select the Projection Matrix
		glMatrixMode(GL_PROJECTION);
		// Reset the Projection Matrix
		glLoadIdentity();

		// Calculate the Aspect Ratio of the window
		gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

		// Select the Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		// Reset the Modelview Matrix
		glLoadIdentity();
	}

	void OpenGL::clearScreen()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGL::resetView()
	{
		glLoadIdentity();
	}

	void OpenGL::applyTranslation(const Vector3D<float>& translation)
	{
		glTranslatef(translation.x, translation.y, translation.z);
	}

	void OpenGL::applyRotation(const Vector3D<float>& rotation)
	{
		glRotatef(rotation.x,1.0,0.0,0.0); // Rotate on x
		glRotatef(rotation.y,0.0,1.0,0.0); // Rotate on y
		glRotatef(rotation.z,0.0,0.0,1.0); // Rotate on z
	}

	void OpenGL::drawTriangles(const Mesh::TriangleList& triangles)
	{
		// Foreach triangle
		const Gfx::Mesh::TriangleList::const_iterator endtr = triangles.end();
		for (Gfx::Mesh::TriangleList::const_iterator it = triangles.begin(); it != endtr; ++it)
		{
			glBegin(GL_TRIANGLES);
			Gfx::Point3D<float> v1 = (*it)->vertex1().position();
			glVertex3f(v1.x, v1.y, v1.z);
			Gfx::Point3D<float> v2 = (*it)->vertex2().position();
			glVertex3f(v2.x, v2.y, v2.z);
			Gfx::Point3D<float> v3 = (*it)->vertex3().position();
			glVertex3f(v3.x, v3.y, v3.z);
			glNormal3f((*it)->normal().x, (*it)->normal().y, (*it)->normal().z);
			glEnd();
		}
	}

	void OpenGL::testDraw()
	{
// 			glRotatef(rotQuad, 1.0f, 0.5f, 0.25f);
		glBegin(GL_QUADS);
		/* top of cube */
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		/* bottom of cube */
		glColor3f(1.0f, 0.5f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		/* front of cube */
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		/* back of cube */
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		/* right side of cube */
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		/* left side of cube */
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glEnd();
	}



} // namespace Render
} // namespace Gfx3D
} // namespace Yuni
