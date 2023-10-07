/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "lcd_functions.h"
#include <stdio.h>

// #define ROW_INT
#define TARGET_INT

volatile int numFrames = 0;
volatile int numRows = 0;

// Camera frame interrupt
CY_ISR(frame_int) {
    ++numFrames;
    
    //char buf[128];
    //sprintf(buf, "%-10d %-10d\r\n", numFrames, numRows);
    //XBee_PutString(buf);
    
    numRows = 0;
}

// Row interrupt
#ifdef ROW_INT
CY_ISR(row_int) {
    ++numRows;
}
#endif

// Target interrupt
#ifdef TARGET_INT
CY_ISR(target_int) {
    
    Dark_Timer_ReadStatusRegister();
    //XBee_PutString(".\r\n");
}
#endif

// Dark (falling edge of comparator) interrupt
CY_ISR(dark_int) {
    
    uint32 timeElapsed = 0-1-Dark_Timer_ReadCapture();
    if (timeElapsed > 1000000) {
        return;
    }
    char buf[128];
    sprintf(buf, "%-10d %-20lu\r\n", numFrames, timeElapsed);
    XBee_PutString(buf);
}


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    // Start the LCD
    initLCD();
    
    XBee_Start();
    XBee_PutString("Start!\r\n");
    
    // Frame interrupt
    Frame_Interrupt_Start();
    Frame_Interrupt_SetVector(frame_int);
    
    // Dark interrupt
    Analog_CMP_Start();
    Reference_Start();
    Dark_Timer_Start();
    Dark_Interrupt_Start();
    Dark_Interrupt_SetVector(dark_int);
    
    // Counter start
    // Row_Counter_Start();
    
    // Target row interrupt
    #ifdef TARGET_INT
    Target_Interrupt_Start();
    Target_Interrupt_SetVector(target_int);
    #endif
    
    // Row interrupt
    #ifdef ROW_INT
    Row_Interrupt_Start();
    Row_Interrupt_SetVector(row_int);
    #endif

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
