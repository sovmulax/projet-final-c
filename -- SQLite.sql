-- SQLite

CREATE TABLE events(Id INTEGER PRIMARY KEY, nom TEXT, type INTEGER, date TEXT, nbplace INTEGER);
CREATE TABLE types(Id INTEGER PRIMARY KEY, intitule TEXT);
CREATE TABLE menus(Id INTEGER PRIMARY KEY, idevent INTEGER, element TEXT);
CREATE TABLE billets(Id INTEGER PRIMARY KEY, idevent INTEGER, idseance INTEGER);
CREATE TABLE jours(Id INTEGER PRIMARY KEY, date TEXT UNIQUE);
CREATE TABLE seances(Id INTEGER PRIMARY KEY, idjour INTEGER, film TEXT, nbplace INTEGER);

SELECT sum(nbplace) as sum, type FROM events GROUP by type

DELETE FROM jours where id = 3