#ifndef __YUNI_GFX_METAOBJECT_H__
# define __YUNI_GFX_METAOBJECT_H__

# include "../yuni.h"
# include "../core/point3D.h"
# include "implicitsurface.h"



namespace Yuni
{
namespace Gfx
{

	/*!
	** \brief Meta objects define implicit surfaces using a generic field function.
	** \ingroup Gfx3DAlgorithms 
	**
	** Actually, meta objects are simplistic implicit surfaces themselves.
	** This class is abstract.
	*/
	class AMetaObject: public ImplicitSurface
	{
	public:
		//! \name Constructors and destructor
		//@{
		//! Default constructor
		AMetaObject(): pPositive(true)
		{}
		//! Full constructor
		AMetaObject(bool positive): pPositive(positive)
		{}
		//! Destructor
		virtual ~AMetaObject()
		{}
		//@}

	protected:
		//! Is the object a positive or negative force? (usually true)
		bool pPositive;

	}; // class AMetaObject

} // Gfx
} // Yuni

#endif // __YUNI_GFX_METAOBBJECT_H_
