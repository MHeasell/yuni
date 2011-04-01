
# include "glsurface.h"


namespace Yuni
{
namespace Private
{
namespace UI
{
namespace Local
{


	bool GLSurface::initialize()
	{
		// Enable Smooth Shading
		glShadeModel(GL_SMOOTH);

		// Background Clear Color
		glClearColor(0.f, 0.f, 0.f, 0.0f);

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



} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni
