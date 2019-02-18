#include "slave_API/slave_API.h"

int main(void)
{
    /* initialize the device */
    SYSTEM_Initialize();
    uint16_t period, dutyCycle, phase;

    period = 0xFFFF;
    dutyCycle = 0xFFF;
    phase = 0xF;

    config_PWM(PWM_GENERATOR_1, dutyCycle, phase, period);
    config_PWM(PWM_GENERATOR_2, dutyCycle, phase, period);
 
    PWM_ModuleEnable(PWM_GENERATOR_1);
    PWM_ModuleEnable(PWM_GENERATOR_2);

    while (1);
    return 1; 
}