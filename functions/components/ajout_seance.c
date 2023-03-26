#include "../sql/sqlite3.h"
#include "../header/header.c"
#include <stdio.h>
#include <time.h>

void ajout_seance(sqlite3 *db, const char *film, int nb)
{
    char *zErrMsg = 0;
    int rc;

    // Ouvre la base de données event.db
    sqlite3_open("event.db", &db);

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

    if (rc == SQLITE_ROW)
    {
        // The current date is already in the jours table, check the number of seances
        int jour_id = sqlite3_column_int(stmt, 0);

        sqlite3_finalize(stmt);

        sql = "SELECT COUNT(*) FROM seances WHERE jour_id = ?";
        sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, jour_id);
        rc = sqlite3_step(stmt);

        if (rc == SQLITE_ROW)
        {
            int nb_seances = sqlite3_column_int(stmt, 0);
            if (nb_seances >= 4)
            {
                printf("Erreur : le nombre maximum de séances a été atteint pour le jour %s.\n", date);
                return;
            }
            else
            {
                // Insert a new seance for the current jour
                sqlite3_finalize(stmt);

                sql = "INSERT INTO seances (jour_id, film, nbplace) VALUES (?, ?, ?)";
                sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
                sqlite3_bind_int(stmt, 1, jour_id);
                sqlite3_bind_text(stmt, 2, film, -1, SQLITE_TRANSIENT);
                sqlite3_bind_int(stmt, 3, nb);
                rc = sqlite3_step(stmt);

                if (rc != SQLITE_DONE)
                {
                    printf("Erreur : impossible d'ajouter la séance pour le jour %s.\n", date);
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

        sql = "INSERT INTO seances (jour_id, film, nb) VALUES (?, ?, ?)";
        sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, sqlite3_last_insert_rowid(db));
        sqlite3_bind_text(stmt, 2, film, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 3, nb);
        rc = sqlite3_step(stmt);
        printf("Nouvelle date ajoutée avec succès avec une première séance.\n");
    }
}
