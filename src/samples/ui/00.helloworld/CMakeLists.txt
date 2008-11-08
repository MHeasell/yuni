
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(ui_00_helloworld main.cpp)
target_link_libraries(ui_00_helloworld ${YUNI_LIBRARIES})

