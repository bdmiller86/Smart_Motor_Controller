/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        7370000L
#define FCY             SYS_FREQ/2

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

<<<<<<< HEAD
void configure_oscillator(void); /* Handles clock switching/osc initialization */

void initialize_smc(void);         /* I/O and Peripheral Initialization */

void initialize_rti(void);
=======
void ConfigureOscillator(void); /* Handles clock switching/osc initialization */

void motor0_init(void);

void motor1(int);

void SPI1_init(void);

void SPI1_SEND(int data);

int SPI1_REC(void);
>>>>>>> 8bb88a5dab0fc86bee57fd49bb9c95909b443296
