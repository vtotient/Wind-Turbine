#include <xc.h>
#include "pwm_interface.h"

/*
 *
 */
bool config_PWM(PWM_GENERATOR pwmx, uint16_t dc, uint16_t phase, uint16_t per){
    switch(pwmx){
        case PWM_GENERATOR_1 :
            PWM_ModuleDisable(pwmx);
            PG1CONHbits.MDCSEL = 0; 
            PG1CONHbits.MPERSEL = 0;
            PG1CONHbits.MPHSEL = 0;
            PWM_DutyCycleSet(pwmx, dc); // 1/4 of the PER
            PWM_PeriodSet(pwmx, per);
            PWM_PhaseSet(pwmx, phase);
            return true;
        case PWM_GENERATOR_2 :
            PWM_ModuleDisable(pwmx);
            PG2CONHbits.MDCSEL = 0; 
            PG2CONHbits.MPERSEL = 0;
            PG2CONHbits.MPHSEL = 0;
            PWM_DutyCycleSet(pwmx, dc); // 1/2 of the PER
            PWM_PeriodSet(pwmx, per);
            PWM_PhaseSet(pwmx, phase); // Equal to the DC of PWM1
            return true;
        case PWM_GENERATOR_3 :
            PWM_ModuleDisable(pwmx);
            PG3CONHbits.MDCSEL = 0; 
            PG3CONHbits.MPERSEL = 0;
            PG3CONHbits.MPHSEL = 0;
            PWM_DutyCycleSet(pwmx, dc); // 3/4 of the period
            PWM_PeriodSet(pwmx, per);
            PWM_PhaseSet(pwmx, phase); // Equal to the DC of PWM2
            return true;
        case PWM_GENERATOR_4 :
            PWM_ModuleDisable(pwmx);
            PG4CONHbits.MDCSEL = 0; 
            PG4CONHbits.MPERSEL = 0;
            PG4CONHbits.MPHSEL = 0; // Disable master dc, phase, and period
            PWM_DutyCycleSet(pwmx, dc);
            PWM_PeriodSet(pwmx, per); 
            PWM_PhaseSet(pwmx, phase); // Equal to the DC of PWM3
            return true;
        case PWM_GENERATOR_5 :
            PWM_ModuleDisable(pwmx);
            PG5CONHbits.MDCSEL = 0; 
            PG5CONHbits.MPERSEL = 0;
            PG5CONHbits.MPHSEL = 0; // Disable master dc, phase, and period
            PWM_DutyCycleSet(pwmx, dc);
            PWM_PeriodSet(pwmx, per); 
            PWM_PhaseSet(pwmx, phase); // Equal to the DC of PWM3
            return true;
        case PWM_GENERATOR_6 :
            PWM_ModuleDisable(pwmx);
            PG6CONHbits.MDCSEL = 0; 
            PG6CONHbits.MPERSEL = 0;
            PG6CONHbits.MPHSEL = 0; // Disable master dc, phase, and period
            PWM_DutyCycleSet(pwmx, dc);
            PWM_PeriodSet(pwmx, per); 
            PWM_PhaseSet(pwmx, phase); // Equal to the DC of PWM3
            return true;
        case PWM_GENERATOR_7 :
            PWM_ModuleDisable(pwmx);
            PG7CONHbits.MDCSEL = 0; 
            PG7CONHbits.MPERSEL = 0;
            PG7CONHbits.MPHSEL = 0; // Disable master dc, phase, and period
            PWM_DutyCycleSet(pwmx, dc);
            PWM_PeriodSet(pwmx, per); 
            PWM_PhaseSet(pwmx, phase); // Equal to the DC of PWM3
            return true;
        case PWM_GENERATOR_8 :
            PWM_ModuleDisable(pwmx);
            PG8CONHbits.MDCSEL = 0; 
            PG8CONHbits.MPERSEL = 0;
            PG8CONHbits.MPHSEL = 0; // Disable master dc, phase, and period
            PWM_DutyCycleSet(pwmx, dc);
            PWM_PeriodSet(pwmx, per); 
            PWM_PhaseSet(pwmx, phase); // Equal to the DC of PWM3
            return true;
        default : return false;
    }
}