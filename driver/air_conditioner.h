/******************************************************************************
 * @file air_conditioner.h
 * @brief OOP-style air conditioner device.
 ******************************************************************************/
#ifndef AIR_CONDITIONER_H
#define AIR_CONDITIONER_H

#include "device.h"

#define AIR_CONDITIONER_MIN_TEMP 16
#define AIR_CONDITIONER_MAX_TEMP 30

typedef struct air_conditioner
{
    device_t base;
    int current_temperature;
    int target_temperature;
    device_state_t power;
} air_conditioner_t;

void air_conditioner_init(air_conditioner_t *air_conditioner,
                          const char *id,
                          const char *name,
                          int current_temperature,
                          int target_temperature,
                          device_state_t power);
int air_conditioner_set_target_temperature(air_conditioner_t *air_conditioner, int target_temperature);
void air_conditioner_power_off(air_conditioner_t *air_conditioner);
void air_conditioner_power_on(air_conditioner_t *air_conditioner);

#endif // AIR_CONDITIONER_H
