#include "../../src/control_loop.h"
#include "../../include/project_config.h"
#include "hw_abstraction.h"
#include "board_config.h"

/**
 * Initializes the controller to safe default gains within our verified ranges
 * TODO: Remove hardcoded test values into a config file
 * @author Luke Nam
 */
static void controller_init(pid_t *pid) {
    pid_init(pid, 0.5f, 0.1f, 0.0f);
}

/**
 * Wires the verified control loop into a real MCU-style infinite loop
 * @author Luke Nam
 */
int main(void) {
    pid_t motor_pid;
    controller_init(&motor_pid);

    hw_init();

    // simple forever loop; in real firmware you'd use a timer interrupt
    while (1) {
        float setpoint = 50.0f;              // TODO: get from comms/UI
        float measured = hw_read_sensor();   // from ADC or encoder
        float dt = HW_LOOP_DT_SECONDS;

        pid_step(&motor_pid, setpoint, measured, dt);

        hw_pwm_write(motor_pid.duty_cycle);
        // TODO: small delay to approximate dt, or move to timer ISR
    }
}
