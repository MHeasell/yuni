
#
# Profile
#
Set(YUNI_PROFILE_NAME "Default")



#
# Target
#
# Uncomment the following line to override the build target
# Accepted values: `debug`, `release`
#Set(YUNI_TARGET  "release")


#
# Modules
#
# Uncomment the following line to override the module list
# Example : `gfx3d,scripts,-net`
# Note : `cmake -DMODULES=help` to have a list of all available modules
#Set(MODULES "gfx3d,scripts")



#
# Packages
#
# A module often requires one or more external packages (`lua` for example).
# Most of the time the system has its own package management utility, which will
# provide all needed and up-to-date packages (`lua`, `libxml`...).
# It is not always the case (Windows for example), so some pre-built packages (DevPacks)
# are available on http://devpacks.libyuni.org and can be automatically downloaded.
#
# Several modes can be given in the preferred order to find and use the appropriate package.
# If nothing suits your needs, it is possible to use the `custom` mode and to set
# the prefix path where the package can be found.
#
# Modes :
#    system  : Try to use the standard way to find the package provided by the system
#              Standard paths, System Frameworks (OS X)
#    custom  : Try to find the package from a custom prefix path
#              The variable `YUNI_DvP_<pkg>_PREFIX` must be set
#    macport : Try to find the package from a macport installation (Mac OS X)
#              (http://www.macports.org)
#    devpack : Download and use the pre-build package from `devpacks.libyuni.org`
#              This is the recommended way when the package is not available on the system
#
# Example :
# Use `lua` compiled by hand, installed in `/opt/lua` (/opt/lua/include and `/opt/lua/lib`) :
#   Set(YUNI_DvP_LUA_MODE custom)
#   Set(YUNI_DvP_LUA_PREFIX "/opt/lua")
#

# PThread (Yuni Core) [NOT IMPLEMENTED]
Set(YUNI_DvP_PTHREAD_MODE     system)

# Lua (+script,+lua)
Set(YUNI_DvP_LUA_MODE         devpack)



#
# Auto-Compile yuni-config from CMake
#
# Enable this option to automatically compile yuni-config from CMake
#
Set(YUNI_AUTO_COMPILE_YUNI_CONFIG  false)


#
# Special instructions sets
#
# Options:
#  auto  : To auto detect if these sets can be used
#  no    : To completely disable it
#  yes   : Try to use it event it may not compile
#
# MMX
Set(YUNI_PROFILE_MMX       "auto")
# 3D-NOW
Set(YUNI_PROFILE_3DNOW     "auto")
# SSE
Set(YUNI_PROFILE_SSE       "auto")
# SSE2 (if "SSE" enabled)
Set(YUNI_PROFILE_SSE2      "auto")
# SSE3 (if "SSE2" enabled)
Set(YUNI_PROFILE_SSE3      "auto")
# SSE4 (if "SSE3" enabled)
Set(YUNI_PROFILE_SSE4      "auto")
# SSE4a (if "SSE3" enabled)
Set(YUNI_PROFILE_SSE4a     "auto")
# SSE4.1 (if "SSE3" enabled)
Set(YUNI_PROFILE_SSE4_1    "auto")
# SSE4.2 (if "SSE3" enabled)
Set(YUNI_PROFILE_SSE4_2    "auto")







#
# C++ Flags
#
# !! For advanced users only : it may not a good idea to use your own CFlags
#    for compiling the Yuni library.
#
# Uncomment the following line to add some C++ compiler flags
#Set(YUNI_CXX_FLAGS_OVERRIDE_ADD_DEBUG          "-Wextra")
#Set(YUNI_CXX_FLAGS_OVERRIDE_ADD_RELEASE        "-Wextra")
#Set(YUNI_CXX_FLAGS_OVERRIDE_ADD_RELWITHDEBINFO "-Wextra")

# Uncomment the following line to override the C++ compiler flags
# This is not recommended.
#Set(YUNI_CXX_FLAGS_OVERRIDE_DEBUG          "-g -ggdb -Wall -Wextra")
#Set(YUNI_CXX_FLAGS_OVERRIDE_RELEASE        "-g -ggdb -Wall -Wextra")
#Set(YUNI_CXX_FLAGS_OVERRIDE_RELWITHDEBINFO "-g -ggdb -Wall -Wextra")



