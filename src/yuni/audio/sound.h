#ifndef __YUNI_AUDIO_SOUND_H__
# define __YUNI_AUDIO_SOUND_H__

# include <map>
# include "../yuni.h"
# include "../core/string.h"
# include "../core/smartptr.h"
# include "../core/string.h"
# include "../thread/signal.h"
# include "../private/audio/file.h"

namespace Yuni
{
namespace Audio
{


	/*!
	** \brief A sound or music loaded from a file or stream
	*/
	class Sound: public Policy::ObjectLevelLockable<Sound>
	{
	public:
		//! Pointer type
		typedef SmartPtr<Sound> Ptr;
		//! Map from a string to a Sound::Ptr
		typedef std::map<String, Ptr> Map;
		//! Threading Policy
		typedef Policy::ObjectLevelLockable<Sound>  ThreadingPolicy;
		//! Stream pointer type
		typedef typename Private::Audio::Stream<Private::Audio::stAudio>::Ptr  StreamPtr;

	public:
		enum // anonymous
		{
			maxBufferCount = 4,
			bufferSize = 65536
		}; // enum anonymous

	public:
		//! Constructor
		Sound();
		~Sound();

		bool prepareDispatched(uint source);

		bool destroyDispatched(Thread::Signal* signal);

		bool updateDispatched(uint source);

		void stream(const StreamPtr& stream) { pStream = stream; }

		bool valid() { return NULL != pStream; }

		//! Get the duration of the stream, 0 if not set
		uint duration() const;

	private:
		//! The audio stream contains the link to the file and the data
		StreamPtr pStream;

		//! Actual number of buffers
		uint pBufferCount;

		//! Identifiers of the OpenAL buffers used
		uint pIDs[maxBufferCount];

		//! Buffer for storing raw data
		CString<bufferSize, false> pData;

	}; // class Sound






} // namespace Audio
} // namespace Yuni

# include "sound.hxx"

#endif // __YUNI_AUDIO_SOUND_H__
