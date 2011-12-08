#ifndef __NANY_AST_CPPWRITERVISITOR_H__
# define __NANY_AST_CPPWRITERVISITOR_H__

# include <fstream>
# include "yuni/yuni.h"
# include "simplevisitor.h"

namespace Nany
{
namespace Ast
{


	/*!
	** \brief Visitor that writes an equivalent C++ code
	*/
	class CppWriterVisitor: public SimpleVisitor
	{
	public:
		CppWriterVisitor(std::ofstream& stream):
			pOut(stream),
			pFunctionScope(false),
			pIndent()
		{}


		virtual void visit(ProgramNode* node)
		{
			pOut << "#include <yuni/yuni.h>" << std::endl;
			pOut << "#include <yuni/core/string.h>" << std::endl;
			pOut << "#include <yuni/io/file.h>" << std::endl;
			pOut << "#include <yuni/io/io.h>" << std::endl;
			pOut << "#include <iostream>" << std::endl;
			pOut << "#include <set>" << std::endl;
			pOut << "#include <list>" << std::endl;
			pOut << "#include <vector>" << std::endl;
			pOut << "#include <map>" << std::endl;
			pOut << "#include <cassert>" << std::endl;
			pOut << std::endl;
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
			pOut << node->name() << '(';
			if (node->params())
				node->params()->accept(this);
			pOut << ')' << std::endl;

			pFunctionScope = true;
			node->body()->accept(this);
			pFunctionScope = false;
		}


		virtual void visit(ScopeNode* node)
		{
			pOut << '{' << std::endl;
			indent();
			if (node->expression())
			{
				bool isList = nullptr != dynamic_cast<ExpressionListNode*>(node->expression());
				// On single expressions, write the indent
				// On expression lists, leave this work to the visit(expressionlistnode)
				if (!isList)
					pOut << pIndent;
				node->expression()->accept(this);
				if (!isList)
					pOut << ';' << std::endl;
			}
			unindent();
			pOut << pIndent << '}' << std::endl;
		}


		virtual void visit(ExpressionListNode* node)
		{
			ExpressionListNode::List& exprList = node->expressions();
			ExpressionListNode::List::iterator end = exprList.end();
			for (ExpressionListNode::List::iterator it = exprList.begin(); it != end; ++it)
			{
				pOut << pIndent;
				(*it)->accept(this);
				pOut << ';' << std::endl;
			}
		}


		virtual void visit(ParameterListNode* node)
		{
			ParameterListNode::List& paramList = node->parameters();
			ParameterListNode::List::iterator end = paramList.end();
			unsigned int size = paramList.size();
			for (ParameterListNode::List::iterator it = paramList.begin(); it != end; ++it)
			{
				(*it)->accept(this);
				if (--size)
					pOut << ", ";
			}
		}


		virtual void visit(ArgumentListNode* node)
		{
			ArgumentListNode::List& argList = node->arguments();
			ArgumentListNode::List::iterator end = argList.end();
			unsigned int size = argList.size();
			for (ArgumentListNode::List::iterator it = argList.begin(); it != end; ++it)
			{
				(*it)->accept(this);
				if (--size)
					pOut << ", ";
			}
		}


		virtual void visit(IfExpressionNode* node)
		{
			pOut << "if (";
			node->condition()->accept(this);
			pOut << ')' << std::endl;
			bool isScope;
			if (node->thenExpr())
			{
				isScope = nullptr != dynamic_cast<ScopeNode*>(node->thenExpr());
				if (!isScope)
					indent();
				pOut << pIndent;
				node->thenExpr()->accept(this);
				if (!isScope)
				{
				 	pOut << ';' << std::endl;
					unindent();
				}
			}
			if (node->elseExpr())
			{
				pOut << pIndent << "else" << std::endl;
				isScope = nullptr != dynamic_cast<ScopeNode*>(node->elseExpr());
				if (!isScope)
					indent();
				pOut << pIndent;
				node->elseExpr()->accept(this);
				if (!isScope)
				{
				 	pOut << ';' << std::endl;
					unindent();
				}
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


		virtual void visit(VarDeclarationNode* node)
		{
			node->typeDecl()->accept(this);
			pOut << " ";
			node->left()->accept(this);
		}


		virtual void visit(AssignmentExpressionNode* node)
		{
			node->left()->accept(this);
			pOut << " = ";
			node->right()->accept(this);
		}


		virtual void visit(EqualExpressionNode* node)
		{
			node->left()->accept(this);
			pOut << " == ";
			node->right()->accept(this);
		}


		virtual void visit(NotEqualExpressionNode* node)
		{
			node->left()->accept(this);
			pOut << " != ";
			node->right()->accept(this);
		}


		virtual void visit(InferiorExpressionNode* node)
		{
			node->left()->accept(this);
			pOut << " < ";
			node->right()->accept(this);
		}


		virtual void visit(InferiorEqualExpressionNode* node)
		{
			node->left()->accept(this);
			pOut << " <= ";
			node->right()->accept(this);
		}


		virtual void visit(SuperiorExpressionNode* node)
		{
			node->left()->accept(this);
			pOut << " > ";
			node->right()->accept(this);
		}


		virtual void visit(SuperiorEqualExpressionNode* node)
		{
			node->left()->accept(this);
			pOut << " >= ";
			node->right()->accept(this);
		}


		virtual void visit(PlusExpressionNode* node)
		{
			node->left()->accept(this);
			pOut << " + ";
			node->right()->accept(this);
		}


		virtual void visit(MinusExpressionNode* node)
		{
			node->left()->accept(this);
			pOut << " - ";
			node->right()->accept(this);
		}


		virtual void visit(MultiplyExpressionNode* node)
		{
			node->left()->accept(this);
			pOut << " * ";
			node->right()->accept(this);
		}


		virtual void visit(DivideExpressionNode* node)
		{
			node->left()->accept(this);
			pOut << " / ";
			node->right()->accept(this);
		}


		virtual void visit(ModulusExpressionNode* node)
		{
			node->left()->accept(this);
			pOut << " % ";
			node->right()->accept(this);
		}


		virtual void visit(AsExpressionNode* node)
		{
			pOut << "((";
			node->right()->accept(this);
			pOut << ")";
			node->left()->accept(this);
			pOut << ")";
		}


		virtual void visit(IsExpressionNode* node)
		{
			if (node->type()->isValue())
			{
				pOut << "(typeid(";
				node->left()->accept(this);
				pOut << ") == typeid(";
				node->right()->accept(this);
				pOut << "))";
			}
			else
			{
				pOut << "(0 != dynamic_cast<";
				node->right()->accept(this);
				pOut << ">(";
				node->left()->accept(this);
				pOut << "))";
			}
		}


		virtual void visit(TypeofExpressionNode* node)
		{
			pOut << "typeof (";
			node->expression()->accept(this);
			pOut << ")";
		}


		virtual void visit(NewExpressionNode* node)
		{
			pOut << "new ";
			node->expression()->accept(this);
		}


		virtual void visit(ReturnExpressionNode* node)
		{
			pOut << "return ";
			node->expression()->accept(this);
		}


		virtual void visit(IdentifierNode* node)
		{
			pOut << node->data;
		}


		virtual void visit(LiteralNode<bool>* node)
		{
			pOut << (node->data ? "true" : "false");
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


		virtual void visit(LiteralNode<double>* node)
		{
			pOut << node->data << 'f';
		}


		virtual void visit(LiteralNode<char>* node)
		{
			pOut << '\'' << node->data << '\'';
		}


		virtual void visit(LiteralNode<wchar_t>* node)
		{
			size_t len = wcslen(&node->data);
			char* buffer = new char[len];
			wctomb(buffer, node->data);
			buffer[len] = '\0';

			pOut << '\'' << buffer << '\'';
		}


		virtual void visit(LiteralNode<char*>* node)
		{
			pOut << '\"' << node->data << '\"';
		}


		virtual void visit(LiteralNode<const char*>* node)
		{
			pOut << '\"' << node->data << '\"';
		}


		virtual void visit(LiteralNode<void*>* node)
		{
			pOut << "(void*)" << node->data;
		}


		virtual void visit(LiteralNode<Typing::Type*>* node)
		{
			if (node->data->isConst())
				pOut << "const ";
			pOut << node->data->name();
		}


	private:
		void indent()
		{
			pIndent << '\t';
		}

		void unindent()
		{
			pIndent.removeLast();
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

		//! Current indent
		Yuni::String pIndent;
	};



} // namespace Ast
} // namespace Nany

#endif // __NANY_AST_CPPWRITERVISITOR_H__
