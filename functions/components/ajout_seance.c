#include "../sql/sqlite3.h"
#include "../header/header.c"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

static int callback_select_id(void *data, int argc, char **argv, char **azColName);
static int callback_select_count(void *data, int argc, char **argv, char **azColName);

/// @brief
/// @param db
/// @param film
/// @param nb
void ajout_seance(sqlite3 *db, char *film, int nb)
{
    // Connexion à la base de données
    int rc = sqlite3_open("event.db", &db);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Erreur lors de l'ouverture de la base de données : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Get the current date
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char date[11];
    sprintf(date, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    // step un
    char query[200];
    int id_jour = 0;
    sprintf(query, "SELECT id FROM jours WHERE date='%s'", date);
    int exist = sqlite3_exec(db, query, callback_select_id, &id_jour, NULL);
    if (exist != SQLITE_OK)
    {
        fprintf(stderr, "Erreur lors de la récupération de l'id du jour : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // step deux
    int nb_seances = 0;
    sprintf(query, "SELECT COUNT(*) FROM seances WHERE idjour =%d", id_jour);
    int count = sqlite3_exec(db, query, callback_select_count, &nb_seances, NULL);
    if (count != SQLITE_OK)
    {
        fprintf(stderr, "Erreur lors de la récupération du nombre de séances : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Ferme la connexion à la base de données
    sqlite3_close(db);

    // step trois
    printf("%d\n", exist);
    printf("%d\n", count);
    printf("%d\n", id_jour);
    printf("%d\n", nb_seances);
    action(exist, count, id_jour, nb_seances, film, nb);
}

static int callback_select_id(void *data, int argc, char **argv, char **azColName)
{
    int *id_jour = (int *)data;
    if (argc > 0 && argv[0] != NULL)
    {
        *id_jour = atoi(argv[0]);
    }
    return 0;
}

static int callback_select_count(void *data, int argc, char **argv, char **azColName)
{
    int *nb_seances = (int *)data;
    if (argc > 0 && argv[0] != NULL)
    {
        *nb_seances = atoi(argv[0]);
    }
    return 0;
}
