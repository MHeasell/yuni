#ifndef __YUNI_GFX_RENDER_FPSCOUNTER_H__
# define __YUNI_GFX_RENDER_FPSCOUNTER_H__

# include "../../yuni.h"
# include "../../threads/timer.h"

namespace Yuni
{
namespace Gfx
{
namespace Render
{

	/*!
	** \brief Count frames per second in a separate thread
	*/
	class FPSCounter : public Yuni::Threads::Timer
	{
	public:
		/*!
		** \brief Main constructor
		**
		** Initialize the FPS counter with a one-second interval
		*/
		FPSCounter()
			:Yuni::Threads::Timer(1000), pFrameCount(0), pTotalFrameCount(0),
			pFPS(0), pSecondsElapsed(0)
		{
			start();
		}
		//! \brief Virtual destructor
		virtual ~FPSCounter()
		{
			stop();
		}

		/*!
		** \brief On timer tick
		**
		** Overridden from Yuni::Threads::Timer
		*/
		virtual bool onExecute(const uint32 /* cycleCount */)
		{
			pTotalFrameCount += pFrameCount;
			pFPS = pFrameCount;
			++pSecondsElapsed;
			pFrameCount = 0;
			return true;
		}

		//! Get the number of frames rendered in the last second
		unsigned int instantFPS()
		{
			return pFPS;
		}

		//! Get the mean number of frames per second since start of rendering
		unsigned int meanFPS()
		{
			return pTotalFrameCount / pSecondsElapsed;
		}

		//! Indicate that more frames have been rendered
		void addFrames(unsigned int nbFrames) { pFrameCount += nbFrames; }

	protected:
		unsigned int pFrameCount;
		unsigned int pTotalFrameCount;
		unsigned int pFPS;
		unsigned int pSecondsElapsed;

	}; // FPSCounter

} // Render
} // Gfx
} // Yuni

#endif // __YUNI_GFX_RENDER_FPSCOUNTER_H__
