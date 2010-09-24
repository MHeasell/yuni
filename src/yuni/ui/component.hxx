
namespace Yuni
{
namespace UI
{


	inline float IComponent::width() const
	{
		return pWidth;
	}

	inline float IComponent::height() const
	{
		return pHeight;
	}

	inline Point2D<float> IComponent::position() const
	{
		return pPosition;
	}

	inline float IComponent::x() const
	{
		return pPosition.x;
	}

	inline float IComponent::y() const
	{
		return pPosition.y;
	}



} // namespace UI
} // namespace Yuni
