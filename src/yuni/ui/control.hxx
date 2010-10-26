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


	inline IControl::IControl(IControl::Ptr newParent)
		:pParent(nullptr)
	{
		parentWL(newParent);
	}


	inline IControl::IControl(float width, float height)
		:IComponent(width, height),
		pParent(nullptr),
		pDepth(0)
	{}


	inline IControl::IControl(IControl::Ptr newParent, float width, float height)
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


	inline IControl::IControl(IControl::Ptr newParent, float x, float y,
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
	inline IControl::IControl(IControl::Ptr newParent, const Point2D<T>& pos,
		float width, float height)
		:IComponent(pos, width, height),
		pParent(nullptr)
	{
		parentWL(newParent);
	}


	inline void IControl::update() const
	{
		ThreadingPolicy::MutexLocker lock(*this);
		updateComponentWL(pLocalID);
	}


	inline IControl::Ptr IControl::parent() const
	{
		return (IControl*)pParent;
	}


	inline const IControl::Map& IControl::children() const
	{
		ThreadingPolicy::MutexLocker lock(*this);
		return pChildren;
	}


	inline bool IControl::hasParent() const
	{
		ThreadingPolicy::MutexLocker lock(*this);
		return NULL != pParent;
	}


	inline unsigned int IControl::depth() const
	{
		ThreadingPolicy::MutexLocker lock(*this);
		return pDepth;
	}


	inline void IControl::parent(IControl::Ptr newParent)
	{
		ThreadingPolicy::MutexLocker lock(*this);
		parentWL(newParent);
	}


	inline void IControl::detachWL()
	{
		parentWL(nullptr);
	}

	inline void IControl::addChildWL(const IControl::Ptr&)
	{}


	inline bool IControl::removeChildWL(const IControl::Ptr&)
	{
		return false;
	}



} // namespace UI
} // namespacs Yuni

#endif // __YUNI_UI_CONTROL_HXX__
