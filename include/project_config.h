#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

#define CFG_NUM_CONTROL_LOOP_ITERATIONS 5

#define CFG_SENSOR_MIN 0.0f
#define CFG_SENSOR_MAX 100.0f

// Time interval represents seconds (e.g., 0.01f = 10ms)
#define CFG_DT_MIN 0.001f
#define CFG_DT_MAX 0.01f

#define CFG_INTEGRAL_MIN -500.0f
#define CFG_INTEGRAL_MAX 500.0f

#define CFG_PWM_MIN 0.0f
#define CFG_PWM_MAX 1.0f

#endif