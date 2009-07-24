
#include <iostream>
#include "gl.engine.h"
#include "../../../core/system/sleep.h"
#include "../../../threads.h"
#include "../../../device/display/resolution.h"

namespace Yuni
{
namespace Private
{
namespace GfxImpl
{
namespace Gl
{

	Engine::Engine()
		:pBackgroundColor(0, 0, 0, 0),
		pRunnable(false)
	{}

	Engine::~Engine()
	{
		pRunnable = false;
		onFPSChanged.disconnectAll();
		release();
	}



	bool Engine::initialize(const Yuni::Gfx::Device::Ptr& dc)
	{
		// We keep a reference to the yuni device
		if (NULL == dc)
			return false;

		// Ensure that a device is not already initialized
		release();
		// Getting a reference to the information about the Device
		pDevice = dc;

		// Clear The Background Color To Black
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		// Enables Clearing Of The Depth Buffer
		glClearDepth(1.0);
		// The Type Of Depth Test To Do
		glDepthFunc(GL_LESS);
		// Enables Depth Testing
		glEnable(GL_DEPTH_TEST);
		// Enables Smooth Color Shading
		glShadeModel(GL_SMOOTH);

		glMatrixMode(GL_PROJECTION);
		// Reset The Projection Matrix
		glLoadIdentity();
		// Calculate The Aspect Ratio Of The Window
		Device::Display::Resolution::Ptr res = dc->resolution();
		gluPerspective(45.0f, (GLfloat)res->width() / (GLfloat)res->height(), 0.1f, 100.0f);

		glMatrixMode(GL_MODELVIEW);

		// Set the window caption
		this->applicationTitle(pApplicationTitle);
		pRunnable = true;
		return true;
	}



	void Engine::run()
	{
		if (!pDevice) // No device, aborting
			return;
		while (pRunnable)
			// TODO
			;
		pRunnable = false;
	}


	void Engine::release()
	{
		pRunnable = false;
	}


	void Engine::waitForEngineToStop()
	{
		// TODO
	}


	void Engine::applicationTitle(const String& t)
	{
		pMutex.lock();
		if (pDevice)
		{
			pApplicationTitle = t;
		}
		pMutex.unlock();
	}




} // namespace Irrlicht
} // namespace GfxImpl
} // namespace Private
} // namespace Yuni

