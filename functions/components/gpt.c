#include "../sql/sqlite3.h"
#include "../header/header.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void insert_data_into_event_and_menu_tables(sqlite3 *db, char *element1, char *element2, char *element3)
// {
//     // Ouvre la base de données event.db
//     sqlite3_open("event.db", &db);

//     // Insère les données dans la table "event"
//     char *sql_event = "INSERT INTO event (column1, column2, column3) VALUES (?, ?, ?)";
//     sqlite3_stmt *stmt_event;
//     sqlite3_prepare_v2(db, sql_event, -1, &stmt_event, NULL);
//     sqlite3_bind_text(stmt_event, 1, element1, -1, SQLITE_STATIC);
//     sqlite3_bind_text(stmt_event, 2, element2, -1, SQLITE_STATIC);
//     sqlite3_bind_text(stmt_event, 3, element3, -1, SQLITE_STATIC);
//     sqlite3_step(stmt_event);
//     sqlite3_finalize(stmt_event);

//     // Récupère l'id de la dernière insertion dans la table "event"
//     int last_id = sqlite3_last_insert_rowid(db);

//     // Insère les données dans la table "menu" en utilisant l'id récupéré
//     char *sql_menu = "INSERT INTO menu (event_id, column4, column5) VALUES (?, ?, ?)";
//     sqlite3_stmt *stmt_menu;
//     sqlite3_prepare_v2(db, sql_menu, -1, &stmt_menu, NULL);
//     sqlite3_bind_int(stmt_menu, 1, last_id);
//     sqlite3_bind_text(stmt_menu, 2, "some data", -1, SQLITE_STATIC);       // example data
//     sqlite3_bind_text(stmt_menu, 3, "some other data", -1, SQLITE_STATIC); // example data
//     sqlite3_step(stmt_menu);
//     sqlite3_finalize(stmt_menu);

//     // Ferme la base de données
//     sqlite3_close(db);
// }

// void retrieve_data_from_event_table(sqlite3 *db) {
//     // Ouvre la base de données event.db
//     sqlite3_open("event.db", &db);
    
//     // Récupère les données de la table "event"
//     sqlite3_stmt *stmt;
//     const char *sql = "SELECT * FROM events";
//     sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
//     // Affiche les données récupérées
//     while (sqlite3_step(stmt) == SQLITE_ROW) {
//         int id = sqlite3_column_int(stmt, 0);
//         const unsigned char *column1 = sqlite3_column_text(stmt, 1);
//         const unsigned char *column2 = sqlite3_column_text(stmt, 2);
//         const unsigned char *column3 = sqlite3_column_text(stmt, 3);
        
//         printf("ID: %d, Column 1: %s, Column 2: %s, Column 3: %s\n", id, column1, column2, column3);
//     }
    
//     // Libère les ressources utilisées par la requête
//     sqlite3_finalize(stmt);
    
//     // Ferme la base de données
//     sqlite3_close(db);
// }
