#ifndef __YUNI_UI_CONTROL_HXX__
# define __YUNI_UI_CONTROL_HXX__


namespace Yuni
{
namespace UI
{


	inline IControl::IControl()
	{}


	inline IControl::IControl(IControlContainer* newParent)
	{
		parent(newParent);
	}


	inline IControl::IControl(float width, float height)
		: IComponent(width, height)
	{}


	inline IControl::IControl(IControlContainer* newParent, float width, float height)
		: IComponent(width, height)
	{
		parent(newParent);
	}


	inline IControl::IControl(float x, float y, float width, float height)
		: IComponent(x, y, width, height)
	{}


	inline IControl::IControl(IControlContainer* newParent, float x, float y,
		float width, float height)
		: IComponent(x, y, width, height)
	{
		parent(newParent);
	}


	template<typename T>
	inline IControl::IControl(Point2D<T>& pos, float width, float height)
		: IComponent(pos, width, height)
	{}


	template<class T>
	inline IControl::IControl(IControlContainer* newParent, const Point2D<T>& pos,
		float width, float height)
		:IComponent(pos, width, height)
	{
		parent(newParent);
	}


	inline IControlContainer* IControl::parent()
	{
		return pParent;
	}


	inline bool IControl::hasParent() const
	{
		return NULL != pParent;
	}



} // namespace UI
} // namespacs Yuni


#endif // __YUNI_UI_CONTROL_HXX__
