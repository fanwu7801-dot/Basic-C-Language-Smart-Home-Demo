#include "basic_ui.h"

#include "bsp_console.h"

#include <stdio.h>

static void basic_ui_clear_impl(basic_ui_t *self);
static void basic_ui_header_impl(basic_ui_t *self);
static void basic_ui_menu_impl(basic_ui_t *self);
static int basic_ui_read_int_impl(basic_ui_t *self, const char *prompt, int *out_value);
static void basic_ui_message_impl(basic_ui_t *self, const char *text);

void basic_ui_init(basic_ui_t *ui)
{
    if (ui == NULL)
    {
        return;
    }

    ui->clear = basic_ui_clear_impl;
    ui->header = basic_ui_header_impl;
    ui->menu = basic_ui_menu_impl;
    ui->read_int = basic_ui_read_int_impl;
    ui->message = basic_ui_message_impl;
}

void basic_ui_wait_enter(basic_ui_t *ui)
{
    char buffer[8] = {0};

    (void)ui;
    bsp_console_print("Press Enter to continue...");
    (void)bsp_console_read_line(buffer, sizeof(buffer));
}

static void basic_ui_clear_impl(basic_ui_t *self)
{
    (void)self;
    bsp_console_clear();
}

static void basic_ui_header_impl(basic_ui_t *self)
{
    (void)self;
    bsp_console_println("=========================");
    bsp_console_println("Smart Home Control Center");
    bsp_console_println("=========================");
}

static void basic_ui_menu_impl(basic_ui_t *self)
{
    (void)self;
    bsp_console_println("");
    bsp_console_println("Choose an action:");
    bsp_console_println("[1] Toggle living room light");
    bsp_console_println("[2] Toggle bedroom light");
    bsp_console_println("[3] Set air conditioner target temperature");
    bsp_console_println("[4] Sleep mode");
    bsp_console_println("[5] Away mode");
    bsp_console_println("[0] Exit system");
}

static int basic_ui_read_int_impl(basic_ui_t *self, const char *prompt, int *out_value)
{
    char buffer[64] = {0};
    char extra = '\0';
    int value = 0;

    (void)self;

    if (prompt != NULL)
    {
        bsp_console_print(prompt);
    }

    if (!bsp_console_read_line(buffer, sizeof(buffer)))
    {
        return 0;
    }

    if (sscanf(buffer, " %d %c", &value, &extra) != 1)
    {
        return 0;
    }

    if (out_value != NULL)
    {
        *out_value = value;
    }

    return 1;
}

static void basic_ui_message_impl(basic_ui_t *self, const char *text)
{
    (void)self;
    bsp_console_print("Message: ");
    bsp_console_println(text);
}
