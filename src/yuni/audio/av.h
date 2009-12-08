#ifndef __YUNI_AUDIO_AV_H__
# define __YUNI_AUDIO_AV_H__

extern "C"
{
# include "libavcodec/avcodec.h"
# include "libavformat/avformat.h"
}

# include "types.h"

namespace Yuni
{
namespace Audio
{

	/*!
	** \brief This is a wrapper around the AV* libs from ffmpeg.
	*/
	class AV
	{
	public:

		//! Open a file with ffmpeg and sets up the streams' information
		static AVFile* openFile(const char* fname);

		//! Close an opened file and any of its streams
		static void closeFile(AVFile* file);

		/*!
		** \brief Retrieve a handle for the given audio stream number
		**
		** The stream number will generally be 0, but some files can have multiple audio streams in one file.
		*/
		static AVStream* getAudioStream(AVFile* file, int streamnum);

		/*!
		** \brief Get information about the given audio stream
		**
		** Currently, ffmpeg always decodes audio (even 8-bit PCM) to 16-bit PCM
		** \returns 0 on success
		*/
		static int getAudioInfo(AVStream* stream, int *rate, int *channels, int *bits);

		/*!
		** \brief Decode audio and write at most length bytes into the provided data buffer
		**
		** Will only return less for end-of-stream or error conditions
		** \returns The number of bytes written
		*/
		static int getAudioData(AVStream* stream, void *data, int length);

	private:

		/*!
		** \brief Get the next packet of data
		**
		** Used by get*Data to search for more compressed data, and buffer it in the
		** correct stream. It won't buffer data for streams that the app doesn't have a
		** handle for.
		*/
		static void getNextPacket(AVFile* file, int streamidx);

	}; // AV

} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_AV_H__
