#include "control_loop.h"

// Simple init: zero state, user supplies gains.
void pid_init(pid_t *pid, float kp, float ki, float kd) {
    if (!pid) {
        return;
    }

    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;

    pid->integral = 0.0f;
    pid-> prev_error = 0.0f;
    pid->duty_cycle = 0.0f;
}

/*
 * Very small, very predictable control step.
 * This is intentionally a bit "boring" so we can verify it.
 * Note that in a real embeded loop, dt is fixed.
 * @author Luke Nam
 */
void pid_step(pid_t *pid, float setpoint, float measured, float dt) {
    if (!pid) {
        return;
    }
    if (dt <= 0.0f) {
        dt = 0.001f;
    }

    float error = setpoint - measured;
    float p_term = pid->kp * error;
    pid->integral += error * dt;

    if (pid->integral > 500.0f) {
        pid->integral = 500.0f;
    } else if (pid->integral < -500.0f) {
        pid->integral = -500.0f;
    }
    float i_term = pid->ki * pid->integral;

    float derivative = (error - pid->prev_error) / dt;
    float d_term = pid-> kd * derivative;

    float control = p_term + i_term + d_term;

    if (control > 1.0f) {
        control = 1.0f;
    } else if (control < 0.0f) {
        control = 0.0f;
    }

    pid->duty_cycle = control;
    pid->prev_error = error;
}