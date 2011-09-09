#ifndef __YUNI_DOCMAKE_INDEXES_H__
# define __YUNI_DOCMAKE_INDEXES_H__

# include <yuni/yuni.h>
# include <yuni/core/string.h>
# include <yuni/io/file.h>
# include "article.h"
# include "dictionary.h"


namespace DocIndex
{


	bool Open(const Yuni::String& folder);

	void Close();

	void Write(const ArticleData& article);


	void RemoveNonExistingEntries();

	void Vacuum();


	bool AppendArticleTitleFromPath(Yuni::String& out, const Yuni::String& path);


	void BuildDirectoryIndex(Yuni::Clob& out, const Yuni::String& path);


	Yuni::sint64 ArticleLastModificationTimeFromCache(const ArticleData& article);


	/*!
	** \brief Build a sitemap
	**
	** \see http://en.wikipedia.org/wiki/Site_map
	** \see http://en.wikipedia.org/wiki/Google_Sitemaps
	**
	** This method must be ran from the main thread
	*/
	void BuildSitemap();


	/*!
	** \brief Register a term in the database
	**
	** \return The ID in the database
	*/
	int RegisterWordReference(const Dictionary::Word& term);

	void RegisterWordIDsForASingleArticle(int articleid, const int* termid,
		const int* countInArticle,
		const float* weights,
		unsigned int count);


	void UpdateAllSEOWeights();


	int FindArticleID(const Yuni::String& href);



	void BuildSEOTermReference(Yuni::Clob& data);

	void BuildSEOArticlesReference();


	void* DatabaseHandle();

} // namespace DocIndex

#endif // __YUNI_DOCMAKE_INDEXES_H__
