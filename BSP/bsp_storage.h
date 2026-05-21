/******************************************************************************
 * @file bsp_storage.h
 * @brief Board support package for line-based storage.
 ******************************************************************************/
#ifndef BSP_STORAGE_H
#define BSP_STORAGE_H

typedef int (*bsp_storage_line_handler_t)(const char *line, void *context);

int bsp_storage_save_lines(const char *path, const char *const *lines, int line_count);
int bsp_storage_load_lines(const char *path, bsp_storage_line_handler_t handler, void *context);

#endif // BSP_STORAGE_H
