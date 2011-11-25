#ifndef __NANY_AST_IFEXPRESSIONNODE_H__
# define __NANY_AST_IFEXPRESSIONNODE_H__

# include "node.h"

namespace Nany
{
namespace Ast
{


	/*!
	** \brief AST node for an if-then or if-then-else expression.
	*/
	class IfExpressionNode: public Node
	{
	public:
		IfExpressionNode(Node* condition, Node* thenExpr, Node* elseExpr):
			pCondition(condition),
			pThenExpr(thenExpr),
			pElseExpr(elseExpr)
		{}

		virtual ~IfExpressionNode()
		{}

		virtual void accept(Visitor* visitor)
		{
			visitor->visit(this);
		}

		Node* condition() const { return pCondition; }
		Node* thenExpr() const { return pThenExpr; }
		Node* elseExpr() const { return pElseExpr; }

	public:
		Node* pCondition;
		Node* pThenExpr;
		Node* pElseExpr;
	};



} // namespace Ast
} // namespace Nany

#endif // __NANY_AST_IFEXPRESSIONNODE_H__
