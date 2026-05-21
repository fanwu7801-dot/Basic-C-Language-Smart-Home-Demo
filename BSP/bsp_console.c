#include "bsp_console.h"

#include <stdio.h>
#include <string.h>

void bsp_console_clear(void)
{
    printf("\n\n\n\n\n");
}

void bsp_console_print(const char *text)
{
    if (text != NULL)
    {
        printf("%s", text);
    }
}

void bsp_console_println(const char *text)
{
    if (text != NULL)
    {
        printf("%s", text);
    }
    printf("\n");
}

int bsp_console_read_line(char *buffer, size_t size)
{
    size_t length = 0;

    if (buffer == NULL || size == 0U)
    {
        return 0;
    }

    if (fgets(buffer, (int)size, stdin) == NULL)
    {
        return 0;
    }

    length = strlen(buffer);
    if (length > 0U && buffer[length - 1U] == '\n')
    {
        buffer[length - 1U] = '\0';
    }

    return 1;
}
