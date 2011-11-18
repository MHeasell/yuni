#ifndef __NANY_AST_FWD_H__
# define __NANY_AST_FWD_H__

namespace Nany
{
namespace Ast
{

	//! Abstract base node
	class Node;

	//! Root node, the full file : either a program or a unit
	class ProgramNode;

	//! Unit or program declaration
	class UnitDeclarationNode;

	//! List of declarations at program scope
	class DeclarationListNode;

	//! Function declaration
	class FunctionDeclarationNode;

	//! Scope
	class ScopeNode;

	//! List of expressions separated by semi-commas
	class ExpressionListNode;

	//! Expression that parallelizes the execution of a contained expression
	class ParallelExpressionNode;

	//! Expression representing a type
	class TypeExpressionNode;

	//! A type or variable identifier
	class IdentifierNode;

	//! Template for any kind of literal node
	template<class DataT>
	class LiteralNode;


} // namespace Ast
} // namespace Nany

#endif // __NANY_AST_FWD_H__
