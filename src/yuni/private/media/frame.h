#ifndef __YUNI_PRIVATE_MEDIA_FRAME_H__
# define __YUNI_PRIVATE_MEDIA_FRAME_H__

# include "../../yuni.h"
# include "../../core/smartptr.h"
# include <queue>


namespace Yuni
{
namespace Private
{
namespace Media
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



} // namespace Media
} // namespace Private
} // namespace Yuni

#endif // __YUNI_PRIVATE_MEDIA_STREAM_H__
