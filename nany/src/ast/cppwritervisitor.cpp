
#include "cppwritervisitor.h"


namespace Nany
{
namespace Ast
{
	
	CppWriterVisitor::CppWriterVisitor(std::ofstream& stream):
		pOut(stream),
		pFunctionScope(false),
		pSkipCOW(0u),
		pIndent()
	{}


	void CppWriterVisitor::visit(ProgramNode* node)
	{
		pOut << "#include <yuni/yuni.h>" << std::endl;
		pOut << "#include <yuni/core/cow.h>" << std::endl;
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
		pOut << "using namespace ::Yuni;" << std::endl;
		pOut << std::endl;
		pOut << std::endl;
		if (node->unitDeclaration())
			node->unitDeclaration()->accept(this);
		node->declarations()->accept(this);
	}

	void CppWriterVisitor::visit(DeclarationListNode* node)
	{
		DeclarationListNode::List& declList = node->declarations();
		DeclarationListNode::List::iterator end = declList.end();
		for (DeclarationListNode::List::iterator it = declList.begin(); it != end; ++it)
			(*it)->accept(this);
	}


	void CppWriterVisitor::visit(FunctionDeclarationNode* node)
	{
		pOut << pIndent;

		// Generate a template parameter for untyped function parameters
		if (node->params())
		{
			ParameterListNode::List& paramList = node->params()->parameters();
			ParameterListNode::List::iterator end = paramList.end();
			unsigned int count = 0;
			for (ParameterListNode::List::iterator it = paramList.begin(); it != end; ++it)
			{
				if (!(*it)->type())
					++count;
			}
			if (count > 0)
			{
				pOut << "template<";
				for (unsigned int increment = 1; increment <= count; ++increment)
				{
					pOut << "class MT" << increment;
					if (increment < count)
						pOut << ", ";
				}
				pOut << '>' << std::endl << pIndent;
			}
		}

		// Return type
		if (node->returnType() && node->returnType()->type())
			writeType(node->returnType()->type());
		else if (node->type())
			writeType(node->type());
		else // Default to void
			pOut << "void";
		// Function name
		pOut << ' ' << node->name() << '(';
		// Function parameters
		if (node->params())
		{
			ParameterListNode::List& paramList = node->params()->parameters();
			unsigned int size = (unsigned int) paramList.size();
			unsigned int count = 1;

			ParameterListNode::List::iterator end = paramList.end();
			for (ParameterListNode::List::iterator it = paramList.begin(); it != end; ++it)
			{
				// If there is no type, we have declared a template parameter for it
				if (!(*it)->type())
					pOut << "COW<MT" << count++ << "> ";
				(*it)->accept(this);
				if (--size)
					pOut << ", ";
			}
		}
		pOut << ')' << std::endl << pIndent;

		// Body
		pFunctionScope = true;
		if (node->body())
			node->body()->accept(this);
		else
			pOut << "{}" << std::endl;
		pOut << std::endl;
		pFunctionScope = false;
	}


	void CppWriterVisitor::visit(ClassDeclarationNode* node)
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


	void CppWriterVisitor::visit(MethodDeclarationNode* node)
	{
		pOut << pIndent;

		// Generate a template parameter for untyped method parameters
		if (node->params())
		{
			ParameterListNode::List& paramList = node->params()->parameters();
			ParameterListNode::List::iterator end = paramList.end();
			unsigned int count = 0;
			for (ParameterListNode::List::iterator it = paramList.begin(); it != end; ++it)
			{
				if (!(*it)->type())
					++count;
			}
			if (count > 0)
			{
				pOut << "template<";
				for (unsigned int increment = 1; increment <= count; ++increment)
				{
					pOut << "class MT" << increment;
					if (increment < count)
						pOut << ", ";
				}
				pOut << '>' << std::endl << pIndent;
			}
		}

		// Return type
		if (node->returnType() && node->returnType()->type())
			writeType(node->returnType()->type());
		else if (node->type())
			writeType(node->type());
		else // Default to void
			pOut << "void";
		// Method name
		pOut << ' ' << node->name() << '(';
		// Method parameters
		if (node->params())
		{
			ParameterListNode::List& paramList = node->params()->parameters();
			unsigned int size = (unsigned int) paramList.size();
			unsigned int count = 1;

			ParameterListNode::List::iterator end = paramList.end();
			for (ParameterListNode::List::iterator it = paramList.begin(); it != end; ++it)
			{
				// If there is no type, we have declared a template parameter for it
				if (!(*it)->type())
					pOut << "COW<MT" << count++ << "> ";
				(*it)->accept(this);
				if (--size)
					pOut << ", ";
			}
		}
		pOut << ')' << std::endl << pIndent;

		// Body
		pFunctionScope = true;
		if (node->body())
			node->body()->accept(this);
		else
			pOut << "{}" << std::endl;
		pOut << std::endl;
		pFunctionScope = false;
	}


	void CppWriterVisitor::visit(AttributeDeclarationNode* node)
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


	void CppWriterVisitor::visit(TypeAliasNode* node)
	{
		pOut << pIndent;
		std::cout << pIndent << "typedef ";
		node->expression()->accept(this);
		pOut << "  " << node->name() << std::endl;
	}


	void CppWriterVisitor::visit(ScopeNode* node)
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


	void CppWriterVisitor::visit(VisibilityQualifierNode* node)
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


	void CppWriterVisitor::visit(ExpressionListNode* node)
	{
		ExpressionListNode::List& exprList = node->expressions();
		unsigned int size = (unsigned int) exprList.size();

		ExpressionListNode::List::iterator end = exprList.end();
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


	void CppWriterVisitor::visit(ParameterListNode* node)
	{
		ParameterListNode::List& paramList = node->parameters();
		unsigned int size = (unsigned int) paramList.size();

		ParameterListNode::List::iterator end = paramList.end();
		for (ParameterListNode::List::iterator it = paramList.begin(); it != end; ++it)
		{
			(*it)->accept(this);
			if (--size)
				pOut << ", ";
		}
	}


	void CppWriterVisitor::visit(ArgumentListNode* node)
	{
		ArgumentListNode::List& argList = node->arguments();
		unsigned int size = (unsigned int) argList.size();

		ArgumentListNode::List::iterator end = argList.end();
		for (ArgumentListNode::List::iterator it = argList.begin(); it != end; ++it)
		{
			(*it)->accept(this);
			if (--size)
				pOut << ", ";
		}
	}


	void CppWriterVisitor::visit(IfExpressionNode* node)
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


	void CppWriterVisitor::visit(WhileExpressionNode* node)
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
				unindent();
			}
		}
		else
			pOut << "{}";
	}


	void CppWriterVisitor::visit(ForExpressionNode* node)
	{
		pOut << "for (auto " << node->identifier() << " = ";
		node->set()->accept(this);
		pOut << "->begin(); " << node->identifier() << " != ";
		node->set()->accept(this);
		pOut << "->end(); ++" << node->identifier() << ')' << std::endl;
		if (node->body())
		{
			bool isScope = dynamic_cast<ScopeNode*>(node->body());
			if (!isScope)
				indent();
			pOut << pIndent;
			node->body()->accept(this);
			if (!isScope)
			{
				unindent();
			}
		}
		else
			pOut << "{}";
	}


	void CppWriterVisitor::visit(ParallelExpressionNode* node)
	{
		// TODO : parallelize the expression
		node->expression()->accept(this);
	}


	void CppWriterVisitor::visit(TypeExpressionNode* node)
	{
		if (!pSkipCOW)
		{
			if (node->isArray())
			{
				pOut << "COW<std::vector<";
				node->expression()->accept(this);
				pOut << " > >";
			}
			else if (!node->type()->isValue())
			{
				pOut << "COW<";
				node->expression()->accept(this);
				pOut << " >";
			}
			else
				node->expression()->accept(this);
		}
		else
		{
			if (node->isArray())
			{
				pOut << "std::vector<";
				node->expression()->accept(this);
				pOut << " >";
			}
			else
				node->expression()->accept(this);
		}
	}


	void CppWriterVisitor::visit(VarDeclarationNode* node)
	{
		node->typeDecl()->accept(this);
		pOut << ' ';

		node->left()->accept(this);
		if (node->typeDecl()->isArray() && node->typeDecl()->arrayCardinality() > 0)
		{
			++pSkipCOW;
			pOut << " = COW<";
			node->typeDecl()->accept(this);
			pOut << " >(new ";
			node->typeDecl()->accept(this);
			pOut << '(' << node->typeDecl()->arrayCardinality() << "))";
			--pSkipCOW;
		}
	}


	void CppWriterVisitor::visit(AssignmentExpressionNode* node)
	{
		node->left()->accept(this);
		pOut << " = ";
		node->right()->accept(this);
	}


	void CppWriterVisitor::visit(DotExpressionNode* node)
	{
		node->left()->accept(this);
		pOut << '.' << node->field();
	}


	void CppWriterVisitor::visit(EqualExpressionNode* node)
	{
		if (node->left()->type() && node->left()->type()->isValue())
			node->left()->accept(this);
		else
		{
			pOut << "(*";
			node->left()->accept(this);
			pOut << ")";
		}

		pOut << " == ";

		if (node->right()->type() && node->right()->type()->isValue())
			node->right()->accept(this);
		else
		{
			pOut << "(*";
			node->right()->accept(this);
			pOut << ")";
		}
	}


	void CppWriterVisitor::visit(NotEqualExpressionNode* node)
	{
		node->left()->accept(this);
		pOut << " != ";
		node->right()->accept(this);
	}


	void CppWriterVisitor::visit(InferiorExpressionNode* node)
	{
		node->left()->accept(this);
		pOut << " < ";
		node->right()->accept(this);
	}


	void CppWriterVisitor::visit(InferiorEqualExpressionNode* node)
	{
		node->left()->accept(this);
		pOut << " <= ";
		node->right()->accept(this);
	}


	void CppWriterVisitor::visit(SuperiorExpressionNode* node)
	{
		node->left()->accept(this);
		pOut << " > ";
		node->right()->accept(this);
	}


	void CppWriterVisitor::visit(SuperiorEqualExpressionNode* node)
	{
		node->left()->accept(this);
		pOut << " >= ";
		node->right()->accept(this);
	}


	void CppWriterVisitor::visit(ShiftLeftExpressionNode* node)
	{
		node->left()->accept(this);
		pOut << " << ";
		node->right()->accept(this);
	}


	void CppWriterVisitor::visit(ShiftRightExpressionNode* node)
	{
		node->left()->accept(this);
		pOut << " >> ";
		node->right()->accept(this);
	}


	void CppWriterVisitor::visit(PlusExpressionNode* node)
	{
		node->left()->accept(this);
		pOut << " + ";
		node->right()->accept(this);
	}


	void CppWriterVisitor::visit(MinusExpressionNode* node)
	{
		node->left()->accept(this);
		pOut << " - ";
		node->right()->accept(this);
	}


	void CppWriterVisitor::visit(MultiplyExpressionNode* node)
	{
		node->left()->accept(this);
		pOut << " * ";
		node->right()->accept(this);
	}


	void CppWriterVisitor::visit(DivideExpressionNode* node)
	{
		node->left()->accept(this);
		pOut << " / ";
		node->right()->accept(this);
	}


	void CppWriterVisitor::visit(ModulusExpressionNode* node)
	{
		node->left()->accept(this);
		pOut << " % ";
		node->right()->accept(this);
	}


	void CppWriterVisitor::visit(AsExpressionNode* node)
	{
		pOut << "((";
		node->right()->accept(this);
		pOut << ")";
		node->left()->accept(this);
		pOut << ")";
	}


	void CppWriterVisitor::visit(IsExpressionNode* node)
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


	void CppWriterVisitor::visit(TypeofExpressionNode* node)
	{
		pOut << "typeof (";
		node->expression()->accept(this);
		pOut << ")";
	}


	void CppWriterVisitor::visit(NewExpressionNode* node)
	{
		pOut << "new ";
		pSkipCOW++;
		node->expression()->accept(this);
		pSkipCOW--;
	}


	void CppWriterVisitor::visit(ReturnExpressionNode* node)
	{
		pOut << "return ";
		node->expression()->accept(this);
	}


	void CppWriterVisitor::visit(FunctionCallNode* node)
	{
		node->function()->accept(this);
		pOut << '(';
		if (node->params())
			node->params()->accept(this);
		pOut << ')';
	}


	void CppWriterVisitor::visit(IdentifierNode* node)
	{
		pOut << node->data;
	}


	void CppWriterVisitor::visit(LiteralNode<bool>* node)
	{
		pOut << (node->data ? "true" : "false");
	}


	void CppWriterVisitor::visit(LiteralNode<int>* node)
	{
		pOut << node->data;
	}


	void CppWriterVisitor::visit(LiteralNode<unsigned int>* node)
	{
		pOut << node->data << 'u';
	}


	void CppWriterVisitor::visit(LiteralNode<float>* node)
	{
		pOut << node->data << 'f';
	}


	void CppWriterVisitor::visit(LiteralNode<double>* node)
	{
		pOut << node->data;
	}


	void CppWriterVisitor::visit(LiteralNode<char>* node)
	{
		pOut << '\'' << node->data << '\'';
	}


	void CppWriterVisitor::visit(LiteralNode<wchar_t>* node)
	{
		size_t len = wcslen(&node->data);
		char* buffer = new char[len];
		wctomb(buffer, node->data);
		buffer[len] = '\0';

		pOut << '\'' << buffer << '\'';
	}


	void CppWriterVisitor::visit(LiteralNode<char*>* node)
	{
		pOut << "COW<String>(new String(\"" << node->data << "\"))";
	}


	void CppWriterVisitor::visit(LiteralNode<const char*>* node)
	{
		pOut << "COW<String>(new String(\"" << node->data << "\"))";
	}


	void CppWriterVisitor::visit(LiteralNode<void*>* node)
	{
		pOut << "(void*)" << node->data;
	}


	void CppWriterVisitor::visit(LiteralNode<Typing::Type*>* node)
	{
		writeType(node->data);
	}


	void CppWriterVisitor::writeType(Typing::Type* type)
	{
		if (!type)
			return;
		if (type->isValue())
		{
			pOut << type->name();
			return;
		}
		if (type->isConst())
			pOut << "const ";
		pOut << "COW<" << type->name()<< " >";
	}





} // namespace Ast
} // namespace Nany
