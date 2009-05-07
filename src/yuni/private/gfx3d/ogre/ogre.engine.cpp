
#include "ogre.h"
#include "ogre.engine.h"
#include "../../../toolbox/string.h"
#include "../../../toolbox/system/sleep.h"
#include "../../../threads.h"
#include <iostream>

#ifdef YUNI_OS_DARWIN
#include <CoreFoundation/CoreFoundation.h>

// This function will locate the path to our application on OS X,
// unlike windows you can not rely on the current working directory
// for locating your configuration files and resources.
static Yuni::String macBundlePath()
{
    char path[1024];
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    assert(mainBundle);

    CFURLRef mainBundleURL = CFBundleCopyBundleURL(mainBundle);
    assert(mainBundleURL);

    CFStringRef cfStringRef = CFURLCopyFileSystemPath( mainBundleURL, kCFURLPOSIXPathStyle);
    assert(cfStringRef);

    CFStringGetCString(cfStringRef, path, 1024, kCFStringEncodingASCII);

    CFRelease(mainBundleURL);
    CFRelease(cfStringRef);

    return Yuni::String(path);
}
#endif


namespace Yuni
{
namespace Private
{
namespace Gfx
{
namespace Ogre
{

	Engine::Engine()
		:Private::Gfx::EngineAbstract(), pRoot(NULL), pWindow(NULL), pRunnable(false)
	{
		#ifdef YUNI_OS_DARWIN
		pResourcePath = macBundlePath() + "/Contents/Resources/";
		#else
		pResourcePath = "";
		#endif
	}

	Engine::Engine(SmartPtr<Yuni::Gfx::Device> dc)
		:Private::Gfx::EngineAbstract(), pRoot(NULL), pWindow(NULL)
	{
		this->initialize(dc);

		#ifdef YUNI_OS_DARWIN
		pResourcePath = macBundlePath() + "/Contents/Resources/";
		#else
		pResourcePath = "";
		#endif
	}


	Engine::~Engine()
	{
		pRunnable = false;
		onFPSChanged.disconnectAll();
		release();
	}



	bool Engine::initialize(SmartPtr<Yuni::Gfx::Device> dc)
	{
		// We keep a reference to the yuni device
		if (NULL == dc)
			return false;

		// Ensure that a device is not already initialized
		release();
		// Getting a reference to the information about the Device
		pDevice = dc;
		String pluginsPath = pResourcePath + "plugins.cfg";
		// Create the Ogre root
		pRoot = new ::Ogre::Root(pluginsPath.data(), pResourcePath + "ogre.cfg", pResourcePath + "Ogre.log");

		if (!pRoot)
			return false;

		// Initialise the renderer but do not create a default window
		pRoot->initialise(false);

		::Ogre::NameValuePairList params;
		#ifdef YUNI_OS_WINDOWS
		params["colourDepth"] = String((uint16)pDevice->resolution()->bitPerPixel()).data();
		#endif
		// We create our own custom window with our own settings
		pWindow = pRoot->createRenderWindow(pApplicationTitle.data(), pDevice->resolution()->width(), pDevice->resolution()->height(), pDevice->fullscreen(), &params);

		// Set the window caption
		this->applicationTitle(pApplicationTitle);
		pRunnable = true;
		return true;
	}



	void Engine::run()
	{
		if (!pRoot) // No device, aborting
			return;

		// The Ogre scene manager
		pSceneManager = pRoot->createSceneManager(::Ogre::ST_GENERIC, ::Ogre::String(pApplicationTitle.data()));
		// Those vars must be valid
		if (!pWindow || !pSceneManager) // It seems that is not the case
			return;

		// Reduces the scheduling priority for some processes
		// . When the FPS counter changes, it broadcasts an event. However, this information
		//   is not critical and the scheduling priority should be decreased
		// . It is the same to check if the window is active
		int limitCPUConsuming = 1;
		// Indicates that the engine is running
		pIsRunning = true;
		// Ready to loop
		pRunnable = true;

		while (pRunnable) // Cycle
		{
			pRoot->renderOneFrame();
			//// Begin the entire scene
			//pIrrVideoDriver->beginScene(true, true, pBackgroundColor);
			//// Draw all 3D objects
			//pIrrSceneManager->drawAll();
			//// End
			//pIrrVideoDriver->endScene();

			//--limitCPUConsuming;
			//if (0 == limitCPUConsuming)
			//{
			//	// Frames per second
			//	int currentFPS = pWindow->getLastFPS();
			//	if (currentFPS != pFPS)
			//	{
			//		pFPS = currentFPS;
			//		// Call event onFPSChanged here
			//		this->onFPSChanged(pFPS);
			//	}

			//	// When the window is inactive, there is no need for full-speed
			//	if (!pIrrDevice->isWindowActive())
			//	{
			//		Yuni::SleepMilliSeconds(30 /*ms*/);
			//	}

			//	// Next in 10 cycles
			//	limitCPUConsuming = 10; 
			// }
		}

		// Resetting vars
		pIsRunning = false;
		pSceneManager = NULL;
	}


	void Engine::release()	
	{
		pRunnable = false;
		if (pRoot)
		{
			// Close the device
			waitForEngineToStop();
			// Destroy the Irrlicht device
			if (pRoot) // double check
				delete pRoot;
		}
		pSceneManager = NULL;
		pWindow = NULL;
		pRoot = NULL;
	}



	/*!
	 * \todo Must be removed. Created for debug purposes
	 */
	class ThreadWaitForEngineToStop : public Yuni::Threads::AThread
	{
	public:
		ThreadWaitForEngineToStop(Yuni::Private::Gfx::EngineAbstract& engineToWait)
			:Yuni::Threads::AThread(), pEngineToWait(engineToWait)
		{}

		~ThreadWaitForEngineToStop() {stop();}

		virtual void onExecute()
		{
			while (pEngineToWait.isRunning())
			{
				//suspend(1000 /* ms */);
				SleepMilliSeconds(1000);
				std::cout << "Wait...\n";
			}
		}

	private:
		Yuni::Private::Gfx::EngineAbstract& pEngineToWait;
	};



	void Engine::waitForEngineToStop()
	{
		// We should stop as soon as possible
		pRunnable = false;

		if (pRoot && pIsRunning)
		{
			ThreadWaitForEngineToStop th(*this);
			th.start();
			// Let the other thread
			SleepMilliSeconds(100 /* ms */);
			th.stop(10);

			// Does not destroy the device, it will only be closed
			pRoot->shutdown();
		}
	}


	void Engine::applicationTitle(const String& t)
	{
		pMutex.lock();
		if (pRoot)
		{
			pApplicationTitle = t;
			// TODO: Find a way to do this. Is it even possible?
			// pRoot->setWindowCaption(t);
		}
		pMutex.unlock();
	}




} // namespace Ogre
} // namespace Gfx
} // namespace Private
} // namespace Yuni

