#ifndef __NANY_AST_CPPWRITERVISITOR_H__
# define __NANY_AST_CPPWRITERVISITOR_H__

# include <fstream>
# include "all.h"
# include "visitor.h"

namespace Nany
{
namespace Ast
{


	/*!
	** \brief Visitor that writes an equivalent C++ code
	*/
	class CppWriterVisitor: public Visitor
	{
	public:
		CppWriterVisitor(std::ofstream& stream):
			pOut(stream),
			pFunctionScope(false)
		{}


		virtual void visit(ProgramNode* node)
		{
			node->unitDeclaration()->accept(this);
			node->declarations()->accept(this);
		}

		virtual void visit(DeclarationListNode* node)
		{
			DeclarationListNode::List& declList = node->declarations();
			DeclarationListNode::List::iterator end = declList.end();
			for (DeclarationListNode::List::iterator it = declList.begin(); it != end; ++it)
				(*it)->accept(this);
		}

		virtual void visit(FunctionDeclarationNode* node)
		{
			if (node->returnType())
			{
				node->returnType()->accept(this);
				pOut << " ";
			}
			else
				pOut << "void ";
			// TODO : handle parameter list
			pOut << node->name() << '(' << ')' << std::endl
				 << '{' << std::endl;
			pFunctionScope = true;
			if (node->body())
				node->body()->accept(this);
			pFunctionScope = false;
			pOut << '}' << std::endl;
		}

		virtual void visit(ExpressionListNode* node)
		{
			ExpressionListNode::List& exprList = node->expressions();
			ExpressionListNode::List::iterator end = exprList.end();
			for (ExpressionListNode::List::iterator it = exprList.begin(); it != end; ++it)
			{
				(*it)->accept(this);
				pOut << ';' << std::endl;
			}
		}

		virtual void visit(ParallelExpressionNode* node)
		{
			// TODO : parallelize the expression
			node->expression()->accept(this);
		}

		virtual void visit(TypeExpressionNode* node)
		{
			node->expression()->accept(this);
		}

		virtual void visit(IdentifierNode* node)
		{
			pOut << node->data;
		}

		virtual void visit(LiteralNode<bool>* node)
		{
			pOut << node->data;
		}

		virtual void visit(LiteralNode<int>* node)
		{
			pOut << node->data;
		}

		virtual void visit(LiteralNode<unsigned int>* node)
		{
			pOut << node->data << 'u';
		}

		virtual void visit(LiteralNode<float>* node)
		{
			pOut << node->data << 'f';
		}

		virtual void visit(LiteralNode<char>* node)
		{
			pOut << '\'' << node->data << '\'';
		}

		virtual void visit(LiteralNode<const char*>* node)
		{
			pOut << '\"' << node->data << '\"';
		}

		virtual void visit(LiteralNode<void*>* node)
		{
			pOut << "(void*)" << node->data;
		}

		virtual void visit(LiteralNode<Type*>* node)
		{
			pOut << node->data->name();
		}


	private:
		//! Stream to the destination C++ file
		std::ofstream& pOut;

		/*!
		** \brief Are we at the lowest scope inside a function ?
		**
		** This is useful to know when we might need to add a return keyword.
		*/
		bool pFunctionScope;
	};



} // namespace Ast
} // namespace Nany

#endif // __NANY_AST_CPPWRITERVISITOR_H__
