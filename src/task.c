#include "database.h"
#include "todo.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load_tasks(char tasks[][MAX_TASK_LEN], int *count)
{
    if (db_load_tasks(tasks, count) != 0) {
        ui_print("Error loading tasks from database.\n");
        *count = 0;
    }
}

void save_tasks(char tasks[][MAX_TASK_LEN], int count)
{
    if (db_save_tasks(tasks, count) != 0) {
        ui_print("Error saving tasks to database.\n");
    }
}

void add_task(char tasks[][MAX_TASK_LEN], int *count, const char *task)
{
    if (*count >= MAX_TASKS)
        return;
    strncpy(tasks[*count], task, MAX_TASK_LEN);
    (*count)++;
}

void delete_task(char tasks[][MAX_TASK_LEN], int *count, int index)
{
    if (index < 0 || index >= *count)
        return;
    for (int i = index; i < *count - 1; ++i)
        strcpy(tasks[i], tasks[i + 1]);
    (*count)--;
}

void view_tasks(char tasks[][MAX_TASK_LEN], int count)
{
    for (int i = 0; i < count; ++i)
        ui_print("%d. %s\n", i + 1, tasks[i]);
}
