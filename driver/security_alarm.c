#include "security_alarm.h"

#include <stdio.h>

static void security_alarm_display(const device_t *self, int index);
static void security_alarm_serialize(const device_t *self, char *buffer, size_t size);

static const device_ops_t SECURITY_ALARM_OPS = {
    security_alarm_display,
    security_alarm_serialize,
};

void security_alarm_init(security_alarm_t *alarm, const char *id, const char *name, device_state_t armed)
{
    if (alarm == NULL)
    {
        return;
    }

    device_init(&alarm->base, id, name, DEVICE_SECURITY_ALARM, &SECURITY_ALARM_OPS);
    alarm->armed = armed;
}

void security_alarm_arm(security_alarm_t *alarm)
{
    security_alarm_set_state(alarm, DEVICE_ON);
}

void security_alarm_disarm(security_alarm_t *alarm)
{
    security_alarm_set_state(alarm, DEVICE_OFF);
}

void security_alarm_set_state(security_alarm_t *alarm, device_state_t armed)
{
    if (alarm == NULL)
    {
        return;
    }

    alarm->armed = armed;
}

static void security_alarm_display(const device_t *self, int index)
{
    const security_alarm_t *alarm = (const security_alarm_t *)self;
    printf("%d. %s: [%s]\n", index, alarm->base.name, alarm->armed == DEVICE_ON ? "ARMED" : "DISARMED");
}

static void security_alarm_serialize(const device_t *self, char *buffer, size_t size)
{
    const security_alarm_t *alarm = (const security_alarm_t *)self;
    (void)snprintf(buffer, size, "SECURITY_ALARM %d", (int)alarm->armed);
}
