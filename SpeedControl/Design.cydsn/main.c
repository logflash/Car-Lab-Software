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
#include "pid_functions.h"
#include "xbee_functions.h"
#include <stdio.h>

uint32 lastTime = 0-1;

// Buffer for the command
char cmdBuf[128];
int cmdIdx = 0; // Command index

// Current scaled speed
// volatile uint32 currScaledSpeed = 0;

// Current (averaged) low-passed scaled speed)
volatile uint32 avgdScaledSpeed = 0;

// Index of the low-pass filter
volatile int lpSpeedIdx = 0;

// Speed low-pass filter
#define LP_SPEED_SIZE 6

// A low-pass filter for the scaled speed
volatile uint32 lpSpeed[LP_SPEED_SIZE];

// Goal scaled speed
uint32 goalScaledSpeed = 10000;

// Summing window for calculating the average scaled speed
uint32 lpWindowSum = 0;

// Magic speed number
#define MAGIC_SPEED_NUMBER 3926390000 // 3243198138

// Hall Effect sensor
CY_ISR(hall_int) {
    
    // Clear the LCD
    clearLCD();
    
    // Keep track of the time since the last Hall Effect Sensor pulse
    uint32 pulseTime = Timer_ReadCapture();
    uint32 diffTime = lastTime - pulseTime;
    lastTime = pulseTime;
    
    // Find the scaled frequency
    uint32 scaledSpeed = MAGIC_SPEED_NUMBER / diffTime;
    printUint32LCD(scaledSpeed, 0);
    printUint32LCD(avgdScaledSpeed, 1);
    
    // Advance the low-pass filter index
    int nextLpSpeedIdx = (lpSpeedIdx + 1) % LP_SPEED_SIZE;
    
    // Update the low-pass filter array
    lpSpeed[lpSpeedIdx] = diffTime;
    
    // Update the window sum
    lpWindowSum += lpSpeed[lpSpeedIdx];
    lpWindowSum -= lpSpeed[nextLpSpeedIdx];
    
    // Calculate the average from the window sum
    avgdScaledSpeed = MAGIC_SPEED_NUMBER / lpWindowSum * (LP_SPEED_SIZE - 1);
    
    // Update the low-pass filter index
    lpSpeedIdx = nextLpSpeedIdx;
    
    // Read the status register
    Timer_ReadStatusRegister();
}

int uart_step = 0;

// Xbee interrupt
CY_ISR(xbee_int) {
    
    char out[128];
    sprintf(out, "[%d] open", uart_step);
    xBeeWrite(out);
    
    // Read the current character    
    while (XBee_GetRxBufferSize()) {
        char c = XBee_GetChar();
        uint8 stat = XBee_ReadRxStatus();
        char ack[128];
        sprintf(ack, "[%d, status = %3d] echo: %c (%d)", uart_step, stat, c, (int)c);
        xBeeWrite(ack);
    }
    
    sprintf(out, "[%d] close\n", uart_step);
    xBeeWrite(out);
    uart_step++;
    
    /*
    if (c == '\r' || c == '\n' || c == ':') {
        xBeeWrite("~");
        xBeeInterpret(cmdBuf);
        while (cmdIdx) {
            cmdBuf[cmdIdx] = '\0';
            cmdIdx--;
        }
    } else {
        cmdBuf[cmdIdx] = c;
        cmdIdx++;
    }
    */
}

// Cycles to wait within the for loop before making another decision
#define WAIT_CYCLES 1000

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    // Start the LCD
    initLCD();
    printLCD("Ready!", 0);
    
    // Set up an interrupt routine for the Hall Effect sensor
    Hall_Interrupt_Start();
    Timer_Start();
    Hall_Interrupt_SetVector(hall_int);
    
    // Set the PWM duty cycle
    PWM_Start();
    
    // Start the servo
    Servo_Start();
    
    // Start the XBee
    XBee_Start();
    XBee_Interrupt_Start();
    XBee_Interrupt_SetVector(xbee_int);

    // Duty cycle of the motor PWM, multiplied by 4096
    uint16 motorDutyCmp = 0;
    
    // Set a variable for the number of cycles left before the next update
    int waitCyclesLeft = WAIT_CYCLES;
    
    // Main for loop
    for(;;)
    {        
        // Don't do anything if we still need to wait
        if (waitCyclesLeft) {
            waitCyclesLeft--;
            continue;
        }
        
        // Decide the speed
        motorDutyCmp = pidOutput(avgdScaledSpeed, goalScaledSpeed, motorDutyCmp, 0, 4095);
        
        // Reset the wait cycles for the next update
        waitCyclesLeft = WAIT_CYCLES;
        
        // Write the duty cycle to the motor
        PWM_WriteCompare(motorDutyCmp);
    }
}

/* [] END OF FILE */
