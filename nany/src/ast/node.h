#ifndef __NANY_AST_NODE_H__
# define __NANY_AST_NODE_H__

# include "type.h"
# include "visitor.h"

namespace Nany
{
namespace Ast
{


	/*!
	** \brief Abstract syntax tree. Base class for all types of node.
	*/
	class Node
	{
	public:
		Node(): pType(nullptr)
		{}

		virtual ~Node() {}

		//! All nodes must implement visitor acceptance
		virtual void accept(Visitor*) = 0;

		void type(Type* newType)
		{
			pType = newType;
		}

		Type* type() const
		{
			return pType;
		}

	protected:
		//! Types are flyweight patterns, stored as a static map in Nany::Ast::Type.
		Type* pType;
	};



} // namespace Ast
} // namespace Nany

#endif // __NANY_AST_NODE_H__
