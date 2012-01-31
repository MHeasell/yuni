#ifndef __YUNI_AUDIO_QUEUESERVICE_HXX__
# define __YUNI_AUDIO_QUEUESERVICE_HXX__


namespace Yuni
{
namespace Audio
{


	inline bool QueueService::running() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pReady && pAudioLoop.running();
	}


	inline sint64 QueueService::Emitters::elapsedTime(const StringAdapter& name)
	{
		return elapsedTime(get(name));
	}


	inline sint64 QueueService::Emitters::elapsedTime(Emitter::Ptr emitter)
	{
		return !emitter ? 0 : emitter->elapsedTime();
	}


	inline bool QueueService::Emitters::play(const StringAdapter& name)
	{
		return play(get(name));
	}


	inline bool QueueService::Emitters::stop(const StringAdapter& name)
	{
		return stop(get(name));
	}




} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_QUEUESERVICE_HXX__
