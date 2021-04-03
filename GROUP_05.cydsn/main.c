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
#define TIMER_END 7

static char message[20] = {'\0'};
volatile uint8_t flag_received = 0;
volatile uint8_t value;

volatile int timer_value;
int set_timer = 5;

uint8_t state = START;
uint8_t print_message = 0;
uint8_t red;
uint8_t green;
uint8_t blu;
Color COLORE;
uint16 timer;     


int main(void)
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    RGBLed_Start();
    UART_Start();
    TIMER_RESET_Start();
    ISR_UART_StartEx(Custom_UART_RX_ISR);
    ISR_TIMER_StartEx(Custom_TIMER_RESET);
    
    RGBLed_WriteColor(BLACK);
    //ISR_TIMER_StartEx(Custom_TIMER_ISR);
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    for(;;)
    {   
        switch(state) {
            case START:
                if (flag_received == 1)
                {
                    timer_value = 0;
                    state = HEAD_CASE;
                }
                break;
            
            case HEAD_CASE:
                if (value == HEAD)
                {
                    flag_received = 0;
                    timer_value = 0;
                    state = RED_CASE;
                    ISR_TIMER_StartEx(Custom_TIMER_ISR);
                }
                else if (value == 'v')
                {
                    sprintf(message, "RGB LED Program $$$\n");
                    UART_PutString(message);
                    flag_received = 0;
                    timer_value = 0;
                    state = START;
                }
                else if (value == TIMER)
                {
                    flag_received = 0;
                    timer_value = 0;
                    state = TIMER_CASE;
                }
                else if (timer_value == set_timer)
                {
                    flag_received = 0;
                    timer_value = 0;
                    sprintf(message, "RESET\n");
                    UART_PutString(message);
                    state = START;
                }
                break;
                
            case RED_CASE:
                if (flag_received == 1)
                {
                    red = value;
                    flag_received = 0;
                    timer_value = 0;
                    state = GREEN_CASE;
                    ISR_TIMER_StartEx(Custom_TIMER_ISR);
                }
                else if (timer_value == set_timer)
                {
                    flag_received = 0;
                    timer_value = 0;
                    sprintf(message, "RESET\n");
                    UART_PutString(message);
                    state = START;
                }
                break;
                
            case GREEN_CASE:
                if (flag_received == 1)
                {
                    green = value;
                    flag_received = 0;
                    timer_value = 0;
                    state = BLU_CASE;
                    ISR_TIMER_StartEx(Custom_TIMER_ISR);
                }
                else if (timer_value == set_timer)
                {
                    flag_received = 0;
                    timer_value = 0;
                    sprintf(message, "RESET\n");
                    UART_PutString(message);
                    state = START;
                }
                break;
                
            case BLU_CASE:
                if (flag_received == 1)
                {
                    blu = value;
                    flag_received = 0;
                    timer_value = 0;
                    state = COLOR_CASE;
                    ISR_TIMER_StartEx(Custom_TIMER_ISR);
                }
                else if (timer_value == set_timer)
                {
                    flag_received = 0;
                    timer_value = 0;
                    sprintf(message, "RESET\n");
                    UART_PutString(message);
                    state = START;
                }
                break;
                
            case COLOR_CASE:
                if (value == TAIL && flag_received == 1)
                {
                    Color COLORE = {red, green, blu};
                    RGBLed_WriteColor(COLORE);
                    flag_received = 0;
                    timer_value = 0;
                    state = START;
                }
                else if (flag_received == 0 && timer_value == set_timer)
                {
                    flag_received = 0;
                    timer_value = 0;
                    sprintf(message, "RESET\n");
                    UART_PutString(message);
                    state = START;
                }
                break;
            
            case TIMER_CASE:
                if (flag_received == 1)
                {
                    set_timer = value;
                    timer_value = 0;
                    flag_received = 0;
                    state = TIMER_END;
                }
                else if (timer_value == set_timer)
                {
                    flag_received = 0;
                    timer_value = 0;
                    sprintf(message, "RESET\n");
                    UART_PutString(message);
                    state = START;
                }
                break;
                    
            case TIMER_END:
                if (value == TAIL && flag_received == 1)
                {
                    flag_received = 0;
                    timer_value = 0;
                    sprintf(message, "The new reset time value is: %d\r\n", set_timer);
                    UART_PutString(message);
                    state = START;
                }
                else if (timer_value == set_timer)
                {
                    set_timer = 5;
                    flag_received = 0;
                    timer_value = 0;
                    sprintf(message, "RESET\n");
                    UART_PutString(message);
                    state = START;
                }
                break;
        }
    } 
}

/* [] END OF FILE */