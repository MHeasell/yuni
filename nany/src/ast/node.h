#ifndef __NANY_AST_NODE_H__
# define __NANY_AST_NODE_H__

# include "../typing/type.h"
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
		Node(): pType(nullptr), pIsConst(false)
		{}

		Node(bool isConst): pType(nullptr), pIsConst(isConst)
		{}

		virtual ~Node() {}

		//! All nodes must implement visitor acceptance
		virtual void accept(Visitor*) = 0;

		void type(Typing::Type* newType)
		{
			pType = newType;
		}

		Typing::Type* type() const
		{
			return pType;
		}

		bool isConst() const { return pIsConst; }

		void setConst() { pIsConst = true; }

	protected:
		//! Types are flyweight patterns, stored as a static map in Nany::Ast::Type.
		Typing::Type* pType;

		//! Has the node been identified as const ?
		bool pIsConst;
	};



} // namespace Ast
} // namespace Nany

#endif // __NANY_AST_NODE_H__
