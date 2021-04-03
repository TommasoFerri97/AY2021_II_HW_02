/* ========================================
 *
 * InterruptRoutines.c Group 05
 *
 * ========================================
*/

#include "InterruptRoutines.h" 
#include "UART.h"
#include "stdio.h"
#include "RGBLedDriver.h"

extern volatile uint8_t flag_received;
extern volatile uint8_t value;

CY_ISR(Custom_UART_RX_ISR)
{
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {
        value = UART_ReadRxData();
        flag_received = 1;
    } 
}

/* [] END OF FILE */
