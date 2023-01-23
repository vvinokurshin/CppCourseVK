\cd data

DROP TABLE IF EXISTS check_lists_items;
DROP TABLE IF EXISTS check_lists;
DROP TABLE IF EXISTS tags;
DROP TABLE IF EXISTS cards;
DROP TABLE IF EXISTS columns;
DROP TABLE IF EXISTS users2boards;
DROP TABLE IF EXISTS boards;
DROP TABLE IF EXISTS users;

CREATE TABLE IF NOT EXISTS users (
    id INT PRIMARY KEY GENERATED ALWAYS AS identity,
    username VARCHAR(30) UNIQUE NOT NULL,
    email VARCHAR(30) UNIQUE NOT NULL,
    password VARCHAR(30) NOT NULL,
    avatar VARCHAR(30) DEFAULT NULL
);

DROP TABLE IF EXISTS users_import;
CREATE TABLE IF NOT EXISTS users_import(doc json);
\copy users_import FROM 'users_tmp.json';
SELECT * FROM users_import;

INSERT INTO users (username, email, password)
SELECT doc->>'username', doc->>'email', doc->>'password'
FROM users_import;
	  
SELECT * FROM users;

CREATE TABLE IF NOT EXISTS boards (
    id INT PRIMARY KEY GENERATED ALWAYS AS identity,
    name VARCHAR(30) NOT NULL,
    caption VARCHAR(200) DEFAULT NULL,
    background VARCHAR(30) DEFAULT NULL
);


DROP TABLE IF EXISTS boards_import;
CREATE TABLE IF NOT EXISTS boards_import(doc json);
\copy boards_import FROM 'boards_tmp.json';
SELECT * FROM boards_import;

INSERT INTO boards (name, caption)
SELECT doc->>'name', doc->>'caption'
FROM boards_import;
	  
SELECT * FROM boards;

CREATE TABLE IF NOT EXISTS users2boards (
    user_id int NOT NULL REFERENCES users (id) ON DELETE CASCADE,
    board_id int NOT NULL REFERENCES boards (id) ON DELETE CASCADE
);

DROP TABLE IF EXISTS users2boards_import;
CREATE TABLE IF NOT EXISTS users2boards_import(doc json);
\copy users2boards_import FROM 'users2boards_tmp.json';
SELECT * FROM users2boards_import;

INSERT INTO users2boards (user_id, board_id)
SELECT (doc->>'user_id')::int, (doc->>'board_id')::int
FROM users2boards_import;

SELECT * FROM users2boards;

CREATE TABLE IF NOT EXISTS columns (
    id INT PRIMARY KEY GENERATED ALWAYS AS identity,
    name VARCHAR(30) NOT NULL,
    board_id int NOT NULL REFERENCES boards (id) ON DELETE CASCADE
);

DROP TABLE IF EXISTS columns_import;
CREATE TABLE IF NOT EXISTS columns_import(doc json);
\copy columns_import FROM 'columns_tmp.json';
SELECT * FROM columns_import;

INSERT INTO columns (name, board_id)
SELECT doc->>'name', (doc->>'board_id')::int
FROM columns_import;

SELECT * FROM columns;

CREATE TABLE IF NOT EXISTS cards (
    id INT PRIMARY KEY GENERATED ALWAYS AS identity,
    name VARCHAR(30) NOT NULL,
    caption VARCHAR(200) DEFAULT NULL,
    deadline date DEFAULT NULL,
    column_id int NOT NULL REFERENCES columns (id) ON DELETE CASCADE
);

DROP TABLE IF EXISTS cards_import;
CREATE TABLE IF NOT EXISTS cards_import(doc json);
\copy cards_import FROM 'cards_tmp.json';
SELECT * FROM cards_import;

INSERT INTO cards (name, caption, deadline, column_id)
SELECT doc->>'name', doc->>'caption', (doc->>'deadline')::date, (doc->>'column_id')::int
FROM cards_import;

SELECT * FROM cards;

CREATE TABLE IF NOT EXISTS tags (
    id INT PRIMARY KEY GENERATED ALWAYS AS identity,
    name VARCHAR(20) NOT NULL,
    color VARCHAR(30) NOT NULL,
    card_id int NOT NULL REFERENCES cards (id) ON DELETE CASCADE
);

DROP TABLE IF EXISTS tags_import;
CREATE TABLE IF NOT EXISTS tags_import(doc json);
\copy tags_import FROM 'tags_tmp.json';
SELECT * FROM tags_import;

INSERT INTO tags (name, color, card_id)
SELECT doc->>'name', doc->>'color', (doc->>'card_id')::int
FROM tags_import;

SELECT * FROM tags;

CREATE TABLE IF NOT EXISTS check_lists (
    id INT PRIMARY KEY GENERATED ALWAYS AS identity,
    name VARCHAR(20) NOT NULL,
    card_id int NOT NULL REFERENCES cards (id) ON DELETE CASCADE
);

DROP TABLE IF EXISTS check_lists_import;
CREATE TABLE IF NOT EXISTS check_lists_import(doc json);
\copy check_lists_import FROM 'check_lists_tmp.json';
SELECT * FROM check_lists_import;

INSERT INTO check_lists (name, card_id)
SELECT doc->>'name', (doc->>'card_id')::int
FROM check_lists_import;

SELECT * FROM check_lists;

CREATE TABLE IF NOT EXISTS check_lists_items (
    id INT PRIMARY KEY GENERATED ALWAYS AS identity,
    name VARCHAR(20) NOT NULL,
    is_checked bool DEFAULT false,
    check_list_id int NOT NULL REFERENCES check_lists (id) ON DELETE CASCADE
);

DROP TABLE IF EXISTS check_lists_items_import;
CREATE TABLE IF NOT EXISTS check_lists_items_import(doc json);
\copy check_lists_items_import FROM 'check_lists_items_tmp.json';
SELECT * FROM check_lists_items_import;

INSERT INTO check_lists_items (name, is_checked, check_list_id)
SELECT doc->>'name', (doc->>'is_checked')::bool, (doc->>'check_list_id')::int
FROM check_lists_items_import;

SELECT * FROM check_lists_items;
