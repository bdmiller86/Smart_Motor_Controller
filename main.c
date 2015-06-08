/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__dsPIC33E__)
    	#include <p33Exxxx.h>
    #elif defined(__dsPIC33F__)
    	#include <p33Fxxxx.h>
    #endif
#endif


#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition  */
#include <stdio.h>
#include <stdlib.h>

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/
int spi_data = 50;
/* i.e. uint16_t <variable_name>; */

void __attribute__((interrupt, no_auto_psv)) _SPI1Interrupt(void){
       
    
    IFS0bits.SPI1IF = 0; // Clear the Interrupt flag
    IEC0bits.SPI1IE = 0; // Disable the interrupt

    
    spi_data = SPI1_REC();
    // Interrupt Controller Settings
    IFS0bits.SPI1IF = 0; // Clear the Interrupt flag
    IEC0bits.SPI1IE = 1; // Enable the interrupt
}




/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int16_t main(void)
{
    //InitApp();

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();

    motor0_init();
    SPI1SLAVE_init();
    //printf("%d\n", PORTA _SFR_);
    /* TODO <INSERT USER APPLICATION CODE HERE> */
    long int duty = 0;
    //AD1PCFGL = 0x00FF;
    
//    TRISA = 0x0000;
//    TRISB = 0x0000;

//    spi_data = SPI1_REC();

    while(1)
    {
        duty++;
        //InitApp();
//        TRISB = 0x0000;
//        LATB = 0x0000;
//
////        TRISA = 0x00;
//        PORTA = 0xFF;
//
////        TRISB = 0x0000;
//        LATB = 0xFFFF;
//
////        TRISA = 0x00;
//        LATA = 0x00;
//        if((SPI1STAT & _SPIRBF) == 1)
//            spi_data = SPI1_REC();
        //if((duty%50000) == 0){
        //   PWM1CON1 = 0x0770;

        //SPI1_SEND(duty%128);

        if(PORTCbits.RC6 == 1)
            spi_data = SPI1_REC();

            if((duty%100000) == 0){
                motor1(spi_data%255);
                //PWM1CON1 = 0x0707;
            }
        //}
    }
}
