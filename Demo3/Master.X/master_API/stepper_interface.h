 /*
 * File:    stepper_interface.h
 * Purpose: Header file for stepper interface
 */

#ifndef STEPPER_INTERFACE_H
#define STEPPER_INTERFACE_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef PWM_H
  #include "../mcc_generated_files/mcc.h"
#endif

#ifndef ADC_H
    #include "adc1.h"
#endif

#include "pwm_interface.h"
#include "adc1.h"

#define PWM_PULSE_TIME 33/2
#define WITHIN 10

#ifndef MAX_WIND_RANGE
    #define MAX_WIND_RANGE 4095
#endif

#ifndef MIN_WIND_RANGE
    #define MIN_WIND_RANGE 0
#endif

/* Global vars */
extern volatile uint16_t zero;
extern volatile uint16_t desired_pos; 

/* System Variables */
typedef union
{
    uint8_t all_flags;

    struct 
    {
        uint8_t led_flag    : 1, // For toggling LEDs
                timer       : 1, // For stall
                btn_pressed : 1, // For LED toggle
                reliable    : 1, // Debouncing 
                step_dir    : 1, // Stepper Motor direction
                arrive      : 1, 
                on_off      : 1, // Motor on/off
                spare6      : 1;
    };

} FLAGS;

void change_stepper_dir(void);
void stop_stepper(void);
void start_stepper(void);
uint16_t STEPCOUNT_TASK(void);
uint16_t STEPCONTROL_TASK(void);
uint16_t START_TASK(void);
bool within_5(uint16_t prev, uint16_t current);
void init_stepper_interface(void);
void wind_sensor_calibrate(void);
bool track_wind(void);
void spin_clockwise(void);
void spin_counterclockwise(void);

#endif