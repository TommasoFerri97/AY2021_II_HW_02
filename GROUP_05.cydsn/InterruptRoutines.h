/* ========================================
 * 
 * Group 05
 *  
 * File Name: InterruptRoutines.h
 * 
 * PSoC Creator  4.4
 *
 * Description:
 * It contains declarations of all the created ISR functions.
 * 
 * ========================================
*/

#ifndef __INTERRUPT_ROUTINES_H__
    #define __INTERRUPT_ROUTINES_H__
    
    #include "project.h" /*give access to my functions all the generated header files*/
   
<<<<<<< HEAD
    
    CY_ISR_PROTO(Custom_UART_RX_ISR); /* CY_ISR_PROTO used to declare the function Custom_UART_RX_ISR, the ISR related to the UART interface*/
    
    
    CY_ISR_PROTO(Custom_TIMER_RESET); /*CY_ISR_PROTO used to declare the function Custom_TIMER_RESET, the ISR related to the TIMER interface*/
           
=======
    CY_ISR_PROTO(Custom_UART_RX_ISR);
    CY_ISR_PROTO(Custom_TIMER_RESET);
    
>>>>>>> 4c442696de423044ea2b5faf0955df73cc118785
#endif

/* [] END OF FILE */
