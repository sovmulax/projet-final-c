#include "../sql/sqlite3.h"
#include "../header/header.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief 
/// @param db 
/// @param columns 
void event_list(sqlite3 *db, const char *columns)
{
    // Ouvre la base de données event.db
    sqlite3_open("event.db", &db);
    
    // Construit la requête SQL pour sélectionner les colonnes spécifiées
    char *sql;
    asprintf(&sql, "SELECT %s FROM events", columns);
    
    // Récupère les données de la table "event"
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    // Affiche les données récupérées
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Affiche les valeurs des colonnes spécifiées
        int num_cols = sqlite3_column_count(stmt);
        for (int i = 0; i < num_cols; i++) {
            const unsigned char *value = sqlite3_column_text(stmt, i);
            printf("%s: %s\t", sqlite3_column_name(stmt, i), value);
        }
        printf("\n");
    }
    
    // Libère les ressources utilisées par la requête
    sqlite3_finalize(stmt);
    
    // Ferme la base de données
    sqlite3_close(db);
    
    // Libère la mémoire allouée pour la requête SQL
    free(sql);
}