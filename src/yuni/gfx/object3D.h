#ifndef __YUNI_GFX_OBJECT3D_H__
# define __YUNI_GFX_OBJECT3D_H__

# include "../core/string/string.h"
# include "../core/smartptr/smartptr.h"
# include "../core/tree/treeN.h"
# include "skeleton.h"
# include "objectmodel.h"


namespace Yuni
{
namespace Gfx
{


	/*!
	** \brief A 3D object is an abstract scene object
	**
	** It can contain other objects, and has a skeleton for its mesh
	** It also has a shared "template" object storing every characteristic common with similar objects
	** Object3D objects must not be deleted, they are destroyed by the objectmanager.
	*/
	class Object3D: public Core::TreeN<Object3D>
	{
	public:
		//! Pointer
		typedef Core::TreeN<Object3D>::Ptr Ptr;
		typedef uint64 ID;

	public:
		//! Static ID counter (naive version, never reuses old IDs)
		static ID NextID();

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		Object3D(const ObjectModel::Ptr& model);

		/*!
		** \brief Default Constructor
		*/
		Object3D(const Yuni::String& name, const ObjectModel::Ptr& model);

		//! Default Destructor
		virtual ~Object3D();
		//@}


		//! \name Accessors
		//@{

		/*!
		** \brief Access to the object's skeleton
		**
		** \return A smart pointer to the object's skeleton, can point to NULL
		*/
		const Skeleton::Ptr& skeleton()
		{
			return pSkeleton;
		}

		/*!
		** \brief Set the skeleton to use for this object
		**
		** \param newSkeleton Skeleton to use
		*/
		void skeleton(const Skeleton::Ptr& newSkeleton);

		//! Get the name of the object
		const ID id() const {return pID;}

		//@}

	protected:
		//! Unique identifier for this object (type can still change)
		const ID pID;

		//! Name of the object
		String pName;
		//! The object must use a model (template) for its skeleton / textures
		ObjectModel::Ptr pModel;
		//! Optional skeleton, overrides the model!
		Skeleton::Ptr pSkeleton;

	}; // Object3D





} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_OBJECT3D_H__
