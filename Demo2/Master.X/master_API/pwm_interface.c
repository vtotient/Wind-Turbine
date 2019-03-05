/*
 File:        pwm_interface.c
 Purpose:     Used to wrap the mcc_generated files 
              for easier interfacing with the pwm generators.
 */

#include <xc.h>
#include "pwm_interface.h"

/*
 * Configures the appropriate PWM generators for the Slave core. Independent edge
 * complementary mode. Each generator is running on independed time bases. Also
 * disables the master settings for the PWM generators.
 * 
 * pmx:    Enumerated type (see mcc_generated_files/pwm.h), used to select which 
 *         generator to use.
 * dc:     Desired duty cycle
 * phase:  Desired phase
 * per:    Desired period
 *
 * RETURN: True if succesfull, false otherwise
 *
 * PRE:    PWM generator pmx has been disabled
 * POST:   NULL
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

        default : return false;
    }
}

/*
 * Enable the PWM channel's clock as: master clock divided clock divider circuit
 * In other words set a particular pwm instance's clock to be master clock divided by 
 * value selected in set_PWM_CLK_DIV. 
 *
 * pmx:    Enumerated type (see mcc_generated_files/pwm.h), used to select which 
 *         generator to use.
 *
 * RETURN: True if succesfull, false otherwise
 * 
 * PRE:    Prescalar is set by set_PWM_CLK_DIV. 
 * 
 * POST:   NULL
 */
bool enable_PWM_CLK_DIV(PWM_GENERATOR pwmx){

    switch(pwmx){
        case PWM_GENERATOR_1 :
            PG1CONLbits.CLKSEL = 0x02;
            return true;
       case PWM_GENERATOR_2 :
           PG2CONLbits.CLKSEL = 0x02;
           return true;
       case PWM_GENERATOR_3 :
           PG3CONLbits.CLKSEL = 0x02;
           return true;
       case PWM_GENERATOR_4 :
           PG4CONLbits.CLKSEL = 0x02;
           return true;
        default : return false;
    }
}

/*
 * Set the ratio for clock division (Pre-scalar value)
 *
 * ratio:   Enum type used to set the pre-scalar value (see pwm_interface.h)
 * 
 * RETURN:  void
 * 
 * PRE:     Appropriate clocks are selected
 * 
 * POST:    PWM master time base changed
 */
void set_PWM_CLK_DIV(CLK_RATIO ratio){
    PCLKCONbits.DIVSEL = ratio;
}

/*
 * Set the desired frequency of the stepper motor. Frequency must be in the range
 * of 30Hz to 100Hz. The frequency controls the speed at which the stepper motor runs.
 *
 * desired_freq: 16-bit u-int. 30-100
 *
 * RETURN:  Bool val. If true false the requested frequency was out of bounds
 *
 * PRE:     A CLK_RATIO of ONE_FOUR is selected so that
 *          PG time base is 2MHz
 * 
 * POST:    PGxPER is adjusted such that desired frequency is 
 *          set.
 */
bool set_stepper_freq(uint16_t desired_freq){

    if(desired_freq < MIN_STEPPER_FREQ || desired_freq > MAX_STEPPER_FREQ){
        return false;
    }

    uint16_t period = CLK_PRESCALER / desired_freq;

    PWM_PeriodSet(PWM_GENERATOR_1, period);
    PWM_PeriodSet(PWM_GENERATOR_2, period);
    PWM_PeriodSet(PWM_GENERATOR_3, period);
    PWM_PeriodSet(PWM_GENERATOR_4, period);

    return true;
}


