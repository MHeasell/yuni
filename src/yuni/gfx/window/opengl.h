#ifndef __YUNI_GFX_WINDOW_OPENGL_H__
# define __YUNI_GFX_WINDOW_OPENGL_H__

# include "../api/api.h"


namespace Yuni
{
namespace Gfx
{
namespace Window
{


	/*!
	** \brief Window for OpenGL rendering
	*/
	class AOpenGL: public Api::IGfxAPI
	{
	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Contructor
		*/
		AOpenGL() {}
		//! Destructor
		virtual ~AOpenGL() {}
		//@}

	protected:
		/*!
		** \brief Initalize OpenGL
		**
		** This ought to be called from overriden implementations
		*/
		virtual bool initialize();

		/*!
		** \brief For GL, implementation does nothing
		**
		** This ought to be called from overriden implementations
		*/
		virtual void release() {}

		/*!
		** \brief Resize the window
		*/
		virtual void resize(unsigned int width, unsigned int height);

	}; // class OpenGL




} // namespace Window
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_WINDOW_OPENGL_H__
