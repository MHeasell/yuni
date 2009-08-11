
#include "engine.h"
#include "../private/gfx3d/gl/gl.h"
#include "render/opengl.h"

namespace Yuni
{
namespace Gfx
{
	namespace
	{

		Engine globalEngine;

	} // anonymous namespace



	Engine* Engine::Instance()
	{
		return &globalEngine;
	}


	Engine::Engine()
		:pDeviceIsInitialized(false), pMainWindow(NULL), pRenderer(NULL)
	{
	}


	Engine::~Engine()
	{
		// All connected events to onFPSChanged are automatically disconnected on destroy
		this->release();
	}


	bool Engine::reset(const SmartPtr<Device>& dc)
	{
		// Lock
		MutexLocker locker(pMutex);

		// There is nothing to do if the device is null
		if (NULL != dc)
		{
			// Getting a reference to the information about the Device
			pDevice = dc;
			// The settings must be valid
			// e.g. the resolution must be a valid resolution
			pDevice->ensuresSettingsAreValid();

			// Ask to the back-end engine to initialize itself
			pDeviceIsInitialized = true;//external3DEngine.initialize(pDevice);

			// Lock further modifications to the informations about the device
			pDevice->lock();
		}
		return pDeviceIsInitialized;
	}



	bool Engine::resetWithFailSafeSettings(const bool fullscreenMode)
	{
		// Informations about the device
		SmartPtr<Gfx::Device> newDevice(new Gfx::Device());
		newDevice->fullscreen(fullscreenMode);
		// The fail-safe resolution
		SmartPtr<Yuni::Device::Display::Resolution> fsRes(new Yuni::Device::Display::Resolution(800, 600));
		newDevice->resolution(fsRes);

		// Apply the new settings
		return this->reset(newDevice);
	}



	bool Engine::resetWithRecommendedSettings(const bool fullscreenMode)
	{
		// Informations about the device
		SmartPtr<Gfx::Device> newDevice(new Gfx::Device());
		newDevice->fullscreen(fullscreenMode);

		// Apply the new settings
		return this->reset(newDevice);
	}


	void Engine::run()
	{
		pMutex.lock();
		if (pDeviceIsInitialized)
		{
			pMutex.unlock();

			// Window creation and GL init
			pMainWindow = Yuni::Gfx3D::Window::Factory::CreateGLWindow(applicationTitle(), pDevice->resolution()->width(),
				pDevice->resolution()->height(), pDevice->resolution()->bitPerPixel(), pDevice->fullscreen());
			onFPSChanged.connect(pMainWindow, &Yuni::Gfx3D::Window::AWindow::onFPSChanged);

			static unsigned int lastFPS = 0;
			pRenderer = new Yuni::Gfx3D::Render::OpenGL();

			// Main loop
			while (!pMainWindow->closing())
			{
				// Manage events on the window
				pMainWindow->pollEvents();

				pRenderer->drawFrame(*Scene::Instance());

// 				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
// 				glLoadIdentity();					// Reset The View
// 				glTranslatef(-1.5f,0.0f,-6.0f);				// Move Left And Into The Screen
// 				glRotatef(45.0f,0.0f,1.0f,0.0f);				// Rotate The Pyramid On It's Y Axis
// 				glBegin(GL_TRIANGLES);					// Start Drawing The Pyramid
// 					glColor3f(1.0f,0.0f,0.0f);			// Red
// 					glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Front)
// 					glColor3f(0.0f,1.0f,0.0f);			// Green
// 					glVertex3f(-1.0f,-1.0f, 1.0f);			// Left Of Triangle (Front)
// 					glColor3f(0.0f,0.0f,1.0f);			// Blue
// 					glVertex3f( 1.0f,-1.0f, 1.0f);			// Right Of Triangle (Front)

// 					glColor3f(1.0f,0.0f,0.0f);			// Red
// 					glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Right)
// 					glColor3f(0.0f,0.0f,1.0f);			// Blue
// 					glVertex3f( 1.0f,-1.0f, 1.0f);			// Left Of Triangle (Right)
// 					glColor3f(0.0f,1.0f,0.0f);			// Green
// 					glVertex3f( 1.0f,-1.0f, -1.0f);			// Right Of Triangle (Right)

// 					glColor3f(1.0f,0.0f,0.0f);			// Red
// 					glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Back)
// 					glColor3f(0.0f,1.0f,0.0f);			// Green
// 					glVertex3f( 1.0f,-1.0f, -1.0f);			// Left Of Triangle (Back)
// 					glColor3f(0.0f,0.0f,1.0f);			// Blue
// 					glVertex3f(-1.0f,-1.0f, -1.0f);			// Right Of Triangle (Back)

// 					glColor3f(1.0f,0.0f,0.0f);			// Red
// 					glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Left)
// 					glColor3f(0.0f,0.0f,1.0f);			// Blue
// 					glVertex3f(-1.0f,-1.0f,-1.0f);			// Left Of Triangle (Left)
// 					glColor3f(0.0f,1.0f,0.0f);			// Green
// 					glVertex3f(-1.0f,-1.0f, 1.0f);			// Right Of Triangle (Left)
// 				glEnd();						// Done Drawing The Pyramid

// 				glLoadIdentity();
// 				glTranslatef(1.5f,0.0f,-7.0f);				// Move Right And Into The Screen
// 				glRotatef(33.0f,1.0f,1.0f,1.0f);			// Rotate The Cube On X, Y & Z
// 				glBegin(GL_QUADS);					// Start Drawing The Cube
// 					glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Green
// 					glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Top)
// 					glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Top)
// 					glVertex3f(-1.0f, 1.0f, 1.0f);			// Bottom Left Of The Quad (Top)
// 					glVertex3f( 1.0f, 1.0f, 1.0f);			// Bottom Right Of The Quad (Top)

// 					glColor3f(1.0f,0.5f,0.0f);			// Set The Color To Orange
// 					glVertex3f( 1.0f,-1.0f, 1.0f);			// Top Right Of The Quad (Bottom)
// 					glVertex3f(-1.0f,-1.0f, 1.0f);			// Top Left Of The Quad (Bottom)
// 					glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Bottom)
// 					glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Bottom)

// 					glColor3f(1.0f,0.0f,0.0f);			// Set The Color To Red
// 					glVertex3f( 1.0f, 1.0f, 1.0f);			// Top Right Of The Quad (Front)
// 					glVertex3f(-1.0f, 1.0f, 1.0f);			// Top Left Of The Quad (Front)
// 					glVertex3f(-1.0f,-1.0f, 1.0f);			// Bottom Left Of The Quad (Front)
// 					glVertex3f( 1.0f,-1.0f, 1.0f);			// Bottom Right Of The Quad (Front)

// 					glColor3f(1.0f,1.0f,0.0f);			// Set The Color To Yellow
// 					glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Back)
// 					glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Back)
// 					glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Back)
// 					glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Back)

// 					glColor3f(0.0f,0.0f,1.0f);			// Set The Color To Blue
// 					glVertex3f(-1.0f, 1.0f, 1.0f);			// Top Right Of The Quad (Left)
// 					glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Left)
// 					glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Left)
// 					glVertex3f(-1.0f,-1.0f, 1.0f);			// Bottom Right Of The Quad (Left)

// 					glColor3f(1.0f,0.0f,1.0f);			// Set The Color To Violet
// 					glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Right)
// 					glVertex3f( 1.0f, 1.0f, 1.0f);			// Top Left Of The Quad (Right)
// 					glVertex3f( 1.0f,-1.0f, 1.0f);			// Bottom Left Of The Quad (Right)
// 					glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Right)
// 				glEnd();						// Done Drawing The Quad

				// Push the backbuffer to screen
				pMainWindow->blit();
			}
			pMainWindow->close();
			delete pMainWindow;
			pMainWindow = NULL;
			delete pRenderer;
			pRenderer = NULL;
		}
		pMutex.unlock();
	}


	void Engine::release()
	{
		pMutex.lock();
		if (pDeviceIsInitialized)
		{
			pDeviceIsInitialized = false;
		}
		pMutex.unlock();
	}


	void Engine::applicationTitle(const String& t)
	{
		pTitle = t;
		if (NULL != pMainWindow)
			pMainWindow->title(pTitle);
	}


	String Engine::applicationTitle()
	{
		return pTitle;
	}


	bool Engine::toggleFullscreen()
	{
		// Lock
		MutexLocker locker(pMutex);
		// Toggle the flag for the fullscreen mode
		const bool f = pDevice->toggleFullscreen();
		// Reset the device
		// TODO Find a better way to toggle the fullscreen mode
		this->reset(pDevice);
		// Return the current status for the fullscreen mode
		return f;
	}



} // namespace Gfx
} // namespace Yuni

