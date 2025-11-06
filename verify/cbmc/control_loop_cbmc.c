#include "../../src/control_loop.h"
#include "../../include/project_config.h"

/*
 * CBMC will provide this symbol. It represents an arbitrary float.
 * We constrain it later with __CPROVER_assume.
 */
float nondet_float(void);

int main(void) {
    pid_t pid;

    // NOTE: Externalize fixed gains to a separate config file for a later refactor
    pid_init(&pid, 0.5f, 0.1f, 0.0f);

    // Nondet inputs: setpoint, measured value, and time step.
    float setpoint = nondet_float();
    float measured = nondet_float();
    float dt = nondet_float();

    /**
     * Tighten environment assumptions to verify sensor range is within
     * our pre-set ranges
     */
    __CPROVER_assume(setpoint >= CFG_SENSOR_MIN && setpoint <= CFG_SENSOR_MAX);
    __CPROVER_assume(measured >= CFG_SENSOR_MIN && measured <= CFG_SENSOR_MAX);
    __CPROVER_assume(dt >= CFG_DT_MIN && dt <= CFG_DT_MAX);

    // Run exactly one control step.
    pid_step(&pid, setpoint, measured, dt);

    __CPROVER_assert(pid.duty_cycle >= CFG_PWM_MIN, "duty_cycle is lower-bounded");
    __CPROVER_assert(pid.duty_cycle <= CFG_PWM_MAX, "duty_cycle is upper-bounded");

    // Check that the integral stayed within the applied clamp.
    __CPROVER_assert(pid.integral >= CFG_INTEGRAL_MIN && pid.integral <= CFG_INTEGRAL_MAX,
                        "integral is within clamp range");
    
    return 0;

}