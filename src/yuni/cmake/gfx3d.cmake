

LIBYUNI_CONFIG_LIB("gfx3d"      "yuni-static-gfx3d-core")

LIBYUNI_CONFIG_DEPENDENCY("gfx3d" "core") # gfx-core is required
LIBYUNI_CONFIG_DEPENDENCY("gfx3d" "gfx") # gfx-core is required
LIBYUNI_CONFIG_DEPENDENCY("gfx3d" "display") # gfx-core is required
LIBYUNI_CONFIG_LIB("gfx3d"  "yuni-static-device-display")

IF(APPLE)
	# Frameworks
	LIBYUNI_CONFIG_FRAMEWORK("gfx3d" CoreFoundation)
	LIBYUNI_CONFIG_FRAMEWORK("gfx3d" Cocoa)
	LIBYUNI_CONFIG_FRAMEWORK("gfx3d" IOKit)
ENDIF(APPLE)



Set(SRC_GFX3D
		application/gfx3d.h application/gfx3d.cpp
		gfx/engine.h gfx/engine.cpp

		# Window
		gfx/window/window.h
		gfx/window/window.hxx
		gfx/window/window.cpp
		gfx/window/msw.h
		gfx/window/directxmsw.h
		gfx/window/openglmsw.h
		gfx/window/openglx11.h
		gfx/window/openglcocoa.h
		gfx/window/x11yuni.h

		# Renderer
		gfx/render/renderer.h gfx/render/renderer.cpp
		gfx/render/fpscounter.h
		gfx/render/opengl.h gfx/render/opengl.cpp

		# Font
		gfx/text/font.h gfx/text/label.h
		gfx/text/wgl.h gfx/text/wgl.cpp
		)


#
# OpenGL
#
Message(STATUS "Added Support for OpenGL")
find_package(OpenGL)
Set(YUNI_COMPILED_WITH_SUPPORT_FOR_OPENGL  1)
LIBYUNI_CONFIG_INCLUDE_PATH("gfx3d"  "${OPENGL_INCLUDE_DIR}")


#
# DirectX
#
# find_package(DirectX)
IF (WIN32)
	FIND_PATH(DX9_INCLUDE_PATH d3d9.h
		PATHS
			"$ENV{DXSDK_DIR}/Include"
			"$ENV{PROGRAMFILES}/Microsoft DirectX SDK/Include"
		DOC "The directory where D3D9.h resides")

	FIND_LIBRARY(D3D9_LIBRARY d3d9.lib
		PATHS
			"$ENV{DXSDK_DIR}/Lib/x86"
			"$ENV{PROGRAMFILES}/Microsoft DirectX SDK/Lib/x86"
		DOC "The directory where d3d9.lib resides")

	FIND_LIBRARY(D3DX9_LIBRARY d3dx9.lib
		PATHS
			"$ENV{DXSDK_DIR}/Lib/x86"
			"$ENV{PROGRAMFILES}/Microsoft DirectX SDK/Lib/x86"
		DOC "The directory where d3dx9.lib resides")

	SET(SRC_GFX3D ${SRC_GFX3D} gfx/window/msw.cpp gfx/window/openglmsw.cpp)

	IF(D3D9_LIBRARY AND D3DX9_LIBRARY)
		SET(DX9_LIBRARIES "${D3D9_LIBRARY}" "${D3DX9_LIBRARY}")

		IF(DX9_INCLUDE_PATH)
			ADD_DEFINITIONS("-DYUNI_USE_DIRECTX")
			Message(STATUS "Added Support for DirectX")
			Message(STATUS "  DX include: ${DX9_INCLUDE_PATH}")
			Message(STATUS "  DX libs: ${D3X9_LIBRARY} ${D3DX9_LIBRARY}")
			Set(YUNI_COMPILED_WITH_SUPPORT_FOR_DIRECTX 1)
			SET(SRC_GFX3D ${SRC_GFX3D} gfx/window/directxmsw.cpp)
			Include_Directories("${DX9_INCLUDE_PATH}")
			LIBYUNI_CONFIG_INCLUDE_PATH("gfx3d"  "${DX9_INCLUDE_PATH}")
			LIBYUNI_CONFIG_DEFINITION("gfx3d"  "YUNI_USE_DIRECTX")
		ENDIF(DX9_INCLUDE_PATH)
	ENDIF(D3D9_LIBRARY AND D3DX9_LIBRARY)

ELSE(WIN32)
	IF(APPLE)
	ELSE(APPLE)
		Set(SRC_GFX3D ${SRC_GFX3D} gfx/window/openglx11.cpp)
		LIBYUNI_CONFIG_LIB("gfx3d" "GL")
		LIBYUNI_CONFIG_LIB("gfx3d" "GLU")
	ENDIF(APPLE)
ENDIF(WIN32)

source_group(Gfx3D FILES ${SRC_GFX3D})

Add_Library(yuni-static-gfx3d-core STATIC ${SRC_GFX3D})

target_link_libraries(yuni-static-gfx3d-core
	# DirectX
	${OPENGL_LIBRARY} ${DX9_LIBRARIES}
	# Required on Linux
	yuni-static-core yuni-static-device-display yuni-static-gfx-core)

