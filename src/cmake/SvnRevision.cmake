
if(WIN32 AND NOT CMAKE_CROSSCOMPILING)
	execute_process(COMMAND "subwcrev.exe" "${PROJECT_SOURCE_DIR}" OUTPUT_VARIABLE SVN_REV)
	string(REGEX REPLACE ".* committed at revision ([0-9]+).*" "\\1" SVN_REV "${SVN_REV}")
else(WIN32 AND NOT CMAKE_CROSSCOMPILING)
	execute_process(COMMAND "svnversion" "-n" "${PROJECT_SOURCE_DIR}" OUTPUT_VARIABLE SVN_REV)
	string(REGEX REPLACE "[0-9]+:" "" SVN_REV "${SVN_REV}")
	string(REPLACE "M" "" SVN_REV "${SVN_REV}")
endif(WIN32 AND NOT CMAKE_CROSSCOMPILING)

# Dealing with bad revision numbers
if(NOT "${SVN_REV}" GREATER 1)
	set(SVN_REV 1)
endif(NOT "${SVN_REV}" GREATER 1)

set(YUNI_VERSION_REV "${SVN_REV}")
YMESSAGE("Version : v${YUNI_VERSION_HI}.${YUNI_VERSION_LO}-${YUNI_TARGET} (Rev: ${YUNI_VERSION_REV})")

set(YUNI_VERSION_string "${YUNI_VERSION_HI}.${YUNI_VERSION_LO}.${YUNI_VERSION_REV}-${CMAKE_BUILD_TYPE}")
