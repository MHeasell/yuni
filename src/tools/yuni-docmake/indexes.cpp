
#include "indexes.h"
#include "sqlite/sqlite3.h"
#include <yuni/core/io/file.h>
#include "logs.h"
#include "index-db.hxx"
#include "make.h"


# define SEP Core::IO::Separator


using namespace Yuni;


namespace DocIndex
{



	namespace // anonymous
	{

		enum
		{
			dbVersion = 1,
		};

		static sqlite3* gDB = nullptr;


		static bool ResetDBIndex()
		{
			logs.info() << "the index database needs to be rebuilt";
			CustomString<2096> script;

			// Cleanup
			PrepareSQLScriptCleanup(script);
			sqlite3_exec(gDB, script.c_str(), NULL, NULL, NULL);

			// Create tables
			PrepareSQLScript(script);
			sqlite3_exec(gDB, script.c_str(), NULL, NULL, NULL);

			script.clear() << "INSERT INTO index_header (version) VALUES (" << (unsigned int) dbVersion << ");";
			sqlite3_exec(gDB, script.c_str(), NULL, NULL, NULL);
			return true;
		}


		static bool UsePragma()
		{
			// UTF-8
			if (SQLITE_OK != sqlite3_exec(gDB, "PRAGMA encoding = \"UTF-8\"; ", NULL, NULL, NULL))
			{
				logs.error() << "impossible to use the UTF8 encoding";
				return false;
			}
			// Foreign keys
			if (SQLITE_OK != sqlite3_exec(gDB, "PRAGMA foreign_keys = 1;", NULL, NULL, NULL))
			{
				logs.error() << "impossible to enable foreign keys";
				return false;
			}
			return true;
		}


		static bool CheckDBVersion()
		{
			// prepare the SQL statement from the command line
			sqlite3_stmt* stmt;
			if (SQLITE_OK != sqlite3_prepare_v2(gDB, "SELECT version FROM index_header", -1, &stmt, 0))
			{
				if (!ResetDBIndex())
					return false;
				if (SQLITE_OK != sqlite3_prepare_v2(gDB, "SELECT version FROM index_header", -1, &stmt, 0))
				{
					logs.error() << "impossible to retrieve information from the header";
					return false;
				}
			}
			if (SQLITE_ROW == sqlite3_step(stmt))
			{
				const StringAdapter version = (const char*) sqlite3_column_text(stmt, 0);
				if (version.to<int>() == dbVersion)
				{
					sqlite3_finalize(stmt);
					return true;
				}
			}
			sqlite3_finalize(stmt);
			return ResetDBIndex();
		}

	} // anonymous namespace



	bool Open(const String& folder)
	{
		if (gDB)
		{
			sqlite3_close(gDB);
			gDB = nullptr;
		}

		logs.info() << "opening index database";
		String uri;
		uri.clear() << folder << SEP << "yuni-doc-index";
		switch (sqlite3_open(uri.c_str(), &gDB))
		{
			case SQLITE_OK:
				{
					if (!UsePragma() || !CheckDBVersion())
					{
						Close();
						return false;
					}
					break;
				}
			case SQLITE_PERM:
				logs.error() << "not enough permissions to open " << uri;
				return false;
			case SQLITE_BUSY:
				logs.error() << "The index database is locked.";
				return false;
			case SQLITE_CORRUPT:
				logs.error() << "The index database is malformed";
				return false;
			case SQLITE_CANTOPEN:
				logs.error() << "Unable to open " << uri;
				return false;
			default:
				return false;
		}
		return true;
	}


	void Close()
	{
		if (gDB)
		{
			sqlite3_close(gDB);
			gDB = nullptr;
		}
	}


	void Vacuum()
	{
		if (gDB)
			sqlite3_exec(gDB, "VACUUM;", NULL, NULL, NULL);
	}


	void Write(const ArticleData& article)
	{
		if (!gDB)
			return;
		CustomString<256> query;

		query.clear() << "DELETE FROM articles WHERE rel_path = $1;";
		sqlite3_stmt* stmt;
		sqlite3_prepare_v2(gDB, query.c_str(), -1, &stmt, NULL);
		sqlite3_bind_text(stmt, 1, article.relativeFilename.c_str(), article.relativeFilename.size(), NULL);
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);

		String parent = article.htdocsFilename;
		{
			String::Size offset = parent.find_last_of("/\\");
			if (offset != String::npos)
				parent.resize(offset);
		}
		if (!parent)
			parent = "/";

		// Insert the new article
		{
			query.clear() << "INSERT INTO articles (parent_order, weight, show_quick_links, show_history, show_toc, modified, rel_path,html_href, title,parent)"
				<< " VALUES ($1,$2,$3,$4,$5,$6,$7,$8,$9,$10);";
			sqlite3_prepare_v2(gDB, query.c_str(), -1, &stmt, NULL);
			sqlite3_bind_int(stmt, 1, (int)article.order);
			sqlite3_bind_double(stmt, 2, article.coeff);
			sqlite3_bind_int(stmt, 3, (article.showQuickLinks ? 1 : 0));
			sqlite3_bind_int(stmt, 4, (article.showHistory ? 1 : 0)); // show history
			sqlite3_bind_int(stmt, 5, (article.showTOC ? 1 : 0)); // show toc
			sqlite3_bind_int64(stmt, 6, time(NULL));
			sqlite3_bind_text(stmt, 7, article.relativeFilename.c_str(), article.relativeFilename.size(), NULL);
			sqlite3_bind_text(stmt, 8, article.htdocsFilename.c_str(), article.htdocsFilename.size(), NULL);
			sqlite3_bind_text(stmt, 9, article.title.c_str(), article.title.size(), NULL);
			sqlite3_bind_text(stmt, 10, parent.c_str(), parent.size(), NULL);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		}
		if (article.accessPath.notEmpty())
		{
			query.clear() << "UPDATE articles SET force_access_path = $1 WHERE rel_path = $2;";
			sqlite3_prepare_v2(gDB, query.c_str(), -1, &stmt, NULL);
			sqlite3_bind_text(stmt, 1, article.accessPath.c_str(), article.accessPath.size(), NULL);
			sqlite3_bind_text(stmt, 2, article.relativeFilename.c_str(), article.relativeFilename.size(), NULL);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		}
		if (article.directoryIndex.notEmpty())
		{
			query.clear() << "UPDATE articles SET dir_index = $1 WHERE rel_path = $2;";
			sqlite3_prepare_v2(gDB, query.c_str(), -1, &stmt, NULL);
			sqlite3_bind_text(stmt, 1, article.directoryIndex.c_str(), article.directoryIndex.size(), NULL);
			sqlite3_bind_text(stmt, 2, article.relativeFilename.c_str(), article.relativeFilename.size(), NULL);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		}
	}


	void RemoveNonExistingEntries(const Yuni::String& htdocs)
	{
		if (!gDB)
			return;

		logs.info() << "Looking for deprecated entries in the database";

		CustomString<512> s = "DELETE FROM articles WHERE rel_path = \"\";";
		{
			sqlite3_stmt* stmt;
			sqlite3_prepare_v2(gDB, s.c_str(), -1, &stmt, NULL);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		}

		char** result;
		int rowCount, colCount;
		if (SQLITE_OK != sqlite3_get_table(gDB, "SELECT rel_path FROM articles", &result, &rowCount, &colCount, NULL))
			return;

		if (rowCount)
		{
			if (rowCount == 1)
				logs.info() << "1 article available in the index db";
			else
				logs.info() << rowCount << " articles available in the index db";
			unsigned int y = 1;
			for (unsigned int row = 0; row < (unsigned int) rowCount; ++row, ++y)
			{
				const StringAdapter relPath = result[y];
				s.clear() << htdocs << SEP << relPath;
				if (!Core::IO::File::Exists(s))
				{
					logs.info() << "The entry '" << relPath << "' is deprecated";
					s.clear() << "DELETE FROM articles WHERE rel_path = $1;";
					sqlite3_stmt* stmt;
					sqlite3_prepare_v2(gDB, s.c_str(), s.size(), &stmt, NULL);
					sqlite3_bind_text(stmt, 1, relPath.c_str(), relPath.size(), NULL);
					sqlite3_step(stmt);
					sqlite3_finalize(stmt);
				}
			}
		}

		sqlite3_free_table(result);
	}


	bool AppendArticleTitleFromPath(String& out, const String& path)
	{
		if (!gDB)
			return false;

		sqlite3_stmt* stmt;
		if (SQLITE_OK != sqlite3_prepare_v2(gDB, "SELECT title FROM articles WHERE html_href = $1", -1, &stmt, NULL))
			return false;
		sqlite3_bind_text(stmt, 1, path.c_str(), path.size(), NULL);
		if (SQLITE_ROW != sqlite3_step(stmt))
		{
			sqlite3_finalize(stmt);
			return false;
		}
		const StringAdapter title = (const char*) sqlite3_column_text(stmt, 0);
		if (!title)
		{
			sqlite3_finalize(stmt);
			return false;
		}
		out += title;
		sqlite3_finalize(stmt);
		return true;
	}




	namespace // anonymous
	{

		static void InternalBuildDirectoryIndex(String& out, const String& path, unsigned int level)
		{
			char** result;
			int rowCount, colCount;
			String query = "SELECT title, html_href FROM articles WHERE parent = \"";
			query << path << "\" ORDER BY parent_order ASC, title";
			if (SQLITE_OK != sqlite3_get_table(gDB, query.c_str(), &result, &rowCount, &colCount, NULL))
				return;

			if (!rowCount)
			{
				sqlite3_free_table(result);
				return;
			}

			if (!level)
			{
				for (unsigned int x = 0; x != level; ++x)
					out << '\t';
				out << "<div class=\"directoryindex\">Directory Index<br />\n";
			}
			for (unsigned int x = 0; x != level; ++x)
				out << '\t';
			if (level)
				out << "<li><ul>\n";
			else
				out << "<ul>\n";
			unsigned int y = 2;
			for (unsigned int row = 0; row < (unsigned int) rowCount; ++row)
			{
				const StringAdapter title = result[y++];
				const String href  = result[y++];

				for (unsigned int x = 0; x != level; ++x)
					out << '\t';
				out << "<li><a href=\"@{ROOT}/" << href;
				if (!Make::shortUrl)
					out << "/index.html";
				out << "\">" << title << "</a></li>\n";
				InternalBuildDirectoryIndex(out, href, level + 1);
			}

			sqlite3_free_table(result);

			for (unsigned int x = 0; x != level; ++x)
				out << '\t';
			if (level)
				out << "</ul></li>\n";
			else
				out << "</ul>\n";

			if (!level)
			{
				for (unsigned int x = 0; x != level; ++x)
					out << '\t';
				out << "</div>\n";
			}
		}

	} // anonymous namespace


	void BuildDirectoryIndex(String& out, const String& path)
	{
		out.clear();
		InternalBuildDirectoryIndex(out, path, 0);
	}




} // namespace DocIndex
