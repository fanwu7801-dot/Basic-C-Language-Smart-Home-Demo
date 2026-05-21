/******************************************************************************
 * @file smart_home.h
 * @brief Smart home central controller.
 ******************************************************************************/
#ifndef SMART_HOME_H
#define SMART_HOME_H

#include "air_conditioner.h"
#include "basic_ui.h"
#include "device.h"
#include "light.h"
#include "security_alarm.h"

#define SMART_HOME_DEVICE_COUNT 4
#define SMART_HOME_DATA_FILE "device_data.txt"

typedef struct smart_home
{
    basic_ui_t ui;
    light_t living_room_light;
    light_t bedroom_light;
    air_conditioner_t air_conditioner;
    security_alarm_t security_alarm;
    device_t *devices[SMART_HOME_DEVICE_COUNT];
    char last_message[128];
} smart_home_t;

void smart_home_init(smart_home_t *home);
void smart_home_run(smart_home_t *home);
int smart_home_save(const smart_home_t *home, const char *path);
int smart_home_load(smart_home_t *home, const char *path);

#endif // SMART_HOME_H
