/*
 * File:        main.c
 * Purpose:     Main file for Slave Core
 */

#include "slave_API/slave_API.h"

uint16_t delay = 0;

int main(void)
{   
    /* initialize the device */
    SYSTEM_Initialize();
    mppt_init();

    /* Configure ADC channels */
    ADC_SetConfiguration(ADC_CONFIGURATION_DEFAULT);
    ADC_ChannelEnable(SENSOR_1);
    ADC_ChannelEnable(SENSOR_3);
    ADC_ChannelEnable(SENSOR_4);
    ADC_ChannelEnable(SENSOR_5);

    /* For the mailboxes */
    ProtocolB_DATA dataSend; 

    while (1){

        /* Mailbox write */
        MASTER_ProtocolBWrite((ProtocolB_DATA*)&dataSend);
        MASTER_InterruptRequestGenerate();
        MASTER_InterruptRequestGenerate();
        while(!MASTER_IsInterruptRequestAcknowledged());
        MASTER_InterruptRequestComplete();
        while(MASTER_IsInterruptRequestAcknowledged());

        /* Wait for boost converter to settle */
        for(delay = 0; delay < 50; delay++){
            asm(
                "; Software delay: 1ms\n"
                "MOV #1250, W2 \n"
                "loop:\n"
                "SUB #1, W2 \n"
                "BRA NZ, loop \n"
            );
        }

        /* Boost converter is now ready to be sampled */
        dataSend.ProtocolB[0] =  mppt();

     }

    return 1; 
}