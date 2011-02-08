
#ifndef __YUNI_GFX_METABOX_H__
# define __YUNI_GFX_METABOX_H__

# include <climits>
# include "point3D.h"
# include "boundingbox.h"
# include "metaobject.h"

namespace Yuni
{
namespace Gfx
{


	/*!
	** \brief Metaboxes are a simple metaobject for a 3D box
	** \ingroup Gfx3DAlgorithms
	*/
	class MetaBox: public AMetaObject
	{
	public:
		//! \name Constructors and destructor
		//@{
		//! Constructor requiring a 3D point
		MetaBox(const BoundingBox<float>& limits):
			pBox(limits)
		{}
		//! Copy constructor
		MetaBox(const MetaBox& other):
			AMetaObject(), pBox(other.limits())
		{}
		//! Destructor
		virtual ~MetaBox()
		{}
		//@}

		//! Calculate the value of a point through the metabox's function
		virtual float operator()(const Point3D<float>& p) const
		{
			if (!pBox.contains(p))
				return 0;
			return 65536;
		}

		//! Accessor to the limits of the box
		const BoundingBox<float>& limits() const
		{
			return pBox;
		}

		//! Get points that we know are inside the surface, here we give the center
		void insidePoints(ImplicitSurface::PointList& points) const
		{
			points.push_back(pBox.center());
		}

	private:
		//! \name Attributes
		//{

		//! The box limits
		BoundingBox<float> pBox;

		//}
	};

}
}

#endif // !__YUNI_GFX_METABOX_H__
