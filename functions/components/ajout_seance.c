#include "../sql/sqlite3.h"
#include "../header/header.c"
#include <stdio.h>
#include <time.h>

/// @brief
/// @param db
/// @param film
/// @param nb

#define DB_PATH "event.db"

void ajout_seance(char *film, int nb)
{
    char *zErrMsg = 0;
    int rc;

    // Connexion à la base de données
    sqlite3 *db;
    if (sqlite3_open(DB_PATH, &db) != SQLITE_OK)
    {
        fprintf(stderr, "Erreur lors de la connexion à la base de données : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Get the current date
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char date[11];
    strftime(date, sizeof(date), "%Y-%m-%d", t);

    // Check if the current date is already in the jours table
    sqlite3_stmt *stmt;
    char *sql = "SELECT id FROM jours WHERE date = ?";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, date, -1, SQLITE_TRANSIENT);
    rc = sqlite3_step(stmt);
    printf("❌ 1");
    if (rc == SQLITE_ROW)
    {
        printf("❌ 2");

        // The current date is already in the jours table, check the number of seances
        int jour_id = sqlite3_column_int(stmt, 0);

        sqlite3_finalize(stmt);

        sql = "SELECT COUNT(*) FROM seances WHERE idjour = ?";
        sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, jour_id);
        rc = sqlite3_step(stmt);

        if (rc == SQLITE_ROW)
        {
            printf("❌ 3");

            int nb_seances = sqlite3_column_int(stmt, 0);
            if (nb_seances >= 4)
            {
                printf("Erreur : le nombre maximum de séances a été atteint pour le jour %s.\n", date);
                return;
            }
            else
            {
                printf("❌ 4");

                // Insert a new seance for the current jour
                sqlite3_finalize(stmt);

                sql = "INSERT INTO seances(idjour, film, nbplace) VALUES (?, ?, ?)";
                sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
                sqlite3_bind_int(stmt, 1, jour_id);
                sqlite3_bind_text(stmt, 2, film, -1, SQLITE_TRANSIENT);
                sqlite3_bind_int(stmt, 3, nb);
                rc = sqlite3_step(stmt);

                if (rc != SQLITE_DONE)
                {
                    printf("Erreur : impossible d'ajouter la séance pour le jour %s.\n", date);
                    printf("Erreur SQLite : %s\n", sqlite3_errmsg(db));
                }
                else
                {
                    printf("Séance ajoutée avec succès pour le jour %s.\n", date);
                }
            }
        }
    }
    else
    {
        printf("❌ 5");

        // The current date is not in the jours table, insert a new jour and a new seance
        sqlite3_finalize(stmt);

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

        sql = "INSERT INTO seances (idjour, film, nb) VALUES (?, ?, ?)";
        sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, sqlite3_last_insert_rowid(db));
        sqlite3_bind_text(stmt, 2, film, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 3, nb);
        rc = sqlite3_step(stmt);
        printf("Nouvelle date ajoutée avec succès avec une première séance.\n");
    }
}
