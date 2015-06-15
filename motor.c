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

#include "motor.h"


/******************************************************************************/
/* Static Functions                                                           */
/******************************************************************************/

static void set_duty_cycle_motor1(uint16_t);

static void set_duty_cycle_motor2(uint16_t);


/******************************************************************************/
/* Function Definitions                                                       */
/******************************************************************************/

/*
 * INITIALIZE_MOTOR1: Initialize the PWM signal to drive motor1. This motor is
 * driven off of the PWM1H1 and PWM1L1 lines.
 */
void initialize_motor1(void)
{
    /* Disable PWM Timer while configuring */
    P1TCONbits.PTEN     = 0;

    /* PWM time base operates in a Free Running mode */
    P1TCONbits.PTMOD    = 0b00;

    /* Set PWM prescaler, postscaler, and period */
    P1TCONbits.PTCKPS   = 0b00;     // PWM Prescaler = 1
    P1TCONbits.PTOPS    = 0b0000;   // PWM Postscaler = 1
    P1TPER              = PWM_MAX;  // PWM Period = 1999
                                    // Fcy = 40MHz
                                    // Fpwm = Fcy / ( PWMpre * ( PWMper + 1 ) )
                                    //      = 20kHz

    /* PWM pins are run in Independent PWM Output Mode */
    PWM1CON1bits.PMOD1  = 1;

    /* PWM pins are enabled for PWM output */
    PWM1CON1bits.PEN1H  = 1;
    PWM1CON1bits.PEN1L  = 1;

    /* Updated so the duty cycle are immediate */
    PWM1CON2bits.IUE    = 1;

    /* Enable Output Override for motor direction control */
    P1OVDCONbits.POVD1H = 0;
    P1OVDCONbits.POVD1L = 0;

    /* Pull the PWM lines for motor 0 low (coast) */
    P1OVDCONbits.POUT1H = 0;
    P1OVDCONbits.POUT1L = 0;

    /* Enable PWM Timer */
    P1TCONbits.PTEN     = 1;

    /* Set initial duty cycle to 0 */
    set_duty_cycle_motor1(0);
}

/*
 * INITIALIZE_MOTOR2: Initialize the PWM signal to drive motor2. This motor is
 * driven off of the PWM1H2 and PWM1L2 lines.
 */
void initialize_motor2(void)
{
    /* Disable PWM Timer while configuring */
    P1TCONbits.PTEN     = 0;

    /* PWM time base operates in a Free Running mode */
    P1TCONbits.PTMOD    = 0b00;

    /* Set PWM prescaler, postscaler, and period */
    P1TCONbits.PTCKPS   = 0b00;     // PWM Prescaler = 1
    P1TCONbits.PTOPS    = 0b0000;   // PWM Postscaler = 1
    P1TPER              = PWM_MAX;  // PWM Period = 1999
                                    // Fcy = 40MHz
                                    // Fpwm = Fcy / ( PWMpre * ( PWMper + 1 ) )
                                    //      = 20kHz

    /* PWM pins are run in Independent PWM Output Mode */
    PWM1CON1bits.PMOD2  = 1;

    /* PWM pins are enabled for PWM output */
    PWM1CON1bits.PEN2H  = 1;
    PWM1CON1bits.PEN2L  = 1;

    /* Updated so the duty cycle are immediate */
    PWM1CON2bits.IUE    = 1;

    /* Enable Output Override for motor direction control */
    P1OVDCONbits.POVD2H = 0;
    P1OVDCONbits.POVD2L = 0;

    /* Pull the PWM lines for motor 0 low (coast) */
    P1OVDCONbits.POUT2H = 0;
    P1OVDCONbits.POUT2L = 0;

    /* Enable PWM Timer */
    P1TCONbits.PTEN     = 1;

    /* Set initial duty cycle to 0 */
    set_duty_cycle_motor2(0);
}

void motor(int16_t duty,int8_t mtr, int8_t brake)
{
    //Chooses motor direction based on sign of duty
    //Positive = Forward, Negative = Reverse
    if(duty < 0){
        duty = -duty;
        if(mtr == 0){
            move_reverse_motor1(duty);
        }else{
            move_reverse_motor2(duty);
        }
    }
    else if(duty > 0)
    {
        if(mtr == 0){
            move_forward_motor1(duty);
        }else{
            move_forward_motor2(duty);
        }
    }
    else{
        if(brake){
            if(mtr == 0){
                brake_motor1();
            }else{
                brake_motor2();
            }
        }
        else{
            if(mtr == 0){
                coast_motor1();
            }else{
                coast_motor2();
            }
        }
    }

}


/*
 * MOVE_MOTOR1_FORWARD:
 */
void move_forward_motor1(uint16_t duty)
{
    /* Enable Output Override for motor direction control */
    P1OVDCONbits.POVD1H = 1;
    P1OVDCONbits.POVD1L = 0;

    /* Pull PWM1L1 low */
    P1OVDCONbits.POUT1L = 0;

    /* Set the new duty cycle */
    set_duty_cycle_motor1(duty);
}

/*
 * MOVE_MOTOR2_FORWARD:
 */
void move_forward_motor2(uint16_t duty)
{
    /* Enable Output Override for motor direction control */
    P1OVDCONbits.POVD2H = 1;
    P1OVDCONbits.POVD2L = 0;

    /* Pull PWM1L2 low */
    P1OVDCONbits.POUT2L = 0;

    /* Set the new duty cycle */
    set_duty_cycle_motor2(duty);
}

/*
 * MOVE_MOTOR1_REVERSE:
 */
void move_reverse_motor1(uint16_t duty)
{
    /* Enable Output Override for motor direction control */
    P1OVDCONbits.POVD1H = 0;
    P1OVDCONbits.POVD1L = 1;

    /* Pull PWM1H1 low */
    P1OVDCONbits.POUT1H = 0;

    /* Set the new duty cycle */
    set_duty_cycle_motor1(duty);
}

/*
 * MOVE_MOTOR2_REVERSE:
 */
void move_reverse_motor2(uint16_t duty)
{
    /* Enable Output Override for motor direction control */
    P1OVDCONbits.POVD2H = 0;
    P1OVDCONbits.POVD2L = 1;

    /* Pull PWM1H2 low */
    P1OVDCONbits.POUT2H = 0;

    /* Set the new duty cycle */
    set_duty_cycle_motor2(duty);
}

/*
 * BREAK_MOTOR1:
 */
void brake_motor1(void)
{
    /* Enable Output Override for motor direction control */
    P1OVDCONbits.POVD1H = 0;
    P1OVDCONbits.POVD1L = 0;

    /* Pull the PWM lines for motor 0 low (coast) */
    P1OVDCONbits.POUT1H = 1;
    P1OVDCONbits.POUT1L = 1;
}

/*
 * BREAK_MOTOR2:
 */
void brake_motor2(void)
{
    /* Enable Output Override for motor direction control */
    P1OVDCONbits.POVD2H = 0;
    P1OVDCONbits.POVD2L = 0;

    /* Pull the PWM lines for motor 1 high (brake) */
    P1OVDCONbits.POUT2H = 1;
    P1OVDCONbits.POUT2L = 1;
}

/*
 * COAST_MOTOR1:
 */
void coast_motor1(void)
{
    /* Enable Output Override for motor direction control */
    P1OVDCONbits.POVD1H = 0;
    P1OVDCONbits.POVD1L = 0;

    /* Pull the PWM lines for motor 0 low (coast) */
    P1OVDCONbits.POUT1H = 0;
    P1OVDCONbits.POUT1L = 0;
}

/*
 * COAST_MOTOR2:
 */
void coast_motor2(void)
{
    /* Enable Output Override for motor direction control */
    P1OVDCONbits.POVD2H = 0;
    P1OVDCONbits.POVD2L = 0;

    /* Pull the PWM lines for motor 1 low (coast) */
    P1OVDCONbits.POUT2H = 0;
    P1OVDCONbits.POUT2L = 0;
}

/*
 * SET_DUTY_CYCLE_MOTOR1:
 */
static void set_duty_cycle_motor1(uint16_t duty)
{
    P1DC1 = duty;
}

/*
 * SET_DUTY_CYCLE_MOTOR2:
 */
static void set_duty_cycle_motor2(uint16_t duty)
{
    P1DC2 = duty;
}