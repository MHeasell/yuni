
Message(STATUS "[Module] Algorithms")

# Devices
Set(SRC_ALGORITHMS
		algorithm/luhn.h algorithm/luhn.cpp algorithm/luhn.hxx
		)
source_group(Algorithms FILES ${SRC_ALGORITHMS})



Add_Library(yuni-static-algorithms STATIC
			yuni.h
			${SRC_ALGORITHMS}
)
target_link_libraries(yuni-static-algorithms yuni-static-core)


