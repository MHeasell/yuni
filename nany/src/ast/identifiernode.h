#ifndef __NANY_AST_IDENTIFIERNODE_H__
# define __NANY_AST_IDENTIFIERNODE_H__

# include "yuni/core/string.h"
# include "node.h"

namespace Nany
{
namespace Ast
{


	/*!
	** \brief AST node for an identifier
	*/
	class IdentifierNode: public Node
	{
	public:
		IdentifierNode(const char* data): pData(data)
		{}

	public:
		const Yuni::String pData;
	};



} // namespace Ast
} // namespace Nany

#endif // __NANY_AST_IDENTIFIERNODE_H__
