#ifndef __YUNI_PRIVATE_GFX_OPENGL_ENGINE_H__
# define __YUNI_PRIVATE_GFX_OPENGL_ENGINE_H__

# include "gl.h"
# include "../abstract.h"
# include "../../../gfx/core/color/rgba.h"

namespace Yuni
{
namespace Private
{
namespace Gfx
{
namespace Gl
{

	/*!
	** \class Engine
	** \brief Graphics engine specialization for OpenGL
	*/
	class Engine : public Private::Gfx::EngineAbstract
	{
	public:

		//! \name Constructors & Destructor
		//@{
		Engine();
		Engine(SmartPtr<Yuni::Gfx::Device> dc);
		virtual ~Engine();
		//@}

		virtual String name() const {return "Yuni GL Engine";}

		virtual bool initialize(SmartPtr<Yuni::Gfx::Device> dc);
		virtual void release();
		virtual bool ready() const { return pRunnable; }
		virtual void run();
		virtual void waitForEngineToStop();
		virtual void applicationTitle(const String& t);

	private:
		//! The yuni device
		SmartPtr<Yuni::Gfx::Device> pDevice;
		//! Background color
		Yuni::Gfx::Color::RGBA<float> pBackgroundColor;
		//! Can the engine be run?
		bool pRunnable;

	}; // class Engine




} // namespace Gl
} // namespace Gfx
} // namespace Private
} // namespace Yuni



#endif // __YUNI_PRIVATE_GFX_OPENGL_ENGINE_H__
