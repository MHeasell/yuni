
#ifndef __YUNI_GFX_METAOBJECT_H__
# define __YUNI_GFX_METAOBJECT_H__

# include "point3D.h"

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
	class MetaObject
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
		virtual ~MetaObject()
		{}
		//@}

		//! Calculate the value of a point through the object's function
		virtual float operator()(const Point3D<float>& p) const = 0;

	private:
		//! Is the object a positive or negative force? (usually true)
		bool pPositive;

	}; // class MetaObject

} // Gfx
} // Yuni

#endif // __YUNI_GFX_METAOBBJECT_H_
