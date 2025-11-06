#include "hw_abstraction.h"

/* later: include "stm32h7xx_hal.h" */

/**
 * TODO: We need to create the HAL header file to connect to the STM32
 * Probably a file like stm32h753_hal.h
 * @author Luke Nam
 */
void hw_init(void) {
    /* TODO: HAL_Init();
       TODO: SystemClock_Config();
       TODO: MX_TIMx_Init();
       TODO: MX_ADCx_Init();
     */
}

/**
 * Reads a sensor value from the STM32
 * NOTE: Currently set to 0.0f to verify loop functionality
 * @author Luke Nam
 */
float hw_read_sensor(void) {
    return 0.0f;
}

/**
 * Write a duty cycle value (0..1) to TIMx->CCRy
 * TODO: Not finished. Complete for a future issue
 * @author Luke Nam
 */
void hw_pwm_write(float duty) {
    // Verify the clamps have been set
    if (duty < HW_PWM_MIN) duty = HW_PWM_MIN;
    if (duty > HW_PWM_MAX) duty = HW_PWM_MAX;
    (void)duty;
}
