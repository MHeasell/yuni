
#ifndef __LIB_3D_METABALL_H__
# define __LIB_3D_METABALL_H__

# include <math.h>
# include "point.h"
# include "metaobject.h"

namespace W
{
namespace GUI3D
{
    const float INFLUENCE_THRESHOLD = 6.0f;

    /*! class MetaBall
    ** 
    ** Metaballs are the simplest and most used meta objects.
    ** They have a sphere shape and can use a number of field functions.
    */
    class MetaBall: public MetaObject
    {
    public:
        MetaBall(const Point& pos, float density = 1):
            pCenter(pos), pDensity(density)
        {}
        MetaBall(float x, float y, float z, float density = 1):
          pCenter(x, y, z), pDensity(density)
        {}
        MetaBall(const MetaBall& other):
	    pCenter(other.center()), pDensity(other.density())
	{}

        //! Calculate the value of a point through the metaball's function
        virtual float operator()(const Point& p) const
        {
            return distance(p);
        }

        //! Accessor to the center point of the metaball
        const Point& center() const
        {
            return pCenter;
        }

        //! Accessor to the density of the metaball
        const float density() const
        {
            return pDensity;
        }



        /*! \brief Simple density function for euclidean distance
	** \param p Point to calculate the density for
	** \return The calculated density
        */
        float distance(const Point& p) const
        {
            float r2 = pow(pCenter.X - p.X, 2);
            r2 += pow(pCenter.Y - p.Y, 2);
            r2 += pow(pCenter.Z - p.Z, 2);
            return 1.0f / r2;
        }

        /*! \brief Polynomial approximation for euclidean distance
	** \param p Point to calculate the density for
	** \return The calculated density
        */
        float polynomial(const Point& p) const
        {
            float r2 = pow(pCenter.X - p.X, 2);
            r2 += pow(pCenter.Y - p.Y, 2);
            r2 += pow(pCenter.Z - p.Z, 2);
            return pow(1.0f - r2, 2);
        }

        /*! \brief A metaball density function with finite support
        ** D(r) = a(1 - 3r^2/b^2)    when 0 <= r <= b / 3
        ** D(r) = 3a/2(1 - r/b)^2    when b / 3 <= r <= b
        ** D(r) = 0                  when b <= r
        ** where a is a scaling factor (density), and b a threshold
	** \param p Point to calculate the density for
	** \return The calculated density
        */
        float metaballs(const Point& p) const
        {
            float r2 = pow(pCenter.X - p.X, 2);
            r2 += pow(pCenter.Y - p.Y, 2);
            r2 += pow(pCenter.Z - p.Z, 2);
            float r = sqrt(r2);
            float a = pDensity;
            float b = INFLUENCE_THRESHOLD;
            if (r >= b)
                return 0;
            if (r <= (b / 3.0f))
                return a * (1.0f - (3.0f * r2 / (b * b)));
            return 1.5f * a * pow(1.0f - (r / b), 2);
        }

        /*! \brief A soft object polynomial density function, w/ finite support
        ** D(r) = a(1 - 4r^6/9b^6 + 17r^4/9b^4 - 22r^2/9b^2)
	** \param p Point to calculate the density for
	** \return The calculated density
        */
        float softObjects(const Point& p) const
        {
            float a = pDensity;
            float b2 = INFLUENCE_THRESHOLD * INFLUENCE_THRESHOLD;
            float b4 = b2 * b2;
            float b6 = b4 * b2;
            float r2 = pow(pCenter.X - p.X, 2);
            r2 += pow(pCenter.Y - p.Y, 2);
            r2 += pow(pCenter.Z - p.Z, 2);
            float r4 = r2 * r2;
            float r6 = r4 * r2;
            return a  * (1 - (4.0f * r6 / 9.0f / b6)
                         + (17.0f * r4 / 9.0f / b4)
                         - (22.0f * r2 / 9.0f / b2));
        }

    private:
        Point pCenter;
        float pDensity;

    }; // class MetaBall

} // GUI3D
} // W

#endif // __LIB_3D_METABALL_H__
