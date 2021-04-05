/* ========================================
 * 
 * Group 05
 *  
 * File Name: RGBLedDriver.c
 * 
 * PSoC Creator  4.4
 *
 * Description:
 * It contains definitions of all the declared functions to drive the RGB Led;
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

#include "RGBLedDriver.h"
#include "InterruptRoutines.h" 
#include "UART.h"
#include "stdio.h"

/* 
 * ========================================
 *
 * definition of static variables;
 *
 * ========================================
*/ 

static void RGBLed_WriteRed(uint8_t red);
static void RGBLed_WriteGreen(uint8_t green);
static void RGBLed_WriteBlu(uint8_t blu);

/* 
 * ========================================
 *
 * enable the PWM peripherals to drive the Led;
 *
 * ========================================
*/ 

void RGBLed_Start()
{
    PWM_RG_Start();
    PWM_B_Start();
}

/* 
 * ========================================
 *
 * disable the PWM peripherals;
 *
 * ========================================
*/ 

void RGBLed_Stop()
{
    PWM_RG_Stop();
    PWM_B_Stop();
}

/* 
 * ========================================
 *
 * set the values of the PWM channels to change color;
 *
 * ========================================
*/ 

void RGBLed_WriteColor(Color c)
{
    RGBLed_WriteRed(c.red);
    RGBLed_WriteGreen(c.green);
    RGBLed_WriteBlu(c.blu);
}

static void RGBLed_WriteRed(uint8_t red)
{
    PWM_RG_WriteCompare1(red);
}

static void RGBLed_WriteGreen(uint8_t green)
{
    PWM_RG_WriteCompare2(green);
}

static void RGBLed_WriteBlu(uint8_t blu)
{
    PWM_B_WriteCompare(blu);
}

/* [] END OF FILE */
