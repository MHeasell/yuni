#ifndef __YUNI_GFX_SKELETON_H__
# define __YUNI_GFX_SKELETON_H__

# include "../toolbox/tree/treeN.h"
# include "mesh.h"


namespace Yuni
{
namespace Gfx
{


	/*!
	** \brief A skeleton contains a mesh and possibly sub-skeletons
	*/
	class Skeleton: public Toolbox::TreeN<Skeleton>
	{
	public:
		//! \name Constructors & Destructor
		//@{

		/*!
		** \brief Main Constructor
		** \param mesh Mesh to use for this skeleton
		** \param position Position of the skeleton in space relative to its parent (absolute if no parent)
		** \param rotation Rotation of the skeleton relative to its parent (absolute if no parent)
		*/
		Skeleton(SmartPtr<Mesh>& mesh, const Vector3D<float>& position,
			const Vector3D<float>& rotation)
			: pMesh(mesh), pPosition(position), pRotation(rotation)
		{}

		//@}

		//! \name Accessors
		//@{

		/*!
		** \brief Access to the object's mesh
		**
		** \return A smart pointer to the object's mesh, can point to NULL
		*/
		const SmartPtr<Mesh>& mesh() {return pMesh;}

		//@}

	private:
		//! Actual mesh (triangles and vertices) for this skeleton
		SmartPtr<Mesh> pMesh;

		//! Position of the skeleton in space relative to its parent (absolute if no parent)
		Vector3D<float> pPosition;

		//! Rotation of the skeleton relative to its parent (absolute if no parent)
		Vector3D<float> pRotation;
	};





} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_SKELETON_H__
