
#ifndef __YUNI_GFX_OBJECT3D_H__
# define __YUNI_GFX_OBJECT3D_H__

# include "../toolbox/smartptr/sharedptr.h"
# include "skeleton.h"

namespace Yuni
{
namespace Gfx
{

	/*!
	** \brief A 3D object is an abstract scene object
	**
	** It can contain other objects, and has a skeleton for its mesh
	*/
	class Object3D
	{
	public:
		//! Type for Object list
		typedef std::vector<SharedPtr<Object3D> > ObjectList;

	public:
		//! \name Constructors & Destructor
		//@{

		//! Default Constructor
		Object3D(Object3D* parent = NULL)
		: pParent(parent)
		{}

		//! Constructor with mesh initialization
		Object3D(SharedPtr<Skeleton>& skeleton, Object3D* parent)
			: pParent(parent), pSkeleton(skeleton)
		{}

		//! Default Destructor
		~Object3D() {}
		//@}


		//! \name Accessors
		//@{

		/*!
		** \brief Access to the object's children
		**
		** \return A reference to the object's children
		*/
		ObjectList& children()
		{
			return pChildren;
		}

		/*!
		** \brief Access to the object's skeleton
		**
		** \return A smart pointer to the object's skeleton, can point to NULL
		*/
		const SharedPtr<Skeleton>& skeleton()
		{
			return pSkeleton;
		}

		/*!
		** \brief Add a child to the object
		**
		** \param child Child to add
		*/
		void addChild(Object3D& child)
		{
			pChildren.push_back(tri);
		}

		/*!
		** \brief Set the skeleton to use for this object
		**
		** \param newSkeleton Skeleton to use
		*/
		void setSkeleton(const SharedPtr<Skeleton>& newSkeleton)
		{
			// No freeing of the old skeleton is necessary here
			// Smart pointers should do that for us
			pSkeleton = newSkeleton;
		}

		//@}

	protected:
		Object3D* pParent;

		//! The Object can contain other objects
		ObjectList pChildren;

		//! The Skeleton for this object (contains the mesh)
		SharedPtr<Skeleton> pSkeleton;
	};

} // Gfx
} // Yuni

#endif // __YUNI_GFX_OBJECT3D_H__
