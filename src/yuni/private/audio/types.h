#ifndef __YUNI_PRIVATE_AUDIO_TYPES_H__
# define __YUNI_PRIVATE_AUDIO_TYPES_H__

# include <vector>

namespace Yuni
{
namespace Private
{
namespace Audio
{


	class File;


	class Stream final
	{
	public:
		AVCodecContext* codec;
		int streamIdx;

		uint format;
		uint64_t size;

		//! \name Temporary data for old version reading
		//@{
		char* data;
		size_t dataSize;
		size_t dataSizeMax;
		//@}

		//! \name Temporary data for new version reading
		//@{
		uint8* decodedData;
		size_t decodedDataSize;
		AVFrame* frame;
		//@}

		File* parent;

	}; // class Stream


	class File final
	{
	public:
		AVFormatContext* format;
		std::vector<Stream*> streams;

	}; // class File




} // namespace Audio
} // namespace Private
} // namespace Yuni

#endif // __YUNI_PRIVATE_AUDIO_TYPES_H__
