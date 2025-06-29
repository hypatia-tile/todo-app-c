#ifndef DATABASE_H
#define DATABASE_H

#include "todo.h"

/**
 * @brief Initialize the database connection and create tables if needed
 * @return 0 on success, -1 on error
 */
int db_init(void);

/**
 * @brief Close database connection and cleanup
 */
void db_cleanup(void);

/**
 * @brief Load all tasks from database into memory array
 * @param tasks Array to store loaded tasks
 * @param count Pointer to store number of tasks loaded
 * @return 0 on success, -1 on error
 */
int db_load_tasks(char tasks[][MAX_TASK_LEN], int *count);

/**
 * @brief Save all tasks from memory array to database
 * @param tasks Array of tasks to save
 * @param count Number of tasks to save
 * @return 0 on success, -1 on error
 */
int db_save_tasks(char tasks[][MAX_TASK_LEN], int count);

/**
 * @brief Add a new task to the database
 * @param task_text The task text to add
 * @return 0 on success, -1 on error
 */
int db_add_task(const char *task_text);

/**
 * @brief Delete a task from the database by index (1-based)
 * @param task_index The 1-based index of the task to delete
 * @return 0 on success, -1 on error
 */
int db_delete_task_by_index(int task_index);

/**
 * @brief Get the number of tasks in the database
 * @return Number of tasks, -1 on error
 */
int db_get_task_count(void);

#endif // DATABASE_H
