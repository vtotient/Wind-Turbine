
/**
  TMR1 Generated Driver API Source File 

  @Company
    Microchip Technology Inc.

  @File Name
    tmr1.c

  @Summary
    This is the generated source file for the TMR1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for driver for TMR1. 
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.95-b-SNAPSHOT
        Device            :  dsPIC33CH128MP508
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36
        MPLAB             :  MPLAB X v5.10
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include <stdio.h>
#include <stdlib.h>
#include "tmr1.h"
#ifndef MASTER_API_H
    #include "master_API.h"
#endif

/* For ISR */
uint16_t cnt = 0;
int16_t duty_cyle = 0;
int16_t error[2] = {0,0};
int16_t integral[2] = {0,0};

/**
 Section: File specific functions
*/
void (*TMR1_InterruptHandler)(void) = NULL;
void TMR1_CallBack(void);

/**
  Section: Data Type Definitions
*/

/** TMR Driver Hardware Instance Object

  @Summary
    Defines the object required for the maintainence of the hardware instance.

  @Description
    This defines the object required for the maintainence of the hardware
    instance. This object exists once per hardware instance of the peripheral.

  Remarks:
    None.
*/

typedef struct _TMR_OBJ_STRUCT
{
    /* Timer Elapsed */
    bool                                                    timerElapsed;
    /*Software Counter value*/
    uint8_t                                                 count;

} TMR_OBJ;

static TMR_OBJ tmr1_obj;

/**
  Section: Driver Interface
*/

void TMR1_Initialize (void)
{
    //TMR 0; 
    TMR1 = 0x00;
    //Period = 0.1 s; Frequency = 4000000 Hz; PR 50000; 
    PR1 = 350;
    //TCKPS 1:8; PRWIP Write complete; TMWIP Write complete; TON enabled; TSIDL disabled; TCS FOSC/2; TECS T1CK; TSYNC disabled; TMWDIS disabled; TGATE disabled; 
    T1CON = 0x8010;

    if(TMR1_InterruptHandler == NULL)
    {
        TMR1_SetInterruptHandler(&TMR1_CallBack);
    }

    IFS0bits.T1IF = false;
    IEC0bits.T1IE = true;
	
    tmr1_obj.timerElapsed = false;

}


void __attribute__ ( ( interrupt, no_auto_psv ) ) _T1Interrupt (  )
{
    /* Check if the Timer Interrupt/Status is set */

    //***User Area Begin

    // ticker function call;
    // ticker is 1 -> Callback function gets called everytime this ISR executes
    if(TMR1_InterruptHandler) 
    { 
           TMR1_InterruptHandler(); 
    }

    //***User Area End

    tmr1_obj.count++;
    tmr1_obj.timerElapsed = true;
    IFS0bits.T1IF = false;
}

void TMR1_Period16BitSet( uint16_t value )
{
    /* Update the counter values */
    PR1 = value;
    /* Reset the status information */
    tmr1_obj.timerElapsed = false;
}

uint16_t TMR1_Period16BitGet( void )
{
    return( PR1 );
}

void TMR1_Counter16BitSet ( uint16_t value )
{
    /* Update the counter values */
    TMR1 = value;
    /* Reset the status information */
    tmr1_obj.timerElapsed = false;
}

uint16_t TMR1_Counter16BitGet( void )
{
    return( TMR1 );
}

/*
 * Timer interrupt Callback. Exectutes the stepper motor PI Algorithm
 *
 * RETURN:  NULL
 *
 * PRE:     1ms Interrupt rate as definied by settling time
 *
 * POST:    System returns to main exe
 */

void __attribute__ ((weak)) TMR1_CallBack(void) 
{

    /* Normal Mode */
    #ifndef DATA_AQUISTION
        duty_cyle = 100 * track_wind_pi();

        if(cnt <= abs(duty_cyle)){
            if(duty_cyle < 0){
                spin_clockwise();
                LATEbits.LATE1 ^= 1;
            }
            else{
                spin_counterclockwise();
                LATEbits.LATE1 ^= 1;
            }
        }
        else{
            stop_stepper();
        }

        if(cnt == TMAX){
            cnt = 0;
        }
        else{
            cnt++;
        }

    /* Aquiring Data Mode */
    #else
        LATEbits.LATE0 ^= 1;

        if(ADC_ReadPercentage(SENSOR_1)<50){
            track_wind();
            LATEbits.LATE1 = 0;
        }
        else{
            stop_stepper();
            LATEbits.LATE1 = 1;
        }
    #endif

}

/*
 * PI controller for the stepper motor
 *
 * RETURN:  DC value 
 *
 * PRE:     Timer1 initialized
 *
 * POST:    Speed of stepper adjusted according to PI controller equ
 */

int16_t track_wind_pi(void){
    uint16_t current_pot_val = ADC_Read12bitAverage(WIND_SENSOR, 40);
    uint16_t zero = return_zero();
    double u;

    /* Compute the error term as the relative angle of the wind sensor */
    error[0] = zero - current_pot_val;

    /* Compute the current integral term */
    integral[0] = integral[1] + error[0];

    /* Compute PI */
    u = Kp * (error[0] + (1/Ti)*integral[0]);

    /* Store for the next computation */
    error[1] = error[0]; 
    integral[1] = integral[0];

    /* Cast the PI term to an int */
    return (int16_t)u;
}

void  TMR1_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC0bits.T1IE = false;
    TMR1_InterruptHandler = InterruptHandler; 
    IEC0bits.T1IE = true;
}

void TMR1_Start( void )
{
    /* Reset the status information */
    tmr1_obj.timerElapsed = false;

    /*Enable the interrupt*/
    IEC0bits.T1IE = true;

    /* Start the Timer */
    T1CONbits.TON = 1;
}

void TMR1_Stop( void )
{
    /* Stop the Timer */
    T1CONbits.TON = false;

    /*Disable the interrupt*/
    IEC0bits.T1IE = false;
}

bool TMR1_GetElapsedThenClear(void)
{
    bool status;
    
    status = tmr1_obj.timerElapsed;

    if(status == true)
    {
        tmr1_obj.timerElapsed = false;
    }
    return status;
}

int TMR1_SoftwareCounterGet(void)
{
    return tmr1_obj.count;
}

void TMR1_SoftwareCounterClear(void)
{
    tmr1_obj.count = 0; 
}

/**
 End of File
*/