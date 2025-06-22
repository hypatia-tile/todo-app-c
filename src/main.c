#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include "todo.h"

void show_menu();
void handle_view(char tasks[][MAX_TASK_LEN], int count);
void handle_add(char tasks[][MAX_TASK_LEN], int *count);
void handle_delete(char tasks[][MAX_TASK_LEN], int *count);

int main()
{
    char tasks[MAX_TASKS][MAX_TASK_LEN];
    int task_count = 0;

    initscr();                      /* Start curses mode */
    noecho();                       // Don't show typed charcters
    cbreak();                       // Accept input immediately
    keypad(stdscr, TRUE);           // Enable special keys like arrows
    load_tasks(tasks, &task_count); // Load tasks from file

    int choice;
    while (1)
    {
        clear();          /* Clear the screen */
        show_menu();      /* Show the menu */
        choice = getch(); /* Get user input */

        switch (choice)
        {
        case '1':
            clear();
            handle_view(tasks, task_count);
            break;
        case '2':
            clear();
            handle_add(tasks, &task_count);
            break;
        case '3':
            clear();
            handle_delete(tasks, &task_count);
            break;
        case '4':
            save_tasks(tasks, task_count);
            endwin(); /* End of curse mode */
            return 0; /* Exit to the program */
        default:
            break;
        }
    }
    endwin();
    return 0;
}

void show_menu()
{
    printw("=== C ToDo App ===\n");
    printw("1. Wiew Tasks\n");
    printw("2. Add Task\n");
    printw("3. Delete Task\n");
    printw("4. Exit\n");
    printw("Select an option: ");
}

void handle_view(char tasks[][MAX_TASK_LEN], int count)
{
    printw("=== Your Tasks ===\n");
    if (count == 0)
    {
        printw("No tasks available.\n");
    }
    else
    {
        view_tasks(tasks, count);
    }
    printw("\nPress any key to return to the menu...");
    getch();
}

void handle_add(char tasks[][MAX_TASK_LEN], int *count)
{
    echo();
    char buffer[MAX_TASK_LEN];
    printw("Enter new task: ");
    getnstr(buffer, MAX_TASK_LEN - 1);
    add_task(tasks, count, buffer);
    printw("Task added!\n");
    printw("\nPress any key to return to the menu...");
    getch();
    noecho();
}

void handle_delete(char tasks[][MAX_TASK_LEN], int *count)
{
    echo();
    char input[10];
    printw("Enter task number to delete: ");
    getnstr(input, 9);
    int index = atoi(input) - 1; // Convert to zero-based index
    if (index >= 0 && index < *count)
    {
        delete_task(tasks, count, index);
        printw("Task deleted!\n");
    }
    else
    {
        printw("Invalid index.\n");
    }
    printw("\nPress any key to return to menu...");
    noecho();
    getch();
}