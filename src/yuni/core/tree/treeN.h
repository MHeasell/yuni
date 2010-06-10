#ifndef __YUNI_CORE_TREE_N_H__
# define __YUNI_CORE_TREE_N_H__

# include "../../yuni.h"
# include <list>
# include <vector>
# include <stack>
# include "../static/if.h"
# include "../smartptr/smartptr.h"
# include <ostream>



namespace Yuni
{
namespace Core
{


	/*!
	** \brief A generic N-ary tree class.
	**
	** This class provides a generic and thread-safe implementation for
	** N-ary trees. It behaves like a STL container class.
	**
	** \code
	** class MyNode : public Core::TreeN<MyNode, Policy::SingleThreaded>
	** {
	** public:
	** 		MyNode()
	** 			:pValue()
	**		{}
	**
	** 		explicit MyNode(const String& v)
	** 			:pValue(v)
	** 		{}
	**
	** 		virtual ~MyNode() {}
	**
	** 		String value()
	** 		{
	** 			MyNode::ThreadingPolicy::MutexLocker locker(*this);
	** 			return pValue;
	** 		}
	**
	** 		void value(const String& s)
	** 		{
	** 			MyNode::ThreadingPolicy::MutexLocker locker(*this);
	** 			pValue = s;
	** 		}
	**
	** private:
	** 		//! Put here variables for each node
	** 		String pValue;
	** };
	**
	** int main(void)
	** {
	** 		MyNode::Ptr root(new MyNode("Here is a root node"));
	** 		MyNode* n = new MyNode("SubNode 1");
	**
	** 		// Adding `n` as a child for the root node
	** 		*root += n;
	**
	** 		// A few children for the node `n`
	** 		// The operator `+=` and `<<` are equivalent
	** 		n << new MyNode("SubSubNode 1") << new MyNode("SubSubNode 2")
	** 			<< new MyNode("SubSubNode 3");
	**
	** 		return 0;
	** }
	** \endcode
	**
	**
	** Example of a pseudo XML tree :
	** \code
	** class MyXMLNode : public Yuni::Core::TreeN<MyXMLNode>
	** {
	** public:
	**		MyXMLNode() :pValue() {}
	**		virtual MyXMLNode() {}
	**
	**		Yuni::String value()
	**		{
	**			ThreadingPolicy::MutexLocker locker(*this);
	**			return pValue;
	**		}
	**		void value(const Yuni::String& v)
	**		{
	**			ThreadingPolicy::MutexLocker locker(*this);
	**			pValue = v;
	**		}
	**
	** protected:
	**		virtual void printBeginWL(std::ostream& out, const unsigned int) const
	**		{
	**			out << "<node><![CDATA[" << pValue << "]]>";
	**		}
	**		virtual void printBeginWL(std::ostream& out, const unsigned int) const
	**		{
	**			out << "</node>";
	**		}
	**
	** private:
	**		Yuni::String pValue;
	**
	** };
	**
	** int main(void)
	** {
	**		MyXMLNode::Ptr root(new MyXMLNode("root node"));
	**		MyXMLNode* sub = new MyXMLNode("Sub Node 1");
	**		// Adding sub nodes
	**		*root << sub << new MyXMLNode("Sub Node 2");
	**		// Adding sub-sub nodes
	**		*sub << new MyXMLNode("Sub Sub Node 1") << new MyXMLNode("Sub Sub Node 2");
	**
	**		// print
	**		root->print(std::cout) << std::endl;
	**
	**		return 0;
	** }
	** \endcode
	**
	** \note Contrary to a STL-like container class, this class is not designed
	**       to be directly used, but to be a base class.
	**
	** \note Each node is managed by a smart pointer, and assuming the
	**       `SingleThreaded` policy is not used, it is safe to manipulate a
	**       node from everywhere.
	**
	** \note When manipulating nodes, always prefer to use the `Ptr` typedef.
	**
	** \note Any checking policy might be used (passed to the smart pointer).
	**       However, we want to be able to have NULL pointers.
	**
	** \note This implementation will be more efficient when handling large dataset,
	**       and in a multithreaded context.
	**
	**
	** \tparam T The real type of the tree class
	** \tparam TP The Threading policy
	** \tparam ChckP  The Checking policy
	** \tparam ConvP  The Conversion policy
	*/
	template<class T,                                                // The original type
		template<class> class TP     = Policy::ObjectLevelLockable,  // The threading policy
		template <class> class ChckP = Policy::Checking::None,       // Checking policy
		class ConvP			         = Policy::Conversion::Allow     // Conversion policy
		>
	class TreeN : public TP< TreeN<T,TP> >
	{
	public:
		//! The real type
		typedef T Type;
		//! Node
		typedef TreeN<T,TP,ChckP,ConvP> Node;

		//! The threading policy
		typedef TP<Node>  ThreadingPolicy;

		//! A thread-safe node type
		typedef SmartPtr<Node, Policy::Ownership::COMReferenceCounted,ChckP,ConvP>  PtrThreadSafe;
		//! A default node type
		typedef SmartPtr<Node, Policy::Ownership::COMReferenceCounted,ChckP,ConvP>    PtrSingleThreaded;
		//! Pointer to a node
		typedef typename Static::If<ThreadingPolicy::threadSafe, PtrThreadSafe, PtrSingleThreaded>::ResultType Ptr;

		//! The Storage policy
		typedef typename Ptr::StoragePolicy    StoragePolicy;
		//! The Ownership policy
		typedef typename Ptr::OwnershipPolicy  OwnershipPolicy;
		//! The conversion policy
		typedef typename Ptr::ConversionPolicy ConversionPolicy;
		//! The checking policy
		typedef typename Ptr::CheckingPolicy   CheckingPolicy;
		//! The Constness policy
		typedef typename Ptr::ConstnessPolicy  ConstnessPolicy;

		//! A const Pointer
		typedef typename Ptr::ConstSmartPtrType ConstPtr;
		//! A non-const pointer
		typedef typename Ptr::NonConstSmartPtrType NonConstPtr;

		//! Size
		typedef unsigned int SizeType;
		//! Size (signed)
		typedef int SignedSizeType;

		//! A vector of nodes (std::vector)
		typedef std::vector<Ptr>  Vector;
		//! A list of nodes (std::list)
		typedef std::list<Ptr>    List;

		// iterators
		class iterator;

		# include "treeN.iterator.def.h"
		# include "treeN.iterator.h"
		# include "treeN.iterator.undef.h"

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		TreeN();
		//! Destructor
		virtual ~TreeN();
		//@}


		//! \name Parent of the node
		//@{
		//! Get the parent of the node
		Ptr& parent() {return pParent;}
		//! Get the parent of the node
		const Ptr& parent() const {return pParent;}

		/*!
		** \brief ReAttach to another parent
		*/
		void parent(Ptr& newParent);

		/*!
		** \brief Detach the node from its parent
		*/
		void detachFromParent();
		//@}



		//! \name Adding
		//@{
		/*!
		** \brief Append a child node to the end of the list
		** \param node The new child node
		*/
		void append(Ptr& node);
		void append(T* node);

		/*!
		** \brief Append a child node at the end
		** \param node The new child node
		*/
		void push_back(Ptr& node);
		void push_back(T* node);


		/*!
		** \brief Append a child node at the begining
		** \param node The new child node
		*/
		void push_front(Ptr& node);
		void push_front(T* node);
		//@}


		//! \name Removing
		//@{
		/*!
		** \brief Remove all children
		*/
		void clear();

		/*!
		** \brief Remove a child node
		** \return True if the node has been removed, False otherwise
		*/
		bool remove(Ptr& node);

		/*!
		** \brief Remove the n-th child of the node
		**
		** This method is only provided for convenience reasons. This method is
		** slow and should be used with care.
		**
		** \param index Index of the child node to remove (zero-based) and this value
		** can be out of bounds
		** \return True if the node has been removed, False otherwise
		*/
		bool remove(const SizeType index);
		bool remove(const SignedSizeType index);
		//@}


		//! \name Searching
		//@{
		//! Return iterator to the first child of the node
		iterator  begin() {return iterator(pFirstChild);}
		const iterator  begin() const {return iterator(pFirstChild);}
		//! Return iterator to the last child of the node
		iterator  end() {return iterator();}
		const iterator  end() const {return iterator();}


		/*!
		** \brief Find the n-th child of the node
		**
		** This method is only provided for convenience reasons. This method is
		** slow and should be used with care.
		**
		** \param index Index of the child node to remove (zero-based) and this value
		** can be out of bounds
		** \return A pointer to a Ptr, NULL of not found
		*/
		Ptr find(const SizeType index);
		Ptr find(const SignedSizeType index);

		/*!
		** \brief Get if the node has children
		*/
		bool empty();

		/*!
		** \brief
		*/
		SizeType count();
		//! Alias for count()
		SizeType size();

		/*!
		** \brief Get the first child
		*/
		Ptr firstChild() {return pFirstChild;}
		const Ptr firstChild() const {return pFirstChild;}

		/*!
		** \brief Get the last child
		*/
		Ptr lastChild() {return pLastChild;}
		const Ptr lastChild() const {return pLastChild;}

		/*!
		** \brief Get the previous sibling
		*/
		Ptr previousSibling() {return pPreviousSibling;}
		const Ptr previousSibling() const {return pPreviousSibling;}

		/*!
		** \brief Get the next sibling
		*/
		Ptr nextSibling() {return pNextSibling;}
		const Ptr nextSibling() const {return pNextSibling;}
		//@}


		//! \name Extra
		//@{
		/*!
		** \brief Get if the node is a leaf
		**
		** A leaf is merely a node without any children
		** \return True if this node is a leaf, False otherwise
		*/
		bool leaf();

		/*!
		** \brief Computes the depth of this node
		**
		** The depth of a node n is the length of the path from the root to
		** the node. The set of all nodes at a given depth is sometimes called
		** a level of the tree. The root node is at depth zero.
		*/
		SizeType depth();

		/*!
		** \brief Computes the height from this node
		**
		** The height of a tree is the length of the path from the root to the
		** deepest node in the tree.
		** A (rooted) tree with only a node (the root) has a height of zero.
		**
		** \return The height of the tree
		*/
		SizeType treeHeight();
		//@}


		//! \name Comparisons
		//@{
		/*!
		** \brief Test if the current node is equals to another one
		** \return True if the two nodes are equal, false otherwise
		*/
		bool equals(const Ptr& node) const;
		//@}


		//! \name Z-Order
		//@{
		/*!
		** \brief Move the node to the end
		**
		** This method is especially useful when manipulating items on a layer.
		** When iterating over all children, the last one can be considered
		** as the last drawn thus the first visible item for the user.
		*/
		void bringToFront();

		/*!
		** \brief Move the node to the begining
		**
		** This method is especially useful when manipulating items on a layer
		** When iterating over all children, the first one can be considered
		** as the first drawn thus the last visible item for the user.
		*/
		void sendToBack();
		//@}


		//! \name
		//@{
		/*!
		** \brief Schedule an asynchronous update of the item (depending upon the implementation)
		**
		** \internal The method invalidateWL() should be overloaded
		*/
		void invalidate();

		/*!
		** \brief Get if the item is invalidated (depending upon the implementation)
		**
		** \internal The method isInvalidatedWL() should be overloaded
		*/
		bool isInvalidated();
		//@}



		//! \name Operator =
		//@{
		//Node& operator = (Ptr& rhs);
		//@}


		//! \name Operator +=
		//@{
		//! Append a child at the end
		Node& operator += (Ptr& node) {push_back(node);return *this;}
		//! Append a child at the end
		Node& operator += (T* node) {push_back(node);return *this;}
		//@}

		//! \name Operator -=
		//@{
		//! Remove a child node
		Node& operator -= (Ptr& node) {remove(node);return *this;}
		//@}

		//! \name Operator <<
		//@{
		//! Append a child at the end
		Node& operator << (Ptr& node) {push_back(node);return *this;}
		//! Append a child at the end
		Node& operator << (T* node) {push_back(node);return *this;}
		//@}

		//! \name Operator ==
		//@{
		//! Comparison with another node
		Node& operator == (const Ptr& node) const {return equals(node);}
		//@}

		//! \name Operator []
		//@{
		/*!
		** \brief Get the n-th child of the node
		** \see find()
		*/
		Ptr operator [] (const SizeType index) {return find(index);}
		/*!
		** \brief Get the n-th child of the node
		** \see find()
		*/
		Ptr operator [] (const SignedSizeType index) {return find(index);}
		//@}


		/*!
		** \brief Print the entire tree to the output stream
		**
		** Should only be used for debugging purposes only
		*/
		std::ostream& print(std::ostream& out, const bool recursive = true, const unsigned int level = 0);


		//! \name Pointer management
		//@{
		void addRef();
		void release();
		//@}


	protected:
		//! Invalidate the item
		virtual void invalidateWL() {}
		//! Get if the item is invalidated
		virtual bool isInvalidatedWL() {return true;}

		//! (only used for debugging)
		virtual void printBeginWL(std::ostream& out, const unsigned int level) const;
		//! (only used for debugging)
		virtual void printEndWL(std::ostream& out, const unsigned int level) const;

		//! Remove all children
		void clearWL();

		//! Append a child to the end of the list
		void pushBackWL(Ptr& node);
		//! Append a child to the end of the list
		void pushFrontWL(Ptr& node);

		/*!
		** \brief Detach from the parent
		** \note This method assumes that we have a parent
		*/
		void detachFromParentWL();

		//! Find a child node from its index (slow)
		Ptr findFromIndexWL(const SizeType index);


	protected:
		//! Parent
		Ptr pParent;
		/*!
		** \brief Get if this node has a parent
		** \internal Due to the threading policy, this node may require to be
		** thread-safe, the same goes for the smart pointer. Using this variable
		** should avoid unnecessary locks.
		*/
		bool pHaveParent;

		//! How many children do we have ?
		SizeType pChildrenCount;
		//! The previous sibling
		Ptr pPreviousSibling;
		//! The next sibling
		Ptr pNextSibling;
		//! The first child
		Ptr pFirstChild;
		//! The last child
		Ptr pLastChild;

	private:
		/*!
		** \brief Remove a child without any real checks
		**
		** \internal We assume at this stade that the given node is really a child
		** of the current one. We assume in the same way that the given node is
		** already locked.
		**
		** \return True if the node has been removed, False otherwise
		*/
		bool internalRemoveChild(Node& node);
		/*!
		** \brief Remove a child without any real checks (without locks)
		** \return True if the node has been removed, False otherwise
		** \see internalRemoveChild()
		*/
		bool internalRemoveChildWL(Node& node);

		//! Detach from the parent without notifying it
		void internalDetachFromParentWithoutNotify();

	private:
		typename ThreadingPolicy::template Volatile<int>::Type pRefCount;

	}; // class TreeN






} // namespace Core
} // namespace Yuni


# include "treeN.hxx"

#endif // __YUNI_CORE_TREE_N_H__
