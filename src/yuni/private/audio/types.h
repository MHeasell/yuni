#ifndef __YUNI_PRIVATE_AUDIO_TYPES_H__
# define __YUNI_PRIVATE_AUDIO_TYPES_H__

# include <vector>

namespace Yuni
{
namespace Private
{
namespace Audio
{


	struct AudioFile;


	class AudioStream final
	{
	public:
		AVCodecContext* CodecContext;
		int StreamIdx;

		uint Format;
		uint64_t Size;

		char* Data;
		size_t DataSize;
		size_t DataSizeMax;
		char* DecodedData;
		size_t DecodedDataSize;

		AudioFile* parent;
	};

	class AudioFile final
	{
	public:
		AVFormatContext* formatContext;
		std::vector<AudioStream*> streams;
		size_t streamsSize;
	};




} // namespace Audio
} // namespace Private
} // namespace Yuni

#endif // __YUNI_PRIVATE_AUDIO_TYPES_H__
