#include <ncurses.h>
#include <stdarg.h>
#include "ui.h"

void ui_init(void)
{
    initscr();            /* Start curses mode */
    noecho();             /* Don't show typed characters */
    cbreak();             /* Accept input immediately */
    keypad(stdscr, TRUE); /* Enable special keys like arrows */
}

void ui_cleanup(void)
{
    endwin(); /* End of curses mode */
}

void ui_clear(void)
{
    clear(); /* Clear the screen */
}

int ui_getch(void)
{
    return getch(); /* Get user input */
}

void ui_print(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vw_printw(stdscr, fmt, args);
    va_end(args);
}

void ui_get_string(char *buffer, int max_len)
{
    echo(); /* Show typed characters */
    getnstr(buffer, max_len - 1);
    noecho(); /* Hide typed characters again */
}

void ui_wait_for_key(void)
{
    ui_print("\nPress any key to return to the menu...");
    ui_getch();
}
