#include "light.h"

#include <stdio.h>

static void light_display(const device_t *self, int index);
static void light_serialize(const device_t *self, char *buffer, size_t size);

static const device_ops_t LIGHT_OPS = {
    light_display,
    light_serialize,
};

void light_init(light_t *light, const char *id, const char *name, device_state_t state)
{
    if (light == NULL)
    {
        return;
    }

    device_init(&light->base, id, name, DEVICE_LIGHT, &LIGHT_OPS);
    light->state = state;
}

void light_toggle(light_t *light)
{
    if (light == NULL)
    {
        return;
    }

    light->state = light->state == DEVICE_ON ? DEVICE_OFF : DEVICE_ON;
}

void light_turn_off(light_t *light)
{
    light_set_state(light, DEVICE_OFF);
}

void light_set_state(light_t *light, device_state_t state)
{
    if (light == NULL)
    {
        return;
    }

    light->state = state;
}

static void light_display(const device_t *self, int index)
{
    const light_t *light = (const light_t *)self;
    printf("%d. %s: [%s]\n", index, light->base.name, device_state_text(light->state));
}

static void light_serialize(const device_t *self, char *buffer, size_t size)
{
    const light_t *light = (const light_t *)self;
    (void)snprintf(buffer, size, "LIGHT %s %d", light->base.id, (int)light->state);
}
