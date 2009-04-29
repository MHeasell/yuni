#ifndef __YUNI_GFX_OBJECTMANAGER_H__
# define __YUNI_GFX_OBJECTMANAGER_H__

# include "../toolbox/hash/table.h"
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
		** \brief Destructor
		**
		** This destructor must not forget to clear the objects table
		*/
		~ObjectManager()
		{
			pObjects.clear();
		}

		/*!
		** \brief Register a 3D object with the manager
		**
		** \param obj The object to register
		*/
		void registerObject(const SmartPtr<Object3D>& obj);

		//@}

	private:
		//! The 3D objects managed by the ObjectManager
		Objects pObjects;

	}; // ObjectManager





} // namespace Gfx
} // namespace Yuni

#endif // !__YUNI_GFX_OBJECTMANAGER_H__
