
YMESSAGE(":: [Module] Audio")


LIBYUNI_CONFIG_LIB("audio"      "yuni-static-audio-core")
LIBYUNI_CONFIG_DEPENDENCY("audio" "core") # yuni-core is required


#
# Windows-specific
#
IF (WIN32 OR WIN64)
	LIBYUNI_CONFIG_LIB("audio" ws2_32)
ENDIF (WIN32 OR WIN64)


Set(SRC_AUDIO
		audio/queueservice.h
		audio/queueservice.hxx
		audio/queueservice.cpp
		audio/loop.h
		audio/loop.cpp
		audio/emitter.h
		audio/emitter.hxx
		audio/emitter.cpp
		audio/sound.h
		audio/sound.hxx
		audio/sound.cpp
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
YMESSAGE("Added Support for OpenAL")
IF(APPLE)
	# Frameworks
	LIBYUNI_CONFIG_FRAMEWORK("audio" OpenAL)
ELSE(APPLE)
	IF(WIN32 OR WIN64)
		DEVPACK_IMPORT_OPENAL()
	ELSE(WIN32 OR WIN64)
		FIND_PACKAGE(OpenAL)
		IF(NOT OPENAL_FOUND)
			YERROR("[!!] Impossible to find OpenAL")
			YMESSAGE(    " * Packages needed on Debian: libopenal-dev")
			YMESSAGE(    " * Packages needed on Fedora: openal-devel")
		ENDIF(NOT OPENAL_FOUND)
	ENDIF(WIN32 OR WIN64)
	LIBYUNI_CONFIG_LIB_RAW_COMMAND("audio" "${OPENAL_LIBRARY}")
	LIBYUNI_CONFIG_INCLUDE_PATH("audio" "${OPENAL_INCLUDE_DIR}")
	Include_directories(${OPENAL_INCLUDE_DIR})
ENDIF(APPLE)

#
# FFmpeg
#
YMESSAGE("Added Support for FFMpeg")
DEVPACK_IMPORT_FFMPEG()
SET(SRC_AUDIO_FFMPEG ${YUNI_EXT_FFMPEG_HEADERS})

IF (NOT WIN32 AND NOT WIN64)
	# ZLIB
	FIND_PACKAGE(ZLIB)
	IF (ZLIB_FOUND)
		LIST(APPEND YUNI_EXT_FFMPEG_LIB ${ZLIB_LIBRARIES})
	ELSE (ZLIB_FOUND)
		YMESSAGE(    "[!!] Impossible to find ZLib (Audio will not work properly !)")
		YMESSAGE(    " * Packages needed on Debian: libz-dev")
		YMESSAGE(    " * Packages needed on Fedora: zlib-devel")
	ENDIF (ZLIB_FOUND)

	# BZIP2
	FIND_PACKAGE(BZip2)
	IF(BZIP2_FOUND)
		LIST(APPEND YUNI_EXT_FFMPEG_LIB ${BZIP2_LIBRARIES})
	ELSE(BZIP2_FOUND)
		YMESSAGE(    "[!!] Impossible to find BZip2 (Audio will not work properly !)")
		YMESSAGE(    " * Packages needed on Debian: libbz2-dev")
		YMESSAGE(    " * Packages needed on Fedora: bzip2-devel")
	ENDIF(BZIP2_FOUND)
ENDIF (NOT WIN32 AND NOT WIN64)

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
