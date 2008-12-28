
Message(STATUS "Sample: SmartPtr / Simple use of a smartptr")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(sharedptr_00_sharedptr main.cpp)
target_link_libraries(sharedptr_00_sharedptr ${YUNI_STATIC_CORE})

