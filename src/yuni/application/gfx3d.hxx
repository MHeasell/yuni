#ifndef __YUNI_APPLICATION_GFX_3D_HXX__
# define __YUNI_APPLICATION_GFX_3D_HXX__


namespace Yuni
{
namespace Application
{

	inline Gfx3D::Gfx3D(int argc, char* argv[])
		: IApplication(argc, argv), pDeviceIsInitialized(false)
	{
		title("Loading...");
	}


	inline Gfx3D::~Gfx3D()
	{
		// Ensures all notifiers are not linked with this class
		destroyBoundEvents();
	}


	inline String Gfx3D::title() const
	{
		ThreadingPolicy::MutexLocker lock(*this);
		return pTitle;
	}


	template<class StringT>
	inline void Gfx3D::title(const StringT& t)
	{
		ThreadingPolicy::MutexLocker lock(*this);
		pTitle = t;
	}


	inline Gfx::Device::Ptr Gfx3D::device() const
	{
		return pLoop.device;
	}


	inline bool Gfx3D::isDeviceInitialized() const
	{
		return pDeviceIsInitialized;
	}


	inline void Gfx3D::onBeforeCreateDevice()
	{}


	inline void Gfx3D::onAfterCreateDevice(const bool /* success */)
	{}


	inline bool Gfx3D::onBeforeLoop()
	{
		return true;
	}



} // namespace Application
} // namespace Yuni


#endif // __YUNI_APPLICATION_GFX_3D_HXX__
