#ifndef __YUNI_UI_LOCAL_QUEUESERVICE_H__
# define __YUNI_UI_LOCAL_QUEUESERVICE_H__

# include "../../yuni.h"
# include "window.h"


namespace Yuni
{
namespace Private
{
namespace UI
{
namespace Local
{

	template<class ChildT>
    class IQueueService :
		public Core::EventLoop::IEventLoop<ChildT,
			Core::EventLoop::Flow::Continuous, Core::EventLoop::Statistics::None, false>,
		public IEventObserver<IQueueService<ChildT> >
	{
	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		IQueueService();
		//! Destructor
		~IQueueService();
		//@}


		Window::Ptr createWindow();
		void removeWindow(Window::Ptr& window);

	protected:
		//! Map of all local windows
		Window::Map  pWindows;
		
	}; // class IQueueService<>




} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni

#endif // __YUNI_UI_LOCAL_QUEUESERVICE_H__
