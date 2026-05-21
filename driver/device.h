/******************************************************************************
 * @file device.h
 * @brief OOP-style base device abstraction for the smart home demo.
 ******************************************************************************/
#ifndef DEVICE_H
#define DEVICE_H

#include <stddef.h>

typedef enum
{
    DEVICE_LIGHT = 0,
    DEVICE_AIR_CONDITIONER,
    DEVICE_SECURITY_ALARM
} device_type_t;

typedef enum
{
    DEVICE_OFF = 0,
    DEVICE_ON = 1
} device_state_t;

typedef struct device device_t;

typedef struct device_ops
{
    void (*display)(const device_t *self, int index);
    void (*serialize)(const device_t *self, char *buffer, size_t size);
} device_ops_t;

struct device
{
    char id[32];
    char name[32];
    device_type_t type;
    const device_ops_t *ops;
};

void device_init(device_t *device,
                 const char *id,
                 const char *name,
                 device_type_t type,
                 const device_ops_t *ops);
const char *device_state_text(device_state_t state);

#endif // DEVICE_H
