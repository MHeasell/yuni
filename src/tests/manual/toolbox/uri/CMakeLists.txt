Message(STATUS "Test: Toolbox/URIs")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(test_toolbox_uri00 main.cpp)
target_link_libraries(test_toolbox_uri00 ${YUNI_STATIC_CORE} ${YUNI_STATIC_NET})
