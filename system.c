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


#include <stdint.h>          /* For uint16_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */

#include "system.h"          /* variables/params used by system.c             */

/******************************************************************************/
/* System Level Functions                                                     */
/*                                                                            */
/* Custom oscillator configuration funtions, reset source evaluation          */
/* functions, and other non-peripheral microcontroller initialization         */
/* functions get placed in system.c.                                          */
/*                                                                            */
/******************************************************************************/

/* Refer to the device Family Reference Manual Oscillator section for
information about available oscillator configurations.  Typically
this would involve configuring the oscillator tuning register or clock
switching useing the compiler's __builtin_write_OSCCON functions.
Refer to the C Compiler for PIC24 MCUs and dsPIC DSCs User Guide in the
compiler installation directory /doc folder for documentation on the
__builtin functions.*/

/*
 * CONFIGURE_OSCILLATOR: Configures the internal oscillator for the
 * microcontroller. Uses the built-in oscillator to operate at a clock
 * frequency of 40MHz. Check the oscillator spec sheet (Section 39) for more
 * information on set up.
 */
void configure_oscillator(void)
{
    /* Configure PLL prescaler, PLL postscaler, and PLL divisor */
    PLLFBD = 41;            // M = 43
    CLKDIVbits.PLLPOST = 0; // N2 = 2
    CLKDIVbits.PLLPRE = 0;  // N1 = 2
                            // Fosc = 7.37MHz
                            // Fcy = ( Fosc / 2 ) * ( M / ( N1 * N2 ) ) = 40MHz

    /* Initiate Clock Switch to Internal FRC with PLL (NOSC = 0b001) */
    __builtin_write_OSCCONH(0x01);  /* Set OSCCONH for clock switch */
    __builtin_write_OSCCONL(OSCCON | 0x01);  /* Start clock switching */

    /* Wait for Clock Switch to occur */
    while(OSCCONbits.COSC != 0b001);

    /* Wait for PLL to lock */
    while(OSCCONbits.LOCK != 1);
}

void initialize_smc(void)
{
    /* Initialize all GPIOs as inputs */
    TRISA       = 0x001F;
    TRISB       = 0xFFEF; //all but RB4
    TRISC       = 0x03FF;

    /* Disable Input Change Notifications */
    CNEN1       = 0x00;
    CNEN2       = 0x00;

    /* Disable ADC Module */
    AD1CON1     = 0x00;

    /* Set all AD pins to digital mode */
    AD1PCFGL    = 0x01FF;

    /* Disable comparators */
    CMCON       = 0x00;

    /* TODO Initialize User Ports/Peripherals/Project here */

    /* Setup analog functionality and port direction */

    /* Initialize peripherals */
}

void initialize_rti(void)
{
    T1CONbits.TON = 0;// Disable Timer
    T1CONbits.TCS = 0;// Select internal instruction cycle clock
    T1CONbits.TGATE = 0;// Disable Gated Timer mode
//    T1CONbits.TCKPS = 0b00;// Select 1:1 Prescaler
//    T1CONbits.TCKPS = 0b01;// Select 1:8 Prescaler
//    T1CONbits.TCKPS = 0b10;// Select 1:64 Prescaler
    T1CONbits.TCKPS = 0b11;// Select 1:256 Prescaler
    TMR1 = 0x00; // Clear timer register
    PR1 = 76; // Load the period value
//    PR1 = 20; // Load the period value

    IPC0bits.T1IP = 0x01;// Set Timer1 Interrupt Priority Level
    IFS0bits.T1IF = 0;// Clear Timer1 Interrupt Flag
    IEC0bits.T1IE = 1;// Enable Timer1 interrupt

    T1CONbits.TON = 1;// Start Timer
}
