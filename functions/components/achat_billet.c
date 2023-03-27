#include "../sql/sqlite3.h"
#include "../header/header.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief 
/// @param db 
/// @param id 
/// @param cine 
/// @return 
int achat_billet(sqlite3 *db, int id, int cine)
{
    int nbOccurences = 0;
    int nbPlaces = 0;
    char *errorMsg = NULL;
    sqlite3_stmt *stmt;
    // Ouvre la base de données event.db
    sqlite3_open("event.db", &db);

    if (cine == 0)
    {
        // Compte le nombre d'occurrences dans la table "billets" pour l'événement spécifié
        sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM billets WHERE idevent = ?", -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, id);
        sqlite3_step(stmt);
        nbOccurences = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);

        // Récupère le nombre de places disponibles pour l'événement spécifié
        sqlite3_prepare_v2(db, "SELECT nbplace FROM events WHERE Id = ?", -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, id);
        sqlite3_step(stmt);
        nbPlaces = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);

        // Si le nombre d'occurrences est inférieur au nombre de places disponibles, insère une nouvelle occurrence dans la table "billets"
        if (nbOccurences < nbPlaces)
        {
            sqlite3_prepare_v2(db, "INSERT INTO billets (idevent) VALUES (?)", -1, &stmt, NULL);
            sqlite3_bind_int(stmt, 1, id);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
            printf("✅ Billet acheter\n");
            return 0;
        }else{
            printf("❌ Il n'y a plus de place disponible\n");
            return 0;
        }
    }
    else
    {
        // Compte le nombre d'occurrences dans la table "billets" pour l'événement spécifié
        sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM billets WHERE idseance = ?", -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, id);
        sqlite3_step(stmt);
        nbOccurences = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);

        // Récupère le nombre de places disponibles pour l'événement spécifié
        sqlite3_prepare_v2(db, "SELECT nbplace FROM seances WHERE id = ?", -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, id);
        sqlite3_step(stmt);
        nbPlaces = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);

        // Si le nombre d'occurrences est inférieur au nombre de places disponibles, insère une nouvelle occurrence dans la table "billets"
        if (nbOccurences >= nbPlaces)
        {
            sqlite3_prepare_v2(db, "INSERT INTO billets (idseance) VALUES (?)", -1, &stmt, NULL);
            sqlite3_bind_int(stmt, 1, id);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
            printf("✅ Billet acheter\n");

            return 0;
        }else{
            printf("❌ Il n'y a plus de place disponible\n");
            return 0;
        }
    }

    return 0;
}
