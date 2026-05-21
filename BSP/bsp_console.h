/******************************************************************************
 * @file bsp_console.h
 * @brief Board support package for console input/output.
 ******************************************************************************/
#ifndef BSP_CONSOLE_H
#define BSP_CONSOLE_H

#include <stddef.h>

void bsp_console_clear(void);
void bsp_console_print(const char *text);
void bsp_console_println(const char *text);
int bsp_console_read_line(char *buffer, size_t size);

#endif // BSP_CONSOLE_H
