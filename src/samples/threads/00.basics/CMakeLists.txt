
ADD_EXECUTABLE(threads_00_basics main.cpp)
target_link_libraries(threads_00_basics "${YUNI_STATIC_LIB}"
	"${CMAKE_THREAD_LIBS_INIT}")

