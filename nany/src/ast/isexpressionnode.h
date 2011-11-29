#ifndef __NANY_AST_ISEXPRESSIONNODE_H__
# define __NANY_AST_ISEXPRESSIONNODE_H__

# include "node.h"

namespace Nany
{
namespace Ast
{


	/*!
	** \brief AST node for a type-testing binary operation
	**
	** \code
	** <expr> 'is' <expr>
	** \endcode
	*/
	class IsExpressionNode: public Node
	{
	public:
		IsExpressionNode(Node* left, Node* right):
			pLeft(left),
			pRight(right)
		{}

		virtual ~IsExpressionNode()
		{}

		virtual void accept(Visitor* visitor)
		{
			visitor->visit(this);
		}

		Node* left() const { return pLeft; }
		Node* right() const { return pRight; }

	public:
		Node* pLeft;
		Node* pRight;
	};



} // namespace Ast
} // namespace Nany

#endif // __NANY_AST_ISEXPRESSIONNODE_H__
