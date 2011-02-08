#ifndef __YUNI_GFX_MESH_SKELETON_H__
# define __YUNI_GFX_MESH_SKELETON_H__

# include "../../core/tree/treeN.h"
# include "mesh.h"


namespace Yuni
{
namespace Gfx
{


	/*!
	** \brief A skeleton contains a mesh and possibly sub-skeletons
	*/
	class Skeleton: public Core::TreeN<Skeleton>
	{
	public:
		typedef SmartPtr<Skeleton> Ptr;

	public:
		//! \name Constructors & Destructor
		//@{

		/*!
		** \brief Empty Constructor
		**
		** Empty skeleton, empty mesh
		*/
		Skeleton()
			:pMesh(new Mesh())
		{}


		/*!
		** \brief Constructor with no transformation
		** \param Mesh to use for this skeleton
		*/
		Skeleton(Mesh::Ptr& mesh)
			:pMesh(mesh)
		{}

		/*!
		** \brief Main Constructor
		** \param mesh Mesh to use for this skeleton
		** \param position Position of the skeleton in space relative to its parent (absolute if no parent)
		** \param rotation Rotation of the skeleton relative to its parent (absolute if no parent)
		*/
		Skeleton(Mesh::Ptr& mesh, const Vector3D<float>& position,
			const Vector3D<float>& rotation)
			:pMesh(mesh), pPosition(position), pRotation(rotation)
		{}

		//@}

		//! \name Accessors
		//@{

		/*!
		** \brief Access to the object's mesh
		**
		** \return A smart pointer to the object's mesh, can point to NULL
		*/
		const Mesh::Ptr& mesh() const { return pMesh; }

		Vector3D<float> position() const { return pPosition; }

		Vector3D<float> rotation() const { return pRotation; }

		//@}

	private:
		//! Actual mesh (triangles and vertices) for this skeleton
		Mesh::Ptr pMesh;

		//! Position of the skeleton in space relative to its parent (absolute if no parent)
		Vector3D<float> pPosition;

		//! Rotation of the skeleton relative to its parent (absolute if no parent)
		Vector3D<float> pRotation;
	};





} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_MESH_SKELETON_H__
