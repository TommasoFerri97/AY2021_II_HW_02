/* ========================================
 *
 * main.c Group 05
 *
 * ========================================
*/

#include "project.h"
#include "InterruptRoutines.h"
#include "colors.h"
#include "RGBLedDriver.h"
            
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    RGBLed_Start();
    UART_Start();
    RGBLed_WriteColor(BLACK);
    ISR_UART_StartEx(Custom_UART_RX_ISR);
    
    for(;;)
    {
        /* Place your application code here. */
    } 
}

/* [] END OF FILE */