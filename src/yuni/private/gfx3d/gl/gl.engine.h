#ifndef __YUNI_PRIVATE_GFX_OPENGL_ENGINE_H__
# define __YUNI_PRIVATE_GFX_OPENGL_ENGINE_H__

# include "gl.h"
# include "../abstract.h"
# include "../../../gfx/core/color/rgba.h"

namespace Yuni
{
namespace Private
{
namespace GfxImpl
{
namespace Gl
{

	/*!
	** \brief Graphics engine specialization for OpenGL
	*/
	class Engine : public EngineAbstract
	{
	public:
		//! \name Constructors & Destructor
		//@{
		Engine();
		Engine(const Yuni::Gfx::Device::Ptr& dc);
		virtual ~Engine();
		//@}

		virtual String name() const {return "Yuni GL Engine";}

		virtual bool initialize(const Yuni::Gfx::Device::Ptr& dc);
		virtual void release();
		virtual bool ready() const { return pRunnable; }
		virtual void run();
		virtual void waitForEngineToStop();
		virtual void applicationTitle(const String& t);

	private:
		//! Background color
		Yuni::Gfx::Color::RGBA<float> pBackgroundColor;
		//! Can the engine be run?
		bool pRunnable;

	}; // class Engine




} // namespace Gl
} // namespace GfxImpl
} // namespace Private
} // namespace Yuni



#endif // __YUNI_PRIVATE_GFX_OPENGL_ENGINE_H__
