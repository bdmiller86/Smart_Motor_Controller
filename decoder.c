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

#include "decoder.h"        /* variables/params used by system.c              */

/******************************************************************************/
/* Function Definitions                                                       */
/******************************************************************************/

/*
 * INITIALIZE_DECODER1: Initializes the built-in QEI1 module to track the
 *  position of a quadrature encoder
 */
void initialize_decoder1(void)
{
    /* Map reprogrammable pins to QEI Functions */
    _QEA1R = 0b10100;   // QEI1 Phase A on RP20
    _QEB1R = 0b10101;   // QEI1 Phase B on RP21

    /* Configure QEI1CON Register */
    QEI1CONbits.CNTERR  = 0;    // Clears counter errors
    QEI1CONbits.QEISIDL = 0;    // Continue operation in idle mode
    QEI1CONbits.QEIM    = 7;    // QEI interface enabled (x4 mode); reset by
                                // match of MAX1CNT
    QEI1CONbits.SWPAB   = 0;    // Phase A and Phase B inputs are not swapped

    /* Configure digital filter outputs */
    DFLT1CONbits.CEID   = 1;    // Interrupts due to count errors are disabled
    DFLT1CONbits.QEOUT  = 1;    // Digital filters are enabled
    DFLT1CONbits.QECK   = 0;    // 1:1 clock divide for QEA1/QEB1/INDX1

    /* Set maximum counts before overflow */
    MAX1CNT = 65535;
}

/*
 * INITIALIZE_DECODER2: Initializes the built-in QEI2 module to track the
 *  position of a quadrature encoder
 */
void initialize_decoder2(void)
{
    /* Map reprogrammable pins to QEI Functions */
    /* TODO: Decide which pins second decoder will be mapped to */
    _QEA2R = 0b10000;   // QEI1 Phase A on RP16
    _QEB2R = 0b10001;   // QEI1 Phase B on RP17

    /* Configure QEI1CON Register */
    QEI2CONbits.CNTERR  = 0;    // Clears counter errors
    QEI2CONbits.QEISIDL = 0;    // Continue operation in idle mode
    QEI2CONbits.QEIM    = 7;    // QEI interface enabled (x4 mode); reset by
                                // match of MAX2CNT
    QEI2CONbits.SWPAB   = 0;    // Phase A and Phase B inputs are not swapped

    /* Configure digital filter outputs */
    DFLT2CONbits.CEID   = 1;    // Interrupts due to count errors are disabled
    DFLT2CONbits.QEOUT  = 1;    // Digital filters are enabled
    DFLT2CONbits.QECK   = 0;    // 1:1 clock divide for QEA2/QEB2/INDX2

    /* Set maximum counts before overflow */
    MAX2CNT = 65535;
}

/*
 * READ_DECODER1: Reads the current position of the encoder tracked by QEI1
 */
int16_t read_decoder1(void)
{
    return POS1CNT;
}

/*
 * READ_DECODER2: Reads the current position of the encoder tracked by QEI1
 */
int16_t read_decoder2(void)
{
    return POS2CNT;
}

/*
 * RESET_DECODER1: Resets the count of the QEI1 module
 */
void reset_decoder1(void)
{
    POS1CNT = 0;
}

/*
 * RESET_DECODER2: Resets the count of the QEI2 module
 */
void reset_decoder2(void)
{
    POS2CNT = 0;
}