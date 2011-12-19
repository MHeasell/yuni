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
			pOut << "#include <typeinfo>" << std::endl;
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
			pOut << pIndent;
			if (node->returnType() && node->returnType()->type())
				writeType(node->returnType()->type());
			else if (node->type())
				writeType(node->type());
			else // Default to void
				pOut << "void";
			pOut << " " << node->name() << '(';
			if (node->params())
				node->params()->accept(this);
			pOut << ')' << std::endl;

			pFunctionScope = true;
			if (node->body())
				node->body()->accept(this);
			else
				pOut << "{}" << std::endl;
			pOut << std::endl;
			pFunctionScope = false;
		}


		virtual void visit(ClassDeclarationNode* node)
		{
			pOut << "class " << node->name() << std::endl;
			pOut << '{' << std::endl;
			indent();
			if (node->declarations())
				node->declarations()->accept(this);
			unindent();
			pOut << "};" << std::endl;
			pOut << std::endl;
		}


		virtual void visit(MethodDeclarationNode* node)
		{
			pOut << pIndent;
			if (node->returnType() && node->returnType()->type())
				writeType(node->returnType()->type());
			else if (node->type())
				writeType(node->type());
			else // Default to void
				pOut << "void";
			pOut << " " << node->name() << '(';
			if (node->params())
				node->params()->accept(this);
			pOut << ')' << std::endl << pIndent;

			pFunctionScope = true;
			if (node->body())
				node->body()->accept(this);
			else
				pOut << "{}" << std::endl;
			pOut << std::endl;
			pFunctionScope = false;
		}


		virtual void visit(AttributeDeclarationNode* node)
		{
			pOut << pIndent;
			if (node->typeDecl() && node->typeDecl()->type())
				writeType(node->typeDecl()->type());
			else if (node->type())
				writeType(node->type());
			else // Default to int...
				pOut << "int";
			pOut << " " << node->name();
			if (node->value())
			{
				pOut << " = ";
				node->value()->accept(this);
			}
			pOut << ';' << std::endl;
		}


		virtual void visit(ScopeNode* node)
		{
			pOut << '{' << std::endl;
			indent();
			if (node->expression())
			{
				bool isList = (dynamic_cast<ExpressionListNode*>(node->expression()));
				// On single expressions, write the indent
				// On expression lists, leave this work to the visit(expressionlistnode)
				if (!isList)
				{
					pOut << pIndent;
					// On one-liners, add `return` when necessary
					if (pFunctionScope && node->expression()->type() &&
						node->expression()->type() != Typing::Type::Get("void") &&
						!dynamic_cast<ReturnExpressionNode*>(node->expression()))
						pOut << "return ";
				}
				node->expression()->accept(this);
				if (!isList)
					pOut << ';' << std::endl;
			}
			unindent();
			pOut << pIndent << '}' << std::endl;
		}


		virtual void visit(VisibilityQualifierNode* node)
		{
			// Visibility qualifiers are displayed at the same indent level as
			// the underlying class, so one level under the rest of the declarations
			unindent();
			pOut << pIndent;
			switch (node->value())
			{
				case 0:
					pOut << "private:" << std::endl;
					break;
				case 1:
					pOut << "protected:" << std::endl;
					break;
				default: // public + published
					pOut << "public:" << std::endl;
					break;
			}
			indent();
		}


		virtual void visit(ExpressionListNode* node)
		{
			ExpressionListNode::List& exprList = node->expressions();
			ExpressionListNode::List::iterator end = exprList.end();
			unsigned int size = exprList.size();
			for (ExpressionListNode::List::iterator it = exprList.begin(); it != end; ++it)
			{
				pOut << pIndent;

				// If on last expression, check if we may add `return`
				if (!--size && pFunctionScope && !dynamic_cast<ReturnExpressionNode*>(*it))
				{
					// If the type is null, we might as well treat is as `void`
					if ((*it)->type() && (*it)->type() != Typing::Type::Get("void"))
						pOut << "return ";
				}
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
				isScope = (dynamic_cast<ScopeNode*>(node->thenExpr()));
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
				isScope = (dynamic_cast<ScopeNode*>(node->elseExpr()));
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


		virtual void visit(WhileExpressionNode* node)
		{
			pOut << "while (";
			node->condition()->accept(this);
			pOut << ')' << std::endl;
			if (node->expression())
			{
				bool isScope =
					(dynamic_cast<ScopeNode*>(node->expression())) ||
					(dynamic_cast<ExpressionListNode*>(node->expression()));
				if (!isScope)
					indent();
				pOut << pIndent;
				node->expression()->accept(this);
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
			if (!node->type() || node->type()->isValue())
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


		virtual void visit(FunctionCallNode* node)
		{
			pOut << node->name() << '(';
			node->params()->accept(this);
			pOut << ')';
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
			writeType(node->data);
		}


	private:
		void writeType(Typing::Type* type)
		{
			if (!type)
				return;
			if (type->isConst())
				pOut << "const ";
			pOut << type->name();
		}

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

		/*!
		** \brief Is this expression the last one in a list, or a single one ?
		**
		** This is useful to know when we might need to add a return keyword.
		*/
		bool pLastExpression;

		//! Current indent
		Yuni::String pIndent;
	};



} // namespace Ast
} // namespace Nany

#endif // __NANY_AST_CPPWRITERVISITOR_H__
