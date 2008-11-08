Project(Yuni-Framework)

CMake_minimum_required(VERSION 2.6)

# DevPacks utilities
Include("${CMAKE_CURRENT_SOURCE_DIR}/DevPack.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/DevPackStandardImports.cmake")


# Sub Directories
Add_SubDirectory(yuni)
Add_SubDirectory(tests)
Add_SubDirectory(samples)
