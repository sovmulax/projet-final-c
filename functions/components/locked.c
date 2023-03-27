#include "../sql/sqlite3.h"
#include "../header/header.c"
#include <stdio.h>
#include <stdlib.h>

int retry_exec(sqlite3 *db, char *sql, int max_retries, int wait_time_ms) {
    int rc;
    int retries = 0;
    do {
        rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
        if (rc == SQLITE_LOCKED || rc == SQLITE_BUSY) {
            retries++;
            if (retries > max_retries) {
                fprintf(stderr, "Max retries exceeded while waiting for database lock.\n");
                return rc;
            }
            fprintf(stderr, "Database is locked. Waiting %d ms before retrying...\n", wait_time_ms);
            usleep(wait_time_ms * 1000);
        }
    } while (rc == SQLITE_LOCKED || rc == SQLITE_BUSY);

    return rc;
}