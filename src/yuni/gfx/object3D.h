#ifndef __YUNI_GFX_OBJECT3D_H__
# define __YUNI_GFX_OBJECT3D_H__

# include "../toolbox/string/string.h"
# include "../toolbox/smartptr/smartptr.h"
# include "../toolbox/tree/treeN.h"
# include "skeleton.h"
# include "objectmanager.h"
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
	** 3D Objects should not be deleted by hand, they will be deleted by the objectmanager.
	*/
	class Object3D: public Toolbox::TreeN<Object3D>
	{
	public:
		//! \name Constructors & Destructor
		//@{

		//! Default Constructor
		Object3D(const Yuni::String& name, const SmartPtr<ObjectModel>& model)
			: pName(name), pModel(model), pSkeleton(NULL)
		{
			ObjectManager::Instance()->registerObject(SmartPtr<Object3D>(this));
		}

		//! Constructor with mesh initialization
		Object3D(const Yuni::String& name, const SmartPtr<ObjectModel>& model, Skeleton* skeleton)
			: pName(name), pModel(model), pSkeleton(skeleton)
		{
			ObjectManager::Instance()->registerObject(SmartPtr<Object3D>(this));
		}

		//! Default Destructor
		~Object3D()
		{
			if (pSkeleton)
				delete pSkeleton;
		}

		//@}


		//! \name Accessors
		//@{

		/*!
		** \brief Access to the object's skeleton
		**
		** \return A smart pointer to the object's skeleton, can point to NULL
		*/
		const Skeleton* skeleton() {return pSkeleton;}

		/*!
		** \brief Set the skeleton to use for this object
		**
		** \param newSkeleton Skeleton to use
		*/
		void setSkeleton(Skeleton* newSkeleton)
		{
			if (pSkeleton)
				delete pSkeleton;
			pSkeleton = newSkeleton;
		}

		//! Get the name of the object
		const Yuni::String& name() const {return pName;}

		//@}

	protected:
		//! Name of the object
		Yuni::String pName;

		//! The object must use a model (template) for its skeleton / textures
		SmartPtr<ObjectModel> pModel;

		//! Optional skeleton, overrides the model!
		Skeleton* pSkeleton;

	}; // Object3D




} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_OBJECT3D_H__
