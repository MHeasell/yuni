
find_package(Yuni COMPONENTS core net)
if(Yuni_FOUND)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Yuni_CXXFLAGS}")
	link_libraries("${Yuni_LIBS}")

	message(STATUS "Sample: Net / Simple REST Server")
	add_executable(net_00_simple-rest-server main.cpp)
endif(Yuni_FOUND)

