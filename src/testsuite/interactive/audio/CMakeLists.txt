
YUNITESTCASE_BEGIN(libyuni_core_audio_loadandplay
	"
	options.description = 'Test simple audio loading and playing'
	options.args = ''
	options.timeout = 10 # seconds
	options.compareStdoutWith = nil
	options.compareStderrWith = nil
	options.exitStatus = 0
	")
	YUNITESTCASE_MODULES(audio)
	YUNITESTCASE_SOURCE(loadandplay.cpp)
YUNITESTCASE_END()


