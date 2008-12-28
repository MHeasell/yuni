
Message(STATUS "Sample: SmartPtr / With STL containers")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(sharedptr_01_vector main.cpp)
target_link_libraries(sharedptr_01_vector ${YUNI_STATIC_CORE})

