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


	inline void IControlContainer::add(IControl::Ptr& child)
	{
		pChildren[child->id()] = child;
	}


	inline IControlContainer& IControlContainer::operator += (IControl::Ptr& child)
	{
		pChildren[child->id()] = child;
		return *this;
	}


	inline IControlContainer& IControlContainer::operator << (IControl::Ptr& child)
	{
		pChildren[child->id()] = child;
		return *this;
	}


	inline void IControlContainer::remove(IComponent::ID id)
	{
		pChildren.erase(id);
	}


	inline void IControlContainer::remove(IControl::Ptr& child)
	{
		pChildren.erase(child->id());
	}


	inline IControlContainer& IControlContainer::operator -= (IComponent::ID id)
	{
		pChildren.erase(id);
		return *this;
	}


	inline IControlContainer& IControlContainer::operator -= (IControl::Ptr& child)
	{
		pChildren.erase(child->id());
		return *this;
	}



} // namespace UI
} // namespace Yuni

#endif // __YUNI_UI_CONTROL_CONTAINER_HXX__
