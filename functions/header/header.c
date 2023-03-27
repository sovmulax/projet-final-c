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
/// @param db 
/// @param film 
/// @param nb 
void ajout_seance(sqlite3 *db, const char *film, int nb);
/// @brief 
void liste_seance();