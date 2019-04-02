/*
 * File:        main.c
 * Purpose:     Main file for Slave Core
 */

 #include "slave_API/slave_API.h"

uint16_t debug = 0;

int main(void)
{   
    /* initialize the device */
    SYSTEM_Initialize();
    mppt_init();
    mppt_pid_init();

    ADC_SetConfiguration(ADC_CONFIGURATION_DEFAULT);
    ADC_ChannelEnable(SENSOR_1);
    ADC_ChannelEnable(SENSOR_3);
    ADC_ChannelEnable(SENSOR_4);
    ADC_ChannelEnable(SENSOR_5);

    PWM_ModuleDisable(PWM_GENERATOR_5);
    PWM_DutyCycleSet(PWM_GENERATOR_5, INIT_PER/2);
    PWM_ModuleEnable(PWM_GENERATOR_5);

    /* For the mailboxes */
    ProtocolB_DATA dataSend; 


    while (1){

        dataSend.ProtocolB[0] = PG5CONLbits.CLKSEL;//ADC_Read12bitAverage(SENSOR_1, 40)/10; //mppt();

        // /* Mailbox write */
        MASTER_ProtocolBWrite((ProtocolB_DATA*)&dataSend);
        MASTER_InterruptRequestGenerate();

        MASTER_InterruptRequestGenerate();
        while(!MASTER_IsInterruptRequestAcknowledged());
        MASTER_InterruptRequestComplete();
        while(MASTER_IsInterruptRequestAcknowledged());

        // /* Wait for boost converter to settle */
        // for(debug = 0; debug < 1; debug++)
        //  asm(
        //     "; Software delay \n"
        //     "MOV #65535, W2 \n"
        //     "loop:\n"
        //     "SUB #1, W2 \n"
        //     "BRA NZ, loop \n"
        //     );

        mppt();

     }

    return 1; 
}