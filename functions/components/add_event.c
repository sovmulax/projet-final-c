#include "../sql/sqlite3.h"
#include "../header/header.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int add_event(sqlite3 *db, char a[200], char b[200], char c[200], char d[200], char e[200])
{
    // Ouvre la base de données event.db
    sqlite3_open("event.db", &db);

    // Insère les données dans la table "event"
    char *sql_event = "INSERT INTO events (nom, type, date, nbplace) VALUES (?, ?, ?, ?)";
    sqlite3_stmt *stmt_event;
    sqlite3_prepare_v2(db, sql_event, -1, &stmt_event, NULL);
    sqlite3_bind_text(stmt_event, 1, a, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt_event, 2, d, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt_event, 3, b, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt_event, 4, c, -1, SQLITE_STATIC);
    sqlite3_step(stmt_event);
    sqlite3_finalize(stmt_event);

    // Récupère l'id de la dernière insertion dans la table "event"
    int last_id = sqlite3_last_insert_rowid(db);

    // Insère les données dans la table "menu" en utilisant l'id récupéré
    char *sql_menu = "INSERT INTO menus (idevent, element) VALUES (?, ?)";
    sqlite3_stmt *stmt_menu;
    sqlite3_prepare_v2(db, sql_menu, -1, &stmt_menu, NULL);
    sqlite3_bind_int(stmt_menu, 1, last_id);
    sqlite3_bind_text(stmt_menu, 2, e, -1, SQLITE_STATIC);       // example data
    sqlite3_step(stmt_menu);
    sqlite3_finalize(stmt_menu);

    // Ferme la base de données
    sqlite3_close(db);
}