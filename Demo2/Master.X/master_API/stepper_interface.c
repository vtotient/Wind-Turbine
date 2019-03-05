 /*
 * File:		stepper_interface.c
 * Purpose:	Interface with the stepper motor
 */

#include "stepper_interface.h"

FLAGS flags;

/* Global Variables */
volatile uint16_t ms1 = 0; // Used to count number of ms11
volatile uint16_t step = 0; // Used in the timer to count number of steps taken
volatile uint16_t desired_pos = 0; // The desired number of steps to be taken
volatile uint16_t cur_pos = 0; // The current relative position of stepper motor shaft
volatile uint16_t prev_pos = 0;
volatile uint16_t x = 0;

volatile uint16_t zero = 0; // Initialize to know value

/* 
 * Initialize the stepper motor.
 *
 * RETURN:  NULL
 *
 * PRE:     NULL
 *
 * POST:    Stepper motor may now be opperated on
 */
void init_stepper_interface(void){

    PWM_Initialize();
    
    /* Set the clock divison ratio for PWM */
    CLK_RATIO     clk  = ONE_FOUR; 

    /* Enable the clock divison circuit */
    set_PWM_CLK_DIV(clk);  

    /* Generates 100Hz */
    uint16_t period = 0x4E20;  

    config_PWM(PWM_GENERATOR_4, period/4, 3*(period/4), period); // Configure DC, PHASE, PER (in that order)
    enable_PWM_CLK_DIV(PWM_GENERATOR_4); // Enable clock divison 

    config_PWM(PWM_GENERATOR_3, period/4, 2*(period/4), period);
    enable_PWM_CLK_DIV(PWM_GENERATOR_3); 

    config_PWM(PWM_GENERATOR_2, period/4, period/4 , period);
    enable_PWM_CLK_DIV(PWM_GENERATOR_2); 

    config_PWM(PWM_GENERATOR_1, period/4, 0x00, period);
    enable_PWM_CLK_DIV(PWM_GENERATOR_1); 

    PWM_ModuleEnable(PWM_GENERATOR_1);
    PWM_ModuleEnable(PWM_GENERATOR_2);
    PWM_ModuleEnable(PWM_GENERATOR_3);
    PWM_ModuleEnable(PWM_GENERATOR_4);
    stop_stepper();

    /* Calibrate the windsensor */
    wind_sensor_calibrate();
}

void wind_sensor_calibrate(void){
    uint32_t i;
    /* ~1 Second software delay */
    _LATE0 = 1;
    for(i = 0; i < 10; i++){
        asm(
            "; Software delay \n"
            "MOV #65535, W2 \n"
            "loop:\n"
            "SUB #1, W2 \n"
            "BRA NZ, loop \n"
            );
    }
    _LATE0 = 0;

    /* Store the zero value */
    zero = ADC_Read12bitAverage(WIND_SENSOR, 40);
}

/*
 * Track wind direction and request stepper motor to follow. 
 *
 * RETURN:  Bool value. False if error has occurred
 *
 * PRE:     Stepper and wind sensor initialized
 *
 * POST:    Stepper tracks wind
 */
bool track_wind(void){
    uint16_t current_pos = ADC_Read12bitAverage(WIND_SENSOR, 40);

    if(current_pos >= zero - 10 && current_pos <= zero + 10){
        stop_stepper();
    }
    else if(current_pos > zero){
        spin_clockwise();
    }
    else if(current_pos < zero){
        spin_counterclockwise();
    }
    else{
        return false;
    }

    return true;
}

/*
 * Starts the stepper in a clockwise direction. The direction is encodng in the 
 * flags.step_dir field. A value of 0 corresponds to clockwise.
 * 
 * RETURN:  NULL
 * 
 * PRE:     Stepper is initialized. Flags are initialized. 
 * 
 * POST:    Stepper starts is a clockwise direction
 */
void spin_clockwise(void){
    if(flags.step_dir == 0){
        start_stepper();
    }
    else{
        change_stepper_dir();
        start_stepper();
    }
}

/*
 * Starts the stepper in a counterclockwise direction. The direction is encodng in the 
 * flags.step_dir field. A value of 1 corresponds to counterclockwise.
 * 
 * RETURN:  NULL
 * 
 * PRE:     Stepper is initialized. Flags are initialized. 
 * 
 * POST:    Stepper starts is a counterclockwise direction
 */
void spin_counterclockwise(void){
    if(flags.step_dir == 1){
        start_stepper();
    }
    else{
        change_stepper_dir();
        start_stepper();
    }
}

/*
 * Changes the direction of the stepper motor. Done by swapping 
 * the dc and phase of pmw1<->pwm2 and pwm3<->pwm4
 * 
 * RETURN:	NULL
 * 
 * PRE: 	Stepper initialized
 *
 * POST:	Stepper motor rotates in opposite direction
 */
void change_stepper_dir(void){
    stop_stepper();
    uint16_t swap1 = 0x0;
    uint16_t swap2 = 0x0;

    swap1 = PG1DC; // Mask for pwm2 DC
    swap2 = PG2DC; // Mask for pwm1 DC (read)

    PG1DC = swap2;
    PG2DC = swap1; // Values swaped (write)

    swap1 = PG3DC;
    swap2 = PG4DC; 

    PG3DC = swap2;
    PG4DC = swap1; 

    swap1 = PG3PHASE;
    swap2 = PG4PHASE;

    PG3PHASE = swap2;
    PG4PHASE = swap1;

    swap1 = PG2PHASE;
    swap2 = PG1PHASE;

    PG2PHASE = swap2;
    PG1PHASE = swap1;

    start_stepper();
    flags.step_dir ^= 1;
 }

 /*
  * Stops stepper motor by stopping PWM
  */
void stop_stepper(void){
    PWM_GENERATOR pwm1 = PWM_GENERATOR_1;
    PWM_GENERATOR pwm2 = PWM_GENERATOR_2;
    PWM_GENERATOR pwm3 = PWM_GENERATOR_3;
    PWM_GENERATOR pwm4 = PWM_GENERATOR_4;
    PWM_ModuleDisable(pwm1);
    PWM_ModuleDisable(pwm2);
    PWM_ModuleDisable(pwm3);
    PWM_ModuleDisable(pwm4);
    flags.on_off = 0;
}

/*
 * Starts stepper motor by starting PWM
 */ 
void start_stepper(){
    PWM_GENERATOR pwm1 = PWM_GENERATOR_1;
    PWM_GENERATOR pwm2 = PWM_GENERATOR_2;
    PWM_GENERATOR pwm3 = PWM_GENERATOR_3;
    PWM_GENERATOR pwm4 = PWM_GENERATOR_4;
    PWM_ModuleEnable(pwm1);
    PWM_ModuleEnable(pwm2);
    PWM_ModuleEnable(pwm3);
    PWM_ModuleEnable(pwm4);
    flags.on_off = 1;
}

/*
 * Counts the number of steps, passes the responsibilty of clearing the number 
 * of steps
 */
uint16_t STEPCOUNT_TASK(void){
    step++;
    if(flags.step_dir == 0){
        cur_pos++;
    } 
    else if(flags.step_dir == 1){
        cur_pos--;
    }
    STEPCONTROL_TASK();

    return 55;
}

/*
 * Drives the motor to the correct angle. If the number of steps == the desired step
 * i.e. the stepper motor is at the correct angle, clear the steps variable and stop motor
 */
uint16_t STEPCONTROL_TASK(void){    
    if(step >= desired_pos){
        step = 0;
        stop_stepper();
    }
    return 44;
}

/* 
 * This ISR drives the motor. 
 */
uint16_t START_TASK(void){
    if(desired_pos != x){ // Motor needs to move
        if(x > cur_pos){
            if( flags.step_dir == 1){
                change_stepper_dir();
            }

            desired_pos = x - prev_pos;
            
            if(!within_5( desired_pos, cur_pos) && flags.on_off == 0){ 
                start_stepper();
                prev_pos = cur_pos;
            }
        }
        else if(x < cur_pos){
            if(flags.step_dir == 0){
                change_stepper_dir(); 
            }

            desired_pos = prev_pos - x;
            
            if(!within_5( desired_pos, cur_pos) && flags.on_off == 0){ 
                start_stepper();
                prev_pos = cur_pos;
            }
        }
    }
    return 33;
}

/*
 * Checks if within a constant
 */ 
bool within_5(uint16_t prev, uint16_t current){
    if(current <= prev + WITHIN && current  >= prev - WITHIN){
        return true;
    } else if (prev == 0){
        return true;
    }
    return false;
}
