
YMESSAGE("")
YMESSAGE_BOLD("edln-make")

include("${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/CommonSettings.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/Modules.cmake")


include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../..")
include_directories(tinyxml)


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



add_library(edln-make-static-tinyxml STATIC
	tinyxml/tinystr.cpp
	tinyxml/tinystr.h
	tinyxml/tinyxml.cpp
	tinyxml/tinyxml.h
	tinyxml/tinyxmlerror.cpp
	tinyxml/tinyxmlparser.cpp
	)


add_executable(edln-make
	sqlite/sqlite3.c
	sqlite/sqlite3.h
	sqlite/sqlite3ext.h
	article.h
	article.cpp
	dictionary.h
	dictionary.cpp
	program.h
	program.cpp
	program-find-all-source-files.cpp
	job.h
	job.cpp
	job-writer.h
	job-writer.cpp
	logs.h
	logs.cpp
	main.cpp
	indexes.h
	indexes.cpp
	index-db.hxx
)

target_link_libraries(edln-make
	yuni-static-core
	edln-make-static-tinyxml)

if(UNIX AND NOT APPLE)
	# The DL library is required on Unixes for using SQlite
	target_link_libraries(edln-make  dl)
endif()



# ---
# --- dox2article
# ---

# Build the in-tree version of yuni-config.
add_executable(edln-dox2article
	dox2article/main.cpp
	dox2article/compound.h
	dox2article/compound.hxx
	dox2article/compound.cpp
	dox2article/options.h
	dox2article/options.cpp
	dox2article/read-index.h
	dox2article/read-index.cpp
	dox2article/job.h
	dox2article/job.cpp
	dox2article/job-compound-explorer.h
	dox2article/job-compound-explorer.cpp
	dox2article/job-compound-writer.h
	dox2article/job-compound-writer.cpp
	dox2article/indexes.h
	dox2article/indexes.cpp
	logs.h
	logs.cpp
)

target_link_libraries(edln-dox2article
	yuni-static-core
	edln-make-static-tinyxml)


