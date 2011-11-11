#ifndef __NANY_AST_NODE_H__
# define __NANY_AST_NODE_H__

# include "yuni/yuni.h"
# include "yuni/core/tree/treeN.h"
# include "visitor.h"

namespace Nany
{
namespace Ast
{

	// Forward declaration
	class Visitor;


	/*!
	** \brief Abstract syntax tree. Base class for all types of nodes.
	*/
	class Node: public Yuni::Core::TreeN<Node, Yuni::Policy::SingleThreaded>
	{
	public:
		virtual void accept(Visitor*) = 0;
	};



} // namespace Ast
} // namespace Nany

#endif // __NANY_AST_NODE_H__
