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


	void RemoveNonExistingEntries();

	void Vacuum();


	bool AppendArticleTitleFromPath(Yuni::String& out, const Yuni::String& path);


	void BuildDirectoryIndex(Yuni::String& out, const Yuni::String& path);



	/*!
	** \brief Build a sitemap
	**
	** \see http://en.wikipedia.org/wiki/Site_map
	** \see http://en.wikipedia.org/wiki/Google_Sitemaps
	**
	** This method must be ran from the main thread
	*/
	void BuildSitemap();


} // namespace DocIndex

#endif // __YUNI_DOCMAKE_INDEXES_H__
