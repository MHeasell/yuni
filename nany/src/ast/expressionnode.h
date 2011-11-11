#ifndef __NANY_AST_EXPRESSIONNODE_H__
# define __NANY_AST_EXPRESSIONNODE_H__

# include "node.h"

namespace Nany
{
namespace Ast
{


	/*!
	** \brief AST node for an expression
	*/
	template<class DataT>
	class ExpressionNode: public Node
	{
	public:
		typedef DataT DataType;

	public:
		ExpressionNode(DataT other): data(other)
		{}

	public:
		DataT data;
	};



} // namespace Ast
} // namespace Nany

#endif // __NANY_AST_EXPRESSIONNODE_H__
