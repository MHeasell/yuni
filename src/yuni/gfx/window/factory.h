#ifndef __YUNI_GFX_WINDOW_FACTORY__
# define __YUNI_GFX_WINDOW_FACTORY__

# include "window.h"
# include "../device.h"

namespace Yuni
{
namespace Gfx
{
namespace Window
{


	/*!
	** \brief Window factory: manages API-dependent window creation.
	**
	** This is not a factory design pattern stricto sensu. It only collects static methods.
	*/
	class Factory
	{
	public:
		/*!
		** \brief Create a platform-dependent window.
		**
		** The characteristics of this window and its associated renderer wil be determined using the device.
		*/
		static AWindow* Create(const String& title, const Device::Ptr& device);

	private:
		Factory() {}
		Factory(const Factory&) {}

	}; // class Factory




} // namespace Window
} // namespace Gfx3D
} // namespace Yuni

#endif // __YUNI_GFX_WINDOW_FACTORY__
