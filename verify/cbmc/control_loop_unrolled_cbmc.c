#include "../../src/control_loop.h"
#include "../../include/project_config.h"

float nondet_float(void);

int main(void) {
    pid_t pid;
    pid_init(&pid, 0.5f, 0.1f, 0.0f);

    // Environment variables that stay the same across steps
    float setpoint = nondet_float();
    float dt = nondet_float();

    __CPROVER_assume(setpoint >= CFG_SENSOR_MIN && setpoint <= CFG_SENSOR_MAX);
    __CPROVER_assume(dt >= CFG_DT_MIN && dt <= CFG_DT_MAX);

    /**
     * Simulate a set number of control loop iterations. Each iteration has
     * the chance for a different measurement (e.g., noise, sensor jitter),
     * but setpoint and dt stay in-range.
     * 
     * NOTE: Refactor to externalize control loop iteration number to a config file
     */
    for (int i=0; i < CFG_NUM_CONTROL_LOOP_ITERATIONS; i++) {
        float measured = nondet_float();
        __CPROVER_assume(measured >= CFG_SENSOR_MIN && measured <= CFG_SENSOR_MAX);
        pid_step(&pid, setpoint, measured, dt);

        // After each step, the duty_cycle must stay safe
        __CPROVER_assert(pid.duty_cycle >= CFG_PWM_MIN, "duty_cycle lower-bounded");
        __CPROVER_assert(pid.duty_cycle <= CFG_PWM_MAX, "duty_cycle upper-bounded");

        // Integral should never escape the clamp
        __CPROVER_assert(pid.integral >= CFG_INTEGRAL_MIN && pid.integral <= CFG_INTEGRAL_MAX);

    }

    return 0;
}