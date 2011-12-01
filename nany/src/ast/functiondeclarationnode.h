#ifndef __NANY_AST_FUNCTIONDECLARATIONNODE_H__
# define __NANY_AST_FUNCTIONDECLARATIONNODE_H__

# include "fwd.h"
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
		FunctionDeclarationNode(const StringT& name, ScopeNode* body):
			pFunctionName(name),
			pBody(body),
			pReturnType(nullptr)
		{}

		template<class StringT>
		FunctionDeclarationNode(const StringT& name, ScopeNode* body, TypeExpressionNode* returnType):
			pFunctionName(name),
			pBody(body),
			pReturnType(returnType)
		{}

		virtual void accept(Visitor* visitor)
		{
			visitor->visit(this);
		}

		const Yuni::String& name() const { return pFunctionName; }

		ScopeNode* body() const { return pBody; }

		TypeExpressionNode* returnType() const { return pReturnType; }

	private:
		//! Identifier representing the name of the unit or program
		Yuni::String pFunctionName;

		//! The body of the function is an expression
		ScopeNode* pBody;

		//! Return type of the function
		TypeExpressionNode* pReturnType;
	};



} // namespace Ast
} // namespace Nany

#endif // __NANY_AST_FUNCTIONDECLARATIONNODE_H__
