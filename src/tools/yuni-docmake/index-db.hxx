

namespace DocIndex
{
namespace // anonymous
{

	template<class StringT>
	static void PrepareSQLScript(StringT& out)
	{
		out.clear()
			<< "CREATE TABLE index_header (\n"
			<< "	version                INTEGER NOT NULL DEFAULT 1\n"
			<< ");\n"
			<< "CREATE TABLE articles (\n"
			<< "	id                     INTEGER PRIMARY KEY AUTOINCREMENT,\n"
			<< "	-- Psuedo index file\n"
			<< "	rel_path               TEXT NOT NULL,\n"
			<< "	html_href              TEXT NOT NULL UNIQUE,\n"
			<< "	title                  TEXT NOT NULL,\n"
			<< "	weight                 REAL NOT NULL DEFAULT 1.0,\n"
			<< "	parent_order           INTEGER NOT NULL DEFAULT 1000,\n"
			<< "	tag_count              INTEGER NOT NULL DEFAULT 0,\n"
			<< "	show_quick_links       INTEGER NOT NULL DEFAULT 1,\n"
			<< "	show_history           INTEGER NOT NULL DEFAULT 1,\n"
			<< "	show_toc               INTEGER NOT NULL DEFAULT 1,\n"
			<< "	modified               INTEGER NOT NULL DEFAULT 0,\n"
			<< "	parent                 TEXT NOT NULL,\n"
			<< "	force_access_path      TEXT DEFAULT NULL,\n"
			<< "	dir_index              TEXT DEFAULT NULL\n"
			<< ");\n"
			<< "CREATE INDEX ix_art_relpath ON articles(rel_path);\n"
			<< "CREATE INDEX ix_art_parent ON articles(parent);\n"
			<< "CREATE TABLE words (\n"
			<< "	id                     INTEGER PRIMARY KEY AUTOINCREMENT,\n"
			<< "	weight                 REAL NOT NULL DEFAULT 1.0,\n"
			<< "	word                   TEXT NOT NULL UNIQUE\n"
			<< ");\n"
			<< "CREATE TABLE words_per_article (\n"
			<< "	word_id                INTEGER NOT NULL REFERENCES words(id) ON DELETE CASCADE,\n"
			<< "	article_id             INTEGER NOT NULL REFERENCES articles(id) ON DELETE CASCADE,\n"
			<< "	weight                 REAL NOT NULL DEFAULT 1.0\n"
			<< ");\n"
			;
	}



	template<class StringT>
	static void PrepareSQLScriptCleanup(StringT& out)
	{
		out.clear()
			<< "DROP TABLE IF EXISTS index_header;\n"
			<< "DROP TABLE IF EXISTS articles;\n"
			<< "DROP TABLE IF EXISTS words;\n"
			<< "DROP TABLE IF EXISTS words_per_article;\n"
			;
	}



} // anonymous namespace
} // namespace DocIndex

