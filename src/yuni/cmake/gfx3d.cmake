

Set(SRC_GFX3D
		application/gfx3d.h application/gfx3d.cpp
		gfx/engine.h gfx/engine.cpp
		gfx/window/window.h
		gfx/window/factory.h gfx/window/factory.cpp
		gfx/window/opengl.h gfx/window/opengl.cpp
		gfx/window/msw.h
		gfx/window/directxmsw.h
		gfx/window/openglmsw.h
		gfx/window/openglx11.h
		gfx/window/openglcocoa.h
		gfx/window/x11yuni.h
		gfx/render/renderer.h gfx/render/fpscounter.h
		gfx/render/opengl.h gfx/render/opengl.cpp
		)

find_package(OpenGL)

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

	SET(DX9_LIBRARIES ${D3D9_LIBRARY} ${D3DX9_LIBRARY})

	Set(SRC_GFX3D ${SRC_GFX3D} gfx/window/msw.cpp gfx/window/openglmsw.cpp)

	IF(DX9_INCLUDE_PATH)
		ADD_DEFINITIONS("-DYUNI_USE_DIRECTX")
		Set(SRC_GFX3D ${SRC_GFX3D} gfx/window/directxmsw.cpp)
	ENDIF(DX9_INCLUDE_PATH)

ELSE(WIN32)
	IF(APPLE)
	ELSE(APPLE)
		Set(SRC_GFX3D ${SRC_GFX3D} gfx/window/openglx11.cpp)
	ENDIF(APPLE)
ENDIF(WIN32)

source_group(Gfx3D FILES ${SRC_GFX3D})

Add_Library(yuni-static-gfx3d-core STATIC ${SRC_GFX3D})
target_link_libraries(yuni-static-gfx3d-core ${OPENGL_LIBRARY} ${DX9_LIBRARIES})

