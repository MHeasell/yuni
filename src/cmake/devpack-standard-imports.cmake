

#
# FFMpeg
#
macro(DEVPACK_IMPORT_FFMPEG)
	if(WIN64)
		DEVPACK_IMPORT("ffmpeg" "git6cb2085" "1" "windows" "x86_64" "all" "all" "all")
	else()
		if (WIN32)
			DEVPACK_IMPORT("ffmpeg" "git6cb2085" "1" "windows" "i386" "all" "all" "all")
		else()
			DEVPACK_IMPORT("ffmpeg" "22725" "3" "all" "all" "${DEVPACK_COMPILER}" "all")
		endif()
	endif()
	list(APPEND YUNI_STATIC_AUDIO "${YUNI_EXT_FFMPEG_LIB}")
	list(APPEND YUNI_INCLUDE   "${YUNI_EXT_FFMPEG_INCLUDE}")
endmacro()



#
# OpenAL
#
macro(DEVPACK_IMPORT_OPENAL)
	set(OPENAL_INCLUDE_DIR)
	set(OPENAL_LIBRARY)
	if(WIN32 OR WIN64)
		if (WIN64)
			DEVPACK_IMPORT("openal" "1.14" "1" "windows" "x86_64" "all" "all")
		else()
			DEVPACK_IMPORT("openal" "1.14" "1" "windows" "i386" "all" "all")
		endif()
		set(OPENAL_INCLUDE_DIR "${YUNI_EXT_OPENAL_INCLUDE}")
		set(OPENAL_LIBRARY "${YUNI_EXT_OPENAL_LIB}")
	else()
		if(NOT APPLE)
			find_package(OpenAL)
		endif()
	endif()
	list(APPEND YUNI_STATIC_AUDIO "${OPENAL_LIBRARY}")
	list(APPEND YUNI_INCLUDE   "${OPENAL_INCLUDE_DIR}")
endmacro()



#
# Cairo - Pango
#
macro(DEVPACK_IMPORT_CAIROPANGO)
	if(WIN32 OR WIN64)
		if (WIN64)
			DEVPACK_IMPORT("cairopango" "1.10.2+1.29.4+2.28.8" "1" "windows" "x86_64" "all" "all")
		else()
			DEVPACK_IMPORT("cairopango" "1.10.2+1.29.4+2.28.8" "1" "windows" "i386" "all" "all")
		endif()
		string(REPLACE " " ";" includes "${YUNI_EXT_CAIROPANGO_INCLUDE}")
		foreach (it ${includes})
			include_directories("${it}")
		endforeach()
		set(CAIRO_FOUND TRUE)
		set(PANGO_FOUND TRUE)
	else()
		# Cairo
		execute_process(COMMAND pkg-config cairo --cflags
			RESULT_VARIABLE config_error OUTPUT_VARIABLE cairo_cflags
			OUTPUT_STRIP_TRAILING_WHITESPACE)
		if (NOT config_error)
			set(CAIRO_FOUND TRUE)
			string(REPLACE " " ";" cairo_cflags "${cairo_cflags}")
			foreach(it ${cairo_cflags})
				if(it)
					string(REPLACE "-I" "" stripped "${it}")
					include_directories(${stripped})
				endif()
			endforeach()
#			list(APPEND YUNI_INCLUDE  "${cairo_cflags}")
			execute_process(COMMAND pkg-config cairo --libs RESULT_VARIABLE config_error OUTPUT_VARIABLE cairo_libs OUTPUT_STRIP_TRAILING_WHITESPACE)
			set(YUNI_EXT_CAIROPANGO_LIB ${cairo_libs})

			# Pango
			execute_process(COMMAND pkg-config pango --cflags-only-I RESULT_VARIABLE config_error OUTPUT_VARIABLE pango_cflags OUTPUT_STRIP_TRAILING_WHITESPACE)
			if (NOT config_error)
				set(PANGO_FOUND TRUE)
				string(REPLACE " " ";" pango_cflags "${pango_cflags}")
				foreach (it ${pango_cflags})
					if(it)
						string(REPLACE "-I" "" stripped ${it})
						include_directories(${stripped})
					endif()
				endforeach()
				execute_process(COMMAND pkg-config pango --libs RESULT_VARIABLE config_error OUTPUT_VARIABLE pango_libs OUTPUT_STRIP_TRAILING_WHITESPACE)
				list(APPEND YUNI_EXT_CAIROPANGO_LIB ${pango_libs})
			endif ()
		endif ()
#		DEVPACK_IMPORT("cairopango" "1.8.10+1.28.0+2.24.0" "1" "all" "all" "${DEVPACK_COMPILER}" "all")
		list (APPEND YUNI_STATIC_GFX3D ${YUNI_EXT_CAIROPANGO_LIB})
	endif()
endmacro()


