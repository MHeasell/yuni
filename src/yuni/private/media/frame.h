#ifndef __YUNI_PRIVATE_MEDIA_FRAME_H__
# define __YUNI_PRIVATE_MEDIA_FRAME_H__

# include "../../yuni.h"
# include "../../core/smartptr.h"
# include "../../core/bind.h"
# include "streamtype.h"
# include <queue>


namespace Yuni
{
namespace Private
{
namespace Media
{


	//! Forward declaration
	class FrameImpl;


	/*!
	** \brief A frame contains all the data corresponding to a decoded YCbCr 420 frame
	*/
	class Frame final
	{
	public:
		//! Smart pointer
		typedef SmartPtr<Frame>  Ptr;

		//! Frame queue
		typedef std::list<Ptr>  Queue;

	public:
		// This event is triggered when it is time for a new frame to be displayed
		static Yuni::Bind<void (const Frame::Ptr& frame)>  OnFrameChanged;

	public:
		//! Constructor
		Frame(uint index);
		//! Destructor
		~Frame();

		//! Image width (Video only !)
		uint width() const;
		//! Image height (Video only !)
		uint height() const;

		//! Frame index in the stream
		uint index() const { return pIndex; }

		//! Y data
		uint8* dataY() const;
		//! Cb data
		uint8* dataCb() const;
		//! Cr data
		uint8* dataCr() const;

		//! Line size for Y data
		uint lineSizeY() const;
		//! Line size for Cb data (normally: lineSizeY / 2)
		uint lineSizeCb() const;
		//! Line size for Cr data (normally: lineSizeY / 2)
		uint lineSizeCr() const;

	private:
		//! Read a frame from the stream
		void readFrame();

		//! Ugly hidden way of setting the frame in our FrameImpl
		void setData(void* data);

	private:
		//! Frame number
		uint pIndex;

		//! Internal data (wrapper for the AVFrame)
		FrameImpl* pImpl;

		//! Friend declaration
		template<StreamType TypeT>
		friend class Stream;

	}; // class Frame



} // namespace Media
} // namespace Private
} // namespace Yuni

#endif // __YUNI_PRIVATE_MEDIA_STREAM_H__
