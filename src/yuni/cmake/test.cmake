
Message(STATUS ":: [Module] Tests")

LIBYUNI_CONFIG_LIB("tests"      "yuni-static-tests")


Set(SRC_TESTS
		test/test.h  test/checkpoint.h test/checkpoint.cpp)
source_group(Tests FILES ${SRC_TESTS})



Add_Library(yuni-static-tests STATIC  yuni.h ${SRC_TESTS})

