#ifndef MENU_H
#define MENU_H

#include "todo.h"

/**
 * @brief Display the main menu
 */
void menu_show(void);

/**
 * @brief Handle viewing tasks
 * @param tasks Array of tasks
 * @param count Number of tasks
 */
void menu_handle_view(char tasks[][MAX_TASK_LEN], int count);

/**
 * @brief Handle adding a new task
 * @param tasks Array of tasks
 * @param count Pointer to task count
 */
void menu_handle_add(char tasks[][MAX_TASK_LEN], int *count);

/**
 * @brief Handle deleting a task
 * @param tasks Array of tasks
 * @param count Pointer to task count
 */
void menu_handle_delete(char tasks[][MAX_TASK_LEN], int *count);

#endif // MENU_H
