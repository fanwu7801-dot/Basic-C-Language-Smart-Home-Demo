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
#include <stdio.h>
#include <string>
/********************************** Includes *********************************/

/********************************** Defines **********************************/

typedef struct basic_ui
{
    void (*display)();
    void (*clear)();
    void (*update)();
    void (*destroy)();
} basic_ui_t;

#endif // BASIC_UI_H

