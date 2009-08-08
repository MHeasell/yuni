#ifndef __YUNI_SCRIPT_H__
# define __YUNI_SCRIPT_H__



namespace Yuni
{

/*!
** \brief Scripting engine and related tools [work in progress]
** \ingroup Script
** 
** \warning This whole module is currently a work in progress, and is
** far from anything functional.
** The compilation is disabled by default, enable at your own risks.
**
*/
namespace Script
{
} // namespace Script
} // namespace Yuni


// TODO: this must dynamically include only the built-in languages.
// Do we have a config.h or something similar ?

// class Yuni::Script::AScript
# include "script/script.h"
// class Yuni::Script::Lua
# include "script/lua/lua.h"



#endif // __YUNI_SCRIPT_H__
