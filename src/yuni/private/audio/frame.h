#ifndef __YUNI_PRIVATE_AUDIO_FRAME_H__
# define __YUNI_PRIVATE_AUDIO_FRAME_H__

# include "../../yuni.h"
# include "../../core/smartptr.h"
# include <queue>

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


	/*!
	** \brief A frame contains all the data corresponding to a decoded YCbCr 420 frame
	*/
	class Frame final
	{
	public:
		//! Smart pointer
		typedef SmartPtr<Frame>  Ptr;

		//! Frame queue
		typedef std::queue<Ptr>  Queue;

	// public:
		// This event is triggered when it is time for a new frame to be displayed
	// 	Yuni::Bind<void (const Frame::Ptr& frame)>  onFrameChanged;

	public:
		//! Constructor
		Frame(uint width, uint height, uint depth, uint nbChannels);
		//! Destructor
		~Frame();

		//! Image width (Video only !)
		uint width() const;
		//! Image height (Video only !)
		uint height() const;
		//! Color depth, in bits per pixel (Video only !)
		uint depth() const;

	private:
		//! Read a frame from the stream
		void readFrame();

	private:
		//! Frame number
		uint pIndex;

		//! AV Frame (internal data)
		AVFrame* pFrame;

	}; // class Stream



} // namespace Audio
} // namespace Private
} // namespace Yuni

#endif // __YUNI_PRIVATE_AUDIO_STREAM_H__
