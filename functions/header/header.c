#include "../sql/sqlite3.h"

/// @brief 
/// @param db 
/// @param a 
/// @param b 
/// @param c 
/// @param d 
/// @param e 
void add_event(sqlite3 *db, char a[200], char b[200], char c[200], char d[200], char e[200]);
/// @brief 
/// @param db 
/// @param columns 
void event_list(sqlite3 *db, const char *columns);
/// @brief 
/// @param db 
/// @param id 
/// @param cine 
/// @return 
int achat_billet(sqlite3 *db, int id, int cine);
/// @brief 
/// @param film 
/// @param db 
/// @param nb 
void ajout_seance(sqlite3 *db, char *film, int nb);
/// @brief 
void liste_seance();
/// @brief 
/// @param exist 
/// @param count 
/// @param id_jour 
/// @param seance 
/// @param film 
/// @param db 
/// @param nb 
void action(sqlite3 *db, int exist, int count, int id_jour, int seance, char *film, int nb);
/// @brief 
/// @param db 
/// @param sql 
/// @param max_retries 
/// @param wait_time_ms 
/// @return 
int retry_exec(sqlite3 *db, char *sql, int max_retries, int wait_time_ms);