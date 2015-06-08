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
#include "user.h"            /* variables/params used by user.c               */

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    TRISA = 0x0000;
    TRISB = 0x0000;
    TRISC = 0x01FF;

    //BSET    PORTA, #1

    CNEN1 = 0x00;
    CNEN2 = 0x00;
    AD1CON1 = 0x00;

    AD1PCFGL = 0x01FF;

    //AD1PCFGL = 0x00FF;
    //ADON = 0;

    CMCON = 0x00;

    PORTA = 0xFFFF;


    //PORTBbits.RB0 = 1;
    //PORTBbits.RB1 = 1;

    /* TODO Initialize User Ports/Peripherals/Project here */

    /* Setup analog functionality and port direction */

    /* Initialize peripherals */
}
