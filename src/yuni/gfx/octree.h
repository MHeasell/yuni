#ifndef __YUNI_GFX_OCTREE_H__
# define __YUNI_GFX_OCTREE_H__

# include <vector>
# include <iostream>
# include "../yuni.h"
# include "../toolbox/smartptr/sharedptr.h"
# include "point3D.h"
# include "boundingbox.h"


# define YUNI_OCTREE_MAX_CHILDREN  8
# define YUNI_OCTREE_MAX_POINTS_PER_NODE 1


namespace Yuni
{
namespace Gfx
{


	/*!
	** \class Octree
	** \brief Octree datastructure
	**
	** An octree is a tree representing a space partioning.
	** A cube of space is split in 8 smaller cubes around the center.
	**
	** The position of the children in the array is the following :
	** \code
	**   0    1    2    3    4    5    6    7  
	** ------- < X -------||------- >=X -------
	** -- < Y --||-- >=Y -||- < Y --||-- >=Y --
	**  <Z ||>=Z||<Z ||>=Z||<Z ||>=Z||<Z ||>=Z
	** \endcode
	**
	** Or written differently, with Xc, Yc, Zc, being the center's coords :
	** \code
	**    0 : X < Xc,  Y < Yc,  Z < Zc
	**    1 : X < Xc,  Y < Yc,  Z >= Zc
	**    2 : X < Xc,  Y >= Yc, Z < Zc
	**    3 : X < Xc,  Y >= Yc, Z >= Zc
	**    4 : X >= Xc, Y < Yc,  Z < Zc
	**    5 : X >= Xc, Y < Yc,  Z >= Zc
	**    6 : X >= Xc, Y >= Yc, Z < Zc
	**    7 : X >= Xc, Y >= Yc, Z >= Zc
	** \endcode
	**
	** \tparam T
	*/
	template <typename T>
	class Octree
	{
	public:
		//! Max points per node
		const uint16 MaxPointsPerNode;

	public:
		//! \name Constructor & Destructor
		//@{

		//! Constructors
		Octree(const BoundingBox<float>& limits, T* data);
		Octree(const Point3D<float>& min, const Point3D<float>& max, T* data);

		//! Destructor
		virtual ~Octree();

		//@}

		//! Accessors to the value of this treenode
		const T* data() const { return pData; }
		void setData(T* data) { if (pData) delete pData; pData = data; }
		//! Is the node a leaf ?
		bool isLeaf() const { return 0 == pNbChildren; }
		//! Depth of the tree
		uint16 depth() const;
		//! Number of nodes in the tree
		uint32 nodeCount() const;
		//! Number of points in the tree
		uint32 pointCount() const;
		//! Get the bounding box for this tree
		const BoundingBox<float>& boundingBox() const
		{ return pBoundingBox; }

		/*!
		** \brief Add a single point to the  Octree
		**
		** The call should look like this:
		**   myTree = myTree->addPoint(myPoint);
		**
		** \param p The point to add
		** \returns The new root of the tree, or this if it has not changed
		*/
		Octree<T>* addPoint(const Point3D<float>& p, T* data = NULL);

		/*!
		** \brief Recursive find of the leaf whose bounding box contains a given point
		**
		** \param p The point
		** \return The node found
		*/
		Octree<T>* findContainingLeaf(const Point3D<float>& p);

		//! Tells if the point already in the tree
		bool contains(const Point3D<float>& p) const;

		/*!
		** \brief Grow the tree to given depth
		**
		** Only the branches containing points will be grown
		** This is a recursive method
		*/
		void growToDepth(uint16 depth);

		/*!
		** \brief Grow the tree to have leaves of the given size
		**
		** Only the branches containing points will be grown
		** This is a recursive method
		*/
		void growToSize(float size);

		/*!
		** \brief Print all the points contained in the tree (used for debug)
		*/
		std::ostream& print(std::ostream& out) const;

	private:

		/*!
		** \brief Find the index of the child containing the given point
		** \return A value in [0..7]
		*/
		uint16 getChildIndex(const Point3D<float>& p) const;

		/*!
		** \brief Create a child node at given index, if it does not exist yet
		**
		** Automatically calculate its boundaries
		**
		** \return The child in any case
		*/
		Octree<T>* createChild(uint16 index);

		/*!
		** \brief Split a leaf into subnodes
		**
		** Also move each point it contained to the right sub-node.
		** If the node is not a leaf / has no point, do nothing.
		*/
		void split();

	private:
		//! List of points
		typedef typename std::vector< Point3D<float> >  PointList;

	private:
		//! Value of the node. Can be anything at all.
		T* pData;
		//! Center point for the node
		Point3D<float> pCenter;
		//! Bounding box for the points in the tree
		BoundingBox<float> pBoundingBox;

		//! Link to the parent octree (container cube)
		Octree<T>* container;
		//! Links to the children nodes
		Octree<T>* pChildren[YUNI_OCTREE_MAX_CHILDREN];
		//! Store this to know when the node is a leaf (avoid counting children)
		uint16 pNbChildren;
		//! Leaves (and only leaves!) can contain points
		PointList pPoints;

	}; // class Octree




} // namespace Gfx
} // namespace Yuni



//! Operator overload for stream printing
template <typename T>
inline std::ostream& operator << (std::ostream& out, const Yuni::Gfx::Octree<T>& tree)
{
	return tree.print(out);
}


# include "octree.hxx"

#endif // __YUNI_GFX_OCTREE_H__
