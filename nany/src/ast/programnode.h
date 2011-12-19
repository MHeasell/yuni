#ifndef __NANY_AST_PROGRAMNODE_H__
# define __NANY_AST_PROGRAMNODE_H__

# include "node.h"
# include "unitdeclarationnode.h"
# include "declarationlistnode.h"
# include "visitor.h"

namespace Nany
{
namespace Ast
{


	/*!
	** \brief Root node, the full file : either a program or a unit
	**
	** \code
	** 'program' Identifier ';'
	** \endcode
	*/
	class ProgramNode: public Node
	{
	public:
		ProgramNode(UnitDeclarationNode* unitDecl, DeclarationListNode* declarations):
			pUnitDeclaration(unitDecl),
			pDeclarations(declarations)
		{}

		virtual ~ProgramNode()
		{
			delete pUnitDeclaration;
			delete pDeclarations;
		}

		virtual void accept(Visitor* visitor)
		{
			visitor->visit(this);
		}

		UnitDeclarationNode* unitDeclaration() { return pUnitDeclaration; }

		DeclarationListNode* declarations() { return pDeclarations; }

	private:
		UnitDeclarationNode* pUnitDeclaration;

		DeclarationListNode* pDeclarations;

	}; // class ProgramNode



} // namespace Ast
} // namespace Nany

#endif // __NANY_AST_PROGRAMNODE_H__
