
DELETE FROM index_header;
DELETE FROM articles;
DELETE FROM toc;
DELETE FROM terms;
DELETE FROM terms_per_article;


DROP TABLE IF EXISTS index_header;
DROP TABLE IF EXISTS articles;
DROP TABLE IF EXISTS toc;
DROP TABLE IF EXISTS terms;
DROP TABLE IF EXISTS terms_per_article;


VACUUM;
