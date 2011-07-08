#
# LUA
#
macro(DEVPACK_IMPORT_LUA)
	if(YUNI_EXTERNAL_SCRIPT_LUA)
		if(APPLE)
			DEVPACK_IMPORT("lua" "5.1.4" "2" "macos" "ub" "${DEVPACK_COMPILER}" "all")
		endif(APPLE)
		if(MSVC)
			DEVPACK_SMART_IMPORT("lua" "5.1.4" "1" "all")
		endif(MSVC)
		if(MINGW)
			DEVPACK_SMART_IMPORT("lua" "5.1.4" "1" "all")
		endif(MINGW)

		if(IsLinux)
			DEVPACK_SMART_IMPORT("lua" "5.1.4" "1" "all")
		endif(IsLinux)
		list(APPEND YUNI_STATIC_SCRIPT "${YUNI_EXT_LUA_LIB}")
		list(APPEND YUNI_INCLUDE   "${YUNI_EXT_LUA_INCLUDE}")
	endif()
endmacro()


