#include "todo.h"
#include "ui.h"
#include "menu.h"

/**
 * @brief Initialize the main UI and welcome message
 *
 * Starts the ncurses screen and displays a main menu
 */
int main()
{
    char tasks[MAX_TASKS][MAX_TASK_LEN];
    int task_count = 0;

    ui_init();                      /* Start UI */
    load_tasks(tasks, &task_count); /* Load tasks from file */

    int choice;
    while (1)
    {
        ui_clear();          /* Clear the screen */
        menu_show();         /* Show the menu */
        choice = ui_getch(); /* Get user input */

        switch (choice)
        {
        case '1':
            ui_clear();
            menu_handle_view(tasks, task_count);
            break;
        case '2':
            ui_clear();
            menu_handle_add(tasks, &task_count);
            break;
        case '3':
            ui_clear();
            menu_handle_delete(tasks, &task_count);
            break;
        case '4':
            save_tasks(tasks, task_count);
            ui_cleanup(); /* End of UI mode */
            return 0;     /* Exit the program */

          default:
            break;
        }
    }
    ui_cleanup();
    return 0;
}
