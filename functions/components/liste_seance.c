#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <time.h>

#define DB_PATH "event.db"

void liste_seance() {
    // Connexion à la base de données
    sqlite3 *db;
    if (sqlite3_open(DB_PATH, &db) != SQLITE_OK) {
        fprintf(stderr, "Erreur lors de la connexion à la base de données : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    
    // Récupération de l'ID de l'occurrence du jour courant
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char date[11];
    sprintf(date, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    char query[200];
    sprintf(query, "SELECT id FROM jours WHERE date='%s'", date);
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erreur lors de la préparation de la requête : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        int id_jour = sqlite3_column_int(stmt, 0);
        printf("Occurrence du jour courant (date=%s, id=%d):\n", date, id_jour);
        
        // Récupération des séances en lien avec l'occurrence du jour courant
        sprintf(query, "SELECT id, debut, fin FROM seances WHERE id_jour=%d", id_jour);
        rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Erreur lors de la préparation de la requête : %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return;
        }
        rc = sqlite3_step(stmt);
        while (rc == SQLITE_ROW) {
            int id_seance = sqlite3_column_int(stmt, 0);
            char debut[6], fin[6];
            sprintf(debut, "%02d:%02d", sqlite3_column_int(stmt, 1), sqlite3_column_int(stmt, 2));
            rc = sqlite3_step(stmt);
            if (rc != SQLITE_OK && rc != SQLITE_DONE) {
                fprintf(stderr, "Erreur lors de l'exécution de la requête : %s\n", sqlite3_errmsg(db));
                sqlite3_finalize(stmt);
                sqlite3_close(db);
                return;
            }
            sprintf(fin, "%02d:%02d", sqlite3_column_int(stmt, 1), sqlite3_column_int(stmt, 2));
            printf("- Séance %d : de %s à %s\n", id_seance, debut, fin);
        }
    } else {
        printf("Il n'y a pas d'occurrence pour le jour courant (date=%s).\n", date);
    }
    
    // Fermeture de la connexion à la base de données
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
