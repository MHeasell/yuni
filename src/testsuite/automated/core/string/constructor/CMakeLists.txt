
YUNITESTCASE_BEGIN(libyuni_core_string_constructor_char
	"
	options.description = 'String instanciation in various ways (char)'
	options.args = ''
	options.timeout = 5 # seconds
	options.compareStdoutWith = 'result.stdout.txt'
	options.compareStderrWith = nil
	options.exitStatus = 0
	")
	YUNITESTCASE_SOURCE(main_char.cpp common.hxx)
	YUNITESTCASE_LINK(${YUNI_STATIC_CORE})
YUNITESTCASE_END()




YUNITESTCASE_BEGIN(libyuni_core_string_constructor_wchar
	"
	options.description = 'String instanciation in various ways (wchar_t)'
	options.args = ''
	options.timeout = 5 # seconds
	options.compareStdoutWith = 'result.stdout.txt'
	options.compareStderrWith = nil
	options.exitStatus = 0
	")
	YUNITESTCASE_SOURCE(main_wchart.cpp common.hxx)
	YUNITESTCASE_LINK(${YUNI_STATIC_CORE})
YUNITESTCASE_END()



