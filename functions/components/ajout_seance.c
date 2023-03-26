#include <stdio.h>
#include <sqlite3.h>
#include <time.h>

void insert_data_into_jours_and_seances_tables(sqlite3 *db, char *element1, char *element2)
{
    time_t current_time = time(NULL);
    struct tm *tm = localtime(&current_time);
    char date[11];
    strftime(date, sizeof(date), "%Y-%m-%d", tm);

    // Insertion de l'occurrence dans la table "jours"
    char *sql_jours = sqlite3_mprintf("INSERT OR IGNORE INTO jours(date) VALUES('%s')", date);
    int rc = sqlite3_exec(db, sql_jours, NULL, NULL, NULL);
    sqlite3_free(sql_jours);

    if (rc == SQLITE_CONSTRAINT)
    {
        printf("Erreur : le jour %s existe déjà dans la base de données.\n", date);
        return;
    }

    // Récupération de l'ID de l'occurrence insérée dans la table "jours"
    sqlite3_stmt *stmt;
    const char *sql_jours_id = "SELECT id FROM jours WHERE date=?";
    sqlite3_prepare_v2(db, sql_jours_id, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, date, -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_int64 jours_id = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);

    // Vérification du nombre d'occurrences de la table "seances" pour le jour courant
    const char *sql_count_seances = "SELECT COUNT(*) FROM seances WHERE jours_id=?";
    sqlite3_prepare_v2(db, sql_count_seances, -1, &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, jours_id);
    sqlite3_step(stmt);
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    if (count >= 4)
    {
        printf("Erreur : il y a déjà 4 séances pour le jour %s.\n", date);
    }
    else
    {
        // Insertion de l'occurrence dans la table "seances"
        char *sql_seances = sqlite3_mprintf("INSERT INTO seances(jours_id, element1, element2) VALUES(%lld, '%s', '%s')",
                                            jours_id, element1, element2);
        sqlite3_exec(db, sql_seances, NULL, NULL, NULL);
        sqlite3_free(sql_seances);
    }
}
