#ifndef __YUNI_MEDIA_SOURCE_H__
# define __YUNI_MEDIA_SOURCE_H__

# include <map>
# include "../yuni.h"
# include "../core/string.h"
# include "../core/smartptr.h"
# include "../core/string.h"
# include "../thread/signal.h"
# include "../private/media/file.h"

namespace Yuni
{
namespace Media
{


	/*!
	** \brief A media source loaded from a file or network stream
	*/
	class Source: public Policy::ObjectLevelLockable<Source>
	{
	public:
		//! Pointer type
		typedef SmartPtr<Source> Ptr;
		//! Map from a string to a Source::Ptr
		typedef std::map<String, Ptr> Map;
		//! Threading Policy
		typedef Policy::ObjectLevelLockable<Source>  ThreadingPolicy;
		//! Audio stream pointer type
		typedef Private::Media::Stream<Private::Media::stAudio>::Ptr  AStreamPtr;
		//! Video stream pointer type
		typedef Private::Media::Stream<Private::Media::stVideo>::Ptr  VStreamPtr;

	public:
		enum // anonymous
		{
			maxBufferCount = 4,
			minBufferSize = 60000, // ~4k buffers are apparently the norm
			maxBufferSize = 65536,

			bestQueueSize = 150

		}; // enum anonymous

	public:
		//! Constructor
		Source();
		~Source();

		bool prepareDispatched(uint source);

		bool destroyDispatched(Thread::Signal* signal);

		bool updateDispatched(uint source);

		void stream(const AStreamPtr& audioStream) { pAStream = audioStream; }

		void stream(const VStreamPtr& videoStream) { pVStream = videoStream; }

		void stream(const VStreamPtr& videoStream, const AStreamPtr& audioStream)
		{
			pAStream = audioStream;
			pVStream = videoStream;
		}

		bool valid() { return nullptr != pAStream || nullptr != pVStream; }

		//! Get the duration of the stream, 0 if not set
		uint duration() const;

		//! Get the current elapsed time of the source
		float elapsedTime() const
		{
			if (!pAStream)
				return 0.0;
			return (float)(pSamplesRead + pSamplesCurrent) / pAStream->rate();
		}

	private:
		//! Refill audio buffer
		uint fillBuffer();

		//! Refill the video frame queue
		void fillQueue();

	private:
		//! The audio stream
		AStreamPtr pAStream;

		//! The video stream
		VStreamPtr pVStream;

		//! Actual number of buffers
		uint pBufferCount;

		//! Samples already played in previous buffers
		uint pSamplesRead;

		//! Samples played from current buffer
		uint pSamplesCurrent;

		//! Identifiers of the OpenAL buffers used
		uint pIDs[maxBufferCount];

		//! Buffer for storing decoded audio data
		CString<maxBufferSize, false> pData;

		//! Currently loaded video frames
		Private::Media::Frame::Queue pFrames;

	}; // class Source






} // namespace Media
} // namespace Yuni

# include "source.hxx"

#endif // __YUNI_MEDIA_SOURCE_H__
