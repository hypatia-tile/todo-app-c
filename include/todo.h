#ifndef TODO_H
#define TODO_H

#define MAX_TASKS 100
#define MAX_TASK_LEN 256

void load_tasks(char tasks[][MAX_TASK_LEN], int *count);
void save_tasks(char tasks[][MAX_TASK_LEN], int count);
void add_task(char tasks[][MAX_TASK_LEN], int *count, const char *task);
void delete_task(char tasks[][MAX_TASK_LEN], int *count, int index);
void view_tasks(char tasks[][MAX_TASK_LEN], int count);

#endif // TODO_H