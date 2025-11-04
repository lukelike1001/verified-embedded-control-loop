#include "../../src/control_loop.h"

/*
 * CBMC will provide this symbol. It represents an arbitrary float.
 * We constrain it later with __CPROVER_assume.
 */
float nondet_float(void);

int main(void) {
    pid_t pid;

    // Initialize with fixed gains for easier proving.
    pid_init(&pid, 0.5f, 0.1f, 0.0f);

    // Nondet inputs: setpoint, measured value, and time step.
    float setpoint = nondet_float();
    float measured = nondet_float();
    float dt = nondet_float();

    /*
     * Assumptions = our model of the environment
     * These make the state space finite and realistic.
     */
    __CPROVER_assume(setpoint >= 0.0f && setpoint <= 100.0f);
    __CPROVER_assume(measured >= 0.0f && measured <= 100.0f);

    // Control loops usually run from -50Hz to 2 kHz.
    __CPROVER_assume(dt >= 0.0005f && dt <= 0.02f);

    // Run exactly one control step.
    pid_step(&pid, setpoint, measured, dt);

    __CPROVER_assert(pid.duty_cycle >= 0.0f, "duty_cycle is lower-bounded");
    __CPROVER_assert(pid.duty_cycle <= 1.0f, "duty_cycle is upper-bounded");

    // Check that the integral stayed within the applied clamp.
    __CPROVER_assert(pid.integral <= 500.0f && pid.integral >= -500.0f,
                        "integral is within clamp range");
    
    return 0;

}