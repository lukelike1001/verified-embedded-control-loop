#include "control_loop.h"
#include "../include/project_config.h"

static float clampf(float v, float lo, float hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}


/**
 * Initializes the PID controller to a zero state
 * @author Luke Nam
 */
void pid_init(pid_t *pid, float kp, float ki, float kd) {
    if (!pid) return;

    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;

    pid->integral = 0.0f;
    pid->prev_error = 0.0f;
    pid->duty_cycle = 0.0f;
}


/**
 * Computes the i_term for the PID ontroller
 * @author Luke Nam
 */
static float compute_integral(pid_t *pid, float error, float dt) {
    pid->integral += error * dt;
    pid->integral = clampf(pid->integral, CFG_INTEGRAL_MIN, CFG_INTEGRAL_MAX);
    return pid->ki * pid->integral;
}


/**
 * Computes the d_term for the PID controller
 * @author Luke Nam
 */
static float compute_derivative(pid_t *pid, float error, float dt) {
    // avoid division by zero
    if (dt <= 0.0f) {
        dt = CFG_DT_MIN;
    }
    
    float derivative = (error - pid->prev_error) / dt;
    return pid->kd * derivative;
}


/**
 * Simulates the control step of a simple PID controller
 * Note that in a real embedded loop, dt is fixed.
 * @author Luke Nam
 */
void pid_step(pid_t *pid, float setpoint, float measured, float dt) {
    if (!pid) return;
    if (dt <= 0.0f) dt = 0.001f;

    float error = setpoint - measured;

    float p_term = pid->kp * error;
    float i_term = compute_integral(pid, error, dt);
    float d_term = compute_derivative(pid, error, dt);

    float control = p_term + i_term + d_term;
    control = clampf(control, CFG_PWM_MIN, CFG_PWM_MAX);

    pid->duty_cycle = control;
    pid->prev_error = error;

}
