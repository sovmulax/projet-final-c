#include "../sql/sqlite3.h"
#include "../header/header.c"
#include <stdio.h>
#include <time.h>

/// @brief
/// @param exist
/// @param count
/// @param id_jour
/// @param seance
/// @param film
/// @param nb
void action(int exist, int count, int id_jour, int seance, char *film, int nb)
{
    // Connexion à la base de données
    sqlite3 *db;
    sqlite3_open("event.db", &db);

    sqlite3_stmt *stmt;
    char query[200];

    if (exist == SQLITE_ROW)
    {
        if (count == SQLITE_ROW)
        {
            /* si le jour existe déja */
            if (seance >= 4)
            {
                printf("Erreur : le nombre maximum de séances a été atteint pour le jour .\n");
                return;
            }
            else
            {
                sprintf(query, "INSERT INTO seances(idjour, film, nbplace) VALUES (%d, '%s', %d)", id_jour, film, seance);
                int rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
                rc = sqlite3_step(stmt);
                if (rc != SQLITE_DONE)
                {
                    printf("Erreur SQLite : %s\n", sqlite3_errmsg(db));
                }
                else
                {
                    printf("Séance ajoutée avec succès pour le jour.\n");
                }

                sqlite3_finalize(stmt);
                sqlite3_close(db);
            }
        }
    }
    else
    {
        /* si le jour n'existe pas */

        sprintf(query, "INSERT INTO seances(idjour, film, nbplace) VALUES (%d, %s, %d)", id_jour, film, seance);
        int rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
        rc = sqlite3_step(stmt);

        if (rc != SQLITE_DONE)
        {
            printf("Erreur : impossible d'ajouter le jour .\n");
        }
        else
        {
            printf("Jour ajouté avec succès : \n");
        }

        sqlite3_finalize(stmt);

        sprintf(query, "INSERT INTO seances(idjour, film, nbplace) VALUES (%lld, %s, %d)", sqlite3_last_insert_rowid(db), film, seance);
        rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
        rc = sqlite3_step(stmt);

        if (rc != SQLITE_DONE)
        {
            printf("Erreur : impossible d'ajouter le jour .\n");
        }
        else
        {
            printf("Nouvelle date ajoutée avec succès avec une première séance.\n");
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }
}