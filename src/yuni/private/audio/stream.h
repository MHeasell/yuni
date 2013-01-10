#ifndef __YUNI_PRIVATE_AUDIO_FILE_H__
# error "Do not include stream.h directly, please include file.h instead !"
#endif

#ifndef __YUNI_PRIVATE_AUDIO_STREAM_H__
# define __YUNI_PRIVATE_AUDIO_STREAM_H__

# include "../../yuni.h"
# include "../../core/smartptr.h"
# include <map>

# if (YUNI_OS_GCC_VERSION >= 40102)
#	pragma GCC diagnostic ignored "-Wconversion"
# endif

extern "C"
{
# include "libavutil/pixfmt.h"
# include "libavutil/pixdesc.h"
# include "libavcodec/avcodec.h"
# include "libavformat/avformat.h"
}

namespace Yuni
{
namespace Private
{
namespace Audio
{


	//! Forward declaration
	class File;



	//! Stream type
	enum StreamType
	{
		//! Audio stream type
		stAudio,

		//! Video stream type
		stVideo

	}; // enum StreamType



	/*!
	** \brief A media stream can be either audio or video data encoded with a given codec
	*/
	template<StreamType TypeT>
	class Stream final
	{
	public:
		enum // anonymous
		{
			IsVideo = TypeT == stVideo,
			IsAudio = TypeT == stAudio

		}; // enum anonymous

	public:
		//! Smart pointer
		typedef SmartPtr<Stream>  Ptr;

		//! Map
		typedef std::map<uint, Ptr>  Map;

	public:
		//! Constructor
		Stream(File* parent, AVFormatContext* format, AVCodecContext* codec, uint index);
		//! Destructor
		~Stream();

		//! Stream index in file
		uint index() const;

		//! Parent file
		File* parent() { return pParent; }

		//! Image width (Video only !)
		uint width() const;
		//! Image height (Video only !)
		uint height() const;
		//! Color depth, in bits per pixel (Video only !)
		uint depth() const;

		//! Sample rate (Audio only !)
		uint rate() const;
		//! Number of channels (Audio only !)
		uint channels() const;
		//! Bits per sample (Audio only !)
		uint bits() const;

		//! Stream duration in seconds
		uint duration() const;

		//! Stream data full size
		uint size() const { return pSize; }

		//! Get the stream type
		StreamType type() const;

		//! OpenAL audio format (Audio only !)
		uint alFormat() const { YUNI_STATIC_ASSERT(IsAudio, NotAccessibleInVideo); return pALFormat; }

		//! Get the next frame (Video only !)
		AVFrame* nextFrame();

		/*!
		** \brief Get the next buffer of data (Audio only !)
		**
		** \returns Number of bytes read
		*/
		template<uint SizeT>
		uint nextBuffer(CString<SizeT, false>& buffer);

		//! Is the stream ready for decoding ?
		// The OpenAL format check is done only for audio
		bool valid() const { return nullptr != pCodec && IsAudio == (0 != pALFormat); }

	private:
		//! Read a frame from the stream
		void readFrame();

	private:
		//! Codec information
		AVCodecContext* pCodec;

		//! Format information
		AVFormatContext* pFormat;

		//! Index in the media file
		uint pIndex;

		//! Stream format
		uint pALFormat;

		//! Stream data full size
		uint64 pSize;

		//! \name Temporary data for old version reading
		//@{
		char* pData;
		size_t pDataSize;
		size_t pDataSizeMax;
		//@}

		//! \name Temporary data for new version reading
		//@{
		uint8* pDecodedData;
		size_t pDecodedDataSize;
		AVFrame* pFrame;
		//@}

		//! Parent file
		File* pParent;

	private:
		//! Friend declaration
		friend class File;

	}; // class Stream



} // namespace Audio
} // namespace Private
} // namespace Yuni

#endif // __YUNI_PRIVATE_AUDIO_STREAM_H__
