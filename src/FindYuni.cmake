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
Include_Directories(${YUNI_INCLUDE})


#
# Irrlicht
#
If(YUNI_EXTERNAL_3D_IRRLICHT)
	DEVPACK_IMPORT_IRRLICHT()
Endif(YUNI_EXTERNAL_3D_IRRLICHT)

