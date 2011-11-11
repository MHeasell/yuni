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
		CppWriterVisitor(std::ofstream& stream): pOut(stream)
		{}

		void visit(IdentifierNode* node)
		{
			pOut << node->data;
		}

		void visit(LiteralNode<bool>* node)
		{
			pOut << node->data;
		}

		void visit(LiteralNode<int>* node)
		{
			pOut << node->data;
		}

		void visit(LiteralNode<unsigned int>* node)
		{
			pOut << node->data;
		}


	private:
		//! Stream to the destination C++ file
		std::ofstream& pOut;
	};



} // namespace Ast
} // namespace Nany

#endif // __NANY_AST_CPPWRITERVISITOR_H__
