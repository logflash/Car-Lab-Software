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
#include "lp_filter.h"
#include <stdio.h>

volatile int numFrames = 0;

// Low-pass filter of darkness detector (video)
volatile lpFilter darkFilter;

// Low-pass filter of hall effect sensor speed (mrpm)
volatile lpFilter hallFilter;

// Last Hall effect sensor time
uint32 lastHallTime = 0-1;

// Average mprm of the DC motor
double avgRpm;

// A timeout (if 0.2 seconds pass before a Hall update, clear the rpm)
uint32 timeOutCounter = 0;

// Camera frame interrupt
CY_ISR(frame_int) {
    ++numFrames;
}

// Target interrupt
CY_ISR(target_int) {
    Dark_Timer_ReadStatusRegister();
}

// Hall sensor interrupt
CY_ISR(hall_int) {
    
    // Clear the LCD
    clearLCD();
    
    // Keep track of the time since the last Hall Effect Sensor pulse
    uint32 hallTime = Hall_Timer_ReadCapture();
    uint32 diffTime = lastHallTime - hallTime;
    lastHallTime = hallTime;
    filterPush(&hallFilter, diffTime);
    
    // Average hall effect mrpm
    avgRpm = (double)((uint64) 12000000000 / (uint64) hallFilter.avg) / 1000.0;
    
    // Print the time
    //char buf[128];
    //sprintf(buf, "%lu\r\n", avgMrpm);
    //XBee_PutString(buf);
    
    // Un-capture the hall timer
    Hall_Timer_ReadStatusRegister();
    
    // Clear the RPM
    timeOutCounter = 0;
}

// Dark (falling edge of comparator) interrupt
CY_ISR(dark_int) {
    
    // Get the elapsed time, and if applicable, send it to the lp filter
    uint32 timeElapsed = 0-1-Dark_Timer_ReadCapture();
    if (timeElapsed > 800 || timeElapsed < 20) {
        return;
    }
    if (timeElapsed > 600) {
        timeElapsed = 320;
    }
    filterPush(&darkFilter, timeElapsed);
    
    // Center (median) time
    uint32 centerTime = darkFilter.median;

    // Write the center elapsed time to the XBee
    // char buf[128];
    // sprintf(buf, "%-10d %-20lu\r\n", numFrames, centerTime);
    
    // Servo PWM Input
    int servoPWM = centerTime * 2 + 824;
    
    // Servo Limits
    if (servoPWM > 1900) {
        servoPWM = 1900;
    } else if (servoPWM < 1100) {
        servoPWM = 1100;
    }
    
    // Write to the Servo PWM Pin
    Servo_PWM_WriteCompare(servoPWM);
    
    // Write the value to the screen
    // XBee_PutString(buf);
}

// PID (speed) last
double lastErr_speed = 0.0;

// PID (speed) sum
double sumErr_speed = 0.0;

// Goal (speed) rpm
double goalRpm = 400.0;

// PID constants (speed)
//double kp_speed = 0.07;
//double ki_speed = 0.60;
double kp_speed = 0.10;
double ki_speed = 0.30;
double kd_speed = 0.00;

// PID period (sec)
double pid_period = 0.020;

// PID ISR (every 20 msec)
CY_ISR(pid_int) {
    
    // Time out counter increment
    timeOutCounter++;
    if (timeOutCounter >= 10) {
        avgRpm = 0.0;
    }
    
    double currErr_speed = goalRpm - avgRpm;
    
    // Integral calculation (and windup protection)
    sumErr_speed += currErr_speed;
    double integralTerm_speed = (ki_speed * sumErr_speed * pid_period);
    if (integralTerm_speed > 2048) {
        integralTerm_speed = 2048;
    } else if (integralTerm_speed < -2048) {
        integralTerm_speed = -2048;
    }
    
    if (currErr_speed * lastErr_speed < 0) {
        sumErr_speed = 0;
    }
    
    // Proportional calculation
    double proportionalTerm_speed = (kp_speed * sumErr_speed);
    
    // Derivative calculation
    double derivativeTerm_speed = (kd_speed * (currErr_speed - lastErr_speed) / pid_period);
    
    // PID sum
    double pidOutput_speed = (uint32)(2.2 * goalRpm + proportionalTerm_speed + integralTerm_speed + derivativeTerm_speed);
    
    // Store the previous error
    lastErr_speed = currErr_speed;
    
    // Bound the PID output
    if (pidOutput_speed < 0) {
        pidOutput_speed = 0;
    } else if (pidOutput_speed > 4095) {
        pidOutput_speed = 4095;
    }
    
    // Update the speed as a result of the PID
    Throttle_PWM_WriteCompare((uint16)pidOutput_speed);
    
    // Print to show the ISR has been triggered and the PID has been calculated
    char buf[128];
    //sprintf(buf, "%10ld %10d\r\n", (int32)avgRpm, (uint16)pidOutput_speed);
    sprintf(buf, "%10ld %10u %10ld\r\n", (int32)avgRpm, (uint16)pidOutput_speed, (int32)integralTerm_speed);
    XBee_PutString(buf);
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    // Start the LCD
    initLCD();
    
    XBee_Start();
    XBee_PutString("\r\nStart!\r\n");
    
    // Frame interrupt
    Frame_Interrupt_Start();
    Frame_Interrupt_SetVector(frame_int);
    
    // Dark interrupt
    Analog_CMP_Start();
    Reference_Start();
    Dark_Timer_Start();
    Dark_Interrupt_Start();
    Dark_Interrupt_SetVector(dark_int);
    filterResize(&darkFilter, 3);
    
    // Hall sensor interrupt
    Hall_Interrupt_Start();
    Hall_Timer_Start();
    Hall_Interrupt_SetVector(hall_int);
    filterResize(&hallFilter, 5);
    
    // Target row interrupt
    Target_Interrupt_Start();
    Target_Interrupt_SetVector(target_int);
    
    // Servo PWM
    Servo_PWM_Start();
    
    // Throttle PWM
    Throttle_PWM_Start();
    
    // PID ISR
    PID_Timer_Start();
    PID_Interrupt_Start();
    PID_Interrupt_SetVector(pid_int);

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
