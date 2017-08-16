# PWMFanController
This is a simple AVR based PWM PC fan controller.

The MCU is an ATtiny85.

Software in interrupt-driven. A potentiometer value is read by the ADC and then used to set the duty-cycle of a 8bits PWM, driving the fan's speed.
