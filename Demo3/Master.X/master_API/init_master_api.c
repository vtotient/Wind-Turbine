/*
 File:        init_master_api.c
 Purpose:     Set up the Master Core API
 */

#include "init_master_api.h"

#ifndef GLOBAL_DC
    #define GLOBAL_DC
    volatile int16_t new_s_dc;
#endif

/*
 * Initializes the system. Must Initialize in presented order
 *
 * RETURN: 	NULL
 *
 * PRE: 	Nothing exe yet
 *
 * POST:	System operational
 */
void init_master_api(void){
    _ANSELB2 = 1;
    _TRISC4 = 0;
    SYSTEM_Initialize();
    UART1_Initialize();

    ADC_SetConfiguration(ADC_CONFIGURATION_DEFAULT);
    ADC_ChannelEnable(WIND_SENSOR);

    /* Calibrate windsensor then start timer */
    init_stepper_interface();

    SLAVE1_Program();
    SLAVE1_Start();
}