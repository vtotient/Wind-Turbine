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

    PWM_ModuleEnable(PWM_GENERATOR_1);

    /* For the mailboxes */
    ProtocolB_DATA dataSend; 

    while (1){

        //if(debug == 0){
        dataSend.ProtocolB[0] = ADC_ReadPercentage(SENSOR_1);
        // }
        // else if(debug == 11){
        //      dataSend.ProtocolB[0] = 11;
        // }
        // else if(debug == 22){
        //      dataSend.ProtocolB[0] = 22;
        // }
        // else if(debug == 33)
        //     dataSend.ProtocolB[0] = 33;
        // else if(debug == 44)
        //     dataSend.ProtocolB[0] = 33;
        // else
        //     dataSend.ProtocolB[0] = 55;

        /* Mailbox write */
        MASTER_ProtocolBWrite((ProtocolB_DATA*)&dataSend);
        MASTER_InterruptRequestGenerate();

        MASTER_InterruptRequestGenerate();
        while(!MASTER_IsInterruptRequestAcknowledged());
        MASTER_InterruptRequestComplete();
        while(MASTER_IsInterruptRequestAcknowledged());

        /* Duty Cycle for boost convertor */
        //debug = mppt();

    }

    return 1; 
}