#include "../sql/sqlite3.h"
#include "../header/header.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int event_list(sqlite3 *db)
{
    // Ouvre la base de données event.db
    sqlite3_open("event.db", &db);

    // Récupère les données de la table "event"
    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM events";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    // Affiche les données récupérées
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *c1 = sqlite3_column_text(stmt, 1);
        const unsigned char *c2 = sqlite3_column_text(stmt, 2);
        const unsigned char *c3 = sqlite3_column_text(stmt, 3);
        const unsigned char *c4 = sqlite3_column_text(stmt, 4);

        printf("ID: %d, Nom : %s, Type : %s, Date : %s, Nombre de Place : %s\n", id, c1, c2, c3, c4);
    }

    // Libère les ressources utilisées par la requête
    sqlite3_finalize(stmt);

    // Ferme la base de données
    sqlite3_close(db);
}