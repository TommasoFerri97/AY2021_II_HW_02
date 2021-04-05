/* ========================================
 * 
 * Group 05
 *  
 * File Name: RGBLedDriver.h
 * 
 * PSoC Creator  4.4
 *
 * Description:
 * It contains declarations of all the functions to drive the Led with the PWM;
 * Definition of Color type; 
 *
 * ========================================
*/

#ifndef __RGB_LED_DRIVER_H__
    #define __RGB_LED_DRIVER_H__
    
    #include "project.h"

    typedef struct {
        uint8_t red;    // Value for RED (0-255)
        uint8_t green;  // Value for GREEN (0-255)
        uint8_t blu;    // Value for BLU (0-255)
    } Color;
    
    void RGBLed_Start(void);
    void RGBLed_Stop(void);
    void RGBLed_WriteColor(Color c);
    
#endif

/* [] END OF FILE */
