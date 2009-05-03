#ifndef __YUNI_GFX_OBJECT3D_H__
# define __YUNI_GFX_OBJECT3D_H__

# include "../toolbox/string/string.h"
# include "../toolbox/smartptr/smartptr.h"
# include "../toolbox/tree/treeN.h"
# include "skeleton.h"
# include "objectmodel.h"
# include "scene.h"
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
	class Object3D: public Toolbox::TreeN<Object3D>
	{
	public:
		typedef SmartPtr<Object3D> Ptr;

	public:
		//! Static ID counter (naive version, never reuses old IDs)
		static uint64 sNextID;

	public:
		//! \name Constructors & Destructor
		//@{

		//! Default Constructor
		Object3D(const Yuni::String& name, const SmartPtr<ObjectModel>& model)
			:pID(sNextID++), pName(name), pModel(model), pSkeleton(NULL)
		{
			Scene::Instance()->registerObject(Ptr(this));
		}

		//! Constructor with mesh initialization
		Object3D(const Yuni::String& name, const ObjectModel::Ptr& model, const Skeleton::Ptr& skeleton)
			:pID(sNextID++), pName(name), pModel(model), pSkeleton(skeleton)
		{
			Scene::Instance()->registerObject(Ptr(this));
		}

		//! Default Destructor
		virtual ~Object3D()
		{
		}

		//@}


		//! \name Accessors
		//@{

		/*!
		** \brief Access to the object's skeleton
		**
		** \return A smart pointer to the object's skeleton, can point to NULL
		*/
		const Skeleton::Ptr& skeleton() {return pSkeleton;}

		/*!
		** \brief Set the skeleton to use for this object
		**
		** \param newSkeleton Skeleton to use
		*/
		void skeleton(const Skeleton::Ptr& newSkeleton)
		{
			pSkeleton = newSkeleton;
		}

		//! Get the name of the object
		const uint64 id() const {return pID;}

		//@}

	protected:
		//! Unique identifier for this object (type can still change)
		uint64 pID;

		//! Name of the object
		Yuni::String pName;

		//! The object must use a model (template) for its skeleton / textures
		ObjectModel::Ptr pModel;

		//! Optional skeleton, overrides the model!
		Skeleton::Ptr pSkeleton;

	}; // Object3D


} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_OBJECT3D_H__
