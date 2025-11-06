#ifndef CONTROL_LOOP_H
#define CONTROL_LOOP_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Create a minimal PID-like controller state
 * We keep everything in a struct so the loop in reentrant and testable.
 * @author Luke Nam 
 */
typedef struct {
    float kp;
    float ki;
    float kd;

    float integral;
    float prev_error;

    float duty_cycle;
} pid_t;

/*
 * Initialize a PID controller with gains.
 * We keep it simple so CBMC can reason about it later
 * @author Luke Nam
 */
void pid_init(pid_t *pid, float kp, float ki, float kd);

/*
 * Perform one control step.
 * 
 * setpoint: desired value (e.g., target speed)
 * measure:  current value (e.g., current speed)
 * dt:       time step in seconds (fixed in a real embedded loop)
 * 
 * On return:
 * - pid->duty_cycle is updated and clamped to [0.0f, 1.0f]
 * - pid->integral is accumulated (anti-windup is very simple for now) 
 */
void pid_step(pid_t *pid, float setpoint, float measured, float dt);

#ifdef __cplusplus
}
#endif

#endif /* CONTROL_LOOP_H */