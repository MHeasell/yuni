
YMESSAGE(":: [Module] Script")

Include(CheckIncludeFile)
LIBYUNI_CONFIG_LIB("script"     "yuni-static-script")


# Scripts
set(SRC_SCRIPT
			script/script.h script/script.hxx script/script.cpp
			script/private.h script/private.hxx
			script/args.hxx
			private/script/script.defines.h private/script/script.undefs.h
	)
source_group("Script\\Script Abstraction" FILES ${SRC_SCRIPT})



# External Lib: Lua script
if(YUNI_EXTERNAL_SCRIPT_LUA)
	YMESSAGE(":: [Module] Script::Lua")

	if(UNIX AND NOT APPLE)
		check_include_files("stdio.h;readline/readline.h" YUNI_HAS_READLINE_HEADER)
		if(NOT "${YUNI_HAS_READLINE_HEADER}" GREATER 0)
			set(YUNI_CMAKE_ERROR 1)
			YMESSAGE(    "[!!] Impossible to find readline/readline.h")
			YMESSAGE(    " * Packages needed on Debian: libreadline-dev")
			YMESSAGE(    " * Packages needed on Fedora: readline-devel.i686")
		endif()
	endif()

	if (YUNI_DvP_LUA_MODE STREQUAL "devpack")
		# Headers for Lua
		DEVPACK_IMPORT_LUA()
		LIBYUNI_CONFIG_LIB_RAW_COMMAND("lua" "${YUNI_EXT_LUA_LIB}")
		LIBYUNI_CONFIG_INCLUDE_PATH("lua" "${YUNI_EXT_LUA_INCLUDE}")
	elseif(YUNI_DvP_LUA_MODE STREQUAL "custom")
		set(YUNI_EXT_LUA_INCLUDE "${YUNI_DvP_LUA_PREFIX}/include")
		set(YUNI_EXT_LUA_LIB "${YUNI_DvP_LUA_PREFIX}/lib")
		LIBYUNI_CONFIG_LIB_RAW_COMMAND("lua" "${YUNI_EXT_LUA_LIB}")
		LIBYUNI_CONFIG_INCLUDE_PATH("lua" "${YUNI_EXT_LUA_INCLUDE}")
	elseif(YUNI_DvP_LUA_MODE STREQUAL "system")
		# Nothing to do, since the system does it.
	else()
		set(YUNI_CMAKE_ERROR 1)
		YFATAL(    "[!!] Invalid YUNI_DvP_LUA_MODE: ${YUNI_DvP_LUA_MODE}")
	endif()

	# Check if we really have a lua.h
	set(CMAKE_REQUIRED_INCLUDES "${YUNI_EXT_LUA_INCLUDE}")
	check_include_files("lua.h" YUNI_HAS_LUA_H)

	if (YUNI_HAS_LUA_H)
		set(YUNI_CMAKE_ERROR 1)
		YMESSAGE(    "[!!] Impossible to find lua.h. Please check your profile.")
		YMESSAGE(    " * Packages needed on Debian: liblua5.1-dev")
	endif()

	LIBYUNI_CONFIG_DEPENDENCY("lua" "script")

	set(SRC_EXTERNAL_SCRIPT_LUA
			${YUNI_EXT_LUA_SRC}  # From DevPack 'lua'
			script/lua/lua.h script/lua/lua.cpp script/lua/args.cpp
			private/script/lua.proxy.h
		)
	source_group("Script\\Script Lua language support" FILES ${SRC_EXTERNAL_SCRIPT_LUA})

endif()


add_library(yuni-static-script STATIC
	${SRC_SCRIPT} ${SRC_EXTERNAL_SCRIPT_LUA})

# Setting output path
set_target_properties(yuni-static-script PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY "${YUNI_OUTPUT_DIRECTORY}/lib")

# Installation
install(TARGETS yuni-static-script ARCHIVE DESTINATION lib/${YUNI_VERSIONED_INST_PATH})

# Install Script-related headers
install(
	DIRECTORY script
	DESTINATION include/${YUNI_VERSIONED_INST_PATH}
	FILES_MATCHING
		PATTERN "*.h"
		PATTERN "*.hxx"
	PATTERN ".svn" EXCLUDE
	PATTERN "CMakeFiles" EXCLUDE
	PATTERN "cmake" EXCLUDE
)

# Link
target_link_libraries(yuni-static-script yuni-static-core)
