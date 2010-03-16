
#ifndef __YUNI_AUDIO_LOOP_H__
# define __YUNI_AUDIO_LOOP_H__

# include "../core/event/loop.h"


namespace Yuni
{
namespace Audio
{

	/*!
	** \brief The audio loop is where every audio event is run
	*/
	class Loop: public Core::EventLoop::IEventLoop<Loop, Core::EventLoop::Flow::Continuous
		, Core::EventLoop::Statistics::None, false>
	{
	public:
		//! The loop itself
		typedef Core::EventLoop::IEventLoop<Loop,
			Core::EventLoop::Flow::Continuous,  // The flow policy
			Core::EventLoop::Statistics::None,  // The statistics policy
			false>                              // Use a separate threads or not
			LoopType; 

		typedef LoopType::RequestType RequestType;

	public:
		bool onLoop()
		{
			return true;
		}

	}; // class Loop



} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_LOOP_H__
