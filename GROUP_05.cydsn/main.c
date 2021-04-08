/* ========================================
 * 
 * Group 05
 *  
 * File Name: main.c
 * 
 * PSoC Creator  4.4
 *
 * Description:
 * It contains the code to read the serial port input about the color information 
 * with astructure " A0 Red Green Bue C0" and to drive the RGB led;
 * It allaws access to an external GUI thanks to the typing of 'v' char from an external terminal as CoolTerm;
 * it permits the user to change the timeout set up with this command structure " A1 Timeout C0 ";
 * Red, Green, Blu and Timeout needs to be set in hexadecimal;
 *
 * ========================================
*/

/* 
 * ========================================
 *
 * include header files containing the needed functions' declations;
 *
 * ========================================
*/ 

#include "project.h"
#include "stdio.h"
#include "InterruptRoutines.h"
#include "RGBLedDriver.h"

/* 
 * ========================================
 *
 * definition of constants;
 *
 * ========================================
*/ 

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
const Color BLACK = {0, 0, 0};

/* 
 * ========================================
 *
 * variables definitions and initialization;
 *
 * ========================================
*/ 

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

/* 
 * ========================================
 *
 * main code definition;
 *
 * ========================================
*/ 
   
int main(void)
{
    /* enabling of peripherals*/
    RGBLed_Start();
    UART_Start();
    TIMER_RESET_Start();
    ISR_UART_StartEx(Custom_UART_RX_ISR);
    ISR_TIMER_StartEx(Custom_TIMER_RESET);
    
    /* LEd color initialization */
    
    RGBLed_WriteColor(BLACK);

    
   /* Enable global interrupts */
    
    CyGlobalIntEnable; 

    
    for(;;)
    {   
        /* the START case is used to check the arrival of a data */
        switch(state) {
            case START:
                if (flag_received == 1)
                {
                    timer_value = 0;
                    state = HEAD_CASE;
                }
            break;
                
        /* the HEAD_CASE case is used to check if the first byte is the packet header of the color,..     
        ...timer or just the 'v' char */
            
            case HEAD_CASE:
                if (value == HEAD) /* checked color header; shift to RED_CASE */
                {
                    flag_received = 0;
                    timer_value = 0;
                    state = RED_CASE;
                }
                else if (value == 'v') /* checked for 'v'; print RGB LED Program $$$ to connect the GUI */
                {
                    sprintf(message, "RGB LED Program $$$\n");
                    UART_PutString(message);
                    flag_received = 0;
                    timer_value = 0;
                    state = START;
                }
                else if (value == TIMER) /* checked timer header; shift to TIMER_CASE*/
                {
                    flag_received = 0;
                    timer_value = 0;
                    state = TIMER_CASE;
                }
                else if (timer_value == set_timer) /* no correct packet header checked; reset timer time out*/
                {
                    flag_received = 0;
                    timer_value = 0;
                    sprintf(message, "RESET\n");
                    UART_PutString(message);
                    state = START; /* move back to START */       
                }
            break;
                
        /* RED_CASE used to read the Red byte value and shift to GREEN_CASE */        
            
            case RED_CASE:
                if (flag_received == 1)
                {
                    red = value;
                    flag_received = 0;
                    timer_value = 0;
                    state = GREEN_CASE;
                }
                else if (timer_value == set_timer) /* no Red byte inside the timeout window; move back to START */
                {
                    flag_received = 0;
                    timer_value = 0;
                    sprintf(message, "RESET\n");
                    UART_PutString(message);
                    state = START;
                }
            break;
                
        /* GREEN_CASE used to read the Green byte value and shift to BLU_CASE */  
                
            case GREEN_CASE:
                if (flag_received == 1)
                {
                    green = value;
                    flag_received = 0;
                    timer_value = 0;
                    state = BLU_CASE;
                }
                else if (timer_value == set_timer)/* no Green byte inside the timeout window; move back to START */
                {
                    flag_received = 0;
                    timer_value = 0;
                    sprintf(message, "RESET\n");
                    UART_PutString(message);
                    state = START;
                }
            break;
                
        /* BLU_CASE used to read the Blu byte value and shift to COLOR_CASE */ 
                
            case BLU_CASE:
                if (flag_received == 1)
                {
                    blu = value;
                    flag_received = 0;
                    timer_value = 0;
                    state = COLOR_CASE;
                }
                else if (timer_value == set_timer)/* no Blu byte inside the timeout window; move back to START */
                {
                    flag_received = 0;
                    timer_value = 0;
                    sprintf(message, "RESET\n");
                    UART_PutString(message);
                    state = START;
                }
            break;
                
        /* COLOR_CASE used to read the Tail byte value and drive the RGB Led */  
                
            case COLOR_CASE:
                if (value == TAIL && flag_received == 1)/* Tail received; define COLORE ; write COLORE; back to START */
                {
                    Color COLORE = {red, green, blu};
                    RGBLed_WriteColor(COLORE);
                    flag_received = 0;
                    timer_value = 0;
                    state = START;
                }
                else if (flag_received == 0 && timer_value == set_timer)/* no Tail byte inside the timeout window; move back to START */
                {
                    flag_received = 0;
                    timer_value = 0;
                    sprintf(message, "RESET\n");
                    UART_PutString(message);
                    state = START;
                }
            break;
                
        /* TIMER_CASE sets the Timeout value */        
            
            case TIMER_CASE:
                if (flag_received == 1)/* read timeout  byte and go to TIMER_END */
                {
                    if (value > 0 && value <= 20) /* check if the the timeout value is within the constrains */
                    {
                        set_timer = value;
                        timer_value = 0;
                        flag_received = 0;
                        state = TIMER_END;
                    }
                    else  /* out of bounds; move back to START */
                    {
                        timer_value = 0;
                        flag_received = 0;
                        sprintf(message, "Timer value out of bounds\n");
                        UART_PutString(message);
                        state = START;
                    }
                }
                else if (timer_value == set_timer)/* no Timeout byte inside the timeout window; move back to START */
                {
                    flag_received = 0;
                    timer_value = 0;
                    sprintf(message, "RESET\n");
                    UART_PutString(message);
                    state = START;
                }
            break;
                
            /* TIMER_END if the Tail is received shows the set value and goes back to START*/    
                    
            case TIMER_END:
                if (value == TAIL && flag_received == 1)
                {
                    flag_received = 0;
                    timer_value = 0;
                    sprintf(message, "The new reset time value is: %d\r\n", set_timer);
                    UART_PutString(message);
                    state = START;
                }
                else if (timer_value == set_timer)/* no Tail byte inside the timeout window; move back to START */
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