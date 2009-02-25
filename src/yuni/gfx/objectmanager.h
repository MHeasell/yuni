
#ifndef __YUNI_GFX_OBJECTMANAGER_H__
# define __YUNI_GFX_OBJECTMANAGER_H__

# include "../toolbox/smartptr/smartptr.h"

namespace Yuni
{
namespace Gfx
{

	// Forward declaration
	class Object3D;


	/*!
	** \brief Manager (singleton) class for 3D Objects management
	*/
	class ObjectManager
	{
	public:
		typedef Hash::Table< uint64, SmartPtr<Object3D> > Objects;

	public:

		//! \name Class methods
		//@{

		//! Accessor to the singleton instance
		static SmartPtr<ObjectManager> Instance();

		//@}

		//! \name Instance methods
		//@{

		/*!
		** \brief Register a 3D object with the manager
		**
		** \param obj The object to register
		*/
		void registerObject(SmartPtr<Object3D>& obj);

		//@}

	private:
		//! The 3D objects managed by the ObjectManager
		Objects pObjects;

	}; // ObjectManager


} // Gfx
} // Yuni

#endif // !__YUNI_GFX_OBJECTMANAGER_H__
