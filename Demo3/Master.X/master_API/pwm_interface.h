/*
 File:        pwm_interface.h
 Purpose:     Header file for pwm_interface
 */

#ifndef PWM_INTERFACE_H
#define PWM_INTERFACE_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "../mcc_generated_files/mcc.h"

#define MAX_STEPPER_FREQ 100
#define MIN_STEPPER_FREQ 30
#define CLK_PRESCALER    2000000

typedef enum
{
  ONE_TWO = 0x0,
  ONE_FOUR = 0x1,
  ONE_EIGHT = 0x2,
  ONE_SIXTEEN = 0x3,
} CLK_RATIO;

bool config_PWM(PWM_GENERATOR pwmx, uint16_t dc, uint16_t phase, uint16_t per);
bool enable_PWM_CLK_DIV(PWM_GENERATOR pwmx);
void set_PWM_CLK_DIV(CLK_RATIO ratio);
bool set_stepper_freq(uint16_t desired_freq);

#endif