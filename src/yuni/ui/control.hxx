#ifndef __YUNI_UI_CONTROL_HXX__
# define __YUNI_UI_CONTROL_HXX__


namespace Yuni
{
namespace UI
{


	inline IControl::IControl()
		:pParent(nullptr),
		pDepth(0)
	{}


	inline IControl::IControl(IControlContainer* newParent)
		:pParent(nullptr)
	{
		parentWL(newParent);
	}


	inline IControl::IControl(float width, float height)
		:IComponent(width, height),
		pParent(nullptr),
		pDepth(0)
	{}


	inline IControl::IControl(IControlContainer* newParent, float width, float height)
		:IComponent(width, height),
		pParent(nullptr),
		pDepth(0)
	{
		parentWL(newParent);
	}


	inline IControl::IControl(float x, float y, float width, float height)
		:IComponent(x, y, width, height),
		pParent(nullptr),
		pDepth(0)
	{}


	inline IControl::IControl(IControlContainer* newParent, float x, float y,
		float width, float height)
		:IComponent(x, y, width, height),
		pParent(nullptr)
	{
		parentWL(newParent);
	}


	template<typename T>
	inline IControl::IControl(Point2D<T>& pos, float width, float height)
		:IComponent(pos, width, height),
		pParent(nullptr),
		pDepth(0)
	{}


	template<class T>
	inline IControl::IControl(IControlContainer* newParent, const Point2D<T>& pos,
		float width, float height)
		:IComponent(pos, width, height),
		pParent(nullptr)
	{
		parentWL(newParent);
	}


	inline IControlContainer* IControl::parent()
	{
		ThreadingPolicy::MutexLocker lock(*this);
		return pParent;
	}


	inline bool IControl::hasParent() const
	{
		ThreadingPolicy::MutexLocker lock(*this);
		return NULL != pParent;
	}


	inline size_t IControl::depth() const
	{
		ThreadingPolicy::MutexLocker lock(*this);
		return pDepth;
	}


	inline void IControl::parent(IControlContainer* newParent)
	{
		ThreadingPolicy::MutexLocker lock(*this);
		parentWL(newParent);
	}




} // namespace UI
} // namespacs Yuni

#endif // __YUNI_UI_CONTROL_HXX__
