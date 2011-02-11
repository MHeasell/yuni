
YMESSAGE(":: [Module] Markdown  (EXPERIMENTAL, FOR ADVANCED USERS ONLY)")

LIBYUNI_CONFIG_LIB("both" "markdown"      "yuni-static-extra-markdown")

LIBYUNI_CONFIG_DEPENDENCY("markdown" "core") # core is required

add_definitions("-DYUNI_MODULE_EXTRA_MARKDOWN")


list(APPEND SRC_MARKDOWN
	extra/markdown/reader.h
	extra/markdown/reader.hxx
	extra/markdown/reader.cpp
	extra/markdown/data.h
	extra/markdown/data.cpp
	extra/markdown/node.h
	extra/markdown/signature.h

	# HTML
	extra/markdown/renderer/html.h
	extra/markdown/renderer/html.cpp
)



add_library(yuni-static-extra-markdown STATIC ${SRC_MARKDOWN})

