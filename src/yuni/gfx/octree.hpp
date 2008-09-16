
namespace Yuni
{
namespace Gfx
{

	template <typename T>
	Octree<T>::Octree(const Point3D<float>& min, const Point3D<float>& max, T* data = NULL):
		MAX_POINTS_PER_NODE(32), pData(data),
		pCenter(0, 0, 0), pMin(min), pMax(max)
	{
		// The Center is the mean of the min and the max
		pCenter.move(min);
		pCenter.mean(max);
		for (uint16 i = 0; i < 8; ++i)
			pChildren[i] = NULL;
		pNbChildren = 0;
	}

	template <typename T>
	Octree<T>::~Octree()
	{
		for (uint16 i = 0; i < 8; ++i)
		{
			if (NULL != pChildren[i])
				delete pChildren[i];
		}
	}


	//! Add a single point to the Octree
	template <typename T>
	Octree<T>* Octree<T>::addPoint(const SharedPtr<Point3D<float> >& p)
	{
		// If this is a leaf
		if (isLeaf())
		{
			if (pPoints.size() < MAX_POINTS_PER_NODE)
			{
				// Directly add the point to the node
				pPoints.push_back(p);
				return this;
			}
			// If there are too many points, split the node into subnodes
			split();
		}
		// If this is an inside node
		// Find the correct child to propagate to
		uint16 index = getChildIndex(p);
		// Create the new child if necessary
		if (NULL == pChildren[index])
			createChild(index);
		return pChildren[index]->addPoint(p);
	}

	/*! Split a leaf node into sub-nodes, and move each point
	** it contained to the right sub-node.
	** If the node is not a leaf, do nothing.
	*/
	template <typename T>
	void Octree<T>::split()
	{
		// Loop on all points
		// Nothing will be done if the node contains no point
		while (pPoints.size() > 0)
		{
			Point3D<float> crtPoint(pPoints.back());
			pPoints.pop_back();
			uint16 index = getChildIndex(crtPoint);
			// Create the child if necessary
			if (NULL == pChildren[index])
				createChild(index);
			pChildren[index]->addPoint(crtPoint);
		}
	}

	template <typename T>
	Octree<T>* Octree<T>::findSmallestBBox(const Point3D<float>& p) const
	{
		if (isLeaf())
			return this;
		// Find which sub-node will contain the point
		Octree<T>* child = pChildren[getChildIndex(p)];
		// If there is no child to recurse on, we are on the correct node
		if (NULL == child)
			return this;
		// Recursive call
		return child->findSmallestBox(p);
	}

	//! Depth of the tree
	template <typename T>
	uint16 Octree<T>::depth() const
	{
		uint16 maxChildDepth = 0;
		for (uint16 i = 0; i < 7; ++i)
		{
			if (NULL == pChildren[i])
				continue;
			uint16_t childDepth = pChildren[i]->depth();
			if (maxChildDepth < childDepth)
				maxChildDepth = childDepth;
		}
		return 1 + maxChildDepth;
	}

	//! Number of nodes in the tree
	template <typename T>
	uint32 Octree<T>::nodeCount() const
	{
		uint32_t childNodeCount = 0;
		for (uint16 i = 0; i < 7; ++i)
			if (NULL != pChildren[i])
				childNodeCount += pChildren[i]->nodeCount();
		return 1 + childNodeCount;
	}

	//! Number of points in the tree
	template <typename T>
	uint32 Octree<T>::pointCount() const
	{
		uint32 childPointCount = 0;
		for (uint16 i = 0; i < 7; ++i)
			if (NULL != pChildren[i])
				childPointCount += pChildren[i]->pointCount();
		return pPoints.size() + childPointCount;
	}

	template <typename T>
	uint16 Octree<T>::getChildIndex(const Point3D<float>& p) const
	{
		uint16 index = 0;
		if (p.x >= pCenter.x)
			index += 4;
		if (p.y >= pCenter.y)
			index += 2;
		if (p.z >= pCenter.z)
			index += 1;
		return index;
	}

	template <typename T>
	Octree<T>* Octree<T>::createChild(uint16 index)
	{
		if (NULL != pChildren[index])
		return pChildren[index];
		Point3D<float> newMin(pMin);
		Point3D<float> newMax(pMax);
		// We use the binary encoding of the index to determine
		// the new coordinates
		if ((index & 4) != 0)
			newMin.x = pCenter.x;
		else
			newMax.x = pCenter.x;
		if ((index & 2) != 0)
			newMin.y = pCenter.y;
		else
			newMax.y = pCenter.y;
		if ((index & 1) != 0)
			newMin.z = pCenter.z;
		else
			newMax.z = pCenter.z;
		// Create the new tree node
		pChildren[index] = new Octree(newMin, newMax, NULL);
		++pNbChildren;
		return pChildren[index];
	}

	template <typename T>
	std::ostream& Octree<T>::print(std::ostream& out) const
	{
		out << "Printing Octree node:" << std::endl;
		for (std::vector<Point3D<float> >::const_iterator it = pPoints.begin(); it != pPoints.end(); ++it)
			out << (*it) << std::endl;
		out << "Recursing on " << pNbChildren << " children:" << std::endl;
		for (uint16 i = 0; i < 7; ++i)
		{
			if (NULL != pChildren[i])
				pChildren[i]->print(out);
		}
		return out;
	}


} // Gfx
} // Yuni
