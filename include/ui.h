#ifndef UI_H
#define UI_H

#include "todo.h"

/**
 * @brief Initialize the ncurses interface
 */
void ui_init(void);

/**
 * @brief Cleanup and end ncurses interface
 */
void ui_cleanup(void);

/**
 * @brief Clear the screen
 */
void ui_clear(void);

/**
 * @brief Get a character input from user
 * @return The character pressed by user
 */
int ui_getch(void);

/**
 * @brief Print formatted text to screen
 * @param fmt Format string
 * @param ... Arguments for format string
 */
void ui_print(const char *fmt, ...);

/**
 * @brief Get a string input from user
 * @param buffer Buffer to store the input
 * @param max_len Maximum length of input
 */
void ui_get_string(char *buffer, int max_len);

/**
 * @brief Wait for user to press any key with a message
 */
void ui_wait_for_key(void);

#endif // UI_H
