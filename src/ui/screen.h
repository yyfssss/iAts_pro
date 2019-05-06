#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "../src/target/target.h"

#include "ui/button.h"
#include "ui/screen_i2c.h"
#ifdef USE_BATTERY_MEASUREMENT
#include "ui/battery.h"
#endif

typedef struct tracker_s tracker_t;

#ifdef USE_WIFI
typedef struct wifi_s wifi_t;
#endif

// #if defined(ESP32) && defined(USE_MCPWM)
// typedef struct servo_mcpwm_s servo_t;
// #else
// typedef struct servo_pwmc_s servo_t;
// #endif

typedef enum
{
    SCREEN_MODE_MAIN,
    SCREEN_MODE_WIFI_CONFIG,
    SCREEN_MODE_WAIT_CONNECT,
    SCREEN_MODE_WAIT_SERVER,
} screen_main_mode_e;

typedef enum
{
    SCREEN_SECONDARY_MODE_NONE,
    SCREEN_SECONDARY_MODE_FREQUENCIES,
    SCREEN_SECONDARY_MODE_DEBUG_INFO,
} screen_secondary_mode_e;

typedef enum
{
    SCREEN_ORIENTATION_HORIZONTAL_LEFT = 0,
    SCREEN_ORIENTATION_HORIZONTAL_RIGHT,
    SCREEN_ORIENTATION_VERTICAL,
    SCREEN_ORIENTATION_VERTICAL_UPSIDE_DOWN,

#if defined(SCREEN_FIXED_ORIENTATION)
    SCREEN_ORIENTATION_DEFAULT = SCREEN_FIXED_ORIENTATION,
#else
#if defined(USE_RX_SUPPORT)
#if !defined(SCREEN_DEFAULT_ORIENTATION_RX)
#define SCREEN_DEFAULT_ORIENTATION_RX SCREEN_ORIENTATION_HORIZONTAL_LEFT
#endif
    SCREEN_ORIENTATION_DEFAULT = SCREEN_DEFAULT_ORIENTATION_RX,
#else
#if !defined(SCREEN_DEFAULT_ORIENTATION_TX)
#define SCREEN_DEFAULT_ORIENTATION_TX SCREEN_ORIENTATION_VERTICAL
#endif
    SCREEN_ORIENTATION_DEFAULT = SCREEN_DEFAULT_ORIENTATION_TX,
#endif
#endif
} screen_orientation_e;

typedef enum
{
    SCREEN_BRIGHTNESS_LOW,
    SCREEN_BRIGHTNESS_MEDIUM,
    SCREEN_BRIGHTNESS_HIGH,

    SCREEN_BRIGHTNESS_DEFAULT = SCREEN_BRIGHTNESS_LOW,
} screen_brightness_e;

typedef struct screen_s
{
    struct
    {
        screen_i2c_config_t cfg;
        tracker_t *tracker;
        // servo_t *servo;
#if defined(USE_WIFI)
        wifi_t *wifi;
#endif
#if defined(USE_BATTERY_MEASUREMENT)
        battery_t *battery;
#endif
        bool available;
        int8_t main_mode;      // from screen_main_mode_e
        int8_t secondary_mode; // from screen_secondary_mode_e
        struct
        {
            int8_t page;
            int8_t count;
        } telemetry;
        unsigned w;
        unsigned h;
        unsigned direction;
        char *buf;
        bool splashing;
    } internal;
} screen_t;

// bool screen_init(screen_t *screen, screen_i2c_config_t *cfg, servo_t *servo);
bool screen_init(screen_t *screen, screen_i2c_config_t *cfg, tracker_t *tracker);
bool screen_is_available(const screen_t *screen);
void screen_shutdown(screen_t *screen);
void screen_power_on(screen_t *screen);
void screen_enter_secondary_mode(screen_t *screen, screen_secondary_mode_e mode);

bool screen_handle_button_event(screen_t *screen, bool before_menu, const button_event_t *ev);

void screen_update(screen_t *screen);
void screen_splash(screen_t *screen);
void screen_set_orientation(screen_t *screen, screen_orientation_e orientation);
void screen_set_brightness(screen_t *screen, screen_brightness_e brightness);
bool screen_is_animating(const screen_t *screen);