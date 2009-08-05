#ifndef __YUNI_GFX3D_WINDOW_OPENGL_H__
# define __YUNI_GFX3D_WINDOW_OPENGL_H__

# include "../window/window.h"


namespace Yuni
{
namespace Gfx3D
{
namespace Window
{


	/*!
	** \brief Window for OpenGL rendering
	*/
	class OpenGL: public AWindow
	{
	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Contructor
		*/
		OpenGL(const String& title, unsigned int width, unsigned int height, unsigned int bitDepth, bool fullScreen)
			:AWindow(title, width, height, bitDepth, fullScreen)
		{}
		//! Destructor
		virtual ~OpenGL() {}
		//@}

	protected:
		/*!
		** \brief Initalize OpenGL
		**
		** This ought to be called from overriden implementations
		** (i.e. GLWindow::initialize(); )
		*/
		virtual bool initialize();

		/*!
		** \brief For GL, implementation does nothing
		**
		** This ought to be called from overriden implementations
		** (i.e. GLWindow::close(); )
		*/
		virtual void close();

		/*!
		** \brief Resize the window
		*/
		virtual void resize(unsigned int width, unsigned int height);

	}; // class OpenGL





} // namespace Window
} // namespace Gfx3D
} // namespace Yuni

#endif // __YUNI_GFX3D_WINDOW_OPENGL_H__
