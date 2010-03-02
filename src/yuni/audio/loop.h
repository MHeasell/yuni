
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
	class Loop: public Core::EventLoop::IEventLoop<Loop>
	{
	public:
		bool onLoop()
		{
			return true;
		}

	}; // class Loop



} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_LOOP_H__
