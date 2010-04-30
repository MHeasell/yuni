
YUNITESTCASE_BEGIN(libyuni_core_audio_00_loadandplay
	"
	options.description = 'Test simple audio loading and playing'
	options.args = ''
	options.compareStdoutWith = nil
	options.compareStderrWith = nil
	options.exitStatus = 0
	")
	YUNITESTCASE_MODULES(audio)
	YUNITESTCASE_SOURCE(00.loadandplay.cpp)
YUNITESTCASE_END()



YUNITESTCASE_BEGIN(libyuni_core_audio_01_movingsource
	"
	options.description = 'Load a sound and move the source left and right'
	options.args = ''
	options.compareStdoutWith = nil
	options.compareStderrWith = nil
	options.exitStatus = 0
	")
	YUNITESTCASE_MODULES(audio)
	YUNITESTCASE_SOURCE(01.movingsource.cpp)
YUNITESTCASE_END()


