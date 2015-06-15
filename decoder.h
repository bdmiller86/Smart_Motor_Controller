/* 
 * File:   decoder.h
 * Author: Stride
 *
 * Created on November 21, 2014, 4:30 PM
 */

#ifndef DECODER_H
#define	DECODER_H

#define MAX_COUNTS  (65535)

void initialize_decoder1(void);

void initialize_decoder2(void);

int16_t read_decoder1(void);

int16_t read_decoder2(void);

void reset_decoder1(void);

void reset_decoder2(void);

#endif	/* DECODER_H */

