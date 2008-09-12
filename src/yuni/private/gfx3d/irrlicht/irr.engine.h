#ifndef __YUNI_PRIVATE_GFX_IRRLICHT_ENGINE_H__
# define __YUNI_PRIVATE_GFX_IRRLICHT_ENGINE_H__

# include "irr.h"
# include "../abstract.h"


namespace Yuni
{
namespace Private
{
namespace Gfx
{
namespace Irrlicht
{


	class Engine : public Private::Gfx::Abstract
	{
	public:
		Engine();
		Engine(SharedPtr<Yuni::Gfx::Device> dc);
		virtual ~Engine();

		virtual String name() const {return "Irrlicht Engine";}

		virtual bool initialize(SharedPtr<Yuni::Gfx::Device> dc);
		virtual void release();
		virtual bool ready() const {return (pIrrDevice != NULL);}
		virtual void run();

	private:
		static irr::video::E_DRIVER_TYPE YuniDeviceToIrrDevice(const Yuni::Gfx::Device::Type& t);

	private:
		//! The yuni device
		SharedPtr<Yuni::Gfx::Device> pDevice;
		//! The Irrlicht device
		irr::IrrlichtDevice* pIrrDevice;
		//! The Irrlicht Video Device
		irr::video::IVideoDriver* pIrrVideoDriver;
		//! The Irrlicht Scene manager
		irr::scene::ISceneManager* pIrrSceneManager;

	}; // class Engine


} // namespace Irrlicht
} // namespace Gfx
} // namespace Private
} // namespace Yuni



#endif // __YUNI_PRIVATE_GFX_IRRLICHT_ENGINE_H__
