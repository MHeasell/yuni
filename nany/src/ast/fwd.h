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

	//! List of parameters in a function / method declaration
	class ParameterListNode;

	//! List of arguments in a function / method call
	class ArgumentListNode;

	//! Conditional expression
	class IfExpressionNode;

	//! Repetitive expression
	class WhileExpressionNode;

	//! Expression that parallelizes the execution of a contained expression
	class ParallelExpressionNode;

	//! Expression representing a type
	class TypeExpressionNode;

	//! Variable declaration
	class VarDeclarationNode;

	//! Assignment or variable declaration
	class AssignmentExpressionNode;

	//! Equal comparison
	class EqualExpressionNode;

	//! Not equal comparison
	class NotEqualExpressionNode;

	//! Inferior binary comparison
	class InferiorExpressionNode;

	//! Inferior or equal binary comparison
	class InferiorEqualExpressionNode;

	//! Superior binary comparison
	class SuperiorExpressionNode;

	//! Superior or equal binary comparison
	class SuperiorEqualExpressionNode;

	//! Addition
	class PlusExpressionNode;

	//! Subtraction
	class MinusExpressionNode;

	//! Multiplication
	class MultiplyExpressionNode;

	//! Division
	class DivideExpressionNode;

	//! Modulus
	class ModulusExpressionNode;

	//! Type-testing
	class IsExpressionNode;

	//! Type-casting
	class AsExpressionNode;

	//! typeof operator
	class TypeofExpressionNode;

	//! new operator
	class NewExpressionNode;

	//! Expression following a `return` keyword
	class ReturnExpressionNode;

	//! Function or method call
	class FunctionCallNode;

	//! A type or variable identifier
	class IdentifierNode;

	//! Template for any kind of literal node
	template<class DataT>
	class LiteralNode;


} // namespace Ast
} // namespace Nany

#endif // __NANY_AST_FWD_H__
