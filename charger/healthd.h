/*
 * Copyright (C) 2013 The Android Open Source Project
 * Copyright (C) 2015 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _HEALTHD_H_
#define _HEALTHD_H_

#include <batteryservice/BatteryService.h>
#include <sys/types.h>
#include <utils/Errors.h>
#include <utils/String8.h>

// periodic_chores_interval_fast, periodic_chores_interval_slow: intervals at
// which healthd wakes up to poll health state and perform periodic chores,
// in units of seconds:
//
//    periodic_chores_interval_fast is used while the device is not in
//    suspend, or in suspend and connected to a charger (to watch for battery
//    overheat due to charging).  The default value is 60 (1 minute).  Value
//    -1 turns off periodic chores (and wakeups) in these conditions.
//
//    periodic_chores_interval_slow is used when the device is in suspend and
//    not connected to a charger (to watch for a battery drained to zero
//    remaining capacity).  The default value is 600 (10 minutes).  Value -1
//    tuns off periodic chores (and wakeups) in these conditions.
//
// power_supply sysfs attribute file paths.  Set these to specific paths
// to use for the associated battery parameters.  healthd will search for
// appropriate power_supply attribute files to use for any paths left empty:
//
//    batteryStatusPath: charging status (POWER_SUPPLY_PROP_STATUS)
//    batteryHealthPath: battery health (POWER_SUPPLY_PROP_HEALTH)
//    batteryPresentPath: battery present (POWER_SUPPLY_PROP_PRESENT)
//    batteryCapacityPath: remaining capacity (POWER_SUPPLY_PROP_CAPACITY)
//    batteryVoltagePath: battery voltage (POWER_SUPPLY_PROP_VOLTAGE_NOW)
//    batteryTemperaturePath: battery temperature (POWER_SUPPLY_PROP_TEMP)
//    batteryTechnologyPath: battery technology (POWER_SUPPLY_PROP_TECHNOLOGY)
//    batteryCurrentNowPath: battery current (POWER_SUPPLY_PROP_CURRENT_NOW)
//    batteryCurrentAvgPath: battery average (POWER_SUPPLY_PROP_CURRENT_AVG)
//    batteryChargeCounterPath: battery accumulated charge
//                                         (POWER_SUPPLY_PROP_CHARGE_COUNTER)
//
//    dockBatteryStatusPath: dock charging status (POWER_SUPPLY_PROP_STATUS)
//    dockBatteryHealthPath: dock battery health (POWER_SUPPLY_PROP_HEALTH)
//    dockBatteryPresentPath: dock battery present (POWER_SUPPLY_PROP_PRESENT)
//    dockBatteryCapacityPath: remaining dock capacity (POWER_SUPPLY_PROP_CAPACITY)
//    dockBatteryVoltagePath: dock battery voltage (POWER_SUPPLY_PROP_VOLTAGE_NOW)
//    dockBatteryTemperaturePath: dock battery temperature (POWER_SUPPLY_PROP_TEMP)
//    dockBatteryTechnologyPath: dock battery technology (POWER_SUPPLY_PROP_TECHNOLOGY)
//    dockBatteryCurrentNowPath: dock battery current (POWER_SUPPLY_PROP_CURRENT_NOW)
//    dockBatteryCurrentAvgPath: dock battery average (POWER_SUPPLY_PROP_CURRENT_AVG)
//    dockBatteryChargeCounterPath: dock battery accumulated charge
//                                         (POWER_SUPPLY_PROP_CHARGE_COUNTER)
//
// The dockBatterySupported property indicates whether a dock battery is supported
// by the device, and whether this module should fetch dock battery values.
// Defaults is to false.

struct healthd_config {
    int periodic_chores_interval_fast;
    int periodic_chores_interval_slow;

    android::String8 batteryStatusPath;
    android::String8 batteryHealthPath;
    android::String8 batteryPresentPath;
    android::String8 batteryCapacityPath;
    android::String8 batteryVoltagePath;
    android::String8 batteryTemperaturePath;
    android::String8 batteryTechnologyPath;
    android::String8 batteryCurrentNowPath;
    android::String8 batteryCurrentAvgPath;
    android::String8 batteryChargeCounterPath;

    int (*energyCounter)(int64_t *);
    int boot_min_cap;
    bool (*screen_on)(android::BatteryProperties *props);

    bool dockBatterySupported;
    android::String8 dockBatteryStatusPath;
    android::String8 dockBatteryHealthPath;
    android::String8 dockBatteryPresentPath;
    android::String8 dockBatteryCapacityPath;
    android::String8 dockBatteryVoltagePath;
    android::String8 dockBatteryTemperaturePath;
    android::String8 dockBatteryTechnologyPath;
    android::String8 dockBatteryCurrentNowPath;
    android::String8 dockBatteryCurrentAvgPath;
    android::String8 dockBatteryChargeCounterPath;

    int (*dockEnergyCounter)(int64_t *);
};

// Global helper functions

int healthd_register_event(int fd, void (*handler)(uint32_t));
void healthd_battery_update();
android::status_t healthd_get_property(int id,
    struct android::BatteryProperty *val);
android::status_t healthd_get_dock_property(int id,
    struct android::BatteryProperty *val);
void healthd_dump_battery_state(int fd);

struct healthd_mode_ops {
    void (*init)(struct healthd_config *config);
    int (*preparetowait)(void);
    void (*heartbeat)(void);
    void (*battery_update)(struct android::BatteryProperties *props);
};

extern struct healthd_mode_ops *healthd_mode_ops;

// Charger mode

void healthd_mode_charger_init(struct healthd_config *config);
int healthd_mode_charger_preparetowait(void);
void healthd_mode_charger_heartbeat(void);
void healthd_mode_charger_battery_update(
    struct android::BatteryProperties *props);

// The following are implemented in libhealthd_board to handle board-specific
// behavior.
//
// healthd_board_init() is called at startup time to modify healthd's
// configuration according to board-specific requirements.  config
// points to the healthd configuration values described above.  To use default
// values, this function can simply return without modifying the fields of the
// config parameter.

void healthd_board_init(struct healthd_config *config);

// Process updated battery property values.  This function is called when
// the kernel sends updated battery status via a uevent from the power_supply
// subsystem, or when updated values are polled by healthd, as for periodic
// poll of battery state.
//
// props are the battery properties read from the kernel.  These values may
// be modified in this call, prior to sending the modified values to the
// Android runtime.
//
// Return 0 to indicate the usual kernel log battery status heartbeat message
// is to be logged, or non-zero to prevent logging this information.

int healthd_board_battery_update(struct android::BatteryProperties *props);

//This API is called to turn on/off the display backlight incase it can't be
//handle correcty in the display driver by calling gr_fg_blank();
void healthd_board_mode_charger_set_backlight(bool en);

//This API is called to update the battery/charging status by using the user
//noticeable method other then the animation, such as: LEDs
void healthd_board_mode_charger_battery_update(struct android::BatteryProperties *batt_prop);

//This API is used to handle some board specific charger mode initialization,
//such as: checking the charging is enabled or not.
void healthd_board_mode_charger_init(void);

//This API is called in the draw_battery() function to draw more infomation
//about the battery on the animation, such as the SoC (State of Charge).
void healthd_board_mode_charger_draw_battery(struct android::BatteryProperties *batt_prop);

#endif /* _HEALTHD_H_ */
