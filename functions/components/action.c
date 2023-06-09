#include "../sql/sqlite3.h"
#include "../header/header.c"
#include <stdio.h>
#include <time.h>

/// @brief
/// @param exist
/// @param db
/// @param count
/// @param id_jour
/// @param seance
/// @param film
/// @param nb
void action(sqlite3 *db, int exist, int count, int id_jour, int seance, char *film, int nb)
{
    // Connexion à la base de données
    int rc = sqlite3_open("event.db", &db);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Erreur lors de l'ouverture de la base de données : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char date[11];
    sprintf(date, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    char query[200];

    if (exist == 0 && id_jour != 0)
    {
        if (count == 0)
        {
            /* si le jour existe déja */
            if (seance >= 4)
            {
                printf("❌ : le nombre maximum de séances a été atteint pour le jour.\n");
                sqlite3_close(db);
                return;
            }
            else
            {
                sprintf(query, "INSERT INTO seances(idjour, film, nbplace) VALUES (%d, '%s', %d)", id_jour, film, seance);
                rc = sqlite3_exec(db, query, NULL, NULL, NULL);
                if (rc != SQLITE_OK)
                {
                    printf("Erreur SQLite : %s\n", sqlite3_errmsg(db));
                }
                else
                {
                    printf("✅ Séance ajoutée avec succès pour le jour.\n");
                }

                sqlite3_close(db);
            }
        }
    }
    else
    {
        /* si le jour n'existe pas */

        sprintf(query, "INSERT INTO jours(date) VALUES('%s')", date);
        rc = sqlite3_exec(db, query, NULL, NULL, NULL);

        if (rc != SQLITE_OK)
        {
            printf("Erreur : impossible d'ajouter le jour.\n");
            printf("Erreur SQLite : %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return;
        }
        else
        {
            printf("Jour ajouté avec succès \n");
        }

        sprintf(query, "INSERT INTO seances(idjour, film, nbplace) VALUES('%lld', '%s', %d)", sqlite3_last_insert_rowid(db), film, nb);
        rc = sqlite3_exec(db, query, NULL, NULL, NULL);

        if (rc != SQLITE_OK)
        {
            printf("Erreur : impossible d'ajouter la première séance.\n");
            printf("Erreur SQLite : %s\n", sqlite3_errmsg(db));
        }
        else
        {
            printf("✅ Nouvelle date ajoutée avec succès avec une première séance.\n");
        }

        sqlite3_close(db);
    }
}
