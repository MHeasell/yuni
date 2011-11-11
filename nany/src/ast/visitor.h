#ifndef __NANY_AST_VISITOR_H__
# define __NANY_AST_VISITOR_H__

# include "fwd.h"

namespace Nany
{
namespace Ast
{


	/*!
	** \brief Base empty visitor. Visits the tree but does nothing.
	*/
	class Visitor
	{
	public:
		virtual void visit(IdentifierNode*)
		{}

		virtual void visit(LiteralNode<bool>*)
		{}

		virtual void visit(LiteralNode<int>*)
		{}

		virtual void visit(LiteralNode<unsigned int>*)
		{}
	};



} // namespace Ast
} // namespace Nany

#endif // __NANY_AST_VISITOR_H__
