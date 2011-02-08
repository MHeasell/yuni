#ifndef __YUNI_UI_FWD_H__
# define __YUNI_UI_FWD_H__


namespace Yuni
{
namespace UI
{

	//! Forward declaration
	template<class ChildT> class IQueueService;
	class IControlContainer;
	class Application;
	class Desktop;
	class Window;
	class LocalUIEvents;

	//! String identifier type
	typedef CustomString<40, false, false> GUID;


} // namespace UI

namespace Private
{
namespace UI
{
namespace Local
{

	class IWindow;

} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni


#endif // __YUNI_UI_FWD_H__
