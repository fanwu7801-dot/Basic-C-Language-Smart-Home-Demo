/******************************************************************************
 * @file light.h
 * @brief OOP-style light device.
 ******************************************************************************/
#ifndef LIGHT_H
#define LIGHT_H

#include "device.h"

typedef struct light
{
    device_t base;
    device_state_t state;
} light_t;

void light_init(light_t *light, const char *id, const char *name, device_state_t state);
void light_toggle(light_t *light);
void light_turn_off(light_t *light);
void light_set_state(light_t *light, device_state_t state);

#endif // LIGHT_H
