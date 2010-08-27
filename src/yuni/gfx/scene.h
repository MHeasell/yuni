#ifndef __YUNI_GFX_SCENE_H__
# define __YUNI_GFX_SCENE_H__

# include <map>
# include "../yuni.h"
# include "../core/smartptr.h"
# include "object3D.h"


namespace Yuni
{
namespace Gfx
{


	/*!
	** \brief The 3D scene contains a tree of 3D Objects
	*/
	class Scene : public Policy::ObjectLevelLockable<Scene>
	{
	public:
		//! The threading Policy
		typedef Policy::ObjectLevelLockable<Scene> ThreadingPolicy;

		//! Smart pointer
		typedef SmartPtr<Scene> Ptr;

		//! Map of objects
		typedef std::map<uint64, Object3D::Ptr> ObjectMap;


	public:
		//! Empty constructor
		Scene()
		{}
		//! Copy constructor. TODO: Implement deep copy !
		Scene(const Scene& rhs)
			:ThreadingPolicy(), pObjects(rhs.pObjects)
		{}

		/*!
		** \brief Destructor
		**
		** This destructor must not forget to clear the objects table
		*/
		~Scene()
		{
			pObjects.clear();
		}

		//! \name Methods
		//@{
		//! Get the objects in the scene
		const ObjectMap& objects() const { return pObjects; }


	protected:
		/*!
		** \brief Register a 3D object with the manager
		**
		** \param obj The object to register
		*/
		void registerObject(Object3D* obj);

		//@}

	private:
		//! The 3D objects managed by the ObjectManager
		ObjectMap pObjects;

		// Our friends !
		friend class Object3D;

	}; // Scene




} // namespace Gfx
} // namespace Yuni

#endif // !__YUNI_GFX_SCENE_H__
