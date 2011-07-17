#ifndef __YUNI_DOCMAKE_ARTICLE_H__
# define __YUNI_DOCMAKE_ARTICLE_H__

# include <yuni/yuni.h>
# include <yuni/core/string.h>
# include <deque>
# include <set>
# include <map>


	class ArticleData
	{
	public:
		typedef std::deque<float>  CoeffStack;
		typedef Yuni::CustomString<32,false>  Tag;
		typedef std::set<Tag>  TagSet;
		typedef Yuni::CustomString<32,false>  Word;

		class WordStat
		{
		public:
			WordStat()
				:coeff(0.f), count(0)
			{}
			float coeff;
			unsigned int count;
		};

		typedef std::map<Word, WordStat>  WordCount;

		enum State
		{
			stNone = 0,
			stTitle,
		};


	public:
		ArticleData();

		void reset();

	public:
		//! The original XML file
		Yuni::String originalFilename;
		//! Relative filename
		Yuni::String relativeFilename;
		//! The target filename within the htdocs folder
		Yuni::String htdocsFilename;

		//!
		TagSet  allowedTagsInParagraph;
		//! The current coefficient
		float coeff;
		//! Title of the page
		Yuni::String title;

		//! A non empty value to force the display of the access path
		Yuni::String accessPath;

		//! An error has occured
		bool error;

		//! Order
		unsigned int order;

		//! Directory index
		Yuni::String directoryIndex;
		//! Flag to display the TOC (Table Of Content)
		bool showTOC;
		//! Flag to display quick links (on the left)
		bool showQuickLinks;
		//! Flag to display the page history
		bool showHistory;

		//! SEO
		WordCount wordCount;
		//! Tags
		TagSet tags;

	}; // class ArticleData




#endif // __YUNI_DOCMAKE_ARTICLE_H__
