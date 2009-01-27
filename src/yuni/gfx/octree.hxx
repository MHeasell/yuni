
namespace Yuni
{
namespace Gfx
{
	template <typename T>
	Octree<T>::Octree(const BoundingBox<float>& limits, T* data = NULL):
		MaxPointsPerNode(YUNI_OCTREE_MAX_POINTS_PER_NODE), pData(data),
		pBoundingBox(limits), pNbChildren(0), pDepth(1)
	{
		for (int i = 0; i < YUNI_OCTREE_MAX_CHILDREN; ++i)
			pChildren[i] = NULL;
	}

	template <typename T>
	Octree<T>::Octree(const Point3D<float>& min, const Point3D<float>& max, T* data = NULL):
		MaxPointsPerNode(YUNI_OCTREE_MAX_POINTS_PER_NODE), pData(data), pBoundingBox(min, max),
		pNbChildren(0), pDepth(1)
	{
		for (int i = 0; i < YUNI_OCTREE_MAX_CHILDREN; ++i)
			pChildren[i] = NULL;
	}

	template <typename T>
	Octree<T>::Octree(const BoundingBox<float>& limits, uint16 depth, T* data = NULL):
		MaxPointsPerNode(YUNI_OCTREE_MAX_POINTS_PER_NODE), pData(data),
		pBoundingBox(limits), pNbChildren(0), pDepth(1)
	{
		for (int i = 0; i < YUNI_OCTREE_MAX_CHILDREN; ++i)
			pChildren[i] = NULL;
	}

	template <typename T>
	Octree<T>::Octree(const Point3D<float>& min, const Point3D<float>& max, uint16 depth, T* data = NULL):
		MaxPointsPerNode(YUNI_OCTREE_MAX_POINTS_PER_NODE), pData(data), pBoundingBox(min, max),
		pNbChildren(0), pDepth(1)
	{
		for (int i = 0; i < YUNI_OCTREE_MAX_CHILDREN; ++i)
			pChildren[i] = NULL;
	}

	template <typename T>
	Octree<T>::~Octree()
	{
		for (int i = 0; i < YUNI_OCTREE_MAX_CHILDREN; ++i)
		{
			if (pData)
				delete pData;
			if (pChildren[i])
				delete pChildren[i];
		}
	}


	/*!
	 * \brief Add a single point to the Octree
	 *
	 * \param p
	 * \param data
	 * \return
	 */
	template <typename T>
	Octree<T>* Octree<T>::addPoint(const Point3D<float>& p, T* data)
	{
		// If the point is outside the box (we cannot be in a downward recursive call)
		if (!boundingBox().contains(p))
		{
			Point3D<float> newMin(boundingBox().min());
			Point3D<float> newMax(boundingBox().max());
			float width = newMax.x - newMin.x;
			// Adjust x
			if (p.x < newMin.x)
				newMin.x -= width;
			else
				newMax.x += width;
			// Adjust y
			if (p.y < newMin.y)
				newMin.y -= width;
			else
				newMax.y += width;
			// Adjust z
			if (p.z < newMin.z)
				newMin.z -= width;
			else
				newMax.z += width;
			Octree<T>* newRoot = new Octree<T>(newMin, newMax, NULL);
			newRoot->createChild(newRoot->getChildIndex(boundingBox().center()));
			return newRoot->addPoint(p, data);
		}

		// If this is a leaf and the leaf is at the lowest level in the tree
		if (isLeaf() && depth() == 1)
		{
			if (pPoints.size() < MaxPointsPerNode)
			{
				// Directly add the point to the node
				pPoints.push_back(SharedPtr<Point3D<float> >(new Point3D<float>(p)));
				return this;
			}
			// If there are too many points, split the node into subnodes
			split();
		}
		// If this is an inside node or a leaf too high in the tree
		// Find the correct child to propagate to
		uint16 index = getChildIndex(p);
		// Create the new child if necessary
		if (!pChildren[index])
			createChild(index);
		pChildren[index]->addPoint(p, data);
		return this;
	}

	/*!
	** \brief Split a leaf node into sub-nodes
	**
	** Also move each point it contained to the right sub-node.
	** If the node is not a leaf / has no point, do nothing.
	*/
	template <typename T>
	void Octree<T>::split()
	{
		// Loop on all points
		// Nothing will be done if the node contains no point
		while (!pPoints.empty())
		{
			Point3D<float> crtPoint(*(pPoints.back()));
			pPoints.pop_back();
			uint16 index = getChildIndex(crtPoint);
			// Create the child if necessary
			if (!pChildren[index])
				createChild(index);
			pChildren[index]->addPoint(crtPoint);
		}
	}

	/*!
	** \brief Grow the tree to a complete tree of given depth
	**
	** Only the branches containing points will be grown
	** This is a recursive method
	*/
	template <typename T>
	void Octree<T>::growToDepth(uint16 depth)
	{
		if (depth > 0)
		{
			// Split the node if it contains points
			split();
			// Loop on all children
			for (int i = 0; i < YUNI_OCTREE_MAX_CHILDREN; ++i)
				if (pChildren[i])
					// Recursive call
					pChildren[i]->growToDepth(depth - 1);
		}
	}

	/*!
	** \brief Grow the tree to have leaves of the given size
	**
	** Only the branches containing points will be grown
	** This is a recursive method
	*/
	template <typename T>
	void Octree<T>::growToSize(float size)
	{
		if (isLeaf() && boundingBox().max().x - boundingBox().min().x > size)
			// Split the node if it contains points
			split();
		// Loop on all children
		for (int i = 0; i < YUNI_OCTREE_MAX_CHILDREN; ++i)
			if (pChildren[i])
				// Recursive call
				pChildren[i]->growToSize(size);
	}


	template <typename T>
	Octree<T>* Octree<T>::findContainingLeaf(const Point3D<float>& p)
	{
		if (!boundingBox().contains(p))
			return NULL;
		if (isLeaf() && depth() == 1)
			return this;
		// Find which sub-node will contain the point
		Octree<T>* child = pChildren[getChildIndex(p)];
		// If there is no child to recurse on, we are on the correct node
		if (!child)
			return NULL;
		// Recursive call
		return child->findContainingLeaf(p);
	}


	//! Tells if the point already in the tree
	template <typename T>
	bool Octree<T>::contains(const Point3D<float>& p) const
	{
		if (!boundingBox().contains(p))
			return false;
		if (isLeaf())
		{
			for (PointList::const_iterator it = pPoints.begin(); it != pPoints.end(); ++it)
				if ((**it) == p)
					return true;
			return false;
		}
		// Find which sub-node will contain the point
		Octree<T>* child = pChildren[getChildIndex(p)];
		if (!child)
			return false;
		// Recursive call
		return child->contains(p);
	}


	//! Depth of the tree
	template <typename T>
	uint16 Octree<T>::depth() const
	{
		return pDepth;
	}

	//! Number of nodes in the tree
	template <typename T>
	uint32 Octree<T>::nodeCount() const
	{
		uint32 childNodeCount = 0;
		for (int i = 0; i < YUNI_OCTREE_MAX_CHILDREN; ++i)
		{
			if (pChildren[i])
				childNodeCount += pChildren[i]->nodeCount();
		}
		return 1 + childNodeCount;
	}

	//! Number of points in the tree
	template <typename T>
	uint32 Octree<T>::pointCount() const
	{
		uint32 childPointCount = 0;
		for (int i = 0; i < YUNI_OCTREE_MAX_CHILDREN; ++i)
		{
			if (pChildren[i])
				childPointCount += pChildren[i]->pointCount();
		}
		return pPoints.size() + childPointCount;
	}

	template <typename T>
	uint16 Octree<T>::getChildIndex(const Point3D<float>& p) const
	{
		uint16 index = 0;
		const Point3D<float>& center = boundingBox().center();
		if (p.x >= center.x)
			index += 4;
		if (p.y >= center.y)
			index += 2;
		if (p.z >= center.z)
			index += 1;
		return index;
	}

	template <typename T>
	Octree<T>* Octree<T>::createChild(uint16 index)
	{
		if (pChildren[index])
			return pChildren[index];
		Point3D<float> newMin(pBoundingBox.min());
		Point3D<float> newMax(pBoundingBox.max());
		const Point3D<float>& center = pBoundingBox.center();
		// We use the binary encoding of the index to determine
		// the new coordinates
		if ((index & 4) != 0)
			newMin.x = center.x;
		else
			newMax.x = center.x;
		if ((index & 2) != 0)
			newMin.y = center.y;
		else
			newMax.y = center.y;
		if ((index & 1) != 0)
			newMin.z = center.z;
		else
			newMax.z = center.z;
		// Create the new tree node
		pChildren[index] = new Octree(newMin, newMax, depth() - 1, NULL);
		++pNbChildren;
		return pChildren[index];
	}

	template <typename T>
	std::ostream& Octree<T>::print(std::ostream& out) const
	{
		out << "Printing Octree node:" << std::endl;
		for (PointList::const_iterator it = pPoints.begin(); it != pPoints.end(); ++it)
			out << (*it) << std::endl;
		out << "Recursing on " << pNbChildren << " children:" << std::endl;
		for (int i = 0; i < YUNI_OCTREE_MAX_CHILDREN; ++i)
		{
			if (pChildren[i])
				pChildren[i]->print(out);
		}
		return out;
	}


} // Gfx
} // Yuni
