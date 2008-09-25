
#ifndef __YUNI_GFX_IMPLICITSURFACE_H__
# define __YUNI_GFX_IMPLICITSURFACE_H__

# include <vector>
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
		ImplicitSurface() {}
		//! \brief Destructor
		virtual ~ImplicitSurface();
		//@}

		/*!
		** \brief Get some good points that we know are inside the surface
		**
		** \param[out] points Empty point list to fill.
		*/
		virtual void insidePoints(Point3DFList& points) const;

		/*!
		** \brief Add a subsurface as a component of this implicit surface
		**
		** It becomes the responsibility of the ImplicitSurface, so
		** it must not be deleted elsewhere.
		*/
		void addSubSurface(ImplicitSurface* surf);

		/*!
		** \brief Calculate the value of a point regarding to the isosurface
		** The value is the sum of all the values of the metaobjects
		** defining the isosurface.
		**
		** \param p Point to calculate the value for
		*/
		virtual float operator()(const Point3D<float>& p) const;

	protected:
		typedef std::vector<Point3D<float> > Point3DFList;

	private:
		//! An implicit surface can be composed of subsurfaces
		std::vector<ImplicitSurface*> pSubSurfaces;

	}; // class ImplicitSurface

} // Gfx
} // Yuni

#endif // __YUNI_GFX_IMPLICITSURFACE_H__
