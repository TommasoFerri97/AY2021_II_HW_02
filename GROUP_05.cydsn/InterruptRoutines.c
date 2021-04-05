/* ========================================
 * 
 * Group 05
 *  
 * File Name: InterruptRoutines.c
 * 
 * PSoC Creator  4.4
 *
 * Description:
 * It contains definitions of all the declared ISR functions;
 * 
 * ========================================
*/

<<<<<<< HEAD

/* 
 * ========================================
 *
 * include header files containing the needed functions' declations;
 *
 * ========================================
*/ 

#include "InterruptRoutines.h" 
#include "UART.h"
#include "stdio.h"
//#include "RGBLedDriver.h"

/* 
 * ========================================
 *
 * set up of local and global variables;
 * extern: tells the compiler that the variable definition is in another module (main.c file);
 * volatile: volatile tells the compiler that thevariable value may be modified by some external event;
 *
 * ========================================
*/ 
=======
#include "InterruptRoutines.h"
#include "RGBLedDriver.h"
#include "UART.h"
#include "stdio.h"
>>>>>>> 4c442696de423044ea2b5faf0955df73cc118785

extern volatile uint8_t flag_received;
extern volatile uint8_t value;
extern volatile int timer_value;

/* 
 * ========================================
 *
 * Custom_UART_RX_ISR definition;
 *
 * ========================================
*/ 

CY_ISR(Custom_UART_RX_ISR) /* CY_ISR used to define the function declared with CY_ISR_PROTO*/
{
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY) /* check the data arrival */
    {
<<<<<<< HEAD
     
            value = UART_ReadRxData(); /* read arrived data from Rx register */
            flag_received = 1; /* flag variable used to regularize byte acquisition in each main state */
        
} 
=======
        value = UART_ReadRxData();
        flag_received = 1;
    } 
>>>>>>> 4c442696de423044ea2b5faf0955df73cc118785
}

/* 
 * ========================================
 *
 * Custom_TIMER_RESET definition;
 *
 * ========================================
*/ 

CY_ISR(Custom_TIMER_RESET) /* CY_ISR used to define the function declared with CY_ISR_PROTO*/
{
    TIMER_RESET_ReadStatusRegister(); /*Returns the current state of the status register; the interrupt output remains asserted until the status register is read */
    timer_value++; /* timer period set on 1 second from design; time_value updates to track the timeout condition */
}

/* [] END OF FILE */
