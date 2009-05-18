
#include "ogre.h"
#include <ogrefontmanager.h>
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

	/*!
	** \brief Frame rendering event listener for FPS statistics display
	*/
	class FPSFrameListener: public ::Ogre::FrameListener, public ::Ogre::WindowEventListener
	{
	public:
		FPSFrameListener(::Ogre::RenderWindow* window): pWindow(window), pLimitCPUConsuming(1)
		{
			try
			{
				// Create the overlay
				::Ogre::OverlayManager& manager = ::Ogre::OverlayManager::getSingleton();
				::Ogre::Overlay* overlay = manager.create("FPS Stats");
				// Create a panel in the overlay
				::Ogre::OverlayContainer* panel = (::Ogre::OverlayContainer*)manager.createOverlayElement("Panel", "FPS Stats Panel");
				overlay->add2D(panel);
				// Create the various text areas in the panel
				panel->addChild(createTextArea("AverageFps"));
				panel->addChild(createTextArea("CurrFps"));
				panel->addChild(createTextArea("BestFps"));
				panel->addChild(createTextArea("WorstFps"));
				panel->addChild(createTextArea("NumTris"));
				panel->addChild(createTextArea("NumBatches"));

				overlay->show();

				panel->setDimensions(300, 200);
			}
			catch(::Ogre::Exception e)
			{
				int a = 0;
			}
		}

		//! Called when a frame is about to begin rendering.
		virtual bool frameStarted(const ::Ogre::FrameEvent& evt)
		{
			return true;
		}

		//! Called after all render targets have had their rendering commands issued, but before render windows have been asked to flip their buffers over. 
		virtual bool frameRenderingQueued(const ::Ogre::FrameEvent& evt)
		{
			return true;
		}

		//! Called just after a frame has been rendered.
		virtual bool frameEnded(const ::Ogre::FrameEvent& evt)
		{
			updateStats();
			return true;
		}

	private:

		//! Update the FPS stats (called after each frame render)
		void updateStats(void)
		{
			static ::Ogre::String currFps = "Current FPS: ";
			static ::Ogre::String avgFps = "Average FPS: ";
			static ::Ogre::String bestFps = "Best FPS: ";
			static ::Ogre::String worstFps = "Worst FPS: ";
			static ::Ogre::String tris = "Triangle Count: ";
			static ::Ogre::String batches = "Batch Count: ";

			// Only update data every 10 frames
			--pLimitCPUConsuming;
			if (pLimitCPUConsuming > 0)
				return;
			// Next in 10 cycles
			pLimitCPUConsuming = 10; 

			// Update stats when necessary
			try
			{
				::Ogre::OverlayElement* guiAvg = ::Ogre::OverlayManager::getSingleton().getOverlayElement("AverageFps");
				guiAvg->setColour(::Ogre::ColourValue(1.0, 0.0, 0.0));
				::Ogre::OverlayElement* guiCurr = ::Ogre::OverlayManager::getSingleton().getOverlayElement("CurrFps");
				::Ogre::OverlayElement* guiBest = ::Ogre::OverlayManager::getSingleton().getOverlayElement("BestFps");
				::Ogre::OverlayElement* guiWorst = ::Ogre::OverlayManager::getSingleton().getOverlayElement("WorstFps");

				const ::Ogre::RenderTarget::FrameStats& stats = pWindow->getStatistics();
				guiAvg->setCaption(avgFps + ::Ogre::StringConverter::toString(stats.avgFPS));
				guiCurr->setCaption(currFps + ::Ogre::StringConverter::toString(stats.lastFPS));
				guiBest->setCaption(bestFps + ::Ogre::StringConverter::toString(stats.bestFPS)
					+ " " + ::Ogre::StringConverter::toString(stats.bestFrameTime) + " ms");
				guiWorst->setCaption(worstFps + ::Ogre::StringConverter::toString(stats.worstFPS)
					+ " " + ::Ogre::StringConverter::toString(stats.worstFrameTime) + " ms");

				::Ogre::OverlayElement* guiTris = ::Ogre::OverlayManager::getSingleton().getOverlayElement("NumTris");
				guiTris->setCaption(tris + ::Ogre::StringConverter::toString(stats.triangleCount));

				::Ogre::OverlayElement* guiBatches = ::Ogre::OverlayManager::getSingleton().getOverlayElement("NumBatches");
				guiBatches->setCaption(batches + ::Ogre::StringConverter::toString(stats.batchCount));
			}
			catch(::Ogre::Exception) { /* ignore */ }
		}

		//! Create a properly configured text area
		::Ogre::OverlayElement* createTextArea(const char* name) const
		{
			static const ::Ogre::String fontName = "Times New Roman";

			::Ogre::OverlayElement* textArea = ::Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", name);
			textArea->setDimensions(0.8, 0.8);
			textArea->setMetricsMode(::Ogre::GMM_PIXELS);
			textArea->setPosition(0.1, 0.1);
			//::Ogre::Font* font = (::Ogre::Font*) ::Ogre::FontManager::getSingleton().getByName(fontName).getPointer();
			//textArea->setParameter("font_name", fontName);
			//textArea->setParameter("char_height", font->getParameter("size"));
			textArea->setParameter("horz_align", "left");
			textArea->setColour(::Ogre::ColourValue(1.0, 0.0, 0.0));
			textArea->setCaption("");
			return textArea;
		}

	private:
		//! Rendering window
		::Ogre::RenderWindow* pWindow;
		//! Counter to avoid refreshing on each frame.
		int pLimitCPUConsuming;
	};



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
		try
		{
			if (!pRoot->showConfigDialog())
				return false;
			pRoot->initialise(false);
		}
		catch (::Ogre::Exception e)
		{
			// TODO: Log the exception?
			return false;
		}

		::Ogre::NameValuePairList params;
		#ifdef YUNI_OS_WINDOWS
		params["colourDepth"] = String((uint16)pDevice->resolution()->bitPerPixel()).data();
		#endif
		// We create our own custom window with our own settings
		pWindow = pRoot->createRenderWindow(pApplicationTitle.data(), pDevice->resolution()->width(), pDevice->resolution()->height(), pDevice->fullscreen(), &params);
		// Add our FPS statistics listener
		pRoot->addFrameListener(new FPSFrameListener(pWindow));

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

		pRoot->startRendering();

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

