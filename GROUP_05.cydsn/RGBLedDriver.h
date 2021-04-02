/* ========================================
 *
 * RGBLedDriver.h Group 05
 *
 * ========================================
*/

#ifndef __RGB_LED_DRIVER_H__
    #define __RGB_LED_DRIVER_H__
    
    #include "project.h"

    typedef struct {
        uint8_t red;  // Value for RED (0-255)
        uint8_t green;  // Value for GREEN (0-255)
        uint8_t blu;  // Value for BLU (0-255)
    } Color;
    
    void RGBLed_Start(void);// We have some data in the FIFO
    void RGBLed_Stop(void);
    void RGBLed_WriteColor(Color c);
    
#endif

/* [] END OF FILE */
