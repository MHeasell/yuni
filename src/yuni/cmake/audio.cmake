
Message(STATUS ":: [Module] Audio")


LIBYUNI_CONFIG_LIB("audio"      "yuni-static-audio-core")

LIBYUNI_CONFIG_DEPENDENCY("audio" "core") # yuni-core is required
LIBYUNI_CONFIG_DEPENDENCY("audio" "gfx") # gfx-core is required
# LIBYUNI_CONFIG_LIB("audio"  "yuni-static-device-audio")

IF(APPLE)
	# Frameworks
	LIBYUNI_CONFIG_FRAMEWORK("audio" OpenAL)
ENDIF(APPLE)




Set(SRC_AUDIO
		audio/sound.h
		audio/sound.hxx
		audio/sound.cpp
		audio/sound3D.h
		audio/sound3D.cpp
		audio/manager.h
		audio/manager.hxx
		audio/manager.cpp
		audio/loop.h
		audio/music.h
		audio/music.cpp
		audio/playlist.h
		audio/source.h
		audio/source.cpp
		private/audio/openal.h
		private/audio/openal.cpp
		private/audio/av.h
		private/audio/av.hxx
		private/audio/av.cpp
	)


Include(CheckIncludeFile)

#
# OpenAL
#
Message(STATUS "Added Support for OpenAL")
DEVPACK_IMPORT_OPENAL()
LIBYUNI_CONFIG_LIB_RAW_COMMAND("audio" "${OPENAL_LIBRARY}")
LIBYUNI_CONFIG_INCLUDE_PATH("audio" "${OPENAL_INCLUDE_DIR}")

#
# FFmpeg
#
Message(STATUS "Added Support for FFMpeg")
DEVPACK_IMPORT_FFMPEG()
LIBYUNI_CONFIG_LIB_RAW_COMMAND("audio" "${YUNI_EXT_FFMPEG_LIB}")
LIBYUNI_CONFIG_INCLUDE_PATH("audio" "${YUNI_EXT_FFMPEG_INCLUDE}")

source_group(Audio FILES ${SRC_AUDIO})

Add_Library(yuni-static-audio-core STATIC ${SRC_AUDIO})

target_link_libraries(yuni-static-audio-core ${OPENAL_LIBRARY})
