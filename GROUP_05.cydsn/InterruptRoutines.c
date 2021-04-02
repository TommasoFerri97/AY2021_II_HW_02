/* ========================================
 *
 * InterruptRoutines.c Group 05
 *
 * ========================================
*/

#include "InterruptRoutines.h" 
#include "UART.h"
#include "stdio.h"

static char message[20] = {'\0'};

CY_ISR(Custom_UART_RX_ISR)
{
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {
        // We have some data in the FIFO
        
        // Read the RX Data
        uint8_t received = UART_ReadRxData();
        // ... Format it
        sprintf(message, "Received: %c\r\n", received);
        // ... Send it over UART
        UART_PutString(message);
    } 
}

/* [] END OF FILE */
