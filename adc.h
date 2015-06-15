/* 
 * File:   adc.h
 * Author: Stride
 *
 * Created on November 24, 2014, 2:50 PM
 */

#ifndef ADC_H
#define	ADC_H

#define DISABLE_ADC (_ADON = 0) // Disable the ADC module
#define ENABLE_ADC  (_ADON = 1) // Enable the ADC module

void initialize_adc(void);

int16_t* read_adc(void);

#endif	/* ADC_H */
