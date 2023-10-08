/*******************************************************************************
* File Name: hall_clock_1.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_hall_clock_1_H)
#define CY_CLOCK_hall_clock_1_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void hall_clock_1_Start(void) ;
void hall_clock_1_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void hall_clock_1_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void hall_clock_1_StandbyPower(uint8 state) ;
void hall_clock_1_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 hall_clock_1_GetDividerRegister(void) ;
void hall_clock_1_SetModeRegister(uint8 modeBitMask) ;
void hall_clock_1_ClearModeRegister(uint8 modeBitMask) ;
uint8 hall_clock_1_GetModeRegister(void) ;
void hall_clock_1_SetSourceRegister(uint8 clkSource) ;
uint8 hall_clock_1_GetSourceRegister(void) ;
#if defined(hall_clock_1__CFG3)
void hall_clock_1_SetPhaseRegister(uint8 clkPhase) ;
uint8 hall_clock_1_GetPhaseRegister(void) ;
#endif /* defined(hall_clock_1__CFG3) */

#define hall_clock_1_Enable()                       hall_clock_1_Start()
#define hall_clock_1_Disable()                      hall_clock_1_Stop()
#define hall_clock_1_SetDivider(clkDivider)         hall_clock_1_SetDividerRegister(clkDivider, 1u)
#define hall_clock_1_SetDividerValue(clkDivider)    hall_clock_1_SetDividerRegister((clkDivider) - 1u, 1u)
#define hall_clock_1_SetMode(clkMode)               hall_clock_1_SetModeRegister(clkMode)
#define hall_clock_1_SetSource(clkSource)           hall_clock_1_SetSourceRegister(clkSource)
#if defined(hall_clock_1__CFG3)
#define hall_clock_1_SetPhase(clkPhase)             hall_clock_1_SetPhaseRegister(clkPhase)
#define hall_clock_1_SetPhaseValue(clkPhase)        hall_clock_1_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(hall_clock_1__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define hall_clock_1_CLKEN              (* (reg8 *) hall_clock_1__PM_ACT_CFG)
#define hall_clock_1_CLKEN_PTR          ((reg8 *) hall_clock_1__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define hall_clock_1_CLKSTBY            (* (reg8 *) hall_clock_1__PM_STBY_CFG)
#define hall_clock_1_CLKSTBY_PTR        ((reg8 *) hall_clock_1__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define hall_clock_1_DIV_LSB            (* (reg8 *) hall_clock_1__CFG0)
#define hall_clock_1_DIV_LSB_PTR        ((reg8 *) hall_clock_1__CFG0)
#define hall_clock_1_DIV_PTR            ((reg16 *) hall_clock_1__CFG0)

/* Clock MSB divider configuration register. */
#define hall_clock_1_DIV_MSB            (* (reg8 *) hall_clock_1__CFG1)
#define hall_clock_1_DIV_MSB_PTR        ((reg8 *) hall_clock_1__CFG1)

/* Mode and source configuration register */
#define hall_clock_1_MOD_SRC            (* (reg8 *) hall_clock_1__CFG2)
#define hall_clock_1_MOD_SRC_PTR        ((reg8 *) hall_clock_1__CFG2)

#if defined(hall_clock_1__CFG3)
/* Analog clock phase configuration register */
#define hall_clock_1_PHASE              (* (reg8 *) hall_clock_1__CFG3)
#define hall_clock_1_PHASE_PTR          ((reg8 *) hall_clock_1__CFG3)
#endif /* defined(hall_clock_1__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define hall_clock_1_CLKEN_MASK         hall_clock_1__PM_ACT_MSK
#define hall_clock_1_CLKSTBY_MASK       hall_clock_1__PM_STBY_MSK

/* CFG2 field masks */
#define hall_clock_1_SRC_SEL_MSK        hall_clock_1__CFG2_SRC_SEL_MASK
#define hall_clock_1_MODE_MASK          (~(hall_clock_1_SRC_SEL_MSK))

#if defined(hall_clock_1__CFG3)
/* CFG3 phase mask */
#define hall_clock_1_PHASE_MASK         hall_clock_1__CFG3_PHASE_DLY_MASK
#endif /* defined(hall_clock_1__CFG3) */

#endif /* CY_CLOCK_hall_clock_1_H */


/* [] END OF FILE */
