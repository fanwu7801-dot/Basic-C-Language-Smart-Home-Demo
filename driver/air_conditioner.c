#include "air_conditioner.h"

#include <stdio.h>

static void air_conditioner_display(const device_t *self, int index);
static void air_conditioner_serialize(const device_t *self, char *buffer, size_t size);

static const device_ops_t AIR_CONDITIONER_OPS = {
    air_conditioner_display,
    air_conditioner_serialize,
};

void air_conditioner_init(air_conditioner_t *air_conditioner,
                          const char *id,
                          const char *name,
                          int current_temperature,
                          int target_temperature,
                          device_state_t power)
{
    if (air_conditioner == NULL)
    {
        return;
    }

    device_init(&air_conditioner->base, id, name, DEVICE_AIR_CONDITIONER, &AIR_CONDITIONER_OPS);
    air_conditioner->current_temperature = current_temperature;
    air_conditioner->target_temperature = target_temperature;
    air_conditioner->power = power;
}

int air_conditioner_set_target_temperature(air_conditioner_t *air_conditioner, int target_temperature)
{
    if (air_conditioner == NULL)
    {
        return 0;
    }

    if (target_temperature < AIR_CONDITIONER_MIN_TEMP ||
        target_temperature > AIR_CONDITIONER_MAX_TEMP)
    {
        return 0;
    }

    air_conditioner->target_temperature = target_temperature;
    air_conditioner->power = DEVICE_ON;
    return 1;
}

void air_conditioner_power_off(air_conditioner_t *air_conditioner)
{
    if (air_conditioner == NULL)
    {
        return;
    }

    air_conditioner->power = DEVICE_OFF;
}

void air_conditioner_power_on(air_conditioner_t *air_conditioner)
{
    if (air_conditioner == NULL)
    {
        return;
    }

    air_conditioner->power = DEVICE_ON;
}

static void air_conditioner_display(const device_t *self, int index)
{
    const air_conditioner_t *air_conditioner = (const air_conditioner_t *)self;

    if (air_conditioner->power == DEVICE_OFF)
    {
        printf("%d. %s: [OFF] | Current %dC\n",
               index,
               air_conditioner->base.name,
               air_conditioner->current_temperature);
        return;
    }

    printf("%d. %s: Current %dC | Target %dC\n",
           index,
           air_conditioner->base.name,
           air_conditioner->current_temperature,
           air_conditioner->target_temperature);
}

static void air_conditioner_serialize(const device_t *self, char *buffer, size_t size)
{
    const air_conditioner_t *air_conditioner = (const air_conditioner_t *)self;
    (void)snprintf(buffer,
                   size,
                   "AIR_CONDITIONER %d %d %d",
                   air_conditioner->current_temperature,
                   air_conditioner->target_temperature,
                   (int)air_conditioner->power);
}
