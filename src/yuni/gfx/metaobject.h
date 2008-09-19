
#ifndef __YUNI_GFX_METAOBJECT_H__
# define __YUNI_GFX_METAOBJECT_H__

# include "point3D.h"
# include "implicitsurface.h"

namespace Yuni
{
namespace Gfx
{

	/*!
	** \class MetaObject
	**
	** \brief Meta objects define implicit surfaces using a generic field function.
	**
	** Actually, meta objects are simplistic implicit surfaces themselves.
	** This class is abstract.
	*/
	class MetaObject: public ImplicitSurface
	{
	public:
		//! \name Constructors and destructor
		//@{
		//! Default constructor
		MetaObject(): pPositive(true)
		{}
		//! Full constructor
		MetaObject(bool positive): pPositive(positive)
		{}
		//! Destructor
		virtual ~MetaObject
		{}
		//@}

		//! Get any point that we know is inside the surface
		const Point3D<float> getInsidePoint() const = 0;

	private:
		//! Is the object a positive or negative force? (usually true)
		bool pPositive;

	}; // class MetaObject

} // Gfx
} // Yuni

#endif // __YUNI_GFX_METAOBBJECT_H_
