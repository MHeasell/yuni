#ifndef __YUNI_GFX_OBJECTMODEL_H__
# define __YUNI_GFX_OBJECTMODEL_H__

# include "../toolbox/smartptr/smartptr.h"


namespace Yuni
{
namespace Gfx
{

	/*!
	** \brief Manager (singleton) class for 3D Objects management
	*/
	class ObjectModel
	{
	public:
		typedef SmartPtr<ObjectModel> Ptr;

	public:

		//! \name Constructors
		//@{

		//! Main Constructor
		ObjectModel(const SmartPtr<Skeleton>& skeleton)
			: pSkeleton(skeleton)
		{}

		//@}

		//! \name Methods
		//@{

		/*!
		** \brief Access to the object's skeleton
		**
		** \return A smart pointer to the object's skeleton, can point to NULL
		*/
		const SmartPtr<Skeleton>& skeleton() {return pSkeleton;}

		/*!
		** \brief Change the skeleton used for this model
		**
		** \param skeleton Skeleton to use
		*/
		void setSkeleton(const SmartPtr<Skeleton>& skeleton)
		{
			pSkeleton = skeleton;
		}

		//@}

	private:
		//! The Skeleton for this model (contains the mesh)
		SmartPtr<Skeleton> pSkeleton;

	}; // ObjectModel





} // namespace Gfx
} // namespace Yuni

#endif // !__YUNI_GFX_OBJECTMODEL_H__
