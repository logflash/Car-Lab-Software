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
volatile lpFilter darkFilter50;
volatile lpFilter darkFilter100;
volatile lpFilter darkFilter150;

// Low-pass filter of hall effect sensor speed (mrpm)
volatile lpFilter hallFilter;

// Last Hall effect sensor time
uint32 lastHallTime = 0-1;

// Average mprm of the DC motor
volatile double avgRpm;

// The number of milliseconds before the video detects a dark pixel
volatile double darkTime50;
volatile double darkTime100;
volatile double darkTime150;
volatile double darkTimeOverall;

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
    
    // Un-capture the hall timer
    Hall_Timer_ReadStatusRegister();
    
    // Clear the RPM
    timeOutCounter = 0;
}

// Dark (falling edge of comparator) interrupt - line 50
CY_ISR(dark_int_50) {
    
    // Get the elapsed time, and if applicable, send it to the lp filter
    uint32 timeElapsed = 0-1-Dark_Timer_ReadCapture();
    if (timeElapsed > 630 || timeElapsed < 70) {
        return;
    }
    filterPush(&darkFilter50, timeElapsed);
    
    // Center (median) time
    darkTime50 = darkFilter50.median;
}

// Dark (falling edge of comparator) interrupt - line 100
CY_ISR(dark_int_100) {
    
    // Get the elapsed time, and if applicable, send it to the lp filter
    uint32 timeElapsed = 0-1-Dark_Timer_ReadCapture();
    if (timeElapsed > 630 || timeElapsed < 70) {
        return;
    }
    filterPush(&darkFilter100, timeElapsed);
    
    // Center (median) time
    darkTime100 = darkFilter100.median;
}

// Dark (falling edge of comparator) interrupt - line 150
CY_ISR(dark_int_150) {
    
    // Get the elapsed time, and if applicable, send it to the lp filter
    uint32 timeElapsed = 0-1-Dark_Timer_ReadCapture();
    if (timeElapsed > 630 || timeElapsed < 70) {
        return;
    }
    filterPush(&darkFilter150, timeElapsed);
    
    // Center (median) time
    darkTime150 = darkFilter150.median;
}

// PID (speed) last
double lastErr_speed = 0.0;

// PID (speed) sum
double sumErr_speed = 0.0;

// Goal (speed) rpm
double goalRpm = 420.0;

// PID constants (speed)
double kp_speed = 2.00;
double ki_speed = 2.00;// 0.30;
double kd_speed = 0.00;

// PID (steering) last
double lastErr_steer = 0.0;

// PID (steering) sum
double sumErr_steer = 0.0;

// Goal (speed) rpm
double goalDarkTime = 330.0;

// PID constants (steering)
double kp_steer = 1.12; //1.0
double ki_steer = 0.0;  // 0.8;
double kd_steer = 0.05; // 02; // 0.0;

// PID period (sec)
double pid_period = 0.020;
double cubicProportional_steer;

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
    double currErr_steer = (darkTime100 - goalDarkTime);
    
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
    
    /*if (currErr_steer > 150) {
        cubicProportional_steer = (kp_steer * 2e-5 * currErr_steer * currErr_steer * currErr_steer); //(kp_steer * 4e-5 * currErr_steer * currErr_steer * currErr_steer);
    }
    else {
        cubicProportional_steer = 0;
    }*/
    
    // Derivative calculation
    double derivativeTerm_steer = (kd_steer * (currErr_steer - lastErr_steer) / pid_period);
    
    // PID sum
    double pidOutput_steer = (int32)(proportionalTerm_steer + cubicProportional_steer + integralTerm_steer + derivativeTerm_steer);
    
    double leftSense = 1.3;
    double leftIntercept = -50;
    
    if (pidOutput_steer < leftIntercept) {
        pidOutput_steer = leftSense * pidOutput_steer - leftIntercept*(leftSense-1)/2;
    } else if (pidOutput_steer < 0) {
        pidOutput_steer = ((leftSense-1)/(2*leftIntercept)) * pidOutput_steer * pidOutput_steer + pidOutput_steer;    
    }
    /*
    if (pidOutput_steer < 0) {
        pidOutput_steer *= leftSense;    
    }
    else if (pidOutput_steer > 0) {
        pidOutput_steer -= rightSense*pidOutput_steer*pidOutput_steer;
    }*/
    
    pidOutput_steer += 1500;
    
    goalRpm = 421;
    goalRpm -= abs((int32)currErr_steer)*1.1;
    if (goalRpm < 360) {
        goalRpm = 360;
    }
   
    
    // Store the previous error
    lastErr_steer = currErr_steer;
    
    //pidOutput_steer += 1500;
    
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
    
    // Stall the MCU with useless operations so that the servo has enough time to set up
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
    
    // Dark interrupts
    Analog_CMP_Start();
    Reference_Start();
    
    // Line 50
    Dark_Timer_50_Start();
    Dark_Int_50_Start();
    Dark_Int_50_SetVector(dark_int_50);
    filterResize(&darkFilter50, 3);
    
    // Line 100
    Dark_Timer_100_Start();
    Dark_Int_100_Start();
    Dark_Int_100_SetVector(dark_int_100);
    filterResize(&darkFilter100, 3);
    
    // Line 150
    Dark_Timer_150_Start();
    Dark_Int_150_Start();
    Dark_Int_150_SetVector(dark_int_150);
    filterResize(&darkFilter150, 3);
    
    // Hall sensor interrupt
    Hall_Interrupt_Start();
    Hall_Timer_Start();
    Hall_Interrupt_SetVector(hall_int);
    filterResize(&hallFilter, 5);
    
    // Target row interrupt
    Target_Int_50_Start();
    Target_Int_50_SetVector(target_int);
    Target_Int_100_Start();
    Target_Int_100_SetVector(target_int);
    Target_Int_150_Start();
    Target_Int_150_SetVector(target_int);
    
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
