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

// static char message[20] = {'\0'};
#define HEAD 160
#define TAIL 192

uint8_t status_pos = 0;
uint8_t RED;
uint8_t GREEN;
uint8_t BLU;
extern Color COLORE;

CY_ISR(Custom_UART_RX_ISR)
{
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {
        // We have some data in the FIFO
        if (status_pos == 0)
        {
            if (UART_ReadRxData() == HEAD )
            {
                status_pos = 1;
            }
        }
       
        else if (status_pos == 1)
        {
            RED = UART_ReadRxData();
            status_pos++;
            
        }
        else if (status_pos == 2)
        {
            GREEN = UART_ReadRxData();
            status_pos++;
            
        }
        else if (status_pos == 3)
        {
            BLU = UART_ReadRxData();
            status_pos++;
            
        }
        else if (status_pos == 4)
        {   
            if (UART_ReadRxData() == TAIL) 
            {
                Color COLORE = {RED,GREEN,BLU};
                status_pos = 0;
            }
        }
      
    } 
    
}

/* [] END OF FILE */
