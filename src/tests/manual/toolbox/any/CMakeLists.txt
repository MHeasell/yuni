Message(STATUS "Test: Toolbox/Any")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(test_toolbox_any_00 test_00.cpp)
target_link_libraries(test_toolbox_any_00 ${YUNI_STATIC_CORE})
