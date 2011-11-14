#ifndef __NANY_AST_FUNCTIONDECLARATIONNODE_H__
# define __NANY_AST_FUNCTIONDECLARATIONNODE_H__

# include "fwd.h"
# include "type.h"
# include "node.h"
# include "visitor.h"
# include "yuni/yuni.h"
# include "yuni/core/string.h"

namespace Nany
{
namespace Ast
{


	/*!
	** \brief Function declaration
	*/
	class FunctionDeclarationNode: public Node
	{
	public:
		template<class StringT>
		FunctionDeclarationNode(const StringT& name, Node* body):
			pFunctionName(name),
			pBody(body),
			pReturnType(nullptr)
		{}

		virtual void accept(Visitor* visitor)
		{
			visitor->visit(this);
		}

		const Yuni::String& name() const { return pFunctionName; }

		Nany::Ast::Node* body() const { return pBody; }

		const Type* returnType() const { return pReturnType; }

	private:
		//! Identifier representing the name of the unit or program
		Yuni::String pFunctionName;

		//! The body of the function is an expression
		Node* pBody;

		//! Return type of the function
		Type* pReturnType;
	};



} // namespace Ast
} // namespace Nany

#endif // __NANY_AST_FUNCTIONDECLARATIONNODE_H__
