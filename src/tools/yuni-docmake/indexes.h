#ifndef __YUNI_DOCMAKE_INDEXES_H__
# define __YUNI_DOCMAKE_INDEXES_H__

# include <yuni/yuni.h>
# include <yuni/core/string.h>
# include "article.h"


namespace DocIndex
{


	bool Open(const Yuni::String& folder);

	void Close();

	void Write(const ArticleData& article);


	void RemoveNonExistingEntries(const Yuni::String& htdocs);

	void Vacuum();


	bool AppendArticleTitleFromPath(Yuni::String& out, const Yuni::String& path);


	void BuildDirectoryIndex(Yuni::String& out, const Yuni::String& path);


} // namespace DocIndex

#endif // __YUNI_DOCMAKE_INDEXES_H__
