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


<<<<<<< HEAD
#include <stdint.h>         /* Includes uint16_t definition                   */
#include <stdbool.h>        /* Includes true/false definition                 */
#include <stdio.h>
#include <stdlib.h>
#include <qei.h>
//#include <adc.h>

#include "system.h"         /* System funct/params, like osc/periph config    */
#include "user.h"
#include "motor.h"          /* Motor functions, such as motor init and duty   */
#include "com.h"            /* Communication functions, such as SPI send/rec  */
#include "decoder.h"
#include "adc.h"
#include "controller.h"

#define SMC 1
=======
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition  */
#include <stdio.h>
#include <stdlib.h>

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */
>>>>>>> 8bb88a5dab0fc86bee57fd49bb9c95909b443296

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/
<<<<<<< HEAD

int g_spi_data = 50;
int des_pos = MAX_COUNTS/4;
//uint16_t ctr = 0;
//uint16_t cur_pos1 = 0;
//uint16_t cur_pos2 = 0;


//cur_pos[0] = {0};
//prev_pos[0] = {0};
//cur_vel[2] = {0};
//prev_vel[2] = {0};
//cur_acc[2] = {0};

/******************************************************************************/
/* Interrupt Declarations                                                     */
/******************************************************************************/

void __attribute__((interrupt, no_auto_psv)) _SPI1Interrupt(void){

//    uint32_t tmp = 0;
    
    /* Disable SPI Interrupt */
    IEC0bits.SPI1IE = 0;

    /* Read SPI Data Buffer */
//    tmp = receive_spi_command();
//    if( tmp == 0 ){
//        coast_motor1();
//        coast_motor2();
//    }
//    else if( tmp == 1 ){
//        move_forward_motor1(PWM_MAX/2);
//        move_forward_motor2(PWM_MAX/2);
//        }
//    else if( tmp == 2 ){
//        move_reverse_motor1(PWM_MAX/2);
//        move_reverse_motor2(PWM_MAX/2);
//    }
//    else if( tmp == 3 ){
//        brake_motor1();
//        brake_motor2();
//    }

    /* Enable SPI Interrupt */
    IFS0bits.SPI1IF = 0;    // Clear SPI Interrupt flag
    IEC0bits.SPI1IE = 1;    // Enable SPI Interrupt

}

    /* Timer interrupt set up to be called a a frequency of 2 kHz. Was working
     * with creating functions using pointers, but did not get pointers to work.
     *
     * Decided for first attempt to use global variables. The code is modeled
     * after Dr. Chuy's robot.h.
     *
     * Functions and global declarations are in controller.h
     */

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void){

//    uint32_t tmp = 0;


//    uint16_t tmp = 0;


    /* Disable RTCIE Interrupt */
//    IEC0bits.T1IE = 0;


    int8_t mtr = 0;
    int16_t duty = 0;
    float Kp = 1.0;
    float Kd = 0.0;
    int8_t dir = 0;

    PORTB = ~PORTB;

////    if((ctr%1000) == 0){
//        cur_pos1 = read_decoder1();
//        cur_pos2 = read_decoder2();
////    }

    get_status();

    duty = pd_pos_control(des_pos,mtr,Kp,Kd);

    motor(duty,mtr,dir);


    /* Enable SPI Interrupt */
    IFS0bits.T1IF = 0;    // Clear SPI Interrupt flag
//    IEC0bits.T1IE = 1;    // Enable Real Time Interrupt

}

=======
int spi_data = 50;
/* i.e. uint16_t <variable_name>; */

void __attribute__((interrupt, no_auto_psv)) _SPI1Interrupt(void){
       
    
    IFS0bits.SPI1IF = 0; // Clear the Interrupt flag
    IEC0bits.SPI1IE = 0; // Disable the interrupt

    
    spi_data = SPI1_REC();
    // Interrupt Controller Settings
    IFS0bits.SPI1IF = 0; // Clear the Interrupt flag
    IEC0bits.SPI1IE = 1; // Enable the interrupt
}



>>>>>>> 8bb88a5dab0fc86bee57fd49bb9c95909b443296

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int16_t main(void)
{
<<<<<<< HEAD

    /* Configure the oscillator for the device */
    configure_oscillator();

    /* Initialize IO ports and peripherals */
    initialize_smc();
    initialize_motor1();
    initialize_motor2();
    initialize_rti();
//    initialize_spi_master();
    initialize_spi_slave();
    initialize_decoder1();
    initialize_decoder2();
//    initialize_adc();

    /* Initialize variables */
    uint32_t tmp = 0;
    uint32_t mode = 0;
    uint16_t duty = 0;
    uint8_t mode_flag = 1;
    uint8_t len_flag = 1;
    uint8_t rec_flag = 0;
    uint8_t send_flag = 0;
    uint8_t ctrl = 0;
    uint8_t cmd = 0;
    uint8_t chksum = 0;
    uint8_t checksum = 0;
    uint8_t msg_len = 0;
    uint8_t send_data[10];
    uint8_t data[10] = {0};
    uint8_t i = 0;
    uint8_t j = 0;
//    uint32_t cnt = 0;

    PORTB = 0x0006;
    /* TODO <INSERT USER APPLICATION CODE HERE> */

    while(1)
    {

        /*
         * SPI MASTER TEST CODE
         *  Sends an SPI signal that increments with each pass (SSx enabled)
         */

//        tmp++;
//
//        if( ( tmp%0xFFFFF ) == 0x00001 )
//        {
//            cnt++;
//            send_spi_command(cnt%128);
//        }
//        else if( ( tmp%0xFFFFF ) == 0x10001 ){
//            tmp = 0;
//        }

        /*
         * SPI SLAVE TEST CODE
         *  Checks for an SPI input and adjusts the PWM output accordingly
         */

//        if(_SPIRBF)
//        {
//            tmp = receive_spi_command();
//            SPI1BUF = tmp;
//            if( tmp == 0 ){
//                coast_motor1();
//                coast_motor2();
//            }
//            else if( tmp == 1 ){
//                move_forward_motor1(PWM_MAX/2);
//                move_forward_motor2(PWM_MAX/2);
//            }
//            else if( tmp == 2 ){
//                move_reverse_motor1(PWM_MAX/2);
//                move_reverse_motor2(PWM_MAX/2);
//            }
//            else if( tmp == 3 ){
//                brake_motor1();
//                brake_motor2();
//            }
//        }


        
        /* 
         * PWM TEST CODE
         *  Runs a sequence turning on the various PWM functions for motor0 and 
         *  motor1.
         */

//        tmp++;
//
//        if( ( tmp%0xFFFFF ) == 0x00001 ){
//            move_forward_motor1(PWM_MAX/2);
//            move_forward_motor2(PWM_MAX/2);
//        }
//        else if( ( tmp%0xFFFFF ) == 0x10001 ){
//            move_reverse_motor1(PWM_MAX/2);
//            move_reverse_motor2(PWM_MAX/2);
//        }
//        else if( ( tmp%0xFFFFF ) == 0x20001 ){
//            brake_motor1();
//            brake_motor2();
//        }
//        else if( ( tmp%0xFFFFF ) == 0x30001 ){
//            coast_motor1();
//            coast_motor2();
//        }
//        else if( ( tmp%0xFFFFF ) == 0x40001 ){
//            tmp = 0;
//        }


        /*
         * QEI TEST CODE
         *  Returns the current encoder position from the QEI module
         */

//        move_forward_motor1(PWM_MAX/2);
//        move_forward_motor2(PWM_MAX/2);
//        if(_SPIRBF)
//        {
//            tmp = receive_spi_command();
//            if(tmp == 1)
//            {
////                SPI1BUF = (read_decoder1() >> 8);
//                SPI1BUF = (cur_pos[0] >> 8);
////                SPI1BUF = (cur_pos[0]&0xFF);
//            }
//            else if(tmp == 2)
//            {
////                reset_decoder1();
//                SPI1BUF = (cur_pos[1] >> 8);
////                SPI1BUF = (read_decoder1() >> 8);
////                SPI1BUF = (read_decoder2() >> 8);
//            }
//        }

        /*
         * PD Position Control Test Code
         *  Reads SPI to Determine Desired Position
         *  Position is read in Timer Interrupt for PD Control
         *
         *  Format for sending is to send the length of the message you will be
         *    sending, then each byte of data until the total message has been
         *    sent.
         *
         *  Set up for testing PD Control by sending a desired position from
         *    mode 1 then sending current position using mode 2, and sending the
         *    desired position on mode 3.
         */

        if(_SPIRBF)
        {
            if(mode_flag){
                mode = receive_spi_command();
                mode_flag = 0;
                switch(mode){
                    case 1:
                        rec_flag = 1;
                        msg_len = 3;
                        SPI1BUF = msg_len;
                    break;
                    // Send the entire encoder count for both encoders
                    case 2:
                        send_flag = 1;
                        msg_len = 6;

                        send_data[0] = 1;
                        send_data[1] = (cur_pos[0] >> 8)&0xFF;
                        send_data[2] = (cur_pos[0])&0xFF;
                        send_data[3] = 2;
                        send_data[4] = (cur_pos[1] >> 8)&0xFF;
                        send_data[5] = (cur_pos[1])&0xFF;
//                        send_data[0] = 0x23;
//                        send_data[1] = 0x34;
//                        send_data[2] = 0x45;
//                        send_data[3] = 0x56;
//                        send_data[4] = 0x67;
//                        send_data[5] = 0x78;
                        SPI1BUF = msg_len;
                    break;
                    case 3:
                        send_flag = 1;
                        msg_len = 3;

                        send_data[0] = data[0];
                        send_data[1] = data[1];
                        send_data[2] = data[2];

//                        send_data[0] = 0x13;
//                        send_data[1] = 0x35;
//                        send_data[2] = 0x57;
//                        send_data[3] = 0x79;

                        SPI1BUF = msg_len;
                    break;

                }

            }
            else if(rec_flag){
                if(i == 0){
                    i++;
                }
                else if((i-1) > msg_len){
                    mode_flag = rec_flag;
                    rec_flag = 0;
                    i = 0;
                }
                else{
                    data[i-1] = receive_spi_command();
//                    SPI1BUF = (i+5);
                    SPI1BUF = data[i-1];
                    i++;
                }
            }
            else if(send_flag){
                if(i == 0){
                    i++;
                }
                else if((i-1) > msg_len){
                    mode_flag = send_flag;
                    send_flag = 0;
                    i = 0;
                }
                else{
                    tmp = receive_spi_command();
//                    SPI1BUF = (i+5);
                    SPI1BUF = send_data[i-1];
                    i++;
                }
            }
        }



        /*
         * Communication Protocal Development
         *  Receives data over SPI which includes command to be executed
         *
         *  Working to replicate the drive motors forward command from the
         *      RoboClaws
         */


//        if(_SPIRBF)
//        {
//            if(msg_len == 0){
//                msg_len = receive_spi_command();
//            }
//            else if(cmd == 0){
//                cmd = receive_spi_command();
//                i++;
//            }
//            else if(ctrl != SMC){
//                ctrl = receive_spi_command();
//                i++;
//            }
//            else if(i < msg_len)
//            {
//                data[j] = receive_spi_command();
//                j++;
//                i++;
//            }
//            else if(checksum == 0){
//                checksum = receive_spi_command();
//            }
//            else{
//                chksum = cmd+ctrl;
//                while(j > 0){
//                    chksum = chksum + data[j-1];
//                    j--;
//                }
//                chksum = chksum & 0x7f;
//            }
//        }
//
//        if(cmd == 2){
//            duty = (data[0] << 8) + data[1];
//            move_forward_motor1(duty);
//            move_forward_motor2(duty);
//        }


/*
         * ADC TEST CODE
         *  Returns recorded voltage of the ADC module
         */

//        if(_SPIRBF)
//        {
//            tmp = receive_spi_command();
//        }

=======
    //InitApp();

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();

    motor0_init();
    SPI1SLAVE_init();
    //printf("%d\n", PORTA _SFR_);
    /* TODO <INSERT USER APPLICATION CODE HERE> */
    long int duty = 0;
    //AD1PCFGL = 0x00FF;
    
//    TRISA = 0x0000;
//    TRISB = 0x0000;

//    spi_data = SPI1_REC();

    while(1)
    {
        duty++;
        //InitApp();
//        TRISB = 0x0000;
//        LATB = 0x0000;
//
////        TRISA = 0x00;
//        PORTA = 0xFF;
//
////        TRISB = 0x0000;
//        LATB = 0xFFFF;
//
////        TRISA = 0x00;
//        LATA = 0x00;
//        if((SPI1STAT & _SPIRBF) == 1)
//            spi_data = SPI1_REC();
        //if((duty%50000) == 0){
        //   PWM1CON1 = 0x0770;

        //SPI1_SEND(duty%128);

        if(PORTCbits.RC6 == 1)
            spi_data = SPI1_REC();

            if((duty%100000) == 0){
                motor1(spi_data%255);
                //PWM1CON1 = 0x0707;
            }
        //}
>>>>>>> 8bb88a5dab0fc86bee57fd49bb9c95909b443296
    }
}
