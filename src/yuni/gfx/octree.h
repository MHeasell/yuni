#ifndef __LIB_3D_OCTREE_H__
# define __LIB_3D_OCTREE_H__

# include <vector>
# include <iostream>
# include "point.h"

namespace W
{
    namespace GUI3D
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
            const uint16_t MAX_POINTS_PER_NODE;

        public:
            Octree(const Point& min, const Point& max, T* data);
            virtual ~Octree();

            //! Accessor to the value of this treenode
            const T& data() const { return *pData; }
            //! Is the node a leaf?
            bool isLeaf() const { return 0 == pNbChildren; }
            //! Depth of the tree
            inline uint16_t depth() const;
            //! Number of nodes in the tree
            inline uint32_t nodeCount() const;
            //! Number of points in the tree
            inline uint32_t pointCount() const;

            //! Add a single point to the  Octree
            Octree<T>* addPoint(const Point& p);
            //! Find the smallest existing cube containing the given point
            Octree<T>* findSmallestBBox(const Point& p) const;
            //! Split a leaf into subnodes
            void split();
            //! Find the index of the child containing the given point
            uint16_t getChildIndex(const Point& p) const;
            //! Create a child node at given index
            Octree<T>* createChild(uint16_t index);

            std::ostream& print(std::ostream& out) const;

        private:
            //! Value of the node. Can be anything at all.
            T* pData;

            //! Center point for the node
            Point pCenter;
            //! Min point of the bounding box
            Point pMin;
            //! Max point of the bounding box
            Point pMax;

            //! Links to the children nodes
            Octree<T>* pChildren[8];
            //! Store this to know when the node is a leaf (avoid counting children)
            uint16_t pNbChildren;
            //! Leaves (and only leaves!) can contain points
            std::vector<Point> pPoints;

        }; // class Octree


} // GUI3D
} // W




//! Operator overload for stream printing
template <typename T>
std::ostream& operator<<(std::ostream& out, const W::GUI3D::Octree<T>& tree)
{
    return tree.print(out);
}



# include "octree.hpp"

#endif // __LIB_3D_OCTREE_H__
