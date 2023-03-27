#include "../header/header.c"
#include "../sql/sqlite3.h"
#include <stdio.h>
#include <time.h>

#define DB_PATH "event.db"

/// @brief
/// @param film
/// @param nb
void add_one(char *film, int nb);
/// @brief
/// @param film
/// @param nb
void add_two(char *film, int nb);

/// @brief
/// @param db
/// @param film
/// @param nb
void ajout_seance(char *film, int nb)
{
    char *zErrMsg;
    int rc;
    sqlite3 *db;
    time_t now;
    struct tm *t;
    char date[11];
    sqlite3_stmt *stmt;
    char *sql;
    int jour_id;

    zErrMsg = 0;
    // Connexion à la base de données
    if (sqlite3_open(DB_PATH, &db) != SQLITE_OK)
    {
        fprintf(stderr, "Erreur lors de la connexion à la base de données : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    // Get the current date
    now = time(NULL);
    t = localtime(&now);
    strftime(date, sizeof(date), "%Y-%m-%d", t);

    // Check if the current date is already in the jours table
    sql = "SELECT id FROM jours WHERE date = ?";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, date, -1, SQLITE_TRANSIENT);
    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW)
    {
        printf("❌ 2");
        // The current date is already in the jours table, check the number of seances
        jour_id = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        sql = "SELECT COUNT(*) FROM seances WHERE idjour = ?";
        sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, jour_id);
        rc = sqlite3_step(stmt);
        // nb_seances = sqlite3_column_int(stmt, 0);

        if (rc == SQLITE_ROW)
        {
            printf("❌ 3");

            int nb_seances = sqlite3_column_int(stmt, 0);
            sqlite3_close_v2(db);
            sqlite3_finalize(stmt);
            
            if (nb_seances >= 4)
            {
                printf("Erreur : le nombre maximum de séances a été atteint pour le jour %s.\n", date);
                return;
            }
            else
            {
                // sqlite3_close(db);

                if (sqlite3_db_handle(stmt) != NULL)
                {
                    printf("La connexion avec la base de données est ouverte.\n");
                }
                else
                {
                    printf("La connexion avec la base de données est fermée.\n");
                }
                add_one(film, nb);
            }
        }
    }
    else
    {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        add_two(film, nb);
    }
}

void add_one(char *film, int nb)
{
    sqlite3 *db1;
    char date[11];
    sqlite3_stmt *stmt;
    char *sql;
    int rc;
    int jour_id;

    // Connexion à la base de données
    if (sqlite3_open(DB_PATH, &db1) != SQLITE_OK)
    {
        fprintf(stderr, "Erreur lors de la connexion à la base de données : %s\n", sqlite3_errmsg(db1));
        sqlite3_close(db1);
        return;
    }

    sql = "INSERT INTO seances (idjour, film, nbplace) VALUES (?, ?, ?) ";
    sqlite3_prepare_v2(db1, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, jour_id);
    sqlite3_bind_text(stmt, 2, film, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, nb);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        // printf("Erreur : impossible d'ajouter la séance pour le jour 1 %s.\n", date);
        printf("Erreur SQLite : %s\n", sqlite3_errmsg(db1));
    }
    else
    {
        printf("Séance ajoutée avec succès pour le jour %s.\n", date);
    }
}

void add_two(char *film, int nb)
{
    sqlite3 *db;
    char date[11];
    sqlite3_stmt *stmt;
    char *sql;
    int rc;
    int jour_id;

    // Connexion à la base de données
    if (sqlite3_open(DB_PATH, &db) != SQLITE_OK)
    {
        fprintf(stderr, "Erreur lors de la connexion à la base de données : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sql = "INSERT INTO jours (date) VALUES (?)";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, date, -1, SQLITE_TRANSIENT);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        printf("Erreur : impossible d'ajouter le jour %s.\n", date);
    }
    else
    {
        printf("Jour ajouté avec succès : %s\n", date);
    }
    sqlite3_finalize(stmt);
    sqlite3_finalize(stmt);

    sqlite3_finalize(stmt);

    sql = "INSERT INTO seances (idjour, film, nb) VALUES (?, ?, ?)";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, sqlite3_last_insert_rowid(db));
    sqlite3_bind_text(stmt, 2, film, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, nb);
    rc = sqlite3_step(stmt);
    printf("Nouvelle date ajoutée avec succès avec une première séance.\n");
}
