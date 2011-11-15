#ifndef __NANY_AST_TYPEEXPRESSIONNODE_H__
# define __NANY_AST_TYPEEXPRESSIONNODE_H__

# include "fwd.h"
# include "type.h"
# include "node.h"
# include "visitor.h"
# include "yuni/yuni.h"
# include "yuni/core/string.h"

namespace Nany
{
namespace Ast
{


	/*!
	** \brief AST node for an expression representing a reference to a type
	*/
	class TypeExpressionNode: public Node
	{
	public:
		TypeExpressionNode(Node* expr):
			pExpression(expr)
		{}

		virtual ~TypeExpressionNode()
		{}

		virtual void accept(Visitor* visitor)
		{
			visitor->visit(this);
		}

		Node* expression() const { return pExpression; }

	private:
		//! Expression to evaluate to get the type
		Node* pExpression;
	};



} // namespace Ast
} // namespace Nany

#endif // __NANY_AST_TYPEEXPRESSIONNODE_H__
