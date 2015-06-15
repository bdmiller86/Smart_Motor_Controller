/* 
 * File:   motor.h
 * Author: Stride
 *
 * Created on November 11, 2014, 12:50 PM
 */

#ifndef MOTOR_H
#define	MOTOR_H

#define PWM_MAX (1999)
#define PWM_MIN (0)

/* Global Functions */

void initialize_motor1(void);

void initialize_motor2(void);

void motor(int16_t,int8_t,int8_t);

void move_forward_motor1(uint16_t);

void move_forward_motor2(uint16_t);

void move_reverse_motor1(uint16_t);

void move_reverse_motor2(uint16_t);

void brake_motor1(void);

void brake_motor2(void);

void coast_motor1(void);

void coast_motor2(void);

#endif
