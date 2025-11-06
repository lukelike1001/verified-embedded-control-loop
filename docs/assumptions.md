WORK IN PROGRESS

FORMAL-02:
I formally verified boundness of the control output over multiple control cycles under bounded sensor noise and bounded loop period. In other words, for any reasonable setpoint (0-100), any reasonable sensor reading (0-100), and any loop period between 1ms..10ms, no matter how the snsor jitters over 5 consecutive iterations, the control loop loop will never command a PWM duty cycle outside [0,1] nor let the integral blow past the clamp.