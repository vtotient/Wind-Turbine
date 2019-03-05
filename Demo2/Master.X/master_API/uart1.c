/*******************************************************************************
Copyright 2017 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*******************************************************************************/

#include <p33CH128MP508.h>

#include "uart1.h"
//#include <stdio.h>

#ifndef UART1_BAUD
#warning "UART1_BAUD rate not defined. Setting to 9600."
#define UART1_BAUD 9600
#endif

#define FCY 8000000

#ifndef FCY
#error "FCY defintion required to calculate baud rate.  Please define."
#endif

void UART1_Initialize(void)
{
    uint32_t brg;
    
    U1MODEbits.UARTEN = 1;
    U1MODEbits.BRGH = 1; //high-speed
    U1MODEbits.UTXEN = 1;
    U1MODEbits.MOD = 0b0000; //asynchronous 8-bit UART
    U1MODEHbits.STSEL = 0; //1 stop bit
    
    brg = ((2*((FCY/2)/UART1_BAUD/4-1))+1)/2;
    
    U1BRG = (uint16_t)brg;
    U1BRGH = brg>>16;
}

void UART1_Write(uint8_t txData)
{
    while(U1STAHbits.UTXBF == 1){}

    U1TXREG = txData;    // Write the data byte to the USART.
}