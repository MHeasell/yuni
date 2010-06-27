
Message(STATUS ":: [Module] Audio")

IF (NOT WIN32 AND NOT WIN64)
   FIND_PACKAGE(ZLIB)
   FIND_PACKAGE(BZip2)
ENDIF (NOT WIN32 AND NOT WIN64)


LIBYUNI_CONFIG_LIB("audio"      "yuni-static-audio-core")

LIBYUNI_CONFIG_DEPENDENCY("audio" "core") # yuni-core is required
LIBYUNI_CONFIG_DEPENDENCY("audio" "gfx") # gfx-core is required
# LIBYUNI_CONFIG_LIB("audio"  "yuni-static-device-audio")


#
# Windows-specific
#
IF (WIN32 OR WIN64)
	LIBYUNI_CONFIG_LIB_RAW_COMMAND("audio" "-lws2_32")
ENDIF (WIN32 OR WIN64)


Set(SRC_AUDIO
		audio/queueservice.h
		audio/queueservice.hxx
		audio/queueservice.cpp
		audio/loop.h
		audio/loop.cpp
#		audio/playlist.h
		audio/emitter.h
		audio/emitter.hxx
		audio/emitter.cpp
		private/audio/buffer.h
		private/audio/buffer.hxx
		private/audio/types.h
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
IF(APPLE)
	# Frameworks
	LIBYUNI_CONFIG_FRAMEWORK("audio" OpenAL)
ELSE(APPLE)
	DEVPACK_IMPORT_OPENAL()
	LIBYUNI_CONFIG_LIB_RAW_COMMAND("audio" "${OPENAL_LIBRARY}")
	LIBYUNI_CONFIG_INCLUDE_PATH("audio" "${OPENAL_INCLUDE_DIR}")
ENDIF(APPLE)

#
# FFmpeg
#
Message(STATUS "Added Support for FFMpeg")
DEVPACK_IMPORT_FFMPEG()
SET(SRC_AUDIO_FFMPEG ${YUNI_EXT_FFMPEG_HEADERS})
IF (ZLIB_FOUND)
	IF(BZIP2_FOUND)
		LIST(APPEND YUNI_EXT_FFMPEG_LIB ${ZLIB_LIBRARIES} ${BZIP2_LIBRARIES})
	ELSE(BZIP2_FOUND)
		MESSAGE(STATUS "BZip2 library is missing! Audio module will not work properly!")
	ENDIF(BZIP2_FOUND)
ELSE (ZLIB_FOUND)
	MESSAGE(STATUS "Zip library is missing! Audio module will not work properly!")
ENDIF (ZLIB_FOUND)
LIBYUNI_CONFIG_LIB_RAW_COMMAND("audio" "${YUNI_EXT_FFMPEG_LIB}")
LIBYUNI_CONFIG_INCLUDE_PATH("audio" "${YUNI_EXT_FFMPEG_INCLUDE}")

### WARNING: FFmpeg 0.6 (and other versions) fail to compile with:
### error: 'UINT64_C' was not declared in this scope
### This define is required to solve this.
add_definitions(-D__STDC_CONSTANT_MACROS)

source_group(Audio FILES ${SRC_AUDIO})
source_group(Audio\\Ffmpeg FILES ${SRC_AUDIO_FFMPEG})

Add_Library(yuni-static-audio-core STATIC ${SRC_AUDIO_FFMPEG} ${SRC_AUDIO})

target_link_libraries(yuni-static-audio-core ${OPENAL_LIBRARY})
