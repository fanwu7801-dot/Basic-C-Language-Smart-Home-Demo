/******************************************************************************
 * @file security_alarm.h
 * @brief OOP-style security alarm device.
 ******************************************************************************/
#ifndef SECURITY_ALARM_H
#define SECURITY_ALARM_H

#include "device.h"

typedef struct security_alarm
{
    device_t base;
    device_state_t armed;
} security_alarm_t;

void security_alarm_init(security_alarm_t *alarm, const char *id, const char *name, device_state_t armed);
void security_alarm_arm(security_alarm_t *alarm);
void security_alarm_disarm(security_alarm_t *alarm);
void security_alarm_set_state(security_alarm_t *alarm, device_state_t armed);

#endif // SECURITY_ALARM_H
