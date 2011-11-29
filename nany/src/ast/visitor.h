#ifndef __NANY_AST_VISITOR_H__
# define __NANY_AST_VISITOR_H__

# include "yuni/yuni.h"
# include "yuni/core/string.h"
# include "fwd.h"
# include "type.h"

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

		virtual void visit(DeclarationListNode*)
		{}

		virtual void visit(FunctionDeclarationNode*)
		{}

		virtual void visit(ScopeNode*)
		{}

		virtual void visit(IfExpressionNode*)
		{}

		virtual void visit(ExpressionListNode*)
		{}

		virtual void visit(ParallelExpressionNode*)
		{}

		virtual void visit(TypeExpressionNode*)
		{}

		virtual void visit(AssignmentExpressionNode*)
		{}

		virtual void visit(EqualExpressionNode*)
		{}

		virtual void visit(NotEqualExpressionNode*)
		{}

		virtual void visit(InferiorExpressionNode*)
		{}

		virtual void visit(InferiorEqualExpressionNode*)
		{}

		virtual void visit(SuperiorExpressionNode*)
		{}

		virtual void visit(SuperiorEqualExpressionNode*)
		{}

		virtual void visit(PlusExpressionNode*)
		{}

		virtual void visit(MinusExpressionNode*)
		{}

		virtual void visit(MultiplyExpressionNode*)
		{}

		virtual void visit(DivideExpressionNode*)
		{}

		virtual void visit(ModulusExpressionNode*)
		{}

		virtual void visit(ReturnExpressionNode*)
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

		virtual void visit(LiteralNode<wchar_t>*)
		{}

		virtual void visit(LiteralNode<char*>*)
		{}

		virtual void visit(LiteralNode<const char*>*)
		{}

		virtual void visit(LiteralNode<void*>*)
		{}

		virtual void visit(LiteralNode<Type*>*)
		{}


	protected:
		void indent()
		{
			pIndent << '\t';
		}

		void unindent()
		{
			pIndent.removeLast();
		}


	protected:
		//! Current indent, used by several inherited visitors
		Yuni::String pIndent;
	};



} // namespace Ast
} // namespace Nany

#endif // __NANY_AST_VISITOR_H__
