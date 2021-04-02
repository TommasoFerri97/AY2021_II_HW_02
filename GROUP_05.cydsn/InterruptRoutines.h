/* ========================================
 *
 * InterruptRoutines.h Group 05
 *
 * ========================================
*/

#ifndef __INTERRUPT_ROUTINES_H__
    #define __INTERRUPT_ROUTINES_H__
    
    #include "project.h"
    
    extern uint8_t value;
    extern uint8_t status_pos;
    
    CY_ISR_PROTO(Custom_UART_RX_ISR);
    
#endif

/* [] END OF FILE */
