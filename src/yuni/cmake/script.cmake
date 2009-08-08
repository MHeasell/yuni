
Message(STATUS "[Module] Script")

# Scripts
Set(SRC_SCRIPT
			script.h
			script/script.h script/script.hxx script/script.cpp
			script/private.h script/private.hxx
			script/args.hxx
			private/script/script.defines.h private/script/script.undefs.h
	)
source_group("Script\\Script Abstraction" FILES ${SRC_SCRIPT})


# External Lib: Lua script
if(YUNI_EXTERNAL_SCRIPT_LUA)
	Message(STATUS "[Module] Script::Lua")
	# Headers for Lua
	DEVPACK_IMPORT_LUA()
	Set(SRC_EXTERNAL_SCRIPT_LUA
			${YUNI_EXT_LUA_SRC}  # From DevPack 'lua'
			script/lua/lua.h script/lua/lua.cpp script/lua/args.cpp
			private/script/lua.proxy.h
		)
	source_group("Script\\Script Lua language support" FILES ${SRC_EXTERNAL_SCRIPT_LUA})

Endif(YUNI_EXTERNAL_SCRIPT_LUA)

Add_Library(yuni-static-script STATIC
			${SRC_SCRIPT}
			${SRC_EXTERNAL_SCRIPT_LUA}
			)


