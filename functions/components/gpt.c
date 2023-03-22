#include "../sql/sqlite3.h"
#include "../header/header.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void insert_data_into_event_and_menu_tables(sqlite3 *db, char *a, char *b, char *c, char *d)
// {
//     // Ouvre la base de données event.db
//     sqlite3_open("event.db", &db);

//     // Insère les données dans la table "event"
//     char *sql_event = "INSERT INTO events (nom, type, date, nbplace) VALUES (?, ?, ?, ?)";
//     sqlite3_stmt *stmt_event;
//     sqlite3_prepare_v2(db, sql_event, -1, &stmt_event, NULL);
//     sqlite3_bind_text(stmt_event, 1, a, -1, SQLITE_STATIC);
//     sqlite3_bind_text(stmt_event, 2, d, -1, SQLITE_STATIC);
//     sqlite3_bind_text(stmt_event, 3, b, -1, SQLITE_STATIC);
//     sqlite3_bind_text(stmt_event, 4, c, -1, SQLITE_STATIC);
//     sqlite3_step(stmt_event);
//     sqlite3_finalize(stmt_event);

//     // Récupère l'id de la dernière insertion dans la table "event"
//     int last_id = sqlite3_last_insert_rowid(db);

//     // Insère les données dans la table "menu" en utilisant l'id récupéré
//     char *sql_menu = "INSERT INTO menus (idevent, element) VALUES (?, ?)";
//     sqlite3_stmt *stmt_menu;
//     sqlite3_prepare_v2(db, sql_menu, -1, &stmt_menu, NULL);
//     sqlite3_bind_int(stmt_menu, 1, last_id);
//     sqlite3_bind_text(stmt_menu, 2, "element;element;element", -1, SQLITE_STATIC);       // example data
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

// #include <stdio.h>
// #include <time.h>

// int main()
// {
//     time_t t = time(NULL);
//     struct tm tm = *localtime(&t);
//     printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
// }

// #include<stdio.h>
// #include<stdlib.h>
// int main()
// {
//   printf("\e[1;1H\e[2J");
//   printf("Geeksforgeeks\n");
//   printf("A computer Science portal\n");
// }