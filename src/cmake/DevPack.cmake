
#
# DevPacks Settings
#
SET(DevPackSourceFolder     "${CMAKE_CURRENT_SOURCE_DIR}/../devpacks")
SET(DevPackReceiptsFolder   "${CMAKE_CURRENT_SOURCE_DIR}/../devpacks/receipts")
SET(DevPackRepositoryURL    "http://devpacks.libyuni.org/")
SET(DevPackSourceURL        "http://devpacks.libyuni.org/downloads")
SET(DevPackPrefix           "yndevpack")






# Where is unzip ?
SET(DevPackSourceZIP)
IF(WIN32 AND NOT CMAKE_CROSSCOMPILING)
	Find_Program(DevPackSourceZIP NAMES "unzip.exe" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/../bin")
ELSE()
	Find_Program(DevPackSourceZIP NAMES "unzip")
ENDIF()
String(COMPARE EQUAL "${DevPackSourceZIP}" "DevPackSourceZIP-NOTFOUND" DevPackUnzipHasNotBeenFound)
IF(DevPackUnzipHasNotBeenFound)
	Message(FATAL_ERROR "The program 'unzip' has not been found. It is required to ")
EndIF()
IF(WIN32)
	YMESSAGE("unzip: ${DevPackSourceZIP}")
ENDIF()




SET(DEVPACK_OS					) # macos, windows, linux, sun
SET(DEVPACK_ARCH				) # i386, ppc
SET(DEVPACK_COMPILER  "unknown"	) # g++, msvc, mingw



IF(CMAKE_COMPILER_IS_GNUCXX)
	SET(DEVPACK_COMPILER "g++")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)
# Trying to find out the operating system
IF(WIN32)
	SET(DEVPACK_OS   "windows")
	SET(DEVPACK_ARCH "i386")
	IF(MINGW)
		SET(DEVPACK_COMPILER "mingw")
	ELSE(MINGW)
		SET(DEVPACK_COMPILER "msvc")
		IF(MSVC70)
			SET(DEVPACK_COMPILER "vs7")
		ENDIF(MSVC70)
		IF(MSVC80)
			SET(DEVPACK_COMPILER "vs8")
		ENDIF(MSVC80)
		IF(MSVC90)
			SET(DEVPACK_COMPILER "vs9")
		ENDIF(MSVC90)
	ENDIF(MINGW)
ELSE(WIN32)
	execute_process(COMMAND "uname" "-p" OUTPUT_VARIABLE UNAME_P OUTPUT_STRIP_TRAILING_WHITESPACE)
	String(TOLOWER "${UNAME_P}" UNAME_P)
	String(COMPARE EQUAL "${UNAME_P}" "i386" IsI386)
	String(COMPARE EQUAL "${UNAME_P}" "powerpc" IsPPC)
	IF(IsI386)
		SET(DEVPACK_ARCH "i386")
	ENDIF(IsI386)
	IF(IsPPC)
		SET(DEVPACK_ARCH "ppc")
	ENDIF(IsPPC)
ENDIF(WIN32)
IF(NOT DEVPACK_OS)
	String(TOLOWER "${CMAKE_SYSTEM_NAME}" DevPackSystemName)
	String(COMPARE EQUAL "${DevPackSystemName}" "linux" IsLinux)
	IF(IsLinux)
		SET(DEVPACK_OS "linux")
	ENDIF(IsLinux)
	String(COMPARE EQUAL "${DevPackSystemName}" "windows" IsWindows)
	IF(IsWindows)
		SET(DEVPACK_OS "windows")
	ENDIF(IsWindows)
	String(COMPARE EQUAL "${DevPackSystemName}" "freebsd" IsFreeBSD)
	IF(IsFreeBSD)
		SET(DEVPACK_OS "freebsd")
	ENDIF(IsFreeBSD)
	String(COMPARE EQUAL "${DevPackSystemName}" "darwin" IsDarwin)
	IF(IsDarwin)
		SET(DEVPACK_OS "macos")
	ENDIF(IsDarwin)
ENDIF(NOT DEVPACK_OS)
IF(NOT DEVPACK_ARCH)
	SET(DEVPACK_ARCH "i386")
ENDIF(NOT DEVPACK_ARCH)




MACRO(DEVPACK_LIST_CONTAINS var value)
	SET(${var})
	FOREACH (value2 ${ARGN})
		IF ("${value}" STREQUAL "${value2}")
			SET(${var} TRUE)
		ENDIF ("${value}" STREQUAL "${value2}")
	ENDFOREACH (value2)
ENDMACRO(DEVPACK_LIST_CONTAINS)


#
# Check if a DevPack is installed
#
MACRO(DEVPACK_IS_INSTALLED var dpname dpversion dprelease dpos dparch dpcompiler dptarget)

	# Specific to the given pack
	SET(DevPackFolder "${DevPackSourceFolder}/${dpname}")
	SET(DevPackShortFilename "${dpname}-${dpversion}-r${dprelease}-${dpos}-${dparch}-${dpcompiler}-${dptarget}")
	# File for informations about the pack
	SET(DevPackFileInfo "${DevPackFolder}/${DevPackPrefix}-${DevPackShortFilename}")
	# Title for this pack
	SET(DevPackTitle "DevPack: ${dpname} (${dpversion}-r${dprelease}, ${dpos}, ${dparch}, ${dpcompiler}, ${dptarget})")
	# Is this pack already available
	SET(var FALSE)
	SET(DevPackReady)

	# Trying to find the appropriate file
	File(GLOB FilesFound RELATIVE "${DevPackFolder}" "${DevPackFolder}/${DevPackPrefix}-*")
	DEVPACK_LIST_CONTAINS(Contains "${DevPackPrefix}-${DevPackShortFilename}" ${FilesFound})
	IF(Contains)
		File(STRINGS "${DevPackFileInfo}" DevPackInfo)
		List(FIND "${DevPackInfo}" "1" DevPackReady)
		DEVPACK_LIST_CONTAINS(DevPackReady "1" ${DevPackInfo})
		IF(NOT DevPackReady)
			DEVPACK_LIST_CONTAINS(DevPackReady "ok" ${DevPackInfo})
		ENDIF(NOT DevPackReady)
	ENDIF(Contains)

	If(DevPackReady)
		SET(${var} TRUE)
	EndIf(DevPackReady)

ENDMACRO(DEVPACK_IS_INSTALLED)




#
# Check if a DevPack is already avialable in the `receipts` folder
#
MACRO(DEVPACK_IS_IN_RECEIPTS var dpname dpversion dprelease dpos dparch dpcompiler dptarget)

	# Specific to the given pack
	SET(DevPackFolder "${DevPackSourceFolder}/${dpname}")
	SET(DevPackShortFilename "${dpname}-${dpversion}-r${dprelease}-${dpos}-${dparch}-${dpcompiler}-${dptarget}")
	# Is this pack already available
	SET(var FALSE)
	SET(DevPackReady)

	# Trying to find the appropriate file
	File(GLOB FilesFound RELATIVE "${DevPackReceiptsFolder}" "${DevPackReceiptsFolder}/${DevPackShortFilename}.zip")
	DEVPACK_LIST_CONTAINS(Contains "${DevPackShortFilename}.zip" ${FilesFound})
	IF(Contains)
		SET(${var} TRUE)
	ENDIF(Contains)

ENDMACRO(DEVPACK_IS_IN_RECEIPTS)






#
# Import settings from a DevPack
#
MACRO(DEVPACK_IMPORT dpname dpversion dprelease dpos dparch dpcompiler dptarget)

	# Specific to the given pack
	SET(DevPackFolder "${DevPackSourceFolder}/${dpname}")
	SET(DevPackShortFilename "${dpname}-${dpversion}-r${dprelease}-${dpos}-${dparch}-${dpcompiler}-${dptarget}")
	# File for informations about the pack
	SET(DevPackFileInfo "${DevPackFolder}/${DevPackPrefix}-${DevPackShortFilename}")
	SET(DevPackURL "${DevPackSourceURL}/${DevPackShortFilename}.zip")

	# Title for this pack
	SET(DevPackTitle "DevPack: ${dpname} (${dpversion}-r${dprelease}, ${dpos}, ${dparch}, ${dpcompiler}, ${dptarget})")
	# Is this pack already available
	SET(DevPackReady FALSE)

	DEVPACK_IS_INSTALLED(DevPackReady "${dpname}" "${dpversion}" "${dprelease}" "${dpos}" "${dparch}"
		"${dpcompiler}" "${dptarget}")

	IF(NOT DevPackReady)

		YMESSAGE("   ${DevPackTitle}: Missing")
		File(MAKE_DIRECTORY "${DevPackReceiptsFolder}")
		File(MAKE_DIRECTORY "${DevPackFolder}")
		Set(DevPackReceiptReady FALSE)

		DEVPACK_IS_IN_RECEIPTS(DevPackReceiptReady "${dpname}" "${dpversion}" "${dprelease}" "${dpos}" "${dparch}"
			"${dpcompiler}" "${dptarget}")
		IF(NOT DevPackReceiptReady)
			YMESSAGE("    . Downloading ${DevPackURL}")
			# Download the Pack
			File(DOWNLOAD "${DevPackURL}" "${DevPackReceiptsFolder}/${DevPackShortFilename}.zip"
					STATUS DevPackDwnlStatus)
			DEVPACK_IS_IN_RECEIPTS(DevPackReceiptReady "${dpname}" "${dpversion}" "${dprelease}" "${dpos}"
				"${dparch}" "${dpcompiler}" "${dptarget}")
			IF(NOT DevPackReceiptReady)
				YMESSAGE("    . !! The download has failed")
			EndIF(NOT DevPackReceiptReady)
		EndIF(NOT DevPackReceiptReady)

		IF(DevPackReceiptReady)
			# Execute `unzip`
			YMESSAGE("    . Extracting the receipt file")
			execute_process(COMMAND "${DevPackSourceZIP}"
					-u "${DevPackReceiptsFolder}/${DevPackShortFilename}.zip"
					-d "${DevPackFolder}"
					WORKING_DIRECTORY "${DevPackFolder}" OUTPUT_QUIET)
		EndIF(DevPackReceiptReady)

		DEVPACK_IS_INSTALLED(DevPackReady "${dpname}" "${dpversion}" "${dprelease}" "${dpos}" "${dparch}"
			"${dpcompiler}" "${dptarget}")

	Else()
		YMESSAGE("   ${DevPackTitle}")
	EndIf()

	IF(NOT DevPackReady)
		YMESSAGE("")
		YMESSAGE("[!!] The installation of the DevPack `${dpname}` has failed.")
		YMESSAGE("     You can download the DevPack from this url :")
		YMESSAGE("      `${DevPackURL}`")
		YMESSAGE("     And put it into the `receipts` folder :")
		YMESSAGE("      `${DevPackReceiptsFolder}`")
		YMESSAGE("")
		YMESSAGE("[!!] If the devpack is already available in the receipts folder and you still have")
		YMESSAGE("     issues, please manually remove it and try again.")
		YMESSAGE("     Please visit `${DevPackRepositoryURL}` for all devpacks.")
		YMESSAGE("")
		Message(FATAL_ERROR "Aborting now.")
	Else()
		SET(YUNI_CURRENT_DEVPACK_SOURCE_DIR "${DevPackFolder}/${dpversion}/r${dprelease}/${dparch}/${dpcompiler}")
		Include("${DevPackFolder}/${dpversion}/r${dprelease}/${dparch}/cmake/CMakeLists-${dpname}-${dpos}-${dpcompiler}-${dptarget}.cmake")
	EndIF()

ENDMACRO()






MACRO(DEVPACK_SMART_IMPORT dpname dpversion dprelease dptarget)
	# Import
	DEVPACK_IMPORT("${dpname}" "${dpversion}" "${dprelease}" "${DEVPACK_OS}"
		"${DEVPACK_ARCH}" "${DEVPACK_COMPILER}" "${dptarget}")
ENDMACRO(DEVPACK_SMART_IMPORT)


