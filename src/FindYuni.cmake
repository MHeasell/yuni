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
		"${PROJECT_SOURCE_DIR}/../../externals/irrlicht/lib/libIrrlicht.a")
IF(APPLE)
		Set(YUNI_EXT_IRRLICHT_LIB ${YUNI_EXT_IRRLICHT_LIB} "-framework Foundation -framework AppKit -framework Cocoa -framework Carbon -framework OpenGL")
Else(APPLE)
	IF(UNIX)
		Set(YUNI_EXT_IRRLICHT_LIB ${YUNI_EXT_IRRLICHT_LIB} " -L/usr/X11R6/lib -lGL -lXxf86vm  -lX11")
	EndIF(UNIX)
EndIF(APPLE)

