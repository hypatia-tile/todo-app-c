#include "menu.h"
#include "todo.h"
#include "ui.h"
#include <stdlib.h>

void menu_show(void)
{
    ui_print("=== C ToDo App ===\n");
    ui_print("1. View Tasks\n");
    ui_print("2. Add Task\n");
    ui_print("3. Delete Task\n");
    ui_print("4. Exit\n");
    ui_print("Select an option: ");
}

void menu_handle_view(char tasks[][MAX_TASK_LEN], int count)
{
    ui_print("=== Your Tasks ===\n");
    if (count == 0) {
        ui_print("No tasks available.\n");
    } else {
        view_tasks(tasks, count);
    }
    ui_wait_for_key();
}

void menu_handle_add(char tasks[][MAX_TASK_LEN], int *count)
{
    char buffer[MAX_TASK_LEN];
    ui_print("Enter new task: ");
    ui_get_string(buffer, MAX_TASK_LEN);
    add_task(tasks, count, buffer);
    ui_print("Task added!\n");
    ui_wait_for_key();
}

void menu_handle_delete(char tasks[][MAX_TASK_LEN], int *count)
{
    char input[10];
    ui_print("Enter task number to delete: ");
    ui_get_string(input, 10);
    int index = atoi(input) - 1; // Convert to zero-based index
    if (index >= 0 && index < *count) {
        delete_task(tasks, count, index);
        ui_print("Task deleted!\n");
    } else {
        ui_print("Invalid index.\n");
    }
    ui_wait_for_key();
}
