
#include "../api/gl.h"
#include "opengl.h"


namespace Yuni
{
namespace Gfx
{
namespace Window
{

	bool AOpenGL::initialize()
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

		// flush
		glFlush();
		return true;
	}


	void AOpenGL::resize(unsigned int width, unsigned int height)
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



} // namespace Window
} // namespace Gfx
} // namespace Yuni
