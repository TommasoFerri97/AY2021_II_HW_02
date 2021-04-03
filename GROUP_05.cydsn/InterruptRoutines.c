/* ========================================
 *
 * InterruptRoutines.c Group 05
 *
 * ========================================
*/

#include "InterruptRoutines.h"
#include "RGBLedDriver.h"
#include "UART.h"
#include "stdio.h"

extern volatile uint8_t flag_received;
extern volatile uint8_t value;
extern volatile int timer_value;

CY_ISR(Custom_UART_RX_ISR)
{
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {
        value = UART_ReadRxData();
        flag_received = 1;
    } 
}

CY_ISR(Custom_TIMER_RESET)
{
    TIMER_RESET_ReadStatusRegister();
    timer_value++;
}

/* [] END OF FILE */
