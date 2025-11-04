#include "../../src/control_loop.h"

float nondet_float(void);
const int NUM_CONTROL_LOOP_ITERATIONS = 5;

int main(void) {
    pid_t pid;
    pid_init(&pid, 0.5f, 0.1f, 0.0f);

    // Environment variables that stay the same across steps
    float setpoint = nondet_float();
    float dt = nondet_float();

    __CPROVER_assume(setpoint >= 0.0f && setpoint <= 100.0f);
    __CPROVER_assume(dt >= 0.001f && dt <= 0.01f);

    /**
     * Simulate a set number of control loop iterations. Each iteration has
     * the chance for a different measurement (e.g., noise, sensor jitter),
     * but setpoint and dt stay in-range.
     * 
     * NOTE: Refactor to externalize control loop iteration number to a config file
     */
    for (int i=0; i < NUM_CONTROL_LOOP_ITERATIONS; i++) {
        float measured = nondet_float();
        __CPROVER_assume(measured >= 0.0f && measured <= 100.0f);
        pid_step(&pid, setpoint, measured, dt);

        // After each step, the duty_cycle must stay safe
        __CPROVER_assert(pid.duty_cycle >= 0.0f, "duty_cycle lower-bounded");
        __CPROVER_assert(pid.duty_cycle <= 1.0f, "duty_cycle upper-bounded");

        // Integral should never escape the clamp
        __CPROVER_assert(pid.integral >= -500.0f && pid.integral <= 500.0f);

    }

    return 0;
}