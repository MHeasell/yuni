#ifndef __NANY_AST_DECLARATIONLISTNODE_H__
# define __NANY_AST_DECLARATIONLISTNODE_H__

# include <list>
# include "fwd.h"
# include "node.h"
# include "visitor.h"

namespace Nany
{
namespace Ast
{


	/*!
	** \brief A list of declarations at program scope: classes, functions, enums and workflows
	*/
	class DeclarationListNode: public Node
	{
	public:
		typedef std::list<Node*>  Vector;

	public:
		DeclarationListNode(): pDeclarations()
		{}

		virtual ~DeclarationListNode()
		{}

		virtual void accept(Visitor* visitor)
		{
			visitor->visit(this);
		}

		void prepend(Node* child)
		{
			pDeclarations.push_front(child);
		}

		const Vector& declarations() { return pDeclarations; }

	private:
		Vector pDeclarations;
	};



} // namespace Ast
} // namespace Nany

#endif // __NANY_AST_DECLARATIONLISTNODE_H__
