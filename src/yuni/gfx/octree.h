#ifndef __YUNI_GFX_OCTREE_H__
# define __YUNI_GFX_OCTREE_H__

# include <vector>
# include <iostream>
# include "../yuni.h"
# include "../misc/sharedptr.h"
# include "point3D.h"

namespace Yuni
{
namespace Gfx
{

	/*! Class Octree
	**
	** An octree is a tree representing a space partioning.
	** A cube of space is split in 8 smaller cubes around the center.
	**
	** The position of the children in the array is the following:
	**   0    1    2    3    4    5    6    7  
	** ------- < X -------||------- >=X -------
	** -- < Y --||-- >=Y -||- < Y --||-- >=Y --
	**  <Z ||>=Z||<Z ||>=Z||<Z ||>=Z||<Z ||>=Z
	**
	** Or written differently, with Xc, Yc, Zc, being the center's coords:
	** 0 : X < Xc , Y < Yc , Z < Zc
	** 1 : X < Xc , Y < Yc , Z >= Zc
	** 2 : X < Xc , Y >= Yc , Z < Zc
	** 3 : X < Xc , Y >= Yc , Z >= Zc
	** 4 : X >= Xc , Y < Yc , Z < Zc
	** 5 : X >= Xc , Y < Yc , Z >= Zc
	** 6 : X >= Xc , Y >= Yc , Z < Zc
	** 7 : X >= Xc , Y >= Yc , Z >= Zc
	*/
	template <typename T>
	class Octree
	{
	public:
		const uint16 MAX_POINTS_PER_NODE;

	public:
		Octree(const Point3D<float>& min, const Point3D<float>& max, T* data);
		virtual ~Octree();

		//! Accessor to the value of this treenode
		const T& data() const { return *pData; }
		//! Is the node a leaf?
		bool isLeaf() const { return 0 == pNbChildren; }
		//! Depth of the tree
		inline uint16 depth() const;
		//! Number of nodes in the tree
		inline uint32 nodeCount() const;
		//! Number of points in the tree
		inline uint32 pointCount() const;

		//! Add a single point to the  Octree
		Octree<T>* addPoint(const SharedPtr<Point3D<float> >& p);
		//! Find the smallest existing cube containing the given point
		Octree<T>* findSmallestBBox(const Point3D<float>& p) const;
		//! Split a leaf into subnodes
		void split();

		//! Find the index of the child containing the given point
		uint16 getChildIndex(const Point3D<float>& p) const;
		//! Create a child node at given index
		Octree<T>* createChild(uint16 index);

		std::ostream& print(std::ostream& out) const;

	private:
		//! Value of the node. Can be anything at all.
		T* pData;
		//! Center point for the node
		Point3D<float> pCenter;
		//! Min point of the bounding box
		Point3D<float> pMin;
		//! Max point of the bounding box
		Point3D<float> pMax;

		//! Links to the children nodes
		Octree<T>* pChildren[8];
		//! Store this to know when the node is a leaf (avoid counting children)
		uint16 pNbChildren;
		//! Leaves (and only leaves!) can contain points
		std::vector<SharedPtr<Point3D<float> > > pPoints;

	}; // class Octree


} // Gfx
} // Yuni



//! Operator overload for stream printing
template <typename T>
std::ostream& operator<<(std::ostream& out, const Yuni::Gfx::Octree<T>& tree)
{
	return tree.print(out);
}


# include "octree.hpp"

#endif // __YUNI_GFX_OCTREE_H__
