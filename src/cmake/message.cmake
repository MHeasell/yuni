
set(YUNI_ERROR_HAS_OCCURED   false)


macro(YMESSAGE msg)
	message(STATUS "{yuni} ${msg}")
endmacro()


macro(YMESSAGE_BOLD msg)
	if(UNIX)
		message(STATUS "{yuni} [1;37m[1m${msg}[0m")
	else()
		message(STATUS "{yuni} ${msg}")
	endif()
endmacro()


macro(YMESSAGE_MODULE msg)
	if(UNIX)
		message(STATUS "{yuni} [1;34m[module][0m [1;37m[1m${msg}[0m")
	else()
		message(STATUS "{yuni} [module] ${msg}")
	endif()
endmacro()


macro(YERROR msg)
	if(UNIX)
		message(STATUS "{yuni} [1;31m[error] ${msg} [0m")
	else()
		message(STATUS "{yuni} [ERROR] ${msg}")
	endif()
	set(YUNI_ERROR_HAS_OCCURED  true)
endmacro()


macro(YFATAL msg)
	if(UNIX)
		message(FATAL_ERROR "{yuni} [1;31m[error] ${msg} [0m")
	else()
		message(FATAL_ERROR "{yuni} [ERROR] ${msg}")
	endif()

	set(YUNI_ERROR_HAS_OCCURED  true)
endmacro()


