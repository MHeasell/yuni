#ifndef __YUNI_PRIVATE_AUDIO_AV_HXX__
# define __YUNI_PRIVATE_AUDIO_AV_HXX__

#include "../../core/string.h"

namespace Yuni
{
namespace Private
{
namespace Audio
{

	template<typename AnyStringT>
	AudioFile* AV::OpenFile(const AnyStringT& path)
	{
		YUNI_STATIC_ASSERT(Traits::CString<AnyStringT>::valid, AV_OpenFile_InvalidFileNameType);

		AudioFile* file = (AudioFile*)calloc(1, sizeof(AudioFile));
		if (file && 0 == av_open_input_file(&file->FormatContext,
			Traits::CString<AnyStringT>::Perform(path), NULL, 0, NULL))
		{
			// After opening, we must search for the stream information because not
			// all formats will have it in stream headers (eg. system MPEG streams)
			if (av_find_stream_info(file->FormatContext) >= 0)
				return file;
			av_close_input_file(file->FormatContext);
		}
		free(file);
		return NULL;
	}



} // namespace Audio
} // namespace Private
} // namespace Yuni

#endif // __YUNI_PRIVATE_AUDIO_AV_HXX__
