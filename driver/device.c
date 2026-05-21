#include "device.h"

#include <stdio.h>

void device_init(device_t *device,
                 const char *id,
                 const char *name,
                 device_type_t type,
                 const device_ops_t *ops)
{
    if (device == NULL)
    {
        return;
    }

    (void)snprintf(device->id, sizeof(device->id), "%s", id);
    (void)snprintf(device->name, sizeof(device->name), "%s", name);
    device->type = type;
    device->ops = ops;
}

const char *device_state_text(device_state_t state)
{
    return state == DEVICE_ON ? "ON" : "OFF";
}
