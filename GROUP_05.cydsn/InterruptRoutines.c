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

#define HEAD 160
#define TAIL 192

static char message[20] = {'\0'};
uint8_t value;

CY_ISR(Custom_UART_RX_ISR)
{
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {
        value = UART_ReadRxData();
        status_pos++;
        
        
        /*
        if (UART_ReadRxData() == HEAD && status_pos == 0)
        {
            sprintf(message, "HEAD received: %d\r\n", UART_ReadRxData());
            UART_PutString(message);
            sprintf(message, "Write RED hex:\r\n");
            UART_PutString(message);
            status_pos++;
        }
        else if (status_pos == 1)
        {
            red = UART_ReadRxData();
            sprintf(message, "RED is: %d\r\n", red);
            UART_PutString(message);
            sprintf(message, "Write GREEN hex:\r\n");
            UART_PutString(message);
            status_pos++;
        }
        else if (status_pos == 2)
        {
            green = UART_ReadRxData();
            sprintf(message, "GREEN is: %d\r\n", green);
            UART_PutString(message);
            sprintf(message, "Write BLU hex:\r\n");
            UART_PutString(message);
            status_pos++;
        }
        else if (status_pos == 3)
        {
            blu = UART_ReadRxData();
            sprintf(message, "BLU is: %d\r\n", blu);
            UART_PutString(message);
            sprintf(message, "Write TAIL:\r\n");
            UART_PutString(message);
            status_pos++;
        }
        else if (UART_ReadRxData() == TAIL && status_pos == 4)
        {   
            Color COLORE = {red, green, blu};
            status_pos = 0;
            sprintf(message, "Done!\r\n");
            UART_PutString(message);
        }
        */
    } 
}

/* [] END OF FILE */
