
#ifndef __YUNI_GFX_IMPLICITSURFACE_H__
# define __YUNI_GFX_IMPLICITSURFACE_H__

# include <vector>
# include "metaball.h"
# include "octree.h"

namespace Yuni
{
namespace Gfx
{

	/*!
	** \class ImplicitSurface
	**
	** \brief An implicit surface is a mathematical function defining a spacial surface
	**
	** An implicit surface is defined by metaobjects
	** interacting with each other.
	**
	*/
	class ImplicitSurface
	{
	public:
		//! \name Constructors and destructor
		//@{
		//! \brief Main constructor
		ImplicitSurface();
		//! \brief Destructor
		virtual ~ImplicitSurface();
		//@}

		//! Get some good points that we know are inside the surface
		const std::vector<Point3D<float> > insidePoints() const
		{
			std::vector<Point3D<float> > points = new std::vector<Point3D<float >();
			for (int i = 0; i < pObjects.size(); ++i)
				points.push_back(pObjects.getInsidePoint());
			return points;
		}

		/*!
		** \brief Create a new metaball
		**
		** It becomes the responsibility of the ImplicitSurface, so
		** it must not be deleted elsewhere.
		*/
		MetaBall* addMetaBall(const Point3D<float>& p, float density);
		MetaBall* addMetaBall(float x, float y, float z, float density);

		/*!
		** \brief Calculate the value of a point regarding to the isosurface
		** The value is the sum of all the values of the metaobjects
		** defining the isosurface.
		**
		** \param p Point to calculate the value for
		*/
		virtual float operator()(const Point3D<float>& p) const;

	private:
		//! The meta objects forming the surface
		std::vector<MetaObject*> pObjects;

	}; // class ImplicitSurface

} // Gfx
} // Yuni

#endif // __YUNI_GFX_IMPLICITSURFACE_H__
