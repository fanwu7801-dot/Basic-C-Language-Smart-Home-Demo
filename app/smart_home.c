#include "smart_home.h"

#include "bsp_storage.h"

#include <stdio.h>
#include <string.h>

static void smart_home_set_default_devices(smart_home_t *home);
static void smart_home_bind_devices(smart_home_t *home);
static void smart_home_show_panel(smart_home_t *home);
static void smart_home_set_message(smart_home_t *home, const char *message);
static void smart_home_sleep_mode(smart_home_t *home);
static void smart_home_away_mode(smart_home_t *home);
static int smart_home_load_line(const char *line, void *context);

void smart_home_init(smart_home_t *home)
{
    if (home == NULL)
    {
        return;
    }

    basic_ui_init(&home->ui);
    smart_home_set_default_devices(home);
    smart_home_bind_devices(home);
    smart_home_set_message(home, "System started.");

    if (smart_home_load(home, SMART_HOME_DATA_FILE))
    {
        smart_home_set_message(home, "Loaded previous state from device_data.txt.");
    }
}

void smart_home_run(smart_home_t *home)
{
    int running = 1;

    if (home == NULL)
    {
        return;
    }

    while (running)
    {
        int choice = -1;

        home->ui.clear(&home->ui);
        smart_home_show_panel(home);

        if (!home->ui.read_int(&home->ui, "Input command: ", &choice))
        {
            smart_home_set_message(home, "Invalid input. Please enter a number.");
            continue;
        }

        switch (choice)
        {
            case 1:
                light_toggle(&home->living_room_light);
                smart_home_set_message(home, "Device state changed.");
                break;
            case 2:
                light_toggle(&home->bedroom_light);
                smart_home_set_message(home, "Device state changed.");
                break;
            case 3:
            {
                int temperature = 0;
                if (!home->ui.read_int(&home->ui, "Input new target temperature: ", &temperature))
                {
                    smart_home_set_message(home, "Invalid input. Please enter a temperature number.");
                    break;
                }

                if (air_conditioner_set_target_temperature(&home->air_conditioner, temperature))
                {
                    smart_home_set_message(home, "Air conditioner target temperature updated.");
                }
                else
                {
                    smart_home_set_message(home, "Error: temperature must be between 16C and 30C.");
                }
                break;
            }
            case 4:
                smart_home_sleep_mode(home);
                break;
            case 5:
                smart_home_away_mode(home);
                break;
            case 0:
                if (smart_home_save(home, SMART_HOME_DATA_FILE))
                {
                    printf("System closing. State saved to %s.\n", SMART_HOME_DATA_FILE);
                }
                else
                {
                    printf("System closing, but state save failed.\n");
                }
                running = 0;
                break;
            default:
                smart_home_set_message(home, "Invalid command. Please try again.");
                break;
        }
    }
}

int smart_home_save(const smart_home_t *home, const char *path)
{
    char lines[SMART_HOME_DEVICE_COUNT + 1][128] = {{0}};
    const char *line_ptrs[SMART_HOME_DEVICE_COUNT + 1] = {0};
    int i = 0;

    if (home == NULL || path == NULL)
    {
        return 0;
    }

    (void)snprintf(lines[0], sizeof(lines[0]), "SMART_HOME_DATA_V1");
    line_ptrs[0] = lines[0];

    for (i = 0; i < SMART_HOME_DEVICE_COUNT; ++i)
    {
        const device_t *device = home->devices[i];
        line_ptrs[i + 1] = lines[i + 1];

        if (device != NULL && device->ops != NULL && device->ops->serialize != NULL)
        {
            device->ops->serialize(device, lines[i + 1], sizeof(lines[i + 1]));
        }
    }

    return bsp_storage_save_lines(path, line_ptrs, SMART_HOME_DEVICE_COUNT + 1);
}

int smart_home_load(smart_home_t *home, const char *path)
{
    if (home == NULL || path == NULL)
    {
        return 0;
    }

    return bsp_storage_load_lines(path, smart_home_load_line, home) > 0;
}

static void smart_home_set_default_devices(smart_home_t *home)
{
    light_init(&home->living_room_light, "living_room", "Living Room Light", DEVICE_OFF);
    light_init(&home->bedroom_light, "bedroom", "Bedroom Light", DEVICE_OFF);
    air_conditioner_init(&home->air_conditioner, "central_ac", "Central AC", 24, 26, DEVICE_ON);
    security_alarm_init(&home->security_alarm, "security_alarm", "Security Alarm", DEVICE_OFF);
}

static void smart_home_bind_devices(smart_home_t *home)
{
    home->devices[0] = &home->living_room_light.base;
    home->devices[1] = &home->bedroom_light.base;
    home->devices[2] = &home->air_conditioner.base;
    home->devices[3] = &home->security_alarm.base;
}

static void smart_home_show_panel(smart_home_t *home)
{
    int i = 0;

    home->ui.header(&home->ui);
    printf("Current home device status:\n");

    for (i = 0; i < SMART_HOME_DEVICE_COUNT; ++i)
    {
        const device_t *device = home->devices[i];
        if (device != NULL && device->ops != NULL && device->ops->display != NULL)
        {
            device->ops->display(device, i + 1);
        }
    }

    printf("=========================\n");
    if (home->last_message[0] != '\0')
    {
        home->ui.message(&home->ui, home->last_message);
    }
    home->ui.menu(&home->ui);
}

static void smart_home_set_message(smart_home_t *home, const char *message)
{
    if (home == NULL || message == NULL)
    {
        return;
    }

    (void)snprintf(home->last_message, sizeof(home->last_message), "%s", message);
}

static void smart_home_sleep_mode(smart_home_t *home)
{
    light_turn_off(&home->living_room_light);
    light_turn_off(&home->bedroom_light);
    (void)air_conditioner_set_target_temperature(&home->air_conditioner, 28);
    security_alarm_disarm(&home->security_alarm);
    smart_home_set_message(home, "Sleep mode enabled.");
}

static void smart_home_away_mode(smart_home_t *home)
{
    light_turn_off(&home->living_room_light);
    light_turn_off(&home->bedroom_light);
    air_conditioner_power_off(&home->air_conditioner);
    security_alarm_arm(&home->security_alarm);
    smart_home_set_message(home, "Away mode enabled.");
}

static int smart_home_load_line(const char *line, void *context)
{
    smart_home_t *home = (smart_home_t *)context;
    char key[32] = {0};

    if (line == NULL || home == NULL)
    {
        return 0;
    }

    if (sscanf(line, "%31s", key) != 1 || strcmp(key, "SMART_HOME_DATA_V1") == 0)
    {
        return 0;
    }

    if (strcmp(key, "LIGHT") == 0)
    {
        char id[32] = {0};
        int state = 0;

        if (sscanf(line, "%*s %31s %d", id, &state) != 2)
        {
            return 0;
        }

        if (strcmp(id, home->living_room_light.base.id) == 0)
        {
            light_set_state(&home->living_room_light, state ? DEVICE_ON : DEVICE_OFF);
            return 1;
        }

        if (strcmp(id, home->bedroom_light.base.id) == 0)
        {
            light_set_state(&home->bedroom_light, state ? DEVICE_ON : DEVICE_OFF);
            return 1;
        }
    }
    else if (strcmp(key, "AIR_CONDITIONER") == 0)
    {
        int current = 24;
        int target = 26;
        int power = DEVICE_ON;

        if (sscanf(line, "%*s %d %d %d", &current, &target, &power) == 3)
        {
            home->air_conditioner.current_temperature = current;
            home->air_conditioner.target_temperature = target;
            home->air_conditioner.power = power ? DEVICE_ON : DEVICE_OFF;
            return 1;
        }
    }
    else if (strcmp(key, "SECURITY_ALARM") == 0)
    {
        int armed = 0;

        if (sscanf(line, "%*s %d", &armed) == 1)
        {
            security_alarm_set_state(&home->security_alarm, armed ? DEVICE_ON : DEVICE_OFF);
            return 1;
        }
    }

    return 0;
}
