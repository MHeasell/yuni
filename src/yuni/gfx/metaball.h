#ifndef __YUNI_GFX_METABALL_H__
# define __YUNI_GFX_METABALL_H__

# include "point3D.h"
# include "metaobject.h"


namespace Yuni
{
namespace Gfx
{


	/*!
	** \brief Metaballs are the simplest and most used meta objects.
	** \ingroup Gfx3DAlgorithms
	**
	** They have a sphere shape and can use a number of field functions.
	*/
	class MetaBall: public AMetaObject
	{
	public:
		//! This threshold indicates the limit value for the influence of a metaball
		static const float InfluenceThreshold;


	public:
		//! \name Constructors and destructor
		//@{
		//! Constructor requiring a 3D point
		MetaBall(const Point3D<float>& pos, float density = 1.0f):
			pCenter(pos), pDensity(density)
		{}
		//! Constructor requiring the coordinates of a 3D point
		MetaBall(float x, float y, float z, float density = 1.0f):
			pCenter(x, y, z), pDensity(density)
		{}
		//! Copy constructor
		MetaBall(const MetaBall& other):
			AMetaObject(), pCenter(other.center()), pDensity(other.density())
		{}
		//! Destructor
		virtual ~MetaBall()
		{}
		//@}

		//! Calculate the value of a point through the metaball's function
		virtual float operator()(const Point3D<float>& p) const
		{
			return metaballs(p);
		}

		/*!
		** \brief Accessor to the center point of the metaball
		*/
		const Point3D<float>& center() const {return pCenter;}

		/*!
		** \brief Accessor to the density of the metaball
		*/
		float density() const  {return pPositive ? pDensity : -pDensity;}

		/*!
		** \brief Get points that we know are inside the surface, here we give the center
		*/
		void insidePoints(ImplicitSurface::PointList& points) const
		{points.push_back(center());}


		/*!
		** \brief Simple density function for euclidean distance
		**
		** \param p Point to calculate the density for
		** \return The calculated density
		*/
		float distance(const Point3D<float>& p) const;

		/*!
		** \brief Polynomial approximation for euclidean distance
		** \param p Point to calculate the density for
		** \return The calculated density
		*/
		float polynomial(const Point3D<float>& p) const;

		/*!
		** \brief A metaball density function with finite support
		**
		** D(r) = a(1 - 3r^2/b^2)	when 0 <= r <= b / 3
		** D(r) = 3a/2(1 - r/b)^2	when b / 3 <= r <= b
		** D(r) = 0					when b <= r
		** where a is a scaling factor (density), and b a threshold
		**
		** \param p Point to calculate the density for
		** \return The calculated density
		*/
		float metaballs(const Point3D<float>& p) const;

		/*!
		** \brief A soft object polynomial density function, w/ finite support
		**
		** D(r) = a(1 - 4r^6/9b^6 + 17r^4/9b^4 - 22r^2/9b^2)
		**
		** \param p Point to calculate the density for
		** \return The calculated density
		*/
		float softObjects(const Point3D<float>& p) const;


	private:
		//! Center of the metaball
		Point3D<float> pCenter;
		//! The density of a metaball represents approximately its radius
		float pDensity;

	}; // class MetaBall





} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_METABALL_H__
