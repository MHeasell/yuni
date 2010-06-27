
YMESSAGE(":: [Module] Script")

Include(CheckIncludeFile)
LIBYUNI_CONFIG_LIB("script"     "yuni-static-script")


# Scripts
Set(SRC_SCRIPT
			script/script.h script/script.hxx script/script.cpp
			script/private.h script/private.hxx
			script/args.hxx
			private/script/script.defines.h private/script/script.undefs.h
	)
source_group("Script\\Script Abstraction" FILES ${SRC_SCRIPT})



# External Lib: Lua script
if(YUNI_EXTERNAL_SCRIPT_LUA)
	YMESSAGE(":: [Module] Script::Lua")

	IF(UNIX AND NOT APPLE)
		CHECK_INCLUDE_FILES("stdio.h;readline/readline.h" YUNI_HAS_READLINE_HEADER)
		IF(NOT "${YUNI_HAS_READLINE_HEADER}" GREATER 0)
			Set(YUNI_CMAKE_ERROR 1)
			YMESSAGE(    "[!!] Impossible to find readline/readline.h")
			YMESSAGE(    " * Packages needed on Debian: libreadline-dev")
			YMESSAGE(    " * Packages needed on Fedora: readline-devel.i686")
		ENDIF(NOT "${YUNI_HAS_READLINE_HEADER}" GREATER 0)
	ENDIF(UNIX AND NOT APPLE)

	# Headers for Lua
	DEVPACK_IMPORT_LUA()
	LIBYUNI_CONFIG_DEPENDENCY("lua" "script")
	LIBYUNI_CONFIG_LIB_RAW_COMMAND("lua" "${YUNI_EXT_LUA_LIB}")
	LIBYUNI_CONFIG_INCLUDE_PATH("lua" "${YUNI_EXT_LUA_INCLUDE}")

	Set(SRC_EXTERNAL_SCRIPT_LUA
			${YUNI_EXT_LUA_SRC}  # From DevPack 'lua'
			script/lua/lua.h script/lua/lua.cpp script/lua/args.cpp
			private/script/lua.proxy.h
		)
	source_group("Script\\Script Lua language support" FILES ${SRC_EXTERNAL_SCRIPT_LUA})

Endif(YUNI_EXTERNAL_SCRIPT_LUA)




Add_Library(yuni-static-script STATIC
	${SRC_SCRIPT} ${SRC_EXTERNAL_SCRIPT_LUA})


