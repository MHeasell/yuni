
namespace Yuni
{
namespace UI
{

	inline IComponent::IComponent()
		:pPosition(50, 50),
		pWidth(50),
		pHeight(50)
	{}


	inline IComponent::IComponent(float width, float height)
		:pPosition(50, 50),
		pWidth((width > 0.f) ? width : 0.f),
		pHeight((height > 0.f) ? height : 0.f)
	{}


	inline IComponent::IComponent(float x, float y, float width, float height)
		:pPosition(x, y),
		pWidth((width > 0.f) ? width : 0.f),
		pHeight((height > 0.f) ? height : 0.f)
	{}


	template<class T>
	inline IComponent::IComponent(const Point2D<T>& pos, float width, float height)
		:pPosition(pos),
		pWidth((width > 0.f) ? width : 0.f),
		pHeight((height > 0.f) ? height : 0.f)
	{}


	inline IComponent::~IComponent()
	{}


	inline float IComponent::width() const
	{
		ThreadingPolicy::MutexLocker lock(*this);
		return pWidth;
	}


	inline float IComponent::height() const
	{
		ThreadingPolicy::MutexLocker lock(*this);
		return pHeight;
	}


	inline Point2D<float> IComponent::position() const
	{
		ThreadingPolicy::MutexLocker lock(*this);
		return pPosition;
	}


	inline void IComponent::size(float& width, float& height) const
	{
		ThreadingPolicy::MutexLocker lock(*this);
		width  = pWidth;
		height = pHeight;
	}


	inline float IComponent::x() const
	{
		ThreadingPolicy::MutexLocker lock(*this);
		return pPosition.x;
	}


	inline float IComponent::y() const
	{
		ThreadingPolicy::MutexLocker lock(*this);
		return pPosition.y;
	}


	inline void IComponent::resizeWL(float&, float&)
	{
		// do nothing
	}




} // namespace UI
} // namespace Yuni
