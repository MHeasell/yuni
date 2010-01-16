
Message(STATUS ":: [Module] Gfx::Core")

LIBYUNI_CONFIG_LIB("gfx"        "yuni-static-gfx-core")

Set(SRC_APPLICATION_GFX
		application/gfx3d.h application/gfx3d.cpp)
source_group(Application FILES ${SRC_APPLICATION_GFX})

# Gfx
Set(SRC_GFX
		gfx/device.h gfx/device.cpp
		gfx/vertex.h gfx/triangle.h gfx/edge.h
		gfx/object3D.h gfx/object3D.cpp
		gfx/objectmodel.h gfx/scene.h gfx/scene.cpp
		gfx/skeleton.h gfx/mesh.h gfx/mesh.cpp
		gfx/implicitsurface.h gfx/implicitsurface.cpp gfx/implicitsurfmanager.h
		gfx/metaobject.h gfx/metaball.h  gfx/metaball.cpp  gfx/metabox.h
		gfx/boundingbox.h gfx/boundingbox.hxx
		gfx/polygonizer.h gfx/marchingcubes.h gfx/marchingcubes.cpp
		)
source_group(Gfx FILES ${SRC_GFX})




Add_Library(yuni-static-gfx-core STATIC
			yuni.h
			${SRC_GFX}
			${SRC_APPLICATION_GFX}
)
target_link_libraries(yuni-static-gfx-core yuni-static-core)


