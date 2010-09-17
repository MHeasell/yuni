
#include "metaball.h"
#include "../../core/math.h"



namespace Yuni
{
namespace Gfx
{



	const float MetaBall::InfluenceThreshold = 6.0f;




	float MetaBall::distance(const Point3D<float>& p) const
	{
		float r2 = Math::Power(pCenter.x - p.x, 2.f);
		r2 += Math::Power(pCenter.y - p.y, 2.f);
		r2 += Math::Power(pCenter.z - p.z, 2.f);
		return pDensity * r2;
	}


	float MetaBall::polynomial(const Point3D<float>& p) const
	{
		float r2 = Math::Power(pCenter.x - p.x, 2.f);
		r2 += Math::Power(pCenter.y - p.y, 2.f);
		r2 += Math::Power(pCenter.z - p.z, 2.f);
		return Math::Power(1.0f - r2, 2.f);
	}


	float MetaBall::metaballs(const Point3D<float>& p) const
	{
		float r2 = Math::Power(pCenter.x - p.x, 2.f);
		r2 += Math::Power(pCenter.y - p.y, 2.f);
		r2 += Math::Power(pCenter.z - p.z, 2.f);
		float r = Math::SquareRoot(r2);
		float a = pDensity;
		float b = InfluenceThreshold;
		if (r >= b)
			return 0;
		if (r <= (b / 3.0f))
			return a * (1.0f - (3.0f * r2 / (b * b)));
		return 1.5f * a * Math::Power(1.0f - (r / b), 2.f);
	}



	float MetaBall::softObjects(const Point3D<float>& p) const
	{
		const float a = pDensity;
		const float b2 = InfluenceThreshold * InfluenceThreshold;
		const float b4 = b2 * b2;
		const float b6 = b4 * b2;
		float r2 = Math::Power(pCenter.x - p.x, 2.f);
		r2 += Math::Power(pCenter.y - p.y, 2.f);
		r2 += Math::Power(pCenter.z - p.z, 2.f);
		float r4 = r2 * r2;
		float r6 = r4 * r2;
		return a  * (1 - (4.0f * r6 / 9.0f / b6)
				+ (17.0f * r4 / 9.0f / b4)
				- (22.0f * r2 / 9.0f / b2));
	}




} // namespace Gfx
} // namespace Yuni


