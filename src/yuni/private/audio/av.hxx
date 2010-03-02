
namespace Yuni
{
namespace Private
{
namespace Audio
{

	template<typename AnyStringT>
	AudioFile* AV::openFile(const AnyStringT& path)
	{
		AudioFile* file = (AudioFile*)calloc(1, sizeof(AudioFile));
		if (file && av_open_input_file(&file->FormatContext, String::CString(path),
			NULL, 0, NULL) == 0)
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
