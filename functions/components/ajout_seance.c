#include "../sql/sqlite3.h"
#include "../header/header.c"
#include <stdio.h>
#include <time.h>

/// @brief
/// @param db
/// @param film
/// @param nb
void ajout_seance(char *film, int nb)
{
    // Connexion à la base de données
    sqlite3 *db;
    sqlite3_open("event.db", &db);
    sqlite3_stmt *stmt;

    // Get the current date
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char date[11];
    sprintf(date, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    // step un
    char query[200];
    int id_jour = 0;
    sprintf(query, "SELECT id FROM jours WHERE date='%s'", date);
    int exist = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    exist = sqlite3_step(stmt);
    if (exist == SQLITE_ROW)
    {
        id_jour = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    // step deux
    int nb_seances = 0;
    sprintf(query, "SELECT COUNT(*) FROM seances WHERE idjour =%d", id_jour);
    int count = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    count = sqlite3_step(stmt);
    if (count == SQLITE_ROW)
    {
        nb_seances = sqlite3_column_int(stmt, 0);
    }

    // step trois
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    if (sqlite3_db_handle(stmt) != NULL)
    {
        printf("La stmt avec la base de données est ouverte.\n");
    }
    else
    {
        printf("La stmt avec la base de données est fermée.\n");
    }
    //action(exist, count, id_jour, nb_seances);
}