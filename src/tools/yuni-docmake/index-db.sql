

CREATE TABLE index_header (
	version                INTEGER NOT NULL DEFAULT 1
);

CREATE TABLE articles (
	id                     INTEGER PRIMARY KEY AUTOINCREMENT,
	-- Psuedo index file
	rel_path               TEXT NOT NULL,
	html_href              TEXT NOT NULL UNIQUE,
	title                  TEXT NOT NULL,
	weight                 REAL NOT NULL DEFAULT 1.0,
	parent_order           INTEGER NOT NULL DEFAULT 1000,
	tag_count              INTEGER NOT NULL DEFAULT 0,
	show_quick_links       INTEGER NOT NULL DEFAULT 1,
	show_history           INTEGER NOT NULL DEFAULT 1,
	show_toc               INTEGER NOT NULL DEFAULT 1,
	modified               INTEGER NOT NULL DEFAULT 0,
	parent                 TEXT NOT NULL,
	force_access_path      TEXT DEFAULT NULL,
	dir_index              TEXT DEFAULT NULL
);

CREATE INDEX ix_art_relpath ON articles(rel_path);
CREATE INDEX ix_art_parent ON articles(parent);


CREATE TABLE words (
	id                     INTEGER PRIMARY KEY AUTOINCREMENT,
	weight                 REAL NOT NULL DEFAULT 1.0,
	word                   TEXT NOT NULL UNIQUE
);

CREATE TABLE words_per_article (
	word_id                INTEGER NOT NULL REFERENCES words(id) ON DELETE CASCADE,
	article_id             INTEGER NOT NULL REFERENCES articles(id) ON DELETE CASCADE,
	weight                 REAL NOT NULL DEFAULT 1.0
);


