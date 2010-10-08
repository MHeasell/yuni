
YMESSAGE(":: [Module] Gfx::Core")

LIBYUNI_CONFIG_LIB("gfx"        "yuni-static-gfx-core")


# Gfx
set(SRC_GFX
		gfx/device.h gfx/device.cpp
		gfx/mesh/vertex.h gfx/mesh/triangle.h gfx/mesh/edge.h
		gfx/object3D.h gfx/object3D.cpp
		gfx/objectmodel.h gfx/scene.h gfx/scene.cpp
		gfx/mesh/skeleton.h gfx/mesh/mesh.h gfx/mesh/mesh.cpp
		gfx/mesh/implicitsurface.h gfx/mesh/implicitsurface.cpp
		gfx/mesh/implicitsurfmanager.h
		gfx/mesh/metaobject.h gfx/mesh/metaball.h
		gfx/mesh/metaball.cpp gfx/mesh/metabox.h
		gfx/boundingbox.h gfx/boundingbox.hxx
		gfx/mesh/polygonizer.h gfx/mesh/marchingcubes.h gfx/mesh/marchingcubes.cpp
		)
source_group(Gfx FILES ${SRC_GFX})




add_library(yuni-static-gfx-core STATIC
			yuni.h
			${SRC_GFX}
)

# Setting output path
set_target_properties(yuni-static-gfx-core PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY "${YUNI_OUTPUT_DIRECTORY}/lib")

# Installation
install(TARGETS yuni-static-gfx-core ARCHIVE DESTINATION lib/${YUNI_VERSIONED_INST_PATH})

# Install gfx-related headers
install(
	DIRECTORY gfx
	DESTINATION include/${YUNI_VERSIONED_INST_PATH}
	FILES_MATCHING
		PATTERN "*.h"
		PATTERN "*.hxx"
	PATTERN ".svn" EXCLUDE
	PATTERN "CMakeFiles" EXCLUDE
	PATTERN "cmake" EXCLUDE
)

target_link_libraries(yuni-static-gfx-core yuni-static-core)


