/******************************************************************************
 * @file basic_ui.h 
 * @author Lumos (1456925916@qq.com)
 * @brief the Basic ui  for the project use cmd window to display the ui 
 * @version 0.1
 * @date 2026-05-11
 * 
 * @copyright Copyright (c) 2026
 * 
******************************************************************************/
#ifndef BASIC_UI_H
#define BASIC_UI_H
/********************************** Includes *********************************/
#include <stddef.h>
/********************************** Includes *********************************/

/********************************** Defines **********************************/

typedef struct basic_ui
{
    void (*clear)(struct basic_ui *self);
    void (*header)(struct basic_ui *self);
    void (*menu)(struct basic_ui *self);
    int (*read_int)(struct basic_ui *self, const char *prompt, int *out_value);
    void (*message)(struct basic_ui *self, const char *text);
} basic_ui_t;

void basic_ui_init(basic_ui_t *ui);
void basic_ui_wait_enter(basic_ui_t *ui);

#endif // BASIC_UI_H

