#ifndef HW_ABSTRACTION_H
#define HW_ABSTRACTION_H

#include <stdint.h>
#include "board_config.h"

// initialize clocks, timers, pwm, adc... for now: stubs
void hw_init(void);

// read current process variable (e.g. sensor); stubbed for now
float hw_read_sensor(void);

// write normalized duty (0..1) to PWM hardware; stub for now
void hw_pwm_write(float duty);

#endif