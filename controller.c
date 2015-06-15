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

//
//#include <stdint.h>          /* For uint16_t definition                       */
//#include <stdbool.h>         /* For true/false definition                     */
//
//#include "controller.h"
//#include "decoder.h"
//#include "motor.h"
//
//void get_status(void){
//
//    int i = 0;
//    int16_t delta_t = 10;
//
//    cur_pos[0] = read_decoder1();
//    cur_pos[1] = read_decoder2();
//
//    for(i=0;i<2;i++)
//    {
//        cur_vel[i] = (cur_pos[i]-prev_pos[i]/delta_t);
//        cur_acc[i] = (cur_vel[i]-prev_vel[i]/delta_t);
//        prev_pos[i] = cur_pos[i];
//    }
//}
//
//
//void pd_vel_control(uint8_t des_vel, uint8_t act_vel)
//{
//
//
//
//
//
//
//
//
//
//}
//
//int16_t pd_pos_control(uint16_t des_pos, int8_t mtr, float Kp, float Kd)
//{
//    int16_t PWM_OUT = 0;
////    Kp = 1.0;
//
//    PWM_OUT = (int)(Kp*(des_pos-cur_pos[mtr]))%PWM_MAX;
//
//    return PWM_OUT;
//
//}








