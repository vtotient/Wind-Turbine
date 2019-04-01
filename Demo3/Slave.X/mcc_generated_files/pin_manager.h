/**
  PIN MANAGER Generated Driver File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the generated manager file for the PIC24 / dsPIC33 / PIC32MM MCUs device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description:
    This source file provides implementations for PIN MANAGER.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.95-b-SNAPSHOT
        Device            :  dsPIC33CH128MP508S1
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36
        MPLAB 	          :  MPLAB X v5.10
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

#ifndef _PIN_MANAGER_H
#define _PIN_MANAGER_H
/**
    Section: Includes
*/
#include <xc.h>
#define LED_Toggle()           _LATE0 ^= 1

/**
    Section: Device Pin Macros
*/
/**
  @Summary
    Sets the GPIO pin, RA4, high using LATA4.

  @Description
    Sets the GPIO pin, RA4, high using LATA4.

  @Preconditions
    The RA4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA4 high (1)
    channel_S1AN1_SetHigh();
    </code>

*/
#define channel_S1AN1_SetHigh()          _LATA4 = 1
/**
  @Summary
    Sets the GPIO pin, RA4, low using LATA4.

  @Description
    Sets the GPIO pin, RA4, low using LATA4.

  @Preconditions
    The RA4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA4 low (0)
    channel_S1AN1_SetLow();
    </code>

*/
#define channel_S1AN1_SetLow()           _LATA4 = 0
/**
  @Summary
    Toggles the GPIO pin, RA4, using LATA4.

  @Description
    Toggles the GPIO pin, RA4, using LATA4.

  @Preconditions
    The RA4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RA4
    channel_S1AN1_Toggle();
    </code>

*/
#define channel_S1AN1_Toggle()           _LATA4 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RA4.

  @Description
    Reads the value of the GPIO pin, RA4.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RA4
    postValue = channel_S1AN1_GetValue();
    </code>

*/
#define channel_S1AN1_GetValue()         _RA4
/**
  @Summary
    Configures the GPIO pin, RA4, as an input.

  @Description
    Configures the GPIO pin, RA4, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA4 as an input
    channel_S1AN1_SetDigitalInput();
    </code>

*/
#define channel_S1AN1_SetDigitalInput()  _TRISA4 = 1
/**
  @Summary
    Configures the GPIO pin, RA4, as an output.

  @Description
    Configures the GPIO pin, RA4, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA4 as an output
    channel_S1AN1_SetDigitalOutput();
    </code>

*/
#define channel_S1AN1_SetDigitalOutput() _TRISA4 = 0
/**
  @Summary
    Sets the GPIO pin, RB14, high using LATB14.

  @Description
    Sets the GPIO pin, RB14, high using LATB14.

  @Preconditions
    The RB14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB14 high (1)
    IO_RB14_SetHigh();
    </code>

*/
#define IO_RB14_SetHigh()          _LATB14 = 1
/**
  @Summary
    Sets the GPIO pin, RB14, low using LATB14.

  @Description
    Sets the GPIO pin, RB14, low using LATB14.

  @Preconditions
    The RB14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB14 low (0)
    IO_RB14_SetLow();
    </code>

*/
#define IO_RB14_SetLow()           _LATB14 = 0
/**
  @Summary
    Toggles the GPIO pin, RB14, using LATB14.

  @Description
    Toggles the GPIO pin, RB14, using LATB14.

  @Preconditions
    The RB14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB14
    IO_RB14_Toggle();
    </code>

*/
#define IO_RB14_Toggle()           _LATB14 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RB14.

  @Description
    Reads the value of the GPIO pin, RB14.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB14
    postValue = IO_RB14_GetValue();
    </code>

*/
#define IO_RB14_GetValue()         _RB14
/**
  @Summary
    Configures the GPIO pin, RB14, as an input.

  @Description
    Configures the GPIO pin, RB14, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB14 as an input
    IO_RB14_SetDigitalInput();
    </code>

*/
#define IO_RB14_SetDigitalInput()  _TRISB14 = 1
/**
  @Summary
    Configures the GPIO pin, RB14, as an output.

  @Description
    Configures the GPIO pin, RB14, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB14 as an output
    IO_RB14_SetDigitalOutput();
    </code>

*/
#define IO_RB14_SetDigitalOutput() _TRISB14 = 0
/**
  @Summary
    Sets the GPIO pin, RB2, high using LATB2.

  @Description
    Sets the GPIO pin, RB2, high using LATB2.

  @Preconditions
    The RB2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB2 high (1)
    channel_S1AN3_SetHigh();
    </code>

*/
#define channel_S1AN3_SetHigh()          _LATB2 = 1
/**
  @Summary
    Sets the GPIO pin, RB2, low using LATB2.

  @Description
    Sets the GPIO pin, RB2, low using LATB2.

  @Preconditions
    The RB2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB2 low (0)
    channel_S1AN3_SetLow();
    </code>

*/
#define channel_S1AN3_SetLow()           _LATB2 = 0
/**
  @Summary
    Toggles the GPIO pin, RB2, using LATB2.

  @Description
    Toggles the GPIO pin, RB2, using LATB2.

  @Preconditions
    The RB2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB2
    channel_S1AN3_Toggle();
    </code>

*/
#define channel_S1AN3_Toggle()           _LATB2 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RB2.

  @Description
    Reads the value of the GPIO pin, RB2.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB2
    postValue = channel_S1AN3_GetValue();
    </code>

*/
#define channel_S1AN3_GetValue()         _RB2
/**
  @Summary
    Configures the GPIO pin, RB2, as an input.

  @Description
    Configures the GPIO pin, RB2, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB2 as an input
    channel_S1AN3_SetDigitalInput();
    </code>

*/
#define channel_S1AN3_SetDigitalInput()  _TRISB2 = 1
/**
  @Summary
    Configures the GPIO pin, RB2, as an output.

  @Description
    Configures the GPIO pin, RB2, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB2 as an output
    channel_S1AN3_SetDigitalOutput();
    </code>

*/
#define channel_S1AN3_SetDigitalOutput() _TRISB2 = 0
/**
  @Summary
    Sets the GPIO pin, RC0, high using LATC0.

  @Description
    Sets the GPIO pin, RC0, high using LATC0.

  @Preconditions
    The RC0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC0 high (1)
    channel_S1AN10_SetHigh();
    </code>

*/
#define channel_S1AN10_SetHigh()          _LATC0 = 1
/**
  @Summary
    Sets the GPIO pin, RC0, low using LATC0.

  @Description
    Sets the GPIO pin, RC0, low using LATC0.

  @Preconditions
    The RC0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC0 low (0)
    channel_S1AN10_SetLow();
    </code>

*/
#define channel_S1AN10_SetLow()           _LATC0 = 0
/**
  @Summary
    Toggles the GPIO pin, RC0, using LATC0.

  @Description
    Toggles the GPIO pin, RC0, using LATC0.

  @Preconditions
    The RC0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RC0
    channel_S1AN10_Toggle();
    </code>

*/
#define channel_S1AN10_Toggle()           _LATC0 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RC0.

  @Description
    Reads the value of the GPIO pin, RC0.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RC0
    postValue = channel_S1AN10_GetValue();
    </code>

*/
#define channel_S1AN10_GetValue()         _RC0
/**
  @Summary
    Configures the GPIO pin, RC0, as an input.

  @Description
    Configures the GPIO pin, RC0, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC0 as an input
    channel_S1AN10_SetDigitalInput();
    </code>

*/
#define channel_S1AN10_SetDigitalInput()  _TRISC0 = 1
/**
  @Summary
    Configures the GPIO pin, RC0, as an output.

  @Description
    Configures the GPIO pin, RC0, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC0 as an output
    channel_S1AN10_SetDigitalOutput();
    </code>

*/
#define channel_S1AN10_SetDigitalOutput() _TRISC0 = 0
/**
  @Summary
    Sets the GPIO pin, RC3, high using LATC3.

  @Description
    Sets the GPIO pin, RC3, high using LATC3.

  @Preconditions
    The RC3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC3 high (1)
    channel_S1AN8_SetHigh();
    </code>

*/
#define channel_S1AN8_SetHigh()          _LATC3 = 1
/**
  @Summary
    Sets the GPIO pin, RC3, low using LATC3.

  @Description
    Sets the GPIO pin, RC3, low using LATC3.

  @Preconditions
    The RC3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC3 low (0)
    channel_S1AN8_SetLow();
    </code>

*/
#define channel_S1AN8_SetLow()           _LATC3 = 0
/**
  @Summary
    Toggles the GPIO pin, RC3, using LATC3.

  @Description
    Toggles the GPIO pin, RC3, using LATC3.

  @Preconditions
    The RC3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RC3
    channel_S1AN8_Toggle();
    </code>

*/
#define channel_S1AN8_Toggle()           _LATC3 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RC3.

  @Description
    Reads the value of the GPIO pin, RC3.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RC3
    postValue = channel_S1AN8_GetValue();
    </code>

*/
#define channel_S1AN8_GetValue()         _RC3
/**
  @Summary
    Configures the GPIO pin, RC3, as an input.

  @Description
    Configures the GPIO pin, RC3, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC3 as an input
    channel_S1AN8_SetDigitalInput();
    </code>

*/
#define channel_S1AN8_SetDigitalInput()  _TRISC3 = 1
/**
  @Summary
    Configures the GPIO pin, RC3, as an output.

  @Description
    Configures the GPIO pin, RC3, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC3 as an output
    channel_S1AN8_SetDigitalOutput();
    </code>

*/
#define channel_S1AN8_SetDigitalOutput() _TRISC3 = 0
/**
  @Summary
    Sets the GPIO pin, RC6, high using LATC6.

  @Description
    Sets the GPIO pin, RC6, high using LATC6.

  @Preconditions
    The RC6 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC6 high (1)
    channel_S1AN11_SetHigh();
    </code>

*/
#define channel_S1AN11_SetHigh()          _LATC6 = 1
/**
  @Summary
    Sets the GPIO pin, RC6, low using LATC6.

  @Description
    Sets the GPIO pin, RC6, low using LATC6.

  @Preconditions
    The RC6 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC6 low (0)
    channel_S1AN11_SetLow();
    </code>

*/
#define channel_S1AN11_SetLow()           _LATC6 = 0
/**
  @Summary
    Toggles the GPIO pin, RC6, using LATC6.

  @Description
    Toggles the GPIO pin, RC6, using LATC6.

  @Preconditions
    The RC6 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RC6
    channel_S1AN11_Toggle();
    </code>

*/
#define channel_S1AN11_Toggle()           _LATC6 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RC6.

  @Description
    Reads the value of the GPIO pin, RC6.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RC6
    postValue = channel_S1AN11_GetValue();
    </code>

*/
#define channel_S1AN11_GetValue()         _RC6
/**
  @Summary
    Configures the GPIO pin, RC6, as an input.

  @Description
    Configures the GPIO pin, RC6, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC6 as an input
    channel_S1AN11_SetDigitalInput();
    </code>

*/
#define channel_S1AN11_SetDigitalInput()  _TRISC6 = 1
/**
  @Summary
    Configures the GPIO pin, RC6, as an output.

  @Description
    Configures the GPIO pin, RC6, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC6 as an output
    channel_S1AN11_SetDigitalOutput();
    </code>

*/
#define channel_S1AN11_SetDigitalOutput() _TRISC6 = 0
/**
  @Summary
    Sets the GPIO pin, RD4, high using LATD4.

  @Description
    Sets the GPIO pin, RD4, high using LATD4.

  @Preconditions
    The RD4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD4 high (1)
    IO_RD4_SetHigh();
    </code>

*/
#define IO_RD4_SetHigh()          _LATD4 = 1
/**
  @Summary
    Sets the GPIO pin, RD4, low using LATD4.

  @Description
    Sets the GPIO pin, RD4, low using LATD4.

  @Preconditions
    The RD4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD4 low (0)
    IO_RD4_SetLow();
    </code>

*/
#define IO_RD4_SetLow()           _LATD4 = 0
/**
  @Summary
    Toggles the GPIO pin, RD4, using LATD4.

  @Description
    Toggles the GPIO pin, RD4, using LATD4.

  @Preconditions
    The RD4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RD4
    IO_RD4_Toggle();
    </code>

*/
#define IO_RD4_Toggle()           _LATD4 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RD4.

  @Description
    Reads the value of the GPIO pin, RD4.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RD4
    postValue = IO_RD4_GetValue();
    </code>

*/
#define IO_RD4_GetValue()         _RD4
/**
  @Summary
    Configures the GPIO pin, RD4, as an input.

  @Description
    Configures the GPIO pin, RD4, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD4 as an input
    IO_RD4_SetDigitalInput();
    </code>

*/
#define IO_RD4_SetDigitalInput()  _TRISD4 = 1
/**
  @Summary
    Configures the GPIO pin, RD4, as an output.

  @Description
    Configures the GPIO pin, RD4, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD4 as an output
    IO_RD4_SetDigitalOutput();
    </code>

*/
#define IO_RD4_SetDigitalOutput() _TRISD4 = 0
/**
  @Summary
    Sets the GPIO pin, RD7, high using LATD7.

  @Description
    Sets the GPIO pin, RD7, high using LATD7.

  @Preconditions
    The RD7 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD7 high (1)
    IO_RD7_SetHigh();
    </code>

*/
#define IO_RD7_SetHigh()          _LATD7 = 1
/**
  @Summary
    Sets the GPIO pin, RD7, low using LATD7.

  @Description
    Sets the GPIO pin, RD7, low using LATD7.

  @Preconditions
    The RD7 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD7 low (0)
    IO_RD7_SetLow();
    </code>

*/
#define IO_RD7_SetLow()           _LATD7 = 0
/**
  @Summary
    Toggles the GPIO pin, RD7, using LATD7.

  @Description
    Toggles the GPIO pin, RD7, using LATD7.

  @Preconditions
    The RD7 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RD7
    IO_RD7_Toggle();
    </code>

*/
#define IO_RD7_Toggle()           _LATD7 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RD7.

  @Description
    Reads the value of the GPIO pin, RD7.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RD7
    postValue = IO_RD7_GetValue();
    </code>

*/
#define IO_RD7_GetValue()         _RD7
/**
  @Summary
    Configures the GPIO pin, RD7, as an input.

  @Description
    Configures the GPIO pin, RD7, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD7 as an input
    IO_RD7_SetDigitalInput();
    </code>

*/
#define IO_RD7_SetDigitalInput()  _TRISD7 = 1
/**
  @Summary
    Configures the GPIO pin, RD7, as an output.

  @Description
    Configures the GPIO pin, RD7, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD7 as an output
    IO_RD7_SetDigitalOutput();
    </code>

*/
#define IO_RD7_SetDigitalOutput() _TRISD7 = 0

/**
    Section: Function Prototypes
*/
/**
  @Summary
    Configures the pin settings of the dsPIC33CH128MP508S1
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description
    This is the generated manager file for the PIC24 / dsPIC33 / PIC32MM MCUs device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void SYSTEM_Initialize(void)
    {
        // Other initializers are called from this function
        PIN_MANAGER_Initialize();
    }
    </code>

*/
void PIN_MANAGER_Initialize (void);

#endif
