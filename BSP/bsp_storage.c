#include "bsp_storage.h"

#include <stdio.h>
#include <string.h>

int bsp_storage_save_lines(const char *path, const char *const *lines, int line_count)
{
    FILE *file = NULL;
    int i = 0;

    if (path == NULL || lines == NULL || line_count < 0)
    {
        return 0;
    }

    file = fopen(path, "w");
    if (file == NULL)
    {
        return 0;
    }

    for (i = 0; i < line_count; ++i)
    {
        if (lines[i] != NULL)
        {
            fprintf(file, "%s\n", lines[i]);
        }
    }

    fclose(file);
    return 1;
}

int bsp_storage_load_lines(const char *path, bsp_storage_line_handler_t handler, void *context)
{
    FILE *file = NULL;
    char line[128] = {0};
    int loaded_count = 0;

    if (path == NULL || handler == NULL)
    {
        return 0;
    }

    file = fopen(path, "r");
    if (file == NULL)
    {
        return 0;
    }

    while (fgets(line, sizeof(line), file) != NULL)
    {
        size_t length = strlen(line);
        if (length > 0U && line[length - 1U] == '\n')
        {
            line[length - 1U] = '\0';
        }

        if (handler(line, context))
        {
            ++loaded_count;
        }
    }

    fclose(file);
    return loaded_count;
}
