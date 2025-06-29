#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "todo.h"
#include "ui.h"

void load_tasks(char tasks[][MAX_TASK_LEN], int *count)
{
    FILE *f = fopen("tasks.txt", "r");
    *count = 0;
    if (!f)
        return;
    while (fgets(tasks[*count], MAX_TASK_LEN, f))
    {
        tasks[*count][strcspn(tasks[*count], "\n")] = 0; // trim newline
        (*count)++;
    }
    fclose(f);
}

void save_tasks(char tasks[][MAX_TASK_LEN], int count)
{
    FILE *f = fopen("tasks.txt", "w");
    for (int i = 0; i < count; i++)
        fprintf(f, "%s\n", tasks[i]);
    fclose(f);
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