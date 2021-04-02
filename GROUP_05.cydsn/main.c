/* ========================================
 *
 * main.c Group 05
 *
 * ========================================
*/

#include "project.h"
#include "stdio.h"
#include "InterruptRoutines.h"
#include "colors.h"
#include "RGBLedDriver.h"

#define HEAD 160
#define TAIL 192

static char message[20] = {'\0'};
uint8_t status_pos = 0;
uint8_t red;
uint8_t green;
uint8_t blu;
Color COLORE;
            
int main(void)
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    RGBLed_Start();
    UART_Start();
    RGBLed_WriteColor(BLACK);
    ISR_UART_StartEx(Custom_UART_RX_ISR);
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    for(;;)
    {   
        if (value == HEAD && status_pos == 0)
        {
            sprintf(message, "HEAD received: %d\r\n", value);
            UART_PutString(message);
            sprintf(message, "Write RED hex:\r\n");
            UART_PutString(message);
        }
        else if (status_pos == 1)
        {
            red = value;
            sprintf(message, "RED is: %d\r\n", red);
            UART_PutString(message);
            sprintf(message, "Write GREEN hex:\r\n");
            UART_PutString(message);
        }
        else if (status_pos == 2)
        {
            green = value;
            sprintf(message, "GREEN is: %d\r\n", green);
            UART_PutString(message);
            sprintf(message, "Write BLU hex:\r\n");
            UART_PutString(message);
        }
        else if (status_pos == 3)
        {
            blu = value;
            sprintf(message, "BLU is: %d\r\n", blu);
            UART_PutString(message);
            sprintf(message, "Write TAIL:\r\n");
            UART_PutString(message);
        }
        else if (value == TAIL && status_pos == 4)
        {   
            Color COLORE = {red, green, blu};
            status_pos = 0;
            sprintf(message, "Done!\r\n");
            UART_PutString(message);
        }
    } 
}

/* [] END OF FILE */