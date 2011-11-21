#ifndef __NANY_AST_ASSIGNMENTEXPRESSIONNODE_H__
# define __NANY_AST_ASSIGNMENTEXPRESSIONNODE_H__

# include "yuni/core/string.h"
# include "node.h"
# include "typeexpressionnode.h"

namespace Nany
{
namespace Ast
{


	/*!
	** \brief AST node for an assignment expression
	**
	** \code
	** <expr> : <expr> := <expr>
	** <expr> : <expr>
	** <expr> := <expr>
	** \endcode
	*/
	class AssignmentExpressionNode: public Node
	{
	public:
		AssignmentExpressionNode(Node* left, TypeExpressionNode* type, Node* right):
			pLeft(left),
			pType(type),
			pRight(right)
		{}

		virtual ~AssignmentExpressionNode()
		{}

		virtual void accept(Visitor* visitor)
		{
			visitor->visit(this);
		}

		Node* left() const { return pLeft; }
		TypeExpressionNode* type() const { return pType; }
		Node* right() const { return pRight; }

	public:
		//! Left part of the assignment
		Node* pLeft;
		//! Type may be null if it was a simple assignment or if the type must be inferred
		TypeExpressionNode* pType;
		//! Right part of the assignment. May be null if it was a declaration with no assignment
		Node* pRight;
	};



} // namespace Ast
} // namespace Nany

#endif // __NANY_AST_ASSIGNMENTEXPRESSIONNODE_H__
