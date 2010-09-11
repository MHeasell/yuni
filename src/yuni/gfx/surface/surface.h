#ifndef __YUNI_GFX_SURFACE_SURFACE_H__
# define __YUNI_GFX_SURFACE_SURFACE_H__

# include "../../yuni.h"
# include "../../core/smartptr.h"
# include "../scene.h"
# include "../../core/color/rgb.h"
# include "../../core/color/rgba.h"


namespace Yuni
{
namespace Gfx
{
namespace Surface
{



	/*!
	** \brief A drawing surface is where we can draw stuff for display
	**
	** This is a common interface to Cairo, OpenGL and DirectX backends.
	*/
	class ISurface
	{
	public:
		typedef SmartPtr<ISurface> Ptr;

	protected:
		/*!
		** \brief Main constructor
		*/
		ISurface() {}

		/*!
		** \brief Virtual destructor
		*/
		virtual ~ISurface() {}

	private:
		/*!
		** \brief Private copy cosntructor
		*/
		ISurface(const ISurface&);

	public:
		//! Initialize the surface
		virtual bool initialize() = 0;

		//! Release the surface (uninitialize)
		virtual void release() = 0;

		//! Resize the viewport
		virtual void resize(size_t width, size_t height) = 0;

		//! Refresh view
		virtual bool refresh() = 0;

		//! Set the default color for clearing the surface
		virtual void clearColor(Color::RGB<uint8>& newColor);

	protected:
		//! Clear the surface to clear color, default color depends on back-end
		virtual void clearScreen() = 0;

	protected:
		bool pPaused;

	}; // class ISurface




} // namespace Surface
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_SURFACE_SURFACE_H__
