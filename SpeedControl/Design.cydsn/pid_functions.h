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

// Type for PID constants
typedef double pidk_t;

// Constants for PID control
extern pidk_t kp;
extern pidk_t ki;
extern pidk_t kd;

// Set the PID control constant values
void setKP(pidk_t new_kp);
void setKI(pidk_t new_ki);
void setKD(pidk_t new_kd);

// Get the PID control constant values
pidk_t getKP();
pidk_t getKI();
pidk_t getKD();

// PID decision function
uint32 pidOutput(int32 currInput, int32 goalInput, uint32 currOutput, uint32 minOutput, uint32 maxOutput);

/* [] END OF FILE */
