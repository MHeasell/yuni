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
		static Type* Get(const char* id)
		{
			if (sTypeMap.empty())
			{
				RegisterBuiltinTypes();
			}
			// Find the type
			Map::iterator it = sTypeMap.find(id);
			if (sTypeMap.end() == it)
				return nullptr;
			return it->second;
		}

		static void Add(const char* id, Type* newType)
		{
			if (sTypeMap.empty())
				RegisterBuiltinTypes();
			Map::iterator it = sTypeMap.find(id);
			if (sTypeMap.end() != it)
			{
				delete it->second;
				it->second = newType;
			}
			else
				sTypeMap[id] = newType;
		}


	private:
		static void RegisterBuiltinTypes()
		{
			Yuni::String s;
			sTypeMap[(s = "void")] = new Type("void", true, true);
			sTypeMap[(s = "bool")] = new Type("bool", true);
			sTypeMap[(s = "int")] = new Type("int", true);
			sTypeMap[(s = "uint")] = new Type("unsigned int", true);
			sTypeMap[(s = "int64")] = new Type("long long", true);
			sTypeMap[(s = "uint64")] = new Type("unsigned long long", true);
			sTypeMap[(s = "int32")] = new Type("long", true);
			sTypeMap[(s = "uint32")] = new Type("unsigned long", true);
			sTypeMap[(s = "int16")] = new Type("short", true);
			sTypeMap[(s = "uint16")] = new Type("unsigned short", true);
			sTypeMap[(s = "float")] = new Type("float", true);
			sTypeMap[(s = "double")] = new Type("double", true);
			sTypeMap[(s = "char")] = new Type("char", true);
			sTypeMap[(s = "string")] = new Type("char*", false);
		}


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
