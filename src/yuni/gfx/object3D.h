
#ifndef __YUNI_GFX_OBJECT3D_H__
# define __YUNI_GFX_OBJECT3D_H__

# include "../toolbox/smartptr/smartptr.h"
# include "../toolbox/tree/treeN.h"
# include "skeleton.h"

namespace Yuni
{
namespace Gfx
{

	/*!
	** \brief A 3D object is an abstract scene object
	**
	** It can contain other objects, and has a skeleton for its mesh
	** It also has a shared "template" object storing every characteristic common with similar objects
	*/
	class Object3D: TreeN<Object3D>
	{
	public:
		//! \name Constructors & Destructor
		//@{

		//! Default Constructor
		Object3D(Object3D* parent = NULL)
		: pParent(parent)
		{}

		//! Constructor with mesh initialization
		Object3D(SmartPtr<Skeleton>& skeleton, SmartPtr<Object3D>& parent)
			: pParent(parent), pSkeleton(skeleton)
		{}

		//! Default Destructor
		~Object3D() {}
		//@}


		//! \name Accessors
		//@{

		/*!
		** \brief Access to the object's skeleton
		**
		** \return A smart pointer to the object's skeleton, can point to NULL
		*/
		const SmartPtr<Skeleton>& skeleton()
		{
			return pSkeleton;
		}

		/*!
		** \brief Set the skeleton to use for this object
		**
		** \param newSkeleton Skeleton to use
		*/
		void setSkeleton(const SmartPtr<Skeleton>& newSkeleton)
		{
			// No freeing of the old skeleton is necessary here
			// Smart pointers should do that for us
			pSkeleton = newSkeleton;
		}

		//@}

	protected:
		SmartPtr<Object3D> pParent;

		//! The Skeleton for this object (contains the mesh)
		SmartPtr<Skeleton> pSkeleton;
	};

} // Gfx
} // Yuni

#endif // __YUNI_GFX_OBJECT3D_H__
