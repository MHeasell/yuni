
YMESSAGE("      Using Lua from Mac Ports in ${YUNI_MACPORTS_PREFIX}")

# Set internal include path
Set(YUNI_EXT_LUA_INCLUDE "${YUNI_MACPORTS_PREFIX}/include")

# Set Yuni-Config stuff
LIBYUNI_CONFIG_INCLUDE_PATH("lua" "${YUNI_MACPORTS_PREFIX}/include")
LIBYUNI_CONFIG_LIB_PATH("lua" "${YUNI_MACPORTS_PREFIX}/lib")
LIBYUNI_CONFIG_LIB("lua" "lua")

