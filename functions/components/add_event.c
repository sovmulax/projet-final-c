#include "../sql/sqlite3.h"
#include "../header/header.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int callbacks_id(void *, int, char **, char **);

int	idEvent();
int	addMenu(int a);

int add_event(char a[200], char b[200], char c[200], char d[200])
{
    sqlite3 *db;
    char *err_msg;
    char *sql;
    size_t sz;
    int rc;
    int price;
    char *type;

    err_msg = 0;
    // requete
    sz = snprintf(NULL, 0, "INSERT INTO events(nom, type, date, nbplace) VALUES('%s', '%s', '%s', '%s')", a, b, c, d);
    sql = (char *)malloc(sz + 1);
    snprintf(sql, sz + 1, "INSERT INTO events(nom, type, date, nbplace) VALUES('%s', '%s', '%s', '%s')", a, b, c, d);

    // work
    rc = sqlite3_open("./event.db", &db);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return (1);
    }
    printf("✅ %s\n", sql);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return (1);
    }

    sqlite3_close(db);

    return (0);
}