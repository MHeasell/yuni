
#
# The common paths for Yuni headers
#
Include_Directories("${PROJECT_SOURCE_DIR}/..")

#
# The Yuni library
#
IF(WIN32 AND MSVC)
    Set(YUNI_STATIC_LIB "${PROJECT_SOURCE_DIR}/../../bin/static/Debug/yuni.lib")
Else(WIN32 AND MSVC)
    Set(YUNI_STATIC_LIB "${PROJECT_SOURCE_DIR}/../../bin/static/libyuni.a")
EndIF(WIN32 AND MSVC)


