#ifndef __YUNI_GFX_SURFACE_SURFACE3D_H__
# define __YUNI_GFX_SURFACE_SURFACE3D_H__

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
	class ISurface3D: public ISurface
	{
	public:
		//! The most suitable smart pointer for the class
		typedef SmartPtr<ISurface3D> Ptr;

	public:
		//! Pause / Unpause rendering
		virtual void pause(bool inPause) { pPaused = inPause; }


		//! \name Vertical Synchronization (VSync)
		//@{
		//! Is vertical synchronization (VSync) currently active?
		virtual bool verticalSync() const = 0;

		/*!
		** \brief Activate / deactivate vertical synchronization (VSync)
		**
		** \param active New value for vertical sync, true for active, false for inactive.
		** \return False if changing vertical sync failed. Yes, the stupid thing _can_ fail.
		*/
		virtual bool verticalSync(bool active) = 0;
		//@}


	protected:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Main constructor
		*/
		ISurface3D() : pPaused(false) {}

		/*!
		** \brief Virtual destructor
		*/
		virtual ~ISurface3D() {}
		//@}

		//! Refresh the view
		bool refresh();

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

		//! Event callback for a change in frames per second. To be overridden.
		virtual void onFPSChanged(unsigned int /* FPS */) {}

		//! TEMPORARY
		virtual void testDraw() = 0;

	protected:
		//! Is the rendering paused ?
		bool pPaused;
		//! 3D scene associated with this surface
		Scene::Ptr pScene;

	private:
		/*!
		** Private copy constructor
		*/
		ISurface3D(const ISurface3D&);

	}; // ISurface3D





} // namespace Surface
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_SURFACE_SURFACE3D_H__
