


#
# LUA
#
MACRO(DEVPACK_IMPORT_LUA)
	IF(YUNI_EXTERNAL_SCRIPT_LUA)
		IF(APPLE)
			DEVPACK_IMPORT("lua" "5.1.4" "2" "macos" "ub" "${DEVPACK_COMPILER}" "all")
		ENDIF(APPLE)
		IF(MSVC)
			DEVPACK_SMART_IMPORT("lua" "5.1.4" "1" "all")
		ENDIF(MSVC)
		IF(MINGW)
			DEVPACK_SMART_IMPORT("lua" "5.1.4" "1" "all")
		ENDIF(MINGW)

		IF(IsLinux)
			DEVPACK_SMART_IMPORT("lua" "5.1.4" "1" "all")
		ENDIF(IsLinux)
		LIST(APPEND YUNI_STATIC_SCRIPT "${YUNI_EXT_LUA_LIB}")
		LIST(APPEND YUNI_INCLUDE   "${YUNI_EXT_LUA_INCLUDE}")
	ENDIF(YUNI_EXTERNAL_SCRIPT_LUA)
ENDMACRO(DEVPACK_IMPORT_LUA)



#
# FFMpeg
#
MACRO(DEVPACK_IMPORT_FFMPEG)
	IF(WIN32 OR WIN64)
		DEVPACK_SMART_IMPORT("ffmpeg" "22144" "1" "all")
	ELSE(WIN32 OR WIN64)
		DEVPACK_IMPORT("ffmpeg" "22725" "2" "all" "all" "${DEVPACK_COMPILER}" "all")
	ENDIF(WIN32 OR WIN64)
	LIST(APPEND YUNI_STATIC_AUDIO "${YUNI_EXT_FFMPEG_LIB}")
	LIST(APPEND YUNI_INCLUDE   "${YUNI_EXT_FFMPEG_INCLUDE}")
ENDMACRO(DEVPACK_IMPORT_FFMPEG)



#
# OpenAL
#
MACRO(DEVPACK_IMPORT_OPENAL)
	SET(OPENAL_INCLUDE_DIR)
	SET(OPENAL_LIBRARY)
	IF(WIN32 OR WIN64)
		DEVPACK_IMPORT("openal" "1.10.622" "1" "windows" "i386" "all" "all")
		SET(OPENAL_INCLUDE_DIR "${YUNI_EXT_OPENAL_INCLUDE}")
		SET(OPENAL_LIBRARY "${YUNI_EXT_OPENAL_LIB}")
	ELSE(WIN32 OR WIN64)
		IF(NOT APPLE)
			find_package(OpenAL)
		ENDIF(NOT APPLE)
	ENDIF(WIN32 OR WIN64)
	LIST(APPEND YUNI_STATIC_AUDIO "${OPENAL_LIBRARY}")
	LIST(APPEND YUNI_INCLUDE   "${OPENAL_INCLUDE_DIR}")
ENDMACRO(DEVPACK_IMPORT_OPENAL)



#
# PThreads
#
MACRO(DEVPACK_IMPORT_PTHREADS)
	Include(FindThreads)
	If(CMAKE_USE_WIN32_THREADS_INIT)
		Message(STATUS "Threading Support: PThreads for Windows (via DevPacks)")
		IF(WIN32)
			DEVPACK_SMART_IMPORT("pthreads" "2.8.0" "3" "all")
			LIST(APPEND YUNI_STATIC_CORE "${YUNI_EXT_PTHREADS_LIB}")
			LIST(APPEND YUNI_INCLUDE   "${YUNI_EXT_PTHREADS_INCLUDE}")
			LIBYUNI_CONFIG_INCLUDE_PATH("core" "${YUNI_EXT_PTHREADS_INCLUDE}")
			LIBYUNI_CONFIG_LIB_RAW_COMMAND("core" "${YUNI_EXT_PTHREADS_LIB}")
		ENDIF(WIN32)
	Else(CMAKE_USE_WIN32_THREADS_INIT)
		IF(NOT CMAKE_USE_PTHREADS_INIT)
			MESSAGE(FATAL_ERROR "PThreads is required.")
		ENDIF(NOT CMAKE_USE_PTHREADS_INIT)
		Link_libraries(${CMAKE_THREAD_LIBS_INIT})
		LIBYUNI_CONFIG_LIB_RAW_COMMAND("core" "${CMAKE_THREAD_LIBS_INIT}")
		Message(STATUS "Threading Support: PThreads (${CMAKE_THREAD_LIBS_INIT})")
	EndIF(CMAKE_USE_WIN32_THREADS_INIT)
ENDMACRO(DEVPACK_IMPORT_PTHREADS)

