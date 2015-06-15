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

#include "adc.h"

/******************************************************************************/
/* Function Definitions                                                       */
/******************************************************************************/

/*
 * INITIALIZE_ADC: Initializes the built-in ADC module to track the current draw
 *  of the motors
 */
void initialize_adc(void)
{
    /* Disable the ADC module */
    DISABLE_ADC;

    /* Select port pins for use as analog inputs */
    _PCFG0      = 0;    // Port pin 0 configured for analog input (pin 19)
    _PCFG1      = 0;    // Port pin 8 configured for analog input (pin 27)

    /* Configure ADC configuration register bits */
    _AD12B      = 0;    // 10-bit ADC operation
    _FORM0      = 0;    // Data output is in the form of an integer
    _FORM1      = 0;    // Data output is unsigned
    _SSRC       = 3;    // PWM1 clock is used to end sampling and start
                        //  conversion
    _SIMSAM     = 1;    // CH0 and CH1 are sampled simultaneously
    _ASAM       = 1;    // Sampling begins automatically after the last
                        //  conversion
    _VCFG       = 0;    // Use AVdd and AVss as high and low voltage references
    _CHPS       = 1;    // Samples on channels CH0 and CH1 (2-channel mode)
    _ALTS       = 0;    // Always use same channels

    /* Select channel affilation for analog ports */
    _CH0NA      = 0;    // Use Vref- as negative input for CH0
    _CH0SA      = 8;    // Use AN8 as positive input for CH0
    _CH123NA    = 0;    // Use Vref- as negative input for CH1
    _CH123SA    = 0;    // Use AN0 as positive input for CH1

    /* Enable the ADC module */
    ENABLE_ADC;
}

/*
 * READ_ADC: Reads the current values recorded for motor1 and motor2 by the ADC
 *  module
 */
/*int16_t* read_adc(void)
{
    int16_t tmp[2] = {0};

    tmp[0] = *ADC1BUF0;
}*/