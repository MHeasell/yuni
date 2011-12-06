#ifndef __NANY_TYPE_TYPE_H__
# define __NANY_TYPE_TYPE_H__

# include "yuni/yuni.h"
# include "yuni/core/string.h"
# include <map>

namespace Nany
{
namespace Typing
{

	/*!
	** \brief Type of an AST. May be any built-in or user type in Nany
	*/
	class Type
	{
	public:
		typedef std::map<Yuni::String, Type*>  Map;


	public:
		static Type* Get(const char* id);

		static void Add(const char* id, Type* newType);


	private:
		static void RegisterBuiltinTypes();


	public:
		Type(const char* name, bool isCppValue, bool isConst = false):
			pName(name),
			pIsValue(isCppValue),
			pIsConst(isConst)
		{}

		const Yuni::String& name() const { return pName; }

		bool isValue() const { return pIsValue; }

		bool isConst() const { return pIsConst; }
		void setConst() { pIsConst = false; }

	private:
		static Map sTypeMap;

	private:
		//! C-style name
		Yuni::String pName;

		//! Is the type a value type in C / C++ ?
		bool pIsValue;

		//! Is the type const ? (values of this type cannot be changed)
		bool pIsConst;

	}; // class Type


} // namespace Typing
} // namespace Nany


#endif // __NANY_AST_TYPE_H__
