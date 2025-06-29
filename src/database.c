#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "database.h"
#include "ui.h"

static sqlite3 *db = NULL;
static const char *DB_FILE = "todo.db";

// SQL statements
static const char *CREATE_TABLE_SQL = 
    "CREATE TABLE IF NOT EXISTS tasks ("
    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "text TEXT NOT NULL,"
    "created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
    ");";

static const char *SELECT_ALL_SQL = 
    "SELECT text FROM tasks ORDER BY id;";

static const char *INSERT_TASK_SQL = 
    "INSERT INTO tasks (text) VALUES (?);";

static const char *DELETE_TASK_SQL = 
    "DELETE FROM tasks WHERE id = ("
    "SELECT id FROM tasks ORDER BY id LIMIT 1 OFFSET ?"
    ");";

static const char *COUNT_TASKS_SQL = 
    "SELECT COUNT(*) FROM tasks;";

static const char *CLEAR_TASKS_SQL = 
    "DELETE FROM tasks;";

int db_init(void)
{
    int rc = sqlite3_open(DB_FILE, &db);
    if (rc != SQLITE_OK) {
        ui_print("Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        db = NULL;
        return -1;
    }

    // Create table if it doesn't exist
    char *err_msg = 0;
    rc = sqlite3_exec(db, CREATE_TABLE_SQL, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        ui_print("SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        db = NULL;
        return -1;
    }

    return 0;
}

void db_cleanup(void)
{
    if (db) {
        sqlite3_close(db);
        db = NULL;
    }
}

int db_load_tasks(char tasks[][MAX_TASK_LEN], int *count)
{
    if (!db) {
        return -1;
    }

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, SELECT_ALL_SQL, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        ui_print("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    *count = 0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW && *count < MAX_TASKS) {
        const char *text = (const char*)sqlite3_column_text(stmt, 0);
        if (text) {
            strncpy(tasks[*count], text, MAX_TASK_LEN - 1);
            tasks[*count][MAX_TASK_LEN - 1] = '\0'; // Ensure null termination
            (*count)++;
        }
    }

    sqlite3_finalize(stmt);
    
    if (rc != SQLITE_DONE && rc != SQLITE_ROW) {
        ui_print("Error loading tasks: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    return 0;
}

int db_save_tasks(char tasks[][MAX_TASK_LEN], int count)
{
    if (!db) {
        return -1;
    }

    // Begin transaction
    sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);

    // Clear existing tasks
    char *err_msg = 0;
    int rc = sqlite3_exec(db, CLEAR_TASKS_SQL, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        ui_print("Error clearing tasks: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_exec(db, "ROLLBACK;", NULL, NULL, NULL);
        return -1;
    }

    // Insert all tasks
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, INSERT_TASK_SQL, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        ui_print("Failed to prepare insert statement: %s\n", sqlite3_errmsg(db));
        sqlite3_exec(db, "ROLLBACK;", NULL, NULL, NULL);
        return -1;
    }

    for (int i = 0; i < count; i++) {
        sqlite3_bind_text(stmt, 1, tasks[i], -1, SQLITE_STATIC);
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            ui_print("Error inserting task: %s\n", sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            sqlite3_exec(db, "ROLLBACK;", NULL, NULL, NULL);
            return -1;
        }
        sqlite3_reset(stmt);
    }

    sqlite3_finalize(stmt);
    
    // Commit transaction
    rc = sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        ui_print("Error committing transaction: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    return 0;
}

int db_add_task(const char *task_text)
{
    if (!db || !task_text) {
        return -1;
    }

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, INSERT_TASK_SQL, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        ui_print("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_bind_text(stmt, 1, task_text, -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (rc != SQLITE_DONE) {
        ui_print("Error adding task: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    return 0;
}

int db_delete_task_by_index(int task_index)
{
    if (!db || task_index < 1) {
        return -1;
    }

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, DELETE_TASK_SQL, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        ui_print("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    // SQLite uses 0-based offset, but our UI uses 1-based indexing
    sqlite3_bind_int(stmt, 1, task_index - 1);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (rc != SQLITE_DONE) {
        ui_print("Error deleting task: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    return 0;
}

int db_get_task_count(void)
{
    if (!db) {
        return -1;
    }

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, COUNT_TASKS_SQL, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return -1;
    }

    int count = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return count;
}
