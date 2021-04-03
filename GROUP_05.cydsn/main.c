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
#define TIMER 161
#define TAIL 192

#define START 0
#define HEAD_CASE 1
#define RED_CASE 2
#define GREEN_CASE 3
#define BLU_CASE 4
#define COLOR_CASE 5
#define TIMER_CASE 6

static char message[20] = {'\0'};
volatile uint8_t flag_received = 0;
volatile uint8_t value;

uint8_t state = START;
uint8_t print_message = 0;
uint8_t red;
uint8_t green;
uint8_t blu;
Color COLORE;
            
int main(void)
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    RGBLed_Start();
    UART_Start();
    ISR_UART_StartEx(Custom_UART_RX_ISR);
    
    RGBLed_WriteColor(BLACK);
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    for(;;)
    {   
        switch(state) {
            case START:
                if (flag_received == 0 && print_message == 0)
                {
                    sprintf(message, "Waiting for a color or a command:\n");
                    UART_PutString(message);
                    print_message = 1;
                }
                
                if (flag_received == 1)
                {
                    print_message = 0;
                    flag_received = 0;
                    state = HEAD_CASE;
                }
                break;
            
            case HEAD_CASE:
                if (value == HEAD)
                {
                    sprintf(message, "HEAD received!\n");
                    UART_PutString(message);
                    flag_received = 0;
                    state = RED_CASE;
                }
                else if (value == 'v')
                {
                    sprintf(message, "RGB LED Program $$$\n");
                    UART_PutString(message);
                    flag_received = 0;
                    state = START;
                }
                else if (value == TIMER)
                {
                    sprintf(message, "TIMER ready to set!\n");
                    UART_PutString(message);
                    flag_received = 0;
                    state = TIMER_CASE;
                }
                break;
                
            case RED_CASE:
                if (flag_received == 1)
                {
                    red = value;
                    sprintf(message, "RED is: %d\r\n", red);
                    UART_PutString(message);
                    flag_received = 0;
                    state = GREEN_CASE;
                }
                break;
                
            case GREEN_CASE:
                if (flag_received == 1)
                {
                    green = value;
                    sprintf(message, "GREEN is: %d\r\n", green);
                    UART_PutString(message);
                    flag_received = 0;
                    state = BLU_CASE;
                }
                break;
                
            case BLU_CASE:
                if (flag_received == 1)
                {
                    blu = value;
                    sprintf(message, "BLU is: %d\r\n", blu);
                    UART_PutString(message);
                    flag_received = 0;
                    state = COLOR_CASE;
                }
                break;
                
            case COLOR_CASE:
                if (flag_received == 1)
                {   
                    if (value == TAIL)
                    {
                        Color COLORE = {red, green, blu};
                        sprintf(message, "Done! Color received!\r\n");
                        UART_PutString(message);
                        RGBLed_WriteColor(COLORE);
                        flag_received = 0;
                        state = START;
                    }
                }
                break;
            
            /*
            case TIMER_CASE:
                if (flag_received == 1)
                {
                    timer = value;
                    sprintf(message, "BLU is: %d\r\nWrite TAIL:\r\n", blu);
                    UART_PutString(message);
                    flag_received = 0;
                }
            */
        }
    } 
}

/* [] END OF FILE */