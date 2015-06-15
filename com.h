/* 
 * File:   com.h
 * Author: Stride
 *
 * Created on November 11, 2014, 12:51 PM
 */

#ifndef COM_H
#define	COM_H

#define SS_ENABLE   (0)
#define SS_DISABLE  (1)

void initialize_spi_master(void);

void initialize_spi_slave(void);

uint8_t receive_spi_command(void);

void send_spi_command(uint8_t);

#endif