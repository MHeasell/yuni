
#include "article.h"


ArticleData::ArticleData()
	:error(true)
{
	allowedTagsInParagraph.insert("a");
	allowedTagsInParagraph.insert("b");
	allowedTagsInParagraph.insert("i");
	allowedTagsInParagraph.insert("u");
	allowedTagsInParagraph.insert("br");
	allowedTagsInParagraph.insert("code");
	allowedTagsInParagraph.insert("sub");
	allowedTagsInParagraph.insert("sup");
	allowedTagsInParagraph.insert("big");
	allowedTagsInParagraph.insert("button");
	allowedTagsInParagraph.insert("em");
	allowedTagsInParagraph.insert("img");
	allowedTagsInParagraph.insert("input");
	allowedTagsInParagraph.insert("kbd");
	allowedTagsInParagraph.insert("small");
	allowedTagsInParagraph.insert("span");
	allowedTagsInParagraph.insert("strong");
	allowedTagsInParagraph.insert("textarea");
}


void ArticleData::reset()
{
	coeff = 1.0f;
	title.clear();
	error = false;
	order = (unsigned int) -1;
	directoryIndex.clear();
	tags.clear();
	showTOC = true;
	showHistory = true;
	showQuickLinks = true;
	accessPath.clear();
}


