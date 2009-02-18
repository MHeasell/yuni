
#ifndef __YUNI_GFX_SKELETON_H__
# define __YUNI_GFX_SKELETON_H__

namespace Yuni
{
namespace Gfx
{

	/*!
	** \brief A skeleton contains a mesh and possibly sub-skeletons
	*/
	class Skeleton
	{
	public:
		//! Type for Object list
		typedef std::vector<SharedPtr<Skeleton> > SkeletonList;

	public:
		//! \name Constructors & Destructor
		//@{

		/*!
		** \brief Main Constructor
		** \param mesh Mesh to use for this skeleton
		** \param position Position of the skeleton in space relative to its parent (absolute if no parent)
		** \param rotation Rotation of the skeleton relative to its parent (absolute if no parent)
		** \param parent Parent skeleton, NULL if none
		*/
		Skeleton(SharedPtr<Mesh>& mesh, const Vector3D<float>& position,
			const Vector3D<float>& rotation, Skeleton* parent = NULL)
			: pMesh(mesh), pPosition(position), pRotation(rotation), pParent(parent)
		{}

		//@}


		//! \name Accessors
		//@{

		/*!
		** \brief Access to the sub-skeletons
		**
		** \return A reference to the sub-skeleton list
		*/
		ObjectList& subSkeletons()
		{
			return pSubSkeletons;
		}

		/*!
		** \brief Access to the object's mesh
		**
		** \return A smart pointer to the object's mesh, can point to NULL
		*/
		const SharedPtr<Mesh>& mesh()
		{
			return pMesh;
		}

		/*!
		** \brief Add a sub-skeleton to the skeleton
		**
		** \param sub Sub-skeleton to add
		*/
		void addSubSkeleton(SharedPtr<Skeleton>& sub)
		{
			pSubSkeletons.push_back(sub);
		}

		//@}

	private:
		//! Position of the skeleton in space relative to its parent (absolute if no parent)
		Vector3D<float> Pposition;

		//! Rotation of the skeleton relative to its parent (absolute if no parent)
		Vector3D<float> pRotation;

		//! Actual mesh (triangles and vertices) for this skeleton
		SharedPtr<Mesh> pMesh;

		//! Parent skeleton, NULL if none
		Skeleton* pParent;

		//! Sub-skeletons
		SkeletonList pSubSkeletons;
	};

} // Gfx
} // Yuni

#endif // __YUNI_GFX_SKELETON_H__
