

CREATE TABLE index_header (
	version                INTEGER NOT NULL DEFAULT 1,
	--
	dirty                  INTEGER NOT NULL DEFAULT 0
);

CREATE TABLE articles (
	id                     INTEGER PRIMARY KEY AUTOINCREMENT,
	-- Psuedo index file
	lang                   TEXT NOT NULL DEFAULT 'en',
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
	directory_index        INTEGER NOT NULL DEFAULT 2, -- dicAll
	parent                 TEXT NOT NULL,
	force_access_path      TEXT DEFAULT NULL,
	dir_index              TEXT DEFAULT NULL
);

CREATE INDEX ix_art_relpath ON articles(rel_path);
CREATE INDEX ix_art_parent ON articles(parent);


CREATE TABLE toc (
	html_href              TEXT NOT NULL REFERENCES articles(html_href) ON DELETE CASCADE,
	indx                   INTEGER NOT NULL,
	lvl                    INTEGER NOT NULL,
	href_id                TEXT NOT NULL,
	caption                TEXT NOT NULL,
	PRIMARY KEY (html_href,indx)
);

CREATE TABLE terms (
	id                     INTEGER PRIMARY KEY AUTOINCREMENT,
	weight_user            REAL NOT NULL DEFAULT 1.0,
	weight_rel_others      REAL NOT NULL DEFAULT 1.0,
	-- The total weight
	weight                 REAL NOT NULL DEFAULT 1.0,
	term                   TEXT NOT NULL UNIQUE
);

CREATE TABLE terms_per_article (
	term_id                INTEGER NOT NULL REFERENCES terms(id) ON DELETE CASCADE,
	article_id             INTEGER NOT NULL REFERENCES articles(id) ON DELETE CASCADE,
	count_in_page          INTEGER NOT NULL DEFAULT 0,
	weight                 REAL NOT NULL DEFAULT 1.0
);


CREATE TABLE tags_per_article (
	article_id             INTEGER NOT NULL REFERENCES articles(id) ON DELETE CASCADE,
	tagname                TEXT NOT NULL,
	PRIMARY KEY (article_id, tagname)
);

CREATE TABLE deps (
	input                  TEXT NOT NULL PRIMARY KEY,
	html_href              TEXT NOT NULL,
	article_id             INTEGER NOT NULL REFERENCES articles(id) ON DELETE CASCADE
);

