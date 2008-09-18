
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(devices_00_monitors main.cpp)
target_link_libraries(devices_00_monitors ${YUNI_LIBRARIES})

