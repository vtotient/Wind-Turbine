/*
 File:        main.c
 Purpose:     Master main code
 */

#include "master_API/master_API.h"
#pragma message "Connect USB-UART port on board to your PC and set COM port to: 9600 baud, 8-bit, 1 stop."

int main(void)
{

    /* Initialize the device */
    init_master_api();

    /* Initialize the screen */
    printf("\033[2J");      //Clear screen
    printf("\033[0;0f");    //return cursor to 0,0
    printf("\033[?25l");    //disable cursor
    printf("------------------------------------------------------------------\r\n");
    printf("Group C6: Controller Demo2\r\n");
    printf("------------------------------------------------------------------\r\n");
    printf("Wind Senesor - controls active stepper motor\r\n");
    printf("\r\n");
    
    /* Configure Mailbox FIFO protocol */
    ProtocolB_DATA dataReceive;
    dataReceive.ProtocolB[0] = 0; // Initializing to known value.

    while (1){
    	/* Wait for interrupt from slave */
	    while(!SLAVE1_IsInterruptRequested());
	    SLAVE1_InterruptRequestAcknowledge();
	    while(SLAVE1_IsInterruptRequested());
	    SLAVE1_InterruptRequestAcknowledgeComplete();
	    SLAVE1_ProtocolBRead((ProtocolB_DATA*)&dataReceive);
        
        /* Display Data on Screen */
	    printf("\033[6;0f");
	    printf("Data recieved from slave: %7u\r\n", dataReceive.ProtocolB[0]);
        printf("External Interrupt Count: %7u\r\n", ext_int_cnt);
        printf("Wind Sensor: %7u\r\n", ADC_Read12bitAverage(WIND_SENSOR, 40));
        printf("Zero: %7u\r\n", zero);
        printf("\r\n");

        track_wind();
    }

    return 1; 
}