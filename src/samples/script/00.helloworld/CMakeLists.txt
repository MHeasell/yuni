


find_package(Yuni COMPONENTS core lua)
if(Yuni_FOUND)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Yuni_CXXFLAGS}")
	link_libraries("${Yuni_LIBS}")

	message(STATUS "Sample: Script / A Simple Lua Hello World (not functional yet)")
	add_executable(script_00_helloworld main.cpp)
endif(Yuni_FOUND)

