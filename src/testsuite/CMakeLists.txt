

Set(YuniTestCase_LastExe "")
Set(YuniTestCase_LastID  "")
Set(YuniTestCase_Code  "")
Set(YuniTestCase_ExeExtension "")

# TODO For Visual Studio ? MinGW ?
IF(MSVC)
	Set(YuniTestCaseMake "cl.exe")
ELSE(MSVC)
	IF(MINGW OR MSYS OR CYGWIN)
		Set(YuniTestCaseMake "mingw32-make")
	ELSE(MINGW OR MSYS OR CYGWIN)
		Set(YuniTestCaseMake "make")
	ENDIF(MINGW OR MSYS OR CYGWIN)
ENDIF(MSVC)
IF(WIN32)
	Set(YuniTestCase_ExeExtension ".exe")
ENDIF(WIN32)


add_custom_target(test)
add_custom_target(test_html DEPENDS test)


Set(YuniTestCaseOutput "${CMAKE_CURRENT_SOURCE_DIR}/results/htdocs/${YUNI_VERSION_REV}")
Set(YuniTestCaseRubyInclude "${CMAKE_CURRENT_SOURCE_DIR}/../tools/testsuite")


MACRO(YUNITESTCASE_BEGIN exe settings)
	String(REPLACE "_" "." ID "${exe}")
	Set(YuniTestCase_LastID "${ID}")
	Set(YuniTestCase_LastExe "${exe}")
	Set(YuniTestCase_RubySettings "${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/testcase_${ID}.rb")
	Set(YuniTestCase_Code "
	${settings}
	options.identifier = '${ID}'
	options.report = '${CMAKE_CURRENT_SOURCE_DIR}/testcase_${ID}.xml'
	options.path = '${CMAKE_CURRENT_SOURCE_DIR}'\n
	options.output = '${YuniTestCaseOutput}'
	"
	)
ENDMACRO(YUNITESTCASE_BEGIN)



MACRO(YUNITESTCASE_SOURCE)
	ADD_EXECUTABLE(test_${YuniTestCase_LastExe} ${ARGV})
	Set(YuniTestCase_Code "${YuniTestCase_Code} options.program = '${CMAKE_CURRENT_SOURCE_DIR}/test_${YuniTestCase_LastExe}${YuniTestCase_ExeExtension}'\n")
	Set(YuniTestCase_Code "${YuniTestCase_Code} options.make = '${YuniTestCaseMake} test_${YuniTestCase_LastExe}'\n")
	target_link_libraries(test_${YuniTestCase_LastExe} yuni-static-tests)
ENDMACRO(YUNITESTCASE_SOURCE)



MACRO(YUNITESTCASE_LINK)
	target_link_libraries(test_${YuniTestCase_LastExe} ${ARGV})
ENDMACRO(YUNITESTCASE_LINK)


MACRO(YUNITESTCASE_END)
	Set(YuniTestCase_RubySettings "${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/testcase_${YuniTestCase_LastID}.rb")
	FILE(WRITE "${YuniTestCase_RubySettings}" "${YuniTestCase_Code}")

	ADD_CUSTOM_COMMAND(OUTPUT "testcase_${YuniTestCase_LastID}.xml"
		COMMAND ruby ARGS
			"-I${YuniTestCaseRubyInclude}"
			-W0 "${PROJECT_SOURCE_DIR}/tools/testsuite/testcase.rb"
			"${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/testcase_${YuniTestCase_LastID}.rb"
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
		)
	ADD_CUSTOM_TARGET(testcase_${YuniTestCase_LastExe} SOURCES "testcase_${YuniTestCase_LastID}.xml")
	add_dependencies(test testcase_${YuniTestCase_LastExe})
	set_property(GLOBAL APPEND PROPERTY YuniTestCaseListCount 1)
	set_property(GLOBAL APPEND PROPERTY YuniTestCaseList "${CMAKE_CURRENT_SOURCE_DIR}/testcase_${YuniTestCase_LastExe}${YuniTestCase_ExeExtension}.xml")
ENDMACRO(YUNITESTCASE_END)



Include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/CommonSettings.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/Modules.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/FindYuni.cmake")



set_property(GLOBAL PROPERTY YuniTestCaseList) 
set_property(GLOBAL PROPERTY YuniTestCaseListCount) 
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/..")







#
# Adding Testcases
#
Add_SubDirectory(automated)





get_property(YnList GLOBAL PROPERTY YuniTestCaseListCount)
List(LENGTH YnList YnListCount)

Message(STATUS "Testcase count: ${YnListCount}")

get_property(YnList GLOBAL PROPERTY YuniTestCaseList)
#FOREACH(LIB ${YnList})
#	Message(STATUS "--------- ${LIB}")
#ENDFOREACH(LIB ${YnList})

