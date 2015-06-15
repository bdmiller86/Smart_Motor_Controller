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

#include "com.h"


/******************************************************************************/
/* Function Definitions                                                       */
/******************************************************************************/

/*
 * INITIALIZE_SPI_MASTER: Initializes the built-in SPI functionality and
 *  configures the SMC as the master.
 */
void initialize_spi_master(void)
{
    /* Disable SPI during setup */
    SPI1STATbits.SPIEN  = 0;
    
    /* Map reprogrammable pins to SPI Functions */
    _RP23R      = 0b01000;      // Clock input on RP23
    _RP24R      = 0b00111;      // MOSI (SDO) on RP24
    _SDI1R      = 0b11001;      // MISO (SDI) on RP25

    /* Set the proper input/output functionality for the SPI pins */
    _TRISC6     = 0;
    _LATC6      = 1;


/*
 * The following code sequence shows SPI register configuration for Master mode
 * (from Microchip SPI User Guide)
 */
    
    IFS0bits.SPI1IF     = 0;   // Clear the Interrupt flag
    IEC0bits.SPI1IE     = 0;   // Disable the interrupt

    // SPI1CON1 Register Settings

    SPI1CON1bits.DISSCK = 0;    // Internal serial clock is enabled
    SPI1CON1bits.DISSDO = 0;    // SDOx pin is controlled by the module
    SPI1CON1bits.MODE16 = 0;    // Communication is word-wide (16 bits)
    SPI1CON1bits.MSTEN  = 1;    // Master mode enabled
    SPI1CON1bits.SSEN   = 1;    // Slave Select controlled by GPIO
    SPI1CON1bits.SMP    = 0;    // Input data is sampled at the middle of data output time
    SPI1CON1bits.CKE    = 0;    // Serial output data changes on transition from
                                // Idle clock state to active clock state
    SPI1CON1bits.CKP    = 0;    // Idle state for clock is a low level;
                                // active state is a high level
    SPI1STATbits.SPIEN  = 1;    // Enable SPI module

   // Interrupt Controller Settings (We are not using interrupts with Master)

//   IFS0bits.SPI1IF      = 0;        // Clear the Interrupt flag
//   IEC0bits.SPI1IE      = 1;        // Enable the interrupt

}

/*
 * INITIALIZE_SPI_SLAVE: Initializes the built-in SPI functionality and
 *  configures the SMC as the slave.
 */
void initialize_spi_slave(void)
{
    /* Disable SPI during setup */
    SPI1STATbits.SPIEN  = 0;

    /* Map reprogrammable pins to SPI functions */
    _SCK1R  = 0b10111;      // Clock input on RP23          * Pin 78 on PIM
    _SDI1R  = 0b11000;      // MOSI (data input) on RP24    * Pin 68 on PIM
    _RP25R  = 0b00111;      // MISO (data output) on RP25   * Pin 69 on PIM
    _SS1R   = 0b10110;      // Slave select on RP22         * Pin 77 on PIM

    /* Clear SPI data buffer */
    SPI1BUF             = 0;    // Clear SPI buffer register

    /* Disable SPI interrupts during setup */
//    SRbits.IPL          = 7;    // Disable all interrupts
    IFS0bits.SPI1IF     = 0;    // Clear SPI Interrupt flag
    IEC0bits.SPI1IE     = 0;    // Disable SPI Interrupt

    /* SPI1CON1 Register Settings */
    SPI1CON1bits.DISSCK = 0;    // Internal Serial Clock is enabled
    SPI1CON1bits.DISSDO = 0;    // SDOx pin is controlled by the module
    SPI1CON1bits.MODE16 = 0;    // Communication is byte-wide (8 bits)
    SPI1CON1bits.MSTEN  = 0;    // Master mode disabled
    SPI1CON1bits.SMP    = 0;    // Input data is sampled at the middle of data
                                // output time.
    SPI1CON1bits.CKE    = 0;    // Serial output data changes on transition
                                // from idle clock state to active clock state
    SPI1CON1bits.SSEN   = 1;    // Slave Select pin must be drive low to enable
                                // transmission and reception
    SPI1CON1bits.CKP    = 0;    // Idle state for clock is a low level; active
                                // state is a high level

    /* SPI1STAT Register Settings */
    SPI1STATbits.SPIROV = 0;     // No Receive Overflow has occurred
    SPI1STATbits.SPIEN  = 1;     // Enable SPI module

    /* Set up SPI Interrupt */
//    INTCON1bits.NSTDIS  = 0;    // Enable interrupt nesting
//    IPC2bits.SPI1IP     = 7;    // Interrupt priority 1 (highest)
//    IEC0bits.SPI1IE     = 1;    // Enable SPI Interrupt
//    SRbits.IPL          = 0;    // Enable all interrupts

}

/*
 * RECEIVE_SPI_COMMAND: Returns the value stored in the SPI Buffer
 */
uint8_t receive_spi_command(void)
{
    return(SPI1BUF & 0xff);
}

/*
 * SEND_SPI_COMMAND: Sends out an SPI transmission.
 */
void send_spi_command(uint8_t data)
{
    uint8_t tmp;

    /* Enable the Slave Select line */
    _LATC6 = SS_ENABLE;

    /* Dummy read of the SPI Buffer to clear SPIRBF flag */
    tmp = SPI1BUF;

    /* Write SPI Data to the SPI Buffer */
    SPI1BUF = data;

    /* Wait for the SPI transmission to complete */
    while (!_SPIRBF);

    /* Disable the Slave Select line */
    _LATC6 = SS_DISABLE;
}

void send_spi_data(uint8_t *data, uint8_t len, uint8_t *flag, uint8_t ctr)
{
    uint8_t tmp;
    if(ctr == 0){
        //Dummy read to clear the the buffer to allow transmission
        tmp = receive_spi_command();
//        SPI1BUF = len;
//        ctr++;
    }
    else if((ctr-1) < len){
        tmp = receive_spi_command();
        SPI1BUF = (ctr-1);
//        SPI1BUF = data[(ctr-1)];
//        ctr++;
    }
    else{
        ctr = 0;
        *flag = 0;
    }


}

void receive_spi_data(uint8_t *data, uint8_t len, uint8_t *flag, uint8_t ctr)
{





}

