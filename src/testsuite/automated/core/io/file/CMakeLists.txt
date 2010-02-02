
YUNITESTCASE_BEGIN(libyuni_core_io_file_exists
	"
	options.description = 'File existence'
	options.args = ''
	options.timeout = 5 # seconds
	options.compareStdoutWith = nil
	options.compareStderrWith = nil
	options.exitStatus = 0
	")
	YUNITESTCASE_MODULES(core)
	YUNITESTCASE_SOURCE(exists.cpp)
YUNITESTCASE_END()




YUNITESTCASE_BEGIN(libyuni_core_io_file_isdirectory
	"
	options.description = 'File / Directory detection'
	options.args = ''
	options.timeout = 5 # seconds
	options.compareStdoutWith = nil
	options.compareStderrWith = nil
	options.exitStatus = 0
	")
	YUNITESTCASE_MODULES(core)
	YUNITESTCASE_SOURCE(isdirectory.cpp)
YUNITESTCASE_END()



