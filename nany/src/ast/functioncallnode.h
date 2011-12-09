#ifndef __NANY_AST_FUNCTIONCALLNODE_H__
# define __NANY_AST_FUNCTIONCALLNODE_H__

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
	** \brief Function call
	**
	** \code
	** <Expr> ( <Args> )
	** \endcode
	*/
	class FunctionCallNode: public Node
	{
	public:
		template<class StringT>
		FunctionCallNode(const StringT& name, ArgumentListNode* params):
			pFunctionName(name),
			pParams(params)
		{}

		virtual void accept(Visitor* visitor)
		{
			visitor->visit(this);
		}

		const Yuni::String& name() const { return pFunctionName; }

		ArgumentListNode* params() const { return pParams; }

	private:
		//! Identifier representing the name of the function
		Yuni::String pFunctionName;

		//! Function parameters
		ArgumentListNode* pParams;
	};



} // namespace Ast
} // namespace Nany

#endif // __NANY_AST_FUNCTIONCALLNODE_H__
