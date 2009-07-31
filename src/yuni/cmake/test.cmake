
Message(STATUS "[Module] Tests")

Set(SRC_TESTS
		test/test.h  test/checkpoint.h test/checkpoint.cpp
		)
source_group(Tests FILES ${SRC_TESTS})



Add_Library(yuni-static-tests STATIC
			yuni.h
			${SRC_TESTS}
)


