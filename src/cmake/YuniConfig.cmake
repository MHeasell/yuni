

#
# This variable must only be enabled when compiling
# the yuni library.
# Otherwise, some files could be created in the wrong place
#
if(LIBYUNI_CONFIG_ENABLED)
    if(MSVC)
    	set(YUNI_LIBYUNI_CONFIG_COMPILER "msvc")
    else()
    	if(MINGW)
    		set(YUNI_LIBYUNI_CONFIG_COMPILER "mingw")
    	else()
    		set(YUNI_LIBYUNI_CONFIG_COMPILER "gcc")
   	    endif()
    endif()

	set(YUNI_LIBYUNI_CONFIG_TARGET_INIFILE
		"${CMAKE_CURRENT_SOURCE_DIR}/yuni.config.${YUNI_LIBYUNI_CONFIG_COMPILER}")
	file(WRITE "${YUNI_LIBYUNI_CONFIG_TARGET_INIFILE}" "[settings]\n")
endif()


macro(LIBYUNI_CONFIG_CFLAG module pth)
	if(LIBYUNI_CONFIG_ENABLED)
		file(APPEND "${YUNI_LIBYUNI_CONFIG_TARGET_INIFILE}" "cxxflag:${module} = ${pth}\n")
	endif()
endmacro()


macro(LIBYUNI_CONFIG_LIB module pth)
	if(LIBYUNI_CONFIG_ENABLED)
		foreach(I ${pth})
			file(APPEND "${YUNI_LIBYUNI_CONFIG_TARGET_INIFILE}" "lib:${module} = ${I}\n")
		endforeach()
	endif()
endmacro()


macro(LIBYUNI_CONFIG_LIB_RAW_COMMAND module pth)
	if(LIBYUNI_CONFIG_ENABLED)
		foreach(I ${pth})
			file(APPEND "${YUNI_LIBYUNI_CONFIG_TARGET_INIFILE}" "lib,rawcommand:${module} = ${I}\n")
		endforeach(I ${pth})
	endif()
endmacro()


macro(LIBYUNI_CONFIG_FRAMEWORK module pth)
	if(LIBYUNI_CONFIG_ENABLED)
		foreach(I ${pth})
			file(APPEND "${YUNI_LIBYUNI_CONFIG_TARGET_INIFILE}" "framework:${module} = ${I}\n")
		endforeach()
	endif()
endmacro()



macro(LIBYUNI_CONFIG_DEFINITION module pth)
	if(LIBYUNI_CONFIG_ENABLED)
		foreach(I ${pth})
			file(APPEND "${YUNI_LIBYUNI_CONFIG_TARGET_INIFILE}" "define:${module} = ${I}\n")
		endforeach()
	endif()
endmacro()


macro(LIBYUNI_CONFIG_DEPENDENCY module pth)
	if(LIBYUNI_CONFIG_ENABLED)
		file(APPEND "${YUNI_LIBYUNI_CONFIG_TARGET_INIFILE}" "dependency:${module} = ${pth}\n")
	endif()
endmacro()




macro(LIBYUNI_CONFIG_INCLUDE_PATH module pth)
	if(LIBYUNI_CONFIG_ENABLED)
		foreach(I ${pth})
			file(APPEND "${YUNI_LIBYUNI_CONFIG_TARGET_INIFILE}" "path.include:${module} = ${I}\n")
		endforeach()
	endif()
endmacro()

macro(LIBYUNI_CONFIG_LIB_PATH module pth)
	if(LIBYUNI_CONFIG_ENABLED)
		foreach(I ${pth})
			file(APPEND "${YUNI_LIBYUNI_CONFIG_TARGET_INIFILE}" "path.lib:${module} = ${I}\n")
		endforeach()
	endif()
endmacro()

