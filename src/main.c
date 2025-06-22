#include <ncurses.h>

int main()
{
    initscr();                              /* Start curses mode */
    printw("Welcome to the C ToDo App!\n"); /* Print Hello World */
    refresh();                              /* Print it on to the real screen */
    // TODO: Add menu and Task management functionality
    getch(); /* Wait for user input */
    printw("\nPress any key to exit...");
    getch();
    endwin(); /* End curses mode */
    return 0;
}
