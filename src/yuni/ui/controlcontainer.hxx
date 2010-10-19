#ifndef __YUNI_UI_CONTROL_CONTAINER_HXX__
# define __YUNI_UI_CONTROL_CONTAINER_HXX__


namespace Yuni
{
namespace UI
{


	inline IControlContainer::IControlContainer()
	{}


	inline IControlContainer::IControlContainer(float width, float height)
		:IControl(width, height)
	{}


	inline IControlContainer::IControlContainer(float x, float y, float width, float height)
		:IControl(x, y, width, height)
	{}


	template<class T>
	inline IControlContainer::IControlContainer(const Point2D<T>& pos, float width, float height)
		:IControl(pos, width, height)
	{}


	inline IControlContainer::~IControlContainer()
	{}


	inline void IControlContainer::add(const IControl::Ptr& child)
	{
		ThreadingPolicy::MutexLocker lock(*this);
		addChildWL(child);
	}


	inline IControlContainer& IControlContainer::operator += (const IControl::Ptr& child)
	{
		ThreadingPolicy::MutexLocker lock(*this);
		addChildWL(child);
		return *this;
	}


	inline IControlContainer& IControlContainer::operator << (const IControl::Ptr& child)
	{
		ThreadingPolicy::MutexLocker lock(*this);
		addChildWL(child);
		return *this;
	}


	inline bool IControlContainer::remove(IComponent::ID id)
	{
		ThreadingPolicy::MutexLocker lock(*this);
		return removeChildWL(id);
	}


	inline bool IControlContainer::remove(const IControl::Ptr& child)
	{
		ThreadingPolicy::MutexLocker lock(*this);
		return removeChildWL(child);
	}


	inline IControlContainer& IControlContainer::operator -= (IComponent::ID id)
	{
		ThreadingPolicy::MutexLocker lock(*this);
		removeChildWL(id);
		return *this;
	}


	inline IControlContainer& IControlContainer::operator -= (const IControl::Ptr& child)
	{
		ThreadingPolicy::MutexLocker lock(*this);
		removeChildWL(child);
		return *this;
	}



} // namespace UI
} // namespace Yuni

#endif // __YUNI_UI_CONTROL_CONTAINER_HXX__
