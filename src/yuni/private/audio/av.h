#ifndef __YUNI_PRIVATE_AUDIO_AV_H__
# define __YUNI_PRIVATE_AUDIO_AV_H__

# include "../../yuni.h"

# if (YUNI_OS_GCC_VERSION >= 40102)
#	pragma GCC diagnostic ignored "-Wconversion"
# endif

extern "C"
{
# include "libavutil/pixdesc.h"
# include "libavcodec/avcodec.h"
# include "libavformat/avformat.h"
}

# include "types.h"
# include "../../core/string.h"



namespace Yuni
{
namespace Private
{
namespace Audio
{

	/*!
	** \brief This is a wrapper around the AV* libs from ffmpeg.
	*/
	class AV
	{
	public:
		//! Initialize ffmpeg
		static bool Init();

		//! Open a file with ffmpeg and sets up the streams' information
		static File* OpenFile(const AnyString& filename);

		//! Close an opened file and any of its streams
		static void CloseFile(File*& file);

		/*!
		** \brief Retrieve a handle for the given audio stream number
		**
		** The stream number will generally be 0, but some files can have
		** multiple audio streams in one file.
		*/
		static Stream* GetAudioStream(File* file, int streamIndex);

		static Stream* GetVideoStream(File* file, int streamIndex);

		/*!
		** \brief Get information about the given audio stream
		**
		** Currently, ffmpeg always decodes audio (even 8-bit PCM) to 16-bit PCM
		** \returns true on success, false on failure
		*/
		static bool GetAudioInfo(const Stream* stream, int& rate, int& channels, int& bits);

		static float GetVideoFrameRate(const Stream* stream);
		static bool GetVideoInfo(const Stream* stream, uint& width, uint& height, uint& bits);

		/*!
		** \brief Get the duration of a media file
		**
		** \param file File to get duration for
		** \returns The duration of the file in seconds, 0 if null
		*/
		static uint GetDuration(const File* file);
		/*!
		** \brief Get the duration of a media stream
		**
		** \param stream Stream to get duration for
		** \returns The duration of the stream in seconds, 0 if null
		*/
		static uint GetDuration(const Stream* stream);

		/*!
		** \brief Decode audio and write at most length bytes into the provided data buffer
		**
		** Will only return less for end-of-stream or error conditions
		** \returns The number of bytes written
		*/
		static size_t GetAudioData(Stream* stream, void* data, size_t length);

		static bool GetNextVideoFrame(Stream* stream);

	}; // class AV




} // namespace Audio
} // namespace Private
} // namespace Yuni

#endif // __YUNI_PRIVATE_AUDIO_AV_H__
