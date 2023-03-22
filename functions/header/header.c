int add_event(char a[200], char b[200], char c[200], char d[200]);
void	event_list(sqlite3 *db, const char *columns);
void retrieve_data_from_event_table(sqlite3 *db);