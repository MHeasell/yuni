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
			sTypeMap["void"] = new Type("void");
			sTypeMap["int"] = new Type("int");
			sTypeMap["uint"] = new Type("unsigned int");
			sTypeMap["int64"] = new Type("long long");
			sTypeMap["uint64"] = new Type("unsigned long long");
			sTypeMap["int32"] = new Type("long");
			sTypeMap["uint32"] = new Type("unsigned long");
			sTypeMap["int16"] = new Type("short");
			sTypeMap["uint16"] = new Type("unsigned short");
			sTypeMap["char"] = new Type("char");
			sTypeMap["string"] = new Type("char*");
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
