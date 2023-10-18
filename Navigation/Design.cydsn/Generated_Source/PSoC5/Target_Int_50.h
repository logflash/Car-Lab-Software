/*******************************************************************************
* File Name: Target_Int_50.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_Target_Int_50_H)
#define CY_ISR_Target_Int_50_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Target_Int_50_Start(void);
void Target_Int_50_StartEx(cyisraddress address);
void Target_Int_50_Stop(void);

CY_ISR_PROTO(Target_Int_50_Interrupt);

void Target_Int_50_SetVector(cyisraddress address);
cyisraddress Target_Int_50_GetVector(void);

void Target_Int_50_SetPriority(uint8 priority);
uint8 Target_Int_50_GetPriority(void);

void Target_Int_50_Enable(void);
uint8 Target_Int_50_GetState(void);
void Target_Int_50_Disable(void);

void Target_Int_50_SetPending(void);
void Target_Int_50_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Target_Int_50 ISR. */
#define Target_Int_50_INTC_VECTOR            ((reg32 *) Target_Int_50__INTC_VECT)

/* Address of the Target_Int_50 ISR priority. */
#define Target_Int_50_INTC_PRIOR             ((reg8 *) Target_Int_50__INTC_PRIOR_REG)

/* Priority of the Target_Int_50 interrupt. */
#define Target_Int_50_INTC_PRIOR_NUMBER      Target_Int_50__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Target_Int_50 interrupt. */
#define Target_Int_50_INTC_SET_EN            ((reg32 *) Target_Int_50__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Target_Int_50 interrupt. */
#define Target_Int_50_INTC_CLR_EN            ((reg32 *) Target_Int_50__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Target_Int_50 interrupt state to pending. */
#define Target_Int_50_INTC_SET_PD            ((reg32 *) Target_Int_50__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Target_Int_50 interrupt. */
#define Target_Int_50_INTC_CLR_PD            ((reg32 *) Target_Int_50__INTC_CLR_PD_REG)


#endif /* CY_ISR_Target_Int_50_H */


/* [] END OF FILE */
