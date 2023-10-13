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
volatile double avgRpm;

// The number of milliseconds before the video detects a dark pixel
volatile double darkTime;

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
    if (timeElapsed > 630 || timeElapsed < 70) {
        return;
    }
    filterPush(&darkFilter, timeElapsed);
    
    // Center (median) time
    darkTime = darkFilter.median;

    // Write the center elapsed time to the XBee
    //char buf[128];
    //sprintf(buf, "%ld\r\n", (int32)darkTime);
    
    /*
    // Servo PWM Input
    int servoPWM = darkTime * 2 + 824;
    
    // Servo Limits
    if (servoPWM > 1900) {
        servoPWM = 1900;
    } else if (servoPWM < 1100) {
        servoPWM = 1100;
    }
    */
    
    // Write the value to the screen
    //XBee_PutString(buf);
}

// PID (speed) last
double lastErr_speed = 0.0;

// PID (speed) sum
double sumErr_speed = 0.0;

// Goal (speed) rpm
double goalRpm = 410.0;

// PID constants (speed)
double kp_speed = 2.00;
double ki_speed = 2.00;// 0.30;
double kd_speed = 0.00;

// PID (steering) last
double lastErr_steer = 0.0;

// PID (steering) sum
double sumErr_steer = 0.0;

// Goal (speed) rpm
double goalDarkTime = 380.0;

// PID constants (steering)
double kp_steer = 1.15; //1.0
double ki_steer = 0.0;  // 0.8;
double kd_steer = 0.0; // 02; // 0.0;

// PID period (sec)
double pid_period = 0.020;

// PID ISR (every 20 msec)
CY_ISR(pid_int) {
    
    // Time out counter increment
    timeOutCounter++;
    if (timeOutCounter >= 10) {
        avgRpm = 0;
    }
    
    // Calculate the current speed error
    double currErr_speed = goalRpm - avgRpm;
    
    // Integral calculation (and windup protection)
    sumErr_speed += currErr_speed;
    double integralTerm_speed = (ki_speed * sumErr_speed * pid_period);
    if (integralTerm_speed > 1024) {
        integralTerm_speed = 1024;
    } else if (integralTerm_speed < -1024) {
        integralTerm_speed = -1024;
    }
    
    // Integral reset when the error direction changes
    //if (currErr_speed * lastErr_speed < 0) {
    //    sumErr_speed = 0;
    //}
    
    // Proportional calculation
    double proportionalTerm_speed = (kp_speed * currErr_speed);
    
    // Derivative calculation
    double derivativeTerm_speed = (kd_speed * (currErr_speed - lastErr_speed) / pid_period);
    
    // PID sum
    double pidOutput_speed = (uint32)(1.8 * goalRpm + proportionalTerm_speed + integralTerm_speed + derivativeTerm_speed);
    
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
    //char buf[128];
    //sprintf(buf, "%10ld %10u %10ld\r\n", (int32)avgRpm, (uint16)pidOutput_speed, (int32)integralTerm_speed);
    //XBee_PutString(buf);
    
    // Calculate the current steering error
    double currErr_steer = (darkTime - goalDarkTime);
    
    // Integral calculation (and windup protection)
    sumErr_steer += currErr_steer;
    double integralTerm_steer = (ki_steer * sumErr_steer * pid_period);
    if (integralTerm_steer > 500) {
        integralTerm_steer = 500;
    } else if (integralTerm_steer < -500) {
        integralTerm_steer = -500;
    }
    
    // Integral reset when the error direction changes
    // if (currErr_steer * lastErr_steer < 0) {
    //     sumErr_steer = 0;
    // }
    
    // Proportional calculation
    double proportionalTerm_steer = (kp_steer * currErr_steer);
    
    double cubicProportional_steer = 0.0; //(kp_steer * 4e-5 * currErr_steer * currErr_steer * currErr_steer);
    
    // Derivative calculation
    double derivativeTerm_steer = (kd_steer * (currErr_steer - lastErr_steer) / pid_period);
    
    // PID sum
    double pidOutput_steer = (uint32)(1500 + proportionalTerm_steer + cubicProportional_steer + integralTerm_steer + derivativeTerm_steer);
    
    // Store the previous error
    lastErr_steer = currErr_steer;
    
    // Bound the PID output
    if (pidOutput_steer < 1000) {
        pidOutput_steer = 1000;
    } else if (pidOutput_steer > 2000) {
        pidOutput_steer = 2000;
    }
    
    char buf[128];
    sprintf(buf, "err = %5ld ; cube = %5ld ; output = %4ld\r\n", (int32)currErr_steer, (int32)cubicProportional_steer, (int32)pidOutput_steer);
    XBee_PutString(buf);
    
    // Update the steering as a result of the PID
    Servo_PWM_WriteCompare(pidOutput_steer);
}

int main(void)
{
    // Servo PWM
    Servo_PWM_Start();
    
    int j = 112;
    for (int i=0; i<1234567; i++) {
        if (j & 1) j = 3 * j + 1;
        else j >>= 1;
    }
    
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
