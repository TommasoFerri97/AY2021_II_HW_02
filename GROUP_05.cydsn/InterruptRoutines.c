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
extern uint8_t state ;
#define START 0
/*
#define START 0
#define HEAD_CASE 1
#define RED_CASE 2
#define GREEN_CASE 3
#define BLU_CASE 4
*/
CY_ISR(Custom_UART_RX_ISR)
{
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {
     
            value = UART_ReadRxData();
            flag_received = 1;
        
} 
}




CY_ISR(Custom_TIMER_ISR)
{
        if (flag_received == 0)
        {
            state = START ;
            ISR_TIMER_Stop();
        }
    
}
/* [] END OF FILE */
