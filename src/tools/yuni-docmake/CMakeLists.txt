
YMESSAGE("")
YMESSAGE_BOLD("yuni-docmake")
YMESSAGE("")

include("${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/CommonSettings.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/Modules.cmake")


include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../..")
include_directories(tinyxml)

# Add definitions to help finding yuni parameters once installed (prefix + versioned path)
add_definitions("-DYUNI_VERSIONED_INST_PATH=\"${YUNI_VERSIONED_INST_PATH}\"")
add_definitions("-DYUNI_INSTALL_PREFIX=\"${CMAKE_INSTALL_PREFIX}\"")
add_definitions("-DYUNI_SOURCE_TREE=\"${YUNI_SOURCE_TREE}\"")


# Writing index-db.hxx
file(STRINGS index-db.sql INDEX_DB)
file(STRINGS index-db-cleanup.sql INDEX_DB_CLEANUP)
set(HXX_FILE "\n\n")
set(HXX_FILE "${HXX_FILE}namespace DocIndex\n")
set(HXX_FILE "${HXX_FILE}{\n")
set(HXX_FILE "${HXX_FILE}namespace // anonymous\n")
set(HXX_FILE "${HXX_FILE}{\n")
set(HXX_FILE "${HXX_FILE}\n\ttemplate<class StringT>\n")
set(HXX_FILE "${HXX_FILE}\tstatic void PrepareSQLScript(StringT& out)\n")
set(HXX_FILE "${HXX_FILE}\t{\n")
set(HXX_FILE "${HXX_FILE}\t\tout.clear()\n")
foreach(l ${INDEX_DB})
	string(REPLACE "\"" "\\\"" sline "${l}")
	set(HXX_FILE "${HXX_FILE}\t\t\t<< \"${sline}\\n\"\n")
endforeach()
set(HXX_FILE "${HXX_FILE}\t\t\t;\n")
set(HXX_FILE "${HXX_FILE}\t}\n\n\n")

set(HXX_FILE "${HXX_FILE}\n\ttemplate<class StringT>\n")
set(HXX_FILE "${HXX_FILE}\tstatic void PrepareSQLScriptCleanup(StringT& out)\n")
set(HXX_FILE "${HXX_FILE}\t{\n")
set(HXX_FILE "${HXX_FILE}\t\tout.clear()\n")
foreach(l ${INDEX_DB_CLEANUP})
	string(REPLACE "\"" "\\\"" sline "${l}")
	set(HXX_FILE "${HXX_FILE}\t\t\t<< \"${sline}\\n\"\n")
endforeach()
set(HXX_FILE "${HXX_FILE}\t\t\t;\n")
set(HXX_FILE "${HXX_FILE}\t}\n\n\n\n")

set(HXX_FILE "${HXX_FILE}} // anonymous namespace\n")
set(HXX_FILE "${HXX_FILE}} // namespace DocIndex\n\n")
file(WRITE index-db.hxx "${HXX_FILE}")

# Writing index-db.hxx
file(STRINGS webpage.html WEBPAGE_HTML)
set(HXX_FILE "\n\n")
set(HXX_FILE "${HXX_FILE}namespace // anonymous\n")
set(HXX_FILE "${HXX_FILE}{\n")
set(HXX_FILE "${HXX_FILE}\n\ttemplate<class StringT>\n")
set(HXX_FILE "${HXX_FILE}\tstatic void PrepareWebPageHtml(StringT& out)\n")
set(HXX_FILE "${HXX_FILE}\t{\n")
set(HXX_FILE "${HXX_FILE}\t\tout.clear()\n")
foreach(l ${WEBPAGE_HTML})
	string(REPLACE "\"" "\\\"" sline "${l}")
	set(HXX_FILE "${HXX_FILE}\t\t\t<< \"${sline}\\n\"\n")
endforeach()
set(HXX_FILE "${HXX_FILE}\t\t\t;\n")
set(HXX_FILE "${HXX_FILE}\t}\n\n\n\n")

set(HXX_FILE "${HXX_FILE}} // anonymous namespace\n")
set(HXX_FILE "${HXX_FILE}\n\n")
file(WRITE webpage.hxx "${HXX_FILE}")




set(src
	sqlite/sqlite3.c
	sqlite/sqlite3.h
	sqlite/sqlite3ext.h
	article.h
	article.cpp
	make.h
	make.cpp
	job.h
	job.cpp
	job-writer.h
	job-writer.cpp
	logs.h
	logs.cpp
	find-all-source-files.cpp
	main.cpp
	indexes.h
	indexes.cpp
	index-db.hxx

	tinyxml/tinystr.cpp
	tinyxml/tinystr.h
	tinyxml/tinyxml.cpp
	tinyxml/tinyxml.h
	tinyxml/tinyxmlerror.cpp
	tinyxml/tinyxmlparser.cpp
	)

# Build the in-tree version of yuni-config.
add_executable(yuni-docmake ${src})

target_link_libraries(yuni-docmake  yuni-static-core)

if(UNIX AND NOT APPLE)
	# The DL library is required on Unixes for using SQlite
	target_link_libraries(yuni-docmake  dl)
endif()
