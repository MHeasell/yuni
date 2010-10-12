#ifndef __YUNI_GFX_LOOP_H__
# define __YUNI_GFX_LOOP_H__

# include "../ui/control.h"
# include "../core/smartptr.h"
# include "../core/event/loop.h"
# include "../gfx/window/window.h"

namespace Yuni
{
namespace Gfx
{

	/*!
	** \brief Event loop for graphics rendering
	**
	** The loop is not detached, it runs in the main thread
	*/
	class Loop : public Core::EventLoop::IEventLoop<Loop,
		Core::EventLoop::Flow::Continuous, Core::EventLoop::Statistics::None, false>
	{
	public:
		//! Event loop type
		typedef Core::EventLoop::IEventLoop<Loop,
			Core::EventLoop::Flow::Continuous, // The flow policy
			Core::EventLoop::Statistics::None, // The statistics policy
			false>                             // Run in the main thread
			LoopType;

		//! Threading policy
		typedef LoopType::ThreadingPolicy  ThreadingPolicy;

		//! Smart pointer
		typedef SmartPtr<Loop> Ptr;


	public:
		//! Default constructor
		Loop();

		//! Virtual destructor
		virtual ~Loop();

		//! Override from IEventLoop, run on each loop turn.
		bool onLoop();

		/*!
		** \brief Mark a control as modified
		**
		** When a UI control has undergone changes, it must be marked here
		** so that its internal representation will be updated on next loop.
		*/
		void markControlAsModified(UI::IControl::Ptr control);

	public:
		//! Informations about the 3D device
		Gfx::Device::Ptr device;


	private:
		/*!
		** \brief Special update treatment for windows
		**
		** \returns false if window creation failed
		*/
		bool updateWindow(UI::IControl::Ptr ctrl);

	private:
		//! All modified controls sorted by depth in the UI tree
		UI::IControl::DepthSortedMap pModifiedControls;

		//! All windows
		Gfx::Window::IWindow::Map pWindows;


	}; // class Loop



} // namespace Gfx
} // namespace Yuni

# include "loop.hxx"

#endif // __YUNI_GFX_LOOP_H__
