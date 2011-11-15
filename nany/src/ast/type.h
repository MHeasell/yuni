#ifndef __NANY_AST_TYPE_H__
# define __NANY_AST_TYPE_H__

# include "yuni/yuni.h"
# include "yuni/core/string.h"
# include <map>

namespace Nany
{
namespace Ast
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
			sTypeMap[(s = "void")] = new Type("void");
			sTypeMap[(s = "int")] = new Type("int");
			sTypeMap[(s = "uint")] = new Type("unsigned int");
			sTypeMap[(s = "int64")] = new Type("long long");
			sTypeMap[(s = "uint64")] = new Type("unsigned long long");
			sTypeMap[(s = "int32")] = new Type("long");
			sTypeMap[(s = "uint32")] = new Type("unsigned long");
			sTypeMap[(s = "int16")] = new Type("short");
			sTypeMap[(s = "uint16")] = new Type("unsigned short");
			sTypeMap[(s = "char")] = new Type("char");
			sTypeMap[(s = "string")] = new Type("char*");
		}


	public:
		Type(const char* name): pName(name)
		{}

		const Yuni::String& name() const { return pName; }

	private:
		static Map sTypeMap;

	private:
		//! C-style name
		Yuni::String pName;
	};


} // namespace Ast
} // namespace Nany


#endif // __NANY_AST_TYPE_H__
