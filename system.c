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

#include "system.h"          /* variables/params used by system.c             */

/******************************************************************************/
/* System Level Functions                                                     */
/*                                                                            */
/* Custom oscillator configuration funtions, reset source evaluation          */
/* functions, and other non-peripheral microcontroller initialization         */
/* functions get placed in system.c.                                          */
/*                                                                            */
/******************************************************************************/

/* Refer to the device Family Reference Manual Oscillator section for
information about available oscillator configurations.  Typically
this would involve configuring the oscillator tuning register or clock
switching useing the compiler's __builtin_write_OSCCON functions.
Refer to the C Compiler for PIC24 MCUs and dsPIC DSCs User Guide in the
compiler installation directory /doc folder for documentation on the
__builtin functions.*/

/* TODO Add clock switching code if appropriate.  An example stub is below.   */
void ConfigureOscillator(void)
{
        PLLFBD = 41;
        CLKDIVbits.PLLPOST = 0;
        CLKDIVbits.PLLPRE = 0;

         OSCTUN=0;     // Tune FRC oscillator, if FRC is used

        RCONbits.SWDTEN = 0;
        __builtin_write_OSCCONH(0x01);  /* Set OSCCONH for clock switch */
        __builtin_write_OSCCONL(0x01);  /* Start clock switching */
        while(OSCCONbits.COSC != 0b001);
 //       while(OSCCONbits.LOCK != 1);



}

void motor0_init(void)
{


    P1TCON = 0x80F4;        //Set PWM to be Time Based
                            //set Postscaler to 1:16
                            //Set Prescaler to 1:4
                            //PWM Free Running

    // These Three Options Can Be Used to Change Which Pin the PWM is Output
    PWM1CON1 = 0x0770;      //Turned off PWML and Turned on PWMH
//    PWM1CON1 = 0x0707;      //Turned on PWML and Turned off PWMH
//    PWM1CON1 = 0x0777;      //Turned on PWML and Turned on PWMH

    PWM1CON2 = 0x0004;

    // Setting All Remaining registers
    P1DTCON1 = 0x0000;
    P1DTCON2 = 0x0000;
    P1FLTACON = 0x0000;

    P1OVDCON = 0x3F00;
    P1TPER = 255;




    //Set PWM to 0 Initially
    P1DC1 = 0x0000;
    P1DC2 = 0x0000;
    P1DC3 = 0x0000;

}

void motor1(int duty)
{
    if(duty < 0)
    {
        PORTA = (PORTA & 0xFE) | 0x02;
        duty = -duty;
    }
    else
        PORTA = (PORTA & 0xFD) | 0x01;
    PORTB = 0x0000;
//    PORTB = 0x5400;

    P1DC1 = duty;
    P1DC2 = duty;
    P1DC3 = duty;

}

//SPISlave Init Initializes Pins and Registers
void SPI1SLAVE_init(void)
{
    //Setting Pins to SPI Functions
    RPINR20 = 0x1718;   //Setting MOSI to Pin 24
                        //Setting Clock Signal to Pin 23
    RPINR21 = 0x0016;   //Setting Slave Select Input to Pin 22
    RPOR12 = 0x0700;    //Setting MISO to Pin 25

    // Setting SPI Register Attempts from SPI Example
    SPI1BUF = 0;
    //IFS0bits.SPI1IF = 0; // Clear the Interrupt flag
    //IEC0bits.SPI1IE = 0; // Disable the interrupt

    // setup the SPI peripheral
    SPI1STAT = 0x0;  // disable the SPI module (just in case)
    SPI1CON1 = 0x0141;	// FRAMEN = 0, SPIFSD = 0, DISSDO = 0, 
                        // MODE16 = 0; SMP = 0; CKP = 1; CKE = 1;
                        //SSEN = 0; MSTEN = 1; SPRE = 0b000, PPRE = 0b01
    SPI1CON1bits.CKE = 0x01;
    SPI1CON1bits.CKP = 0x00;
    SPI1STAT = 0x8000; // enable the SPI module

    //Setting SPI Registers Personal Attempts
//    SPI1CON1 =  0x00C0; //Setting 8 Bit(vs 16 Bit) communication
//                        //Enable Slave Select
//                        //Idle High, Active at transisition to low
//                        ////Idle low, Active at transisition to high
//                        //Slave Mode
//                        //Setting Prescalers to 8:1 and 64:1(Should not matter
//                        //since in Slave Mode)
//
//    SPI1CON2 =  0x4002; //Setting Frame Pulse Input
//                        //Setting Pulse to coincide with first bit clock
//    SPI1STAT = 0x800C; //Enable SPI, Continue Operation in Idle
//
//    // Interrupt Controller Settings
//    IFS0bits.SPI1IF = 0; // Clear the Interrupt flag
//    IEC0bits.SPI1IE = 1; // Enable the interrupt
}

void SPI1MASTER_init(void)
{
    //Setting Pins to SPI Functions
    RPINR20 = 0x0019;   //Setting MIS0 to Pin 25
    RPOR12 = 0x0007;    //Setting M0SI to Pin 24
    RPOR11 = 0x0809;    //Setting SCK  to Pin 23
                        //Setting SS   to Pin 22


    // setup the SPI peripheral
    SPI1STAT = 0x0;  // disable the SPI module (just in case)
    SPI1CON1 = 0x0161;	// FRAMEN = 0, SPIFSD = 0, DISSDO = 0, MODE16 = 0; SMP = 0; CKP = 1; CKE = 1; SSEN = 0; MSTEN = 1; SPRE = 0b000, PPRE = 0b01
    SPI1CON1bits.CKE = 0x01;
    SPI1CON1bits.CKP = 0x00;
    SPI1STAT = 0x8000; // enable the SPI module

//    SPI1BUF = 0;
//    IFS0bits.SPI1IF = 0; // Clear the Interrupt flag
//    IEC0bits.SPI1IE = 0; // Disable the interrupt
//    // SPI1CON1 Register Settings
//    SPI1CON1bits.DISSCK = 0; // Internal Serial Clock is enabled
//    SPI1CON1bits.DISSDO = 0; // SDOx pin is controlled by the module
//    SPI1CON1bits.MODE16 = 1; // Communication is word-wide (16 bits)
//    SPI1CON1bits.SMP = 0; // Input data is sampled at the middle of data
//    // output time.
//    SPI1CON1bits.CKE = 0; // Serial output data changes on transition
//    // from Idle clock state to active clock state
//    SPI1CON1bits.CKP = 0; // Idle state for clock is a low level; active
//    // state is a high level
//    SPI1CON1bits.MSTEN = 0; // Master mode disabled
//    SPI1STATbits.SPIROV=0; // No Receive Overflow has occurred
//    SPI1STATbits.SPIEN = 1; // Enable SPI module
//    // Interrupt Controller Settings
//    IFS0bits.SPI1IF = 0; // Clear the Interrupt flag
//    IEC0bits.SPI1IE = 1; // Enable the interrupt
}



void SPI1_SEND(int data)
{

    short temp;

    PORTCbits.RC6 = 0;		// lower the slave select line
    temp = SPI2BUF;			// dummy read of the SPI1BUF register to clear the SPIRBF flag
    SPI1BUF = data;		// write the data out to the SPI peripheral
    while (!SPI1STATbits.SPIRBF)	// wait for the data to be sent out
		;
	PORTCbits.RC6 = 1;		// raise the slave select line

}

int SPI1_REC(void){

    int data;

    //while((SPI1STAT & _SPIRBF) == 0);
    while (!SPI1STATbits.SPIRBF);	// wait for the data to be sent out
    
    data = SPI1BUF;

    while (!SPI1STATbits.SPIRBF);	// wait for the data to be sent out
    //while((SPI1STAT & _SPIRBF) == 0);


    return(data);

}
