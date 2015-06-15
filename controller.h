/* 
 * File:   Controller.h
 * Author: Josh
 *
 * Created on May 19, 2015, 12:39 PM
 */

#ifndef CONTROLLER_H
#define	CONTROLLER_H

#include "motor.h"


#ifdef	__cplusplus
extern "C" {
#endif


int16_t cur_pos[2] = {0};
int16_t prev_pos[2] = {0};
int16_t cur_vel[2] = {0};
int16_t prev_vel[2] = {0};
int16_t cur_acc[2] = {0};

void get_status(void){

    int i = 0;
    int16_t delta_t = 10;

    cur_pos[0] = read_decoder1();
    cur_pos[1] = read_decoder2();

    for(i=0;i<2;i++)
    {
        cur_vel[i] = (cur_pos[i]-prev_pos[i]/delta_t);
        cur_acc[i] = (cur_vel[i]-prev_vel[i]/delta_t);
        prev_pos[i] = cur_pos[i];
        prev_vel[i] = cur_vel[i];
    }
}


void pd_vel_control(uint8_t des_vel, uint8_t act_vel)
{









}

int16_t pd_pos_control(int16_t des_pos, int8_t mtr, float Kp, float Kd)
{
    int16_t PWM_OUT = 0;
    int16_t des_vel = 0;
//    Kp = 1.0;

    PWM_OUT = ((int)(Kp*(des_pos-cur_pos[mtr]))+(int)(Kd*(des_vel-cur_vel[mtr])));

    if(PWM_OUT >= PWM_MAX)
        PWM_OUT = PWM_MAX;

    return PWM_OUT;

}


#ifdef	__cplusplus
}
#endif

#endif	/* CONTROLLER_H */

