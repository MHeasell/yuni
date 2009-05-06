#ifndef __YUNI_PRIVATE_GFX_OGRE_ENGINE_H__
# define __YUNI_PRIVATE_GFX_OGRE_ENGINE_H__

# include "ogre.h"
# include "../abstract.h"

namespace Yuni
{
namespace Private
{
namespace Gfx
{
namespace Ogre
{

	/*!
	** \class Engine
	** \brief Graphics engine specialization for Ogre
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

		virtual String name() const {return "Ogre3D Engine";}

		virtual bool initialize(SmartPtr<Yuni::Gfx::Device> dc);
		virtual void release();
		virtual bool ready() const {return (pRoot != NULL);}
		virtual void run();
		virtual void waitForEngineToStop();
		virtual void applicationTitle(const String& t);

	private:
		//! The yuni device
		SmartPtr<Yuni::Gfx::Device> pDevice;
		//! The Ogre system root
		::Ogre::Root* pRoot;
		//! The Ogre rendering window
		::Ogre::RenderWindow* pWindow;
		//! The Ogre Scene manager
		::Ogre::SceneManager* pSceneManager;
		//! Resource path, system-dependent
		::Ogre::String pResourcePath;
		//! Can the engine be run?
		bool pRunnable;

	}; // class Engine




} // namespace Ogre
} // namespace Gfx
} // namespace Private
} // namespace Yuni



#endif // __YUNI_PRIVATE_GFX_OGRE_ENGINE_H__
