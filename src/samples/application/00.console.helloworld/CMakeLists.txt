
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(appl_00_console main.cpp)
target_link_libraries(appl_00_console ${YUNI_LIBRARIES})

