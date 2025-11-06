// verify/cbmc/control_loop_gains_cbmc.c
#include "../../src/control_loop.h"
#include "../../include/project_config.h"

float nondet_float(void);

/**
 * Assumes that our kp/ki/kd values are within the min/max ranges
 * @author Luke Nam
 */
static void assume_gain_ranges(float *kp, float *ki, float *kd) {
    *kp = nondet_float();
    *ki = nondet_float();
    *kd = nondet_float();

    __CPROVER_assume(*kp >= CFG_KP_MIN && *kp <= CFG_KP_MAX);
    __CPROVER_assume(*ki >= CFG_KI_MIN && *ki <= CFG_KI_MAX);
    __CPROVER_assume(*kd >= CFG_KD_MIN && *kd <= CFG_KD_MAX);
}


/**
 * Assumes our set target and measured values are within the sensor values
 * Then, do the same by checking for dt range
 * @author Luke Nam
 */
static void assume_env(float *setpoint, float *measured, float *dt) {
    *setpoint = nondet_float();
    *measured = nondet_float();
    *dt = nondet_float();

    __CPROVER_assume(*setpoint >= CFG_SENSOR_MIN && *setpoint <= CFG_SENSOR_MAX);
    __CPROVER_assume(*measured >= CFG_SENSOR_MIN && *measured <= CFG_SENSOR_MAX);
    __CPROVER_assume(*dt >= CFG_DT_MIN && *dt <= CFG_DT_MAX);
}


/**
 * Verify that a reading is not NaN, since x==x is false for NaN
 * @author Luke Nam
 */
static void assert_finite(float x) {
    __CPROVER_assert(x == x, "finite float");
}

int main(void) {
    float kp, ki, kd;
    float setpoint, measured, dt;
    pid_t pid;

    assume_gain_ranges(&kp, &ki, &kd);
    assume_env(&setpoint, &measured, &dt);

    pid_init(&pid, kp, ki, kd);

    for (int i = 0; i < CFG_NUM_CONTROL_LOOP_ITERATIONS; i++) {
        measured = nondet_float();
        __CPROVER_assume(measured >= CFG_SENSOR_MIN && measured <= CFG_SENSOR_MAX);

        pid_step(&pid, setpoint, measured, dt);

        // check duty within PWM range
        __CPROVER_assert(pid.duty_cycle >= CFG_PWM_MIN, "duty lower-bounded");
        __CPROVER_assert(pid.duty_cycle <= CFG_PWM_MAX, "duty upper-bounded");

        // check integral within clamp
        __CPROVER_assert(pid.integral >= CFG_INTEGRAL_MIN &&
                         pid.integral <= CFG_INTEGRAL_MAX,
                         "integral bounded");

        // have no NaN readings for key states
        assert_finite(pid.duty_cycle);
        assert_finite(pid.integral);
    }

    return 0;
}
