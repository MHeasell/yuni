#
# YUNI_INCLUDE
#


#
# The common paths for Yuni headers
#
SET(YUNI_INCLUDE "${PROJECT_SOURCE_DIR}/..")

SET(YUNI_LIBRARIES  yuni-static)

IF(APPLE)
	SET(YUNI_LIBRARIES  ${YUNI_LIBRARIES} "-framework Cocoa")
ENDIF(APPLE)
include_directories(${YUNI_INCLUDE})

#
# Irrlicht
#
SET(YUNI_EXT_IRRLICHT_INCLUDE "${PROJECT_SOURCE_DIR}/../../externals/irrlicht/include")
SET(YUNI_EXT_IRRLICHT_LIB
		"${PROJECT_SOURCE_DIR}/../../externals/irrlicht/lib/libIrrlicht.a"
		"-framework Foundation -framework AppKit -framework Cocoa -framework Carbon -framework OpenGL")


# Link_libraries("${PROJECT_SOURCE_DIR}/../../externals/irrlicht/lib/libIrrlicht.a")
