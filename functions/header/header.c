void add_event(sqlite3 *db, char a[200], char b[200], char c[200], char d[200], char e[200]);
void event_list(sqlite3 *db, const char *columns);
int achat_billet(sqlite3 *db, int id, int cine);
void ajout_seance(sqlite3 *db, const char *film, int nb)
void liste_seance();