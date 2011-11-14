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

		virtual void visit(ProgramNode*)
		{}

		virtual void visit(UnitDeclarationNode*)
		{}

		virtual void visit(DeclarationListNode* node)
		{}

		virtual void visit(FunctionDeclarationNode*)
		{}

		virtual void visit(IdentifierNode*)
		{}

		virtual void visit(LiteralNode<bool>*)
		{}

		virtual void visit(LiteralNode<int>*)
		{}

		virtual void visit(LiteralNode<unsigned int>*)
		{}

		virtual void visit(LiteralNode<float>*)
		{}

		virtual void visit(LiteralNode<char>*)
		{}

		virtual void visit(LiteralNode<const char*>*)
		{}

	};



} // namespace Ast
} // namespace Nany

#endif // __NANY_AST_VISITOR_H__
