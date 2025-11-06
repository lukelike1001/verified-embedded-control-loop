#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include "../../include/project_config.h"

/*
 * Hardware-related constants for the STM32H753 Nucleo.
 * NOTE: Map real PWM pins/timers for a later issue
 */
#define HW_LOOP_DT_SECONDS   (CFG_DT_MIN)
#define HW_PWM_MIN           (CFG_PWM_MIN)
#define HW_PWM_MAX           (CFG_PWM_MAX)

// Placeholder ADC range if we read a pot/sensor later
#define HW_ADC_MAX_VALUE     4095.0f
#define HW_SENSOR_MAX_ENGINEERED  (CFG_SENSOR_MAX)

#endif
