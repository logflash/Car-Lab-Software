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

#include "xbee_functions.h"
#include "pid_functions.h"
#include <stdio.h>

/*
// Default values for PID control
#define DEFAULT_KP 0.1
#define DEFAULT_KI 0
#define DEFAULT_KD 2

#define DEFAULT_KP 0.05
#define DEFAULT_KI 0.0001
#define DEFAULT_KD 0

#define DEFAULT_KP 0.05
#define DEFAULT_KI 0.0001
#define DEFAULT_KD 150
*/

// Default values for PID control
#define DEFAULT_KP 0.2
#define DEFAULT_KI 0.0001
#define DEFAULT_KD 150

// Constants for PID control
pidk_t kp = DEFAULT_KP;
pidk_t ki = DEFAULT_KI;
pidk_t kd = DEFAULT_KD;

// Set the PID control constant values
void setKP(pidk_t new_kp) {
  char buf[32];
  sprintf(buf, "kp <- %lf", kp);
  xBeeWrite(buf);
  kp = new_kp;
}
void setKI(pidk_t new_ki) {
  char buf[32];
  sprintf(buf, "ki <- %lf", ki);
  xBeeWrite(buf);
  ki = new_ki;
}
void setKD(pidk_t new_kd) {
  char buf[32];
  sprintf(buf, "kd <- %lf", kd);
  xBeeWrite(buf);
  kd = new_kd;
}

// Get the PID control constant values
pidk_t getKP() {
  return kp;
}
pidk_t getKI() {
  return ki;
}
pidk_t getKD() {
  return kd; 
}

#define MAX_SUM_OUTPUT 4096

// Make the important PID decisions
uint32 pidOutput(int32 currInput, int32 goalInput, uint32 currOutput, uint32 minOutput, uint32 maxOutput) {
  static int32 lastError;
  static int32 sumError;
  int32 currError = goalInput - currInput;
  
  // Sum of the error so far (KI)
  sumError += currError;
  pidk_t sumOutput = (ki * (pidk_t)sumError);
  if (sumOutput > MAX_SUM_OUTPUT) {
    sumOutput = MAX_SUM_OUTPUT;
  } else if (sumOutput < -MAX_SUM_OUTPUT) {
    sumOutput = -MAX_SUM_OUTPUT;
  }
  
  // Calculate PID value
  pidk_t output = (pidk_t)730 + ((kp * (pidk_t)currError) + sumOutput + (kd * (pidk_t)(currError-lastError)));
  
  // Store the previous error
  lastError = currError;
  
  // Bound the PID output
  if (output < (pidk_t)minOutput) {
    output = minOutput;
  } else if (output > (pidk_t)maxOutput) {
    output = maxOutput;
  }

  // Return the final PID output
  return (uint32) output;
}

/* [] END OF FILE */
